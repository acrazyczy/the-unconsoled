//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#include "BA.hpp"

namespace BA {
NBA::NBA(std::shared_ptr<GNBA> gnba){
	size_t k = gnba -> F.size();
	std::vector<std::vector<std::shared_ptr<State>>> states_list; // S * [k]
	std::map<std::shared_ptr<State>, size_t> index;
	for (size_t i = 0;i < gnba -> states.size();++ i) {
		index.emplace(gnba -> states.at(i), i);
		states_list.emplace_back();
		for (size_t j = 0;j < k;++ j) {
			std::shared_ptr<State> state(new State(!j));
			delta.emplace(state, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>());
			states.push_back(state);
			states_list.back().push_back(state);
		}
	}
	for (size_t i = 0;i < gnba -> states.size();++ i)
		if (gnba -> F.at(0).find(gnba -> states.at(i)) != gnba -> F.at(0).end())
			F.insert(states_list.at(i).at(0));
	for (size_t i = 0;i < gnba -> states.size();++ i) {
		std::shared_ptr<State> state = gnba -> states.at(i);
		for (auto [symbol, next_states]: gnba -> delta.at(state)) {
			std::vector<std::set<std::shared_ptr<State>>> next_states_list;
			for (size_t j = 0;j < k;++ j) {
				std::set<std::shared_ptr<State>> next_states_j_set;
				for (auto next_state: next_states)
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
	alphabet = gnba -> alphabet;
}

GNBA::GNBA(std::shared_ptr<LTL_Base> phi, const std::vector<std::shared_ptr<LTL_Base>> &AP) {
	std::set<std::shared_ptr<LTL_Base>> closure = std::move(phi -> get_closure());

	// compute elementary sets of closure(phi)
	std::set<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>> elementary_sets;
	PowerSet<LTL_Base> power_set(std::vector<std::shared_ptr<LTL_Base>>(closure.begin(), closure.end()));
	for (auto B: power_set.get_subsets()) {
		bool flag = true;
		for (auto it = closure.begin();it != closure.end() && flag;++ it) {
			// consistent with respect to propositional logic
			if (instanceof<LTL::And>(*it)) {
				std::shared_ptr<LTL_Base> phi0 = *(*it) -> get_children().begin(), phi1 = *(*it) -> get_children().rbegin();
				flag &= (B -> find(*it) != B -> end()) == ((B -> find(phi0) != B -> end()) && (B -> find(phi1) != B -> end()));
			}
			if (B -> find(*it) != B -> end())
				if (instanceof<LTL::Negation>(*it)) {
					std::shared_ptr<LTL_Base> psi = *(*it) -> get_children().begin();
					flag &= B -> find(psi) == B -> end();
				} else for (auto phi: *B) flag &= !instanceof<LTL::Negation>(phi) || *phi -> get_children().begin() != *it;
			// locally consistent with respect to the until operator
			if (instanceof<LTL::Until>(*it)) {
				std::shared_ptr<LTL_Base> phi0 = *(*it) -> get_children().begin(), phi1 = *(*it) -> get_children().rbegin();
				if (B -> find(phi1) != B -> end()) flag &= B -> find(*it) != B -> end();
				if (B -> find(*it) != B -> end() && B -> find(phi1) == B -> end()) flag &= B -> find(phi0) != B -> end();
			}
			// maximal
			if (B -> find(*it) == B -> end())
				if (instanceof<LTL::Negation>(*it)) {
					std::shared_ptr<LTL_Base> psi = *(*it) -> get_children().begin();
					flag &= B -> find(psi) != B -> end();
				} else {
					bool found = false;
					for (auto phi: *B) found |= instanceof<LTL::Negation>(phi) && *phi -> get_children().begin() == *it;
					flag &= found;
				}
		}
		if (flag) elementary_sets.insert(B);
	}

	// initialize states
	std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<State>> set2state;
	for (auto B: elementary_sets) {
		std::shared_ptr<State> state(new State(B -> find(phi) != B -> end()));
		set2state.emplace(B, state), states.push_back(state);
		delta.emplace(state, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>());
	}

	// initialize accepting conditions F
	for (auto psi: closure)
		if (instanceof<LTL::Until>(psi)) {
			std::set<std::shared_ptr<State>> F_psi;
			std::shared_ptr<LTL_Base> phi1 = *psi -> get_children().rbegin();
			for (auto B: elementary_sets)
				if (B -> find(psi) == B -> end() || B -> find(phi1) != B -> end())
					F_psi.insert(set2state.at(B));
			F.push_back(std::move(F_psi));
		}

	// initialize the alphabet
	std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<Symbol>> set2symbol;
	power_set = PowerSet<LTL_Base>(AP);
	for (auto s: power_set.get_subsets()) {
		std::shared_ptr<Symbol> symbol(new Symbol);
		set2symbol.emplace(s, symbol), alphabet.push_back(symbol);
	}

	// compute the delta function
	for (auto B: elementary_sets) {
		std::vector<std::shared_ptr<LTL_Base>> intersection;
		for (auto psi: AP)
			if (B -> find(psi) != B -> end())
				intersection.push_back(psi);
		std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>> A = power_set.get_subset(intersection);
		for (auto B_prime: elementary_sets) {
			bool flag = true;
			for (auto it = closure.begin();it != closure.end() && flag;++ it) {
				if (instanceof<LTL::Next>(*it)) {
					std::shared_ptr<LTL_Base> psi = *(*it) -> get_children().begin();
					flag &= (B -> find(*it) != B -> end()) == (B_prime -> find(psi) != B_prime -> end());
				}
				if (instanceof<LTL::Until>(*it)) {
					std::shared_ptr<LTL_Base> phi0 = *(*it) -> get_children().begin(), phi1 = *(*it) -> get_children().rbegin();
					flag &= (B -> find(*it) != B -> end()) == ((B -> find(phi1) != B -> end()) || ((B -> find(phi0) != B -> end()) && (B_prime -> find(*it) != B_prime -> end())));
				}
			}
			if (flag) delta.at(set2state.at(B)).at(set2symbol.at(A)).insert(set2state.at(B_prime));
		}
	}
}
}