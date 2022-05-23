//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#include "TS.hpp"

#include <memory>

namespace TS {
void State::set_is_initial(bool is_initial_) {is_initial = is_initial_;}
bool State::get_is_initial() const {return is_initial;}

void Action::set_name(std::string name_) {name = name_;}
std::string Action::to_string() const {return name;}

void Proposition::set_name(std::string name_) {name = name_;}
std::string Proposition::to_string() const {return name;}

std::istream& operator>>(std::istream &is, std::shared_ptr<TS> ts) {
	is >> ts -> N_S >> ts -> N_T;
	for (size_t x = 0;x < ts -> N_S;++ x) {
		std::shared_ptr<State> s(new State);
		ts -> S.push_back(s);
		ts -> trans.emplace(s, std::set<std::pair<std::shared_ptr<State>, std::shared_ptr<Action>>>());
		ts -> L.emplace(s, std::set<std::shared_ptr<Proposition>>());
	}

	std::vector<size_t> int_vector;
	read_data_from_a_line(is, int_vector);
	for (size_t x = 0;x < ts -> N_S;++ x) ts -> S.at(x) -> set_is_initial(true);

	std::vector<std::string> string_vector;
	read_data_from_a_line(is, string_vector);
	for (size_t x = 0;x < ts -> N_S;++ x) ts -> Act.at(x) -> set_name(string_vector.at(x));
	string_vector.clear();
	read_data_from_a_line(is, string_vector);
	for (size_t x = 0;x < ts -> N_S;++ x) ts -> AP.at(x) -> set_name(string_vector.at(x));
	for (size_t t = 0, i, j, k;t < ts -> N_T;++ t) {
		is >> i >> k >> j;
		ts -> trans.at(ts -> S.at(i)).emplace(ts -> S.at(j), ts -> Act.at(k));
	}
	std::vector<size_t> size_t_vector;
	for (auto s: ts -> S) {
		auto& L = ts -> L.at(s);
		read_data_from_a_line(is, size_t_vector);
		std::for_each(size_t_vector.begin(), size_t_vector.end(), [&](const auto& item){L.insert(ts -> AP.at(item));});
	}
	return is;
}

std::shared_ptr<TS> product(
	const std::shared_ptr<TS> ts,
	const std::shared_ptr<BA::NBA> nba,
	const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<BA::Symbol>> &LTL2Symbol,
	const std::map<std::shared_ptr<Proposition>, std::shared_ptr<LTL_Base>> &Prop2LTL,
	const PowerSet<LTL_Base> &power_set
	) {
	std::shared_ptr<TS> ret(new TS);

	// copy Act
	ret -> Act = ts -> Act;

	// initialize states
	std::map<std::shared_ptr<State>, size_t> ts_index;
	std::map<std::shared_ptr<BA::State>, size_t> nba_index;
	for (size_t i = 0;i < ts -> S.size();++ i)
		ts_index.emplace(ts -> S.at(i), i);
	for (size_t i = 0;i < nba -> states.size();++ i)
		nba_index.emplace(nba -> states.at(i), i);
	std::vector<std::vector<std::shared_ptr<State>>> states_list;
	for (size_t i = 0;i < ts -> S.size();++ i) {
		states_list.emplace_back();
		for (size_t j = 0;j < nba -> states.size();++ j) {
			std::shared_ptr<State> state(new State);
			ret -> trans.emplace(), ret -> S.push_back(state), ret -> L.emplace(state, std::set<std::shared_ptr<Proposition>>());
			states_list.back().push_back(state);
		}
	}

	// initialize I
	for (size_t i = 0;i < ts -> S.size();++ i) {
		std::shared_ptr<State> s = ts -> S.at(i);
		if (ts -> S.at(i) -> get_is_initial())
			for (auto q_prime: nba -> states)
				if (q_prime -> get_is_initial()) {
					std::vector<std::shared_ptr<LTL_Base>> tmp;
					for (auto prop: ts -> L.at(s))
						tmp.push_back(Prop2LTL.at(prop));
					std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>> LTL_set = power_set.get_subset(tmp);
					for (auto q: nba -> delta.at(q_prime).at(LTL2Symbol.at(LTL_set)))
						states_list.at(i).at(nba_index.at(q)) -> set_is_initial(true);
				}
	}

	// initialize AP
	for (auto q: nba -> states)
		ret -> AP.emplace_back(new Proposition);

	// initialize L
	for (auto s_list: states_list)
		for (size_t j = 0;j < nba -> states.size();++ j)
			ret -> L.at(s_list.at(j)).insert(ret -> AP.at(j));

	// initialize trans
	for (auto s: ts -> S) {
		auto &s_list = states_list.at(ts_index.at(s));
		for (auto q: nba -> states) {
			std::shared_ptr<State> sq_state = s_list.at(nba_index.at(q));
			for (auto [t, alpha]: ts -> trans.at(s)) {
				auto &t_list = states_list.at(ts_index.at(t));
				for (auto [symbol, states]: nba -> delta.at(q))
					for (auto p: states)
						ret -> trans.at(sq_state).emplace(t_list.at(nba_index.at(p)), alpha);
			}
		}
	}
	return std::move(ret);
}

bool TS::persistence_checking(std::set<std::shared_ptr<Proposition>> F) const {
	cycle_found = false;
	for (auto s: S) if (s -> get_is_initial()) I.insert(s);

	while (!I.empty()) {
		std::shared_ptr<State> s = *I.begin();
		reachable_cycle(F, s);
	}

	R.clear(), T.clear(), I.clear();
	while (!U.empty()) U.pop();
	while (!V.empty()) V.pop();

	return !cycle_found;
}

void TS::reachable_cycle(std::set<std::shared_ptr<Proposition>> F, std::shared_ptr<State> s) const {
	U.push(s);
	R.insert(s);
	if (I.find(s) != I.end()) I.erase(s);
	do {
		std::shared_ptr<State> s_prime = U.top();
		bool found = false;
		for (auto [t, alpha]: trans.at(s_prime))
			if (R.find(t) == R.end()) {
				U.push(t);
				R.insert(t);
				if (I.find(t) != I.end()) I.erase(t);
				found = true;
				break;
			}
		if (!found) {
			U.pop();
			for (auto l: L.at(s_prime))
				if (F.find(l) != F.end()) {
					found = true;
					break;
				}
			if (found) cycle_found = cycle_check(F, s_prime);
		}
	} while (!U.empty() && !cycle_found);
}

bool TS::cycle_check(std::set<std::shared_ptr<Proposition>> F, std::shared_ptr<State> s) const {
	bool inner_cycle_found = false;
	V.push(s);
	do {
		std::shared_ptr<State> s_prime = V.top();
		bool found = false;
		for (auto [t, alpha]: trans.at(s_prime))
			if (s == t) {
				inner_cycle_found = true;
				break;
			}
		if (inner_cycle_found) V.push(s);
		else {
			bool found = false;
			for (auto [t, alpha]: trans.at(s_prime))
				if (T.find(t) == T.end()) {
					V.push(t);
					T.insert(t);
					found = true;
					break;
				}
			if (!found) V.pop();
		}
	} while (!V.empty() && !inner_cycle_found);
	return inner_cycle_found;
}
}