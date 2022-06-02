//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#include "BA.hpp"

namespace BuechiAutomata {
bool State::get_is_initial() const {return is_initial;}

std::shared_ptr<State> BA::make_nonblocking() {
	if (maded_nonblocking) return {nullptr};
	std::shared_ptr<State> trap(new State);
	delta.emplace(trap, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>());
	states.push_back(trap);
	for (const auto &state: states)
		for (const auto &symbol: alphabet)
			if (delta.at(state).find(symbol) == delta.at(state).end())
				delta.at(state).emplace(symbol, std::set<std::shared_ptr<State>>{trap});
	maded_nonblocking = true;
	return trap;
}

NBA::NBA(const std::shared_ptr<GNBA> &gnba, std::map<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, size_t>> &state2state_index) {
	alphabet = gnba -> alphabet;
	size_t k = gnba -> F.size();
	std::vector<std::vector<std::shared_ptr<State>>> states_list; // N_S * [k]
	std::map<std::shared_ptr<State>, size_t> index;
	for (size_t i = 0;i < gnba -> states.size();++ i) {
		const std::shared_ptr<State> &state_ = gnba -> states.at(i);
		index.emplace(state_, i);
		states_list.emplace_back();
		for (size_t j = 0;j < k;++ j) {
			std::shared_ptr<State> state(new State(!j && state_ -> get_is_initial()));
			state2state_index.emplace(state, std::make_pair(state_, j));
			delta.emplace(state, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>());
			for (const auto &symbol: alphabet)
				delta.at(state).emplace(symbol, std::set<std::shared_ptr<State>>());
			states.push_back(state);
			states_list.back().push_back(state);
		}
	}
	if (k)
		for (size_t i = 0;i < gnba -> states.size();++ i)
			if (gnba -> F.at(0).find(gnba -> states.at(i)) != gnba -> F.at(0).end())
				F.insert(states_list.at(i).at(0));
	for (size_t i = 0;i < gnba -> states.size();++ i) {
		std::shared_ptr<State> state = gnba -> states.at(i);
		for (auto [symbol, next_states]: gnba -> delta.at(state)) {
			std::vector<std::set<std::shared_ptr<State>>> next_states_list;
			for (size_t j = 0;j < k;++ j) {
				std::set<std::shared_ptr<State>> next_states_j_set;
				for (const auto &next_state: next_states)
					next_states_j_set.insert(states_list.at(index.at(next_state)).at(j));
				next_states_list.emplace_back(std::move(next_states_j_set));
			}
			for (size_t j = 0;j < k;++ j) {
				if (gnba -> F.at(j).find(state) == gnba -> F.at(j).end())
					delta.at(states_list.at(i).at(j)).at(symbol).insert(next_states_list.at(j).begin(), next_states_list.at(j).end());
				else
					delta.at(states_list.at(i).at(j)).at(symbol).insert(next_states_list.at((j + 1) % k).begin(), next_states_list.at((j + 1) % k).end());
			}
		}
	}
}

std::string to_string(std::shared_ptr<NBA> nba, const std::map<std::shared_ptr<State>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &state2set, const std::map<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, size_t>> &state2state, const std::map<std::shared_ptr<Symbol>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &Symbol2LTL) {
	std::string ret("NBA starts from here.\n");
	ret += nba -> maded_nonblocking ? "(Non-blocking)\n" : "(Maybe Blocking)\n";
	ret += "States:\n";
	for (const auto &state: nba -> states) {
		ret += "\t{";
		const auto &[state_, index] = state2state.at(state);
		for (const auto &phi: *state2set.at(state_)) ret += phi -> to_string() + ", ";
		ret += "} * " + std::to_string(index);
		if (state -> get_is_initial()) ret += " (initial)";
		ret += ",\n";
	}
	ret += "\nAlphabet:\n";
	for (const auto &symbol: nba -> alphabet) {
		ret += "\t{";
		const std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>> &set = Symbol2LTL.at(symbol);
		for (const auto &phi: *set) ret += phi -> to_string() + ", ";
		ret += "},\n";
	}
	ret += "\nDelta function:\n";
	for (const auto &state: nba -> states)
		for (const auto &[symbol, next_states]: nba -> delta.at(state))
			for (const auto &next_state: next_states) {
				ret += "\t{";
				const auto &[state_, index] = state2state.at(state);
				for (const auto &phi: *state2set.at(state_)) ret += phi -> to_string() + ", ";
				ret += "} * " + std::to_string(index) + " -> {";
				const auto &[state__, index_] = state2state.at(next_state);
				for (const auto &phi: *state2set.at(state__)) ret += phi -> to_string() + ", ";
				ret += "} * " + std::to_string(index_) + " with symbol = {";
				for (const auto &phi: *Symbol2LTL.at(symbol)) ret += phi -> to_string() + ", ";
				ret += "},\n";
			}
	ret += "\nF set:\n";
	for (const auto &state: nba -> F) {
		const auto &[state_, index] = state2state.at(state);
		ret += "\t{";
		for (const auto &phi: *state2set.at(state_)) ret += phi -> to_string() + ", ";
		ret += "} * " + std::to_string(index) + ",\n";
	}
	ret += "\nGNBA ends at here.";
	return ret;
}

GNBA::GNBA(const std::shared_ptr<LTL::LTL_Base> &phi, std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<Symbol>> &LTL2Symbol, std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<State>> &set2state, const PowerSet<LTL::LTL_Base> &PropLTLs_power_set, const std::shared_ptr<LTL::LTL_Base> &True) {
	std::set<std::shared_ptr<LTL::LTL_Base>> closure = std::move(phi -> get_closure(phi, std::shared_ptr<LTL::LTL_Base>()));
	for (const auto &propLTL: PropLTLs_power_set.get_universe())
		if (closure.find(propLTL) == closure.end()) {
			closure.emplace(propLTL);
			closure.emplace(std::make_shared<LTL::Negation>(propLTL));
		}
	bool has_True = closure.find(True) != closure.end();

	// compute elementary sets of closure(phi)
	std::set<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> elementary_sets;
	PowerSet<LTL::LTL_Base> closure_power_set(std::vector<std::shared_ptr<LTL::LTL_Base>>(closure.begin(), closure.end()));
	for (const auto &B: closure_power_set.get_subsets()) {
		bool flag = !has_True || B -> find(True) != B -> end();
		for (auto it = closure.begin();it != closure.end() && flag;++ it) {
			// consistent with respect to propositional logic
			if (instanceof<LTL::And>(*it)) {
				std::shared_ptr<LTL::LTL_Base> phi0 = *(*it) -> get_children().begin(), phi1 = *(*it) -> get_children().rbegin();
				flag &= (B -> find(*it) != B -> end()) == ((B -> find(phi0) != B -> end()) && (B -> find(phi1) != B -> end()));
			}
			if (B -> find(*it) != B -> end())
				if (instanceof<LTL::Negation>(*it)) {
					std::shared_ptr<LTL::LTL_Base> psi = *(*it) -> get_children().begin();
					flag &= B -> find(psi) == B -> end();
				} else for (const auto &phi_: *B) flag &= !instanceof<LTL::Negation>(phi_) || *phi_ -> get_children().begin() != *it;
			// locally consistent with respect to the until operator
			if (instanceof<LTL::Until>(*it)) {
				std::shared_ptr<LTL::LTL_Base> phi0 = *(*it) -> get_children().begin(), phi1 = *(*it) -> get_children().rbegin();
				if (B -> find(phi1) != B -> end()) flag &= B -> find(*it) != B -> end();
				if (B -> find(*it) != B -> end() && B -> find(phi1) == B -> end()) flag &= B -> find(phi0) != B -> end();
			}
			// maximal
			if (B -> find(*it) == B -> end())
				if (instanceof<LTL::Negation>(*it)) {
					std::shared_ptr<LTL::LTL_Base> psi = *(*it) -> get_children().begin();
					flag &= B -> find(psi) != B -> end();
				} else {
					bool found = false;
					for (const auto &phi_: *B)
						found |= instanceof<LTL::Negation>(phi_) && *phi_ -> get_children().begin() == *it;
					flag &= found;
				}
		}
		if (flag) elementary_sets.insert(B);
	}

	// initialize states
	for (const auto &B: elementary_sets) {
		std::shared_ptr<State> state(new State(B -> find(phi) != B -> end()));
		set2state.emplace(B, state), states.push_back(state);
		delta.emplace(state, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>());
	}

	// initialize accepting conditions F
	for (const auto &psi: closure)
		if (instanceof<LTL::Until>(psi)) {
			std::set<std::shared_ptr<State>> F_psi;
			std::shared_ptr<LTL::LTL_Base> phi1 = *psi -> get_children().rbegin();
			for (const auto &B: elementary_sets)
				if (B -> find(psi) == B -> end() || B -> find(phi1) != B -> end())
					F_psi.insert(set2state.at(B));
			F.push_back(std::move(F_psi));
		}

	// initialize the alphabet
	std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<Symbol>> set2symbol;
	for (const auto &s: PropLTLs_power_set.get_subsets()) {
		std::shared_ptr<Symbol> symbol(new Symbol);
		set2symbol.emplace(s, symbol), alphabet.push_back(symbol), LTL2Symbol.emplace(s, symbol);
	}

	// compute the delta function
	for (const auto &B: elementary_sets) {
		std::vector<std::shared_ptr<LTL::LTL_Base>> intersection;
		for (const auto &psi: PropLTLs_power_set.get_universe())
			if (B -> find(psi) != B -> end())
				intersection.push_back(psi);
		std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>> A = PropLTLs_power_set.get_subset(intersection);
		for (const auto &B_prime: elementary_sets) {
			bool flag = true;
			for (auto it = closure.begin();it != closure.end() && flag;++ it) {
				if (instanceof<LTL::Next>(*it)) {
					std::shared_ptr<LTL::LTL_Base> psi = *(*it) -> get_children().begin();
					flag &= (B -> find(*it) != B -> end()) == (B_prime -> find(psi) != B_prime -> end());
				}
				if (instanceof<LTL::Until>(*it)) {
					std::shared_ptr<LTL::LTL_Base> phi0 = *(*it) -> get_children().begin(), phi1 = *(*it) -> get_children().rbegin();
					flag &= (B -> find(*it) != B -> end()) == ((B -> find(phi1) != B -> end()) || ((B -> find(phi0) != B -> end()) && (B_prime -> find(*it) != B_prime -> end())));
				}
			}
			if (flag) {
				std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>> &delta_B = delta.at(set2state.at(B));
				std::shared_ptr<Symbol> symbol = set2symbol.at(A);
				std::shared_ptr<State> state_B_prime = set2state.at(B_prime);
				if (delta_B.find(symbol) == delta_B.end())
					delta_B.emplace(symbol, std::set<std::shared_ptr<State>>{state_B_prime});
				else
					delta_B.at(symbol).emplace(state_B_prime);
			}
		}
	}
}

std::string to_string(std::shared_ptr<GNBA> gnba, const std::map<std::shared_ptr<State>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &state2set, const std::map<std::shared_ptr<Symbol>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &Symbol2LTL) {
	std::string ret("GNBA starts from here.\n");
	ret += gnba -> maded_nonblocking ? "(Non-blocking)\n" : "(Maybe Blocking)\n";
	ret += "States:\n";
	for (const auto &state: gnba -> states) {
		ret += "\t{";
		const std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>> &set = state2set.at(state);
		for (const auto &phi: *set) ret += phi -> to_string() + ", ";
		ret += "}";
		if (state -> get_is_initial()) ret += " (initial)";
		ret += ",\n";
	}
	ret += "\nAlphabet:\n";
	for (const auto &symbol: gnba -> alphabet) {
		ret += "\t{";
		const std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>> &set = Symbol2LTL.at(symbol);
		for (const auto &phi: *set) ret += phi -> to_string() + ", ";
		ret += "},\n";
	}
	ret += "\nDelta function:\n";
	for (const auto &state: gnba -> states)
		for (const auto &[symbol, next_states]: gnba -> delta.at(state))
			for (const auto &next_state: next_states) {
				ret += "\t{";
				for (const auto &phi: *state2set.at(state)) ret += phi -> to_string() + ", ";
				ret += "} -> {";
				for (const auto &phi: *state2set.at(next_state)) ret += phi -> to_string() + ", ";
				ret += "} with symbol = {";
				for (const auto &phi: *Symbol2LTL.at(symbol)) ret += phi -> to_string() + ", ";
				ret += "},\n";
			}
	ret += "\nF set family:\n";
	for (const auto &final_set: gnba -> F) {
		ret += "\t{\n";
		for (const auto &state: final_set) {
			ret += "\t\t{";
			for (const auto &phi: *state2set.at(state)) ret += phi -> to_string() + ", ";
			ret += "}\n";
		}
		ret += "\t},\n";
	}
	ret += "\nGNBA ends at here.";
	return ret;
}
}