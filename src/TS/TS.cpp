//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#include "TS.hpp"

#include <memory>

namespace TransitionSystem {
void State::set_is_initial(bool is_initial_) {is_initial = is_initial_;}
bool State::get_is_initial() const {return is_initial;}

void State::set_name(std::string name_) {name = name_;}
std::string State::to_string() const {return name;}
std::string Action::to_string() const {return name;}
std::string Proposition::to_string() const {return name;}

std::istream& operator>>(std::istream &is, std::shared_ptr<TS> ts) {
	std::vector<size_t> int_vector;
	read_data_from_a_line(is, int_vector);
	ts -> N_S = int_vector.front(), ts -> N_T = int_vector.back();
	for (size_t x = 0;x < ts -> N_S;++ x) {
		std::shared_ptr<State> s(new State);
		s -> set_is_initial();
		s -> set_name(std::to_string(x));
		ts -> S.push_back(s);
		ts -> trans.emplace(s, std::set<std::pair<std::shared_ptr<State>, std::shared_ptr<Action>>>());
		ts -> L.emplace(s, std::set<std::shared_ptr<Proposition>>());
	}

	int_vector.clear();
	read_data_from_a_line(is, int_vector);
	for (auto x: int_vector) ts -> S.at(x) -> set_is_initial(true);

	std::vector<std::string> string_vector;
	read_data_from_a_line(is, string_vector);
	for (auto name: string_vector) ts -> Act.emplace_back(std::make_shared<Action>(name));
	string_vector.clear();
	read_data_from_a_line(is, string_vector);
	for (auto name: string_vector) ts -> AP.emplace_back(std::make_shared<Proposition>(name));
	for (size_t t = 0, i, j, k;t < ts -> N_T;++ t) {
		int_vector.clear();
		read_data_from_a_line(is, int_vector);
		i = int_vector.at(0), k = int_vector.at(1), j = int_vector.at(2);
		ts -> trans.at(ts -> S.at(i)).emplace(ts -> S.at(j), ts -> Act.at(k));
	}
	std::vector<size_t> size_t_vector;
	for (const auto& s: ts -> S) {
		size_t_vector.clear();
		auto& L = ts -> L.at(s);
		read_data_from_a_line(is, size_t_vector);
		std::for_each(size_t_vector.begin(), size_t_vector.end(), [&](const auto& item){L.insert(ts -> AP.at(item));});
	}
	return is;
}

std::shared_ptr<TS> product(
	const std::shared_ptr<TS> &ts,
	const std::shared_ptr<BuechiAutomata::NBA> &nba,
	const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol,
	const std::map<std::shared_ptr<Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL,
	const PowerSet<LTL::LTL_Base> &power_set,
	std::set<std::shared_ptr<Proposition>> &F_Props,
	std::map<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, std::shared_ptr<BuechiAutomata::State>>> &s2s_state
	) {
	std::shared_ptr<TS> ret(new TS);

	// copy Act
	ret -> Act = ts -> Act;

	// initialize states
	std::map<std::shared_ptr<State>, size_t> ts_index;
	std::map<std::shared_ptr<BuechiAutomata::State>, size_t> nba_index;
	for (size_t i = 0;i < ts -> S.size();++ i)
		ts_index.emplace(ts -> S.at(i), i);
	for (size_t i = 0;i < nba -> states.size();++ i)
		nba_index.emplace(nba -> states.at(i), i);
	std::vector<std::vector<std::shared_ptr<State>>> states_list;
	for (const auto &s: ts -> S) {
		states_list.emplace_back();
		for (const auto &state: nba -> states) {
			std::shared_ptr<State> state_(new State);
			state_ -> set_is_initial();
			s2s_state.emplace(state_, std::make_pair(s, state));
			ret -> trans.emplace(state_, std::set<std::pair<std::shared_ptr<State>, std::shared_ptr<Action>>>()), ret -> S.push_back(state_), ret -> L.emplace(state_, std::set<std::shared_ptr<Proposition>>());
			states_list.back().push_back(state_);
		}
	}

	// initialize I
	for (size_t i = 0;i < ts -> S.size();++ i) {
		std::shared_ptr<State> s = ts -> S.at(i);
		if (ts -> S.at(i) -> get_is_initial())
			for (const auto &q_prime: nba -> states)
				if (q_prime -> get_is_initial()) {
					std::vector<std::shared_ptr<LTL::LTL_Base>> tmp;
					for (const auto &prop: ts -> L.at(s))
						tmp.push_back(Prop2LTL.at(prop));
					std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>> LTL_set = power_set.get_subset(tmp);
					for (const auto &q: nba -> delta.at(q_prime).at(LTL2Symbol.at(LTL_set)))
						states_list.at(i).at(nba_index.at(q)) -> set_is_initial(true);
				}
	}

	// initialize AP
	for (const auto &q: nba -> states) {
		std::shared_ptr<Proposition> prop = std::make_shared<Proposition>();
		ret -> AP.push_back(prop);
		if (nba -> F.find(q) != nba -> F.end()) F_Props.emplace(prop);
	}

	// initialize L
	for (auto &s_list: states_list)
		for (size_t j = 0;j < nba -> states.size();++ j)
			ret -> L.at(s_list.at(j)).insert(ret -> AP.at(j));

	// initialize trans
	for (const auto &s: ts -> S) {
		auto &s_list = states_list.at(ts_index.at(s));
		for (const auto &q: nba -> states) {
			std::shared_ptr<State> sq_state = s_list.at(nba_index.at(q));
			for (auto [t, alpha]: ts -> trans.at(s)) {
				auto &t_list = states_list.at(ts_index.at(t));
				std::vector<std::shared_ptr<LTL::LTL_Base>> tmp;
				for (const auto &prop: ts -> L.at(t)) tmp.push_back(Prop2LTL.at(prop));
				std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>> LTL_set = power_set.get_subset(tmp);
				for (const auto &p: nba -> delta.at(q).at(LTL2Symbol.at(LTL_set)))
					ret -> trans.at(sq_state).emplace(t_list.at(nba_index.at(p)), alpha);
			}
		}
	}
	return std::move(ret);
}

bool TS::persistence_checking(const std::set<std::shared_ptr<Proposition>> &F) const {
	cycle_found = false;
	for (const auto &s: S) if (s -> get_is_initial()) I.insert(s);

	while (!I.empty() && !cycle_found) {
		std::shared_ptr<State> s = *I.begin();
		reachable_cycle(F, s);
	}

	R.clear(), T.clear(), I.clear();
	while (!U.empty()) U.pop();
	while (!V.empty()) V.pop();

	return !cycle_found;
}

bool TS::persistence_checking(const std::set<std::shared_ptr<Proposition>> &F, const std::set<std::shared_ptr<State>> &entries) const {
	cycle_found = false;
	I = entries;

	while (!I.empty() && !cycle_found) {
		std::shared_ptr<State> s = *I.begin();
		reachable_cycle(F, s);
	}

	R.clear(), T.clear(), I.clear();
	while (!U.empty()) U.pop();
	while (!V.empty()) V.pop();

	return !cycle_found;
}

std::map<std::string, std::shared_ptr<Proposition>> TS::get_Name2Prop() const {
	std::map<std::string, std::shared_ptr<Proposition>> ret;
	for (const auto &p: AP) ret.emplace(p -> to_string(), p);
	return std::move(ret);
}

void TS::reachable_cycle(const std::set<std::shared_ptr<Proposition>> &F, const std::shared_ptr<State> &s) const {
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
			for (const auto &l: L.at(s_prime))
				if (F.find(l) != F.end()) {
					found = true;
					break;
				}
			if (found) cycle_found = cycle_check(s_prime);
		}
	} while (!U.empty() && !cycle_found);
}

