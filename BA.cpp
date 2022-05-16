//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#include "BA.hpp"

namespace BA {
GNBA::GNBA(std::shared_ptr<LTL_Base> phi, const std::vector<std::shared_ptr<LTL_Base>> &AP) {
	std::set<std::shared_ptr<LTL_Base>> closure = std::move(phi -> get_closure());
	std::set<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>> elementary_sets;
	std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<State>> set2state;
	for (auto B: elementary_sets) {
		std::shared_ptr<State> state(new State(B -> find(phi) != B -> end()));
		set2state.emplace(B, state), states.push_back(state);
		delta.emplace(state, std::map<std::shared_ptr<Symbol>, std::shared_ptr<State>>());
	}
	for (auto psi: closure)
		if (instanceof<LTL::Until>(psi)) {
			std::set<std::shared_ptr<State>> F_psi;
			std::shared_ptr<LTL_Base> phi1 = *psi -> get_children().rbegin();
			for (auto B: elementary_sets)
				if (B -> find(psi) == B -> end() || B -> find(phi1) != B -> end())
					F_psi.insert(set2state.at(B));
			F.push_back(std::move(F_psi));
		}
	std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<Symbol>> set2symbol;
	PowerSet<LTL_Base> power_set(AP);
	for (auto s: power_set.get_subsets()) {
		std::shared_ptr<Symbol> symbol(new Symbol);
		set2symbol.emplace(s, symbol), alphabet.push_back(symbol);
	}
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
					std::shared_ptr<LTL_Base> 	phi0 = *(*it) -> get_children().begin(),
												phi1 = *(*it) -> get_children().rbegin();
					flag &= (B -> find(*it) != B -> end()) == ((B -> find(phi1) != B -> end()) || ((B -> find(phi0) != B -> end()) && (B_prime -> find(*it) != B_prime -> end())));
				}
			}
			if (flag) delta.at(set2state.at(B)).emplace(set2symbol.at(A), set2state.at(B_prime));
		}
	}
}
}