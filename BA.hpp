//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#ifndef THE_UNCONSOLED_BA_HPP
#define THE_UNCONSOLED_BA_HPP

#include <vector>
#include <memory>
#include <map>
#include <set>

#include "LTL.hpp"
#include "PowerSet.hpp"

namespace BA {
typedef LTL::LTL_Base LTL_Base;

class State {
	public:
	State(bool is_initial_): is_initial(is_initial_) {}
	private:
	bool is_initial;
};

class Proposition {
};

class BA {
	public:

	protected:

	std::map<std::shared_ptr<State>, > delta;
	std::vector<std::shared_ptr<State>> states;
};

class NBA: public BA {

};

class GNBA: public BA {
	public:
	GNBA(std::shared_ptr<LTL_Base> phi, const PowerSet<TS::Proposition> &ps) {
		std::set<std::shared_ptr<LTL_Base>>	closure = std::move(phi -> get_closure());
		std::set<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>> elementary_sets;
		std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<State>> set2state;
		for (auto B: elementary_sets) {
			std::shared_ptr<State> state(new State(B -> find(phi) != B -> end()));
			set2state.emplace(B, state), states.push_back(state);
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
		for (auto B: elementary_sets) {
			std::vector<std::shared_ptr<LTL_Base>> intersection;
			for (auto psi: )
				if (B -> find(psi) != B -> end())
					intersection.push_back(psi);
			for (auto A: elementary_sets) {
				bool flag = intersection.size() == A -> size();
				for (auto it = intersection.begin();it != intersection.end() && flag;++ it)
					flag &= A -> find(*it) != A -> end();
				if (!flag) continue;

				break;
			}
		}
	}

	private:

	std::vector<std::set<std::shared_ptr<State>>> F;
};
}


#endif //THE_UNCONSOLED_BA_HPP