bool TS::cycle_check(const std::shared_ptr<State> &s) const {
	bool inner_cycle_found = false;
	V.push(s);
	T.insert(s);
	do {
		std::shared_ptr<State> s_prime = V.top();
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

std::set<std::shared_ptr<TransitionSystem::State>> get_entries(
	const std::shared_ptr<TransitionSystem::State> &src_s,
	const std::shared_ptr<TransitionSystem::TS> &ts,
	const std::shared_ptr<BuechiAutomata::NBA> &nba,
	const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol,
	const std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL,
	const PowerSet<LTL::LTL_Base> &power_set,
	const std::map<std::pair<std::shared_ptr<TransitionSystem::State>, std::shared_ptr<BuechiAutomata::State>>, std::shared_ptr<TransitionSystem::State>> &sstate2s
) {
	std::set<std::shared_ptr<TransitionSystem::State>> ret;
	for (const auto &q_prime: nba -> states)
		if (q_prime -> get_is_initial()) {
			std::vector<std::shared_ptr<LTL::LTL_Base>> tmp;
			for (const auto &prop: ts -> L.at(src_s))
				tmp.push_back(Prop2LTL.at(prop));
			std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>> LTL_set = power_set.get_subset(tmp);
			for (const auto &q: nba -> delta.at(q_prime).at(LTL2Symbol.at(LTL_set)))
				ret.insert(sstate2s.at(std::make_pair(src_s, q)));
		}
	return std::move(ret);
}

std::string to_string(std::shared_ptr<TS> prod,
  	const std::map<std::shared_ptr<BuechiAutomata::Symbol>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &Symbol2LTL,
  	const std::map<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, std::shared_ptr<BuechiAutomata::State>>> &s2sstate,
  	const std::map<std::shared_ptr<BuechiAutomata::State>, std::pair<std::shared_ptr<BuechiAutomata::State>, size_t>> &state2state,
  	const std::map<std::shared_ptr<BuechiAutomata::State>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &state2set
  	) {
	std::string ret("TS starts from here.\n");
	ret += "S:\n";
	for (const auto &s_: prod -> S) {
		ret += "\t";
		const auto &[s, state] = s2sstate.at(s_);
		ret += s -> to_string() + " * ";
		const auto &[state_, index] = state2state.at(state);
		ret += "{";
		for (const auto &phi: *state2set.at(state_)) ret += phi -> to_string() + ", ";
		ret += "} * " + std::to_string(index);
		if (s_ -> get_is_initial()) ret += " (initial)";
		ret += ",\n";
	}
	ret += "\nTransition:\n";
	for (const auto &s: prod -> S)
		for (const auto &[next_s, action]: prod -> trans.at(s)) {
			ret += "\t";
			const auto &[s_, state] = s2sstate.at(s);
			ret += s_ -> to_string() + " * ";
			const auto &[state_, index] = state2state.at(state);
			ret += "{";
			for (const auto &phi: *state2set.at(state_)) ret += phi -> to_string() + ", ";
			ret += "} * " + std::to_string(index) + " -> ";
			const auto &[_s_, _state] = s2sstate.at(next_s);
			ret += _s_ -> to_string() + " * ";
			const auto &[_state_, _index] = state2state.at(_state);
			ret += "{";
			for (const auto &phi: *state2set.at(_state_)) ret += phi -> to_string() + ", ";
			ret += "} * " + std::to_string(_index) + " with action = " + action -> to_string();
			ret += ",\n";
		}
	ret += "\nTS ends at here.";
	return ret;
}
}

namespace LTL {
std::string Variable::to_string() const {
	return p -> to_string();
}
}