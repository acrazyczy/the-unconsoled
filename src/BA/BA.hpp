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

namespace BuechiAutomata {
class NBA;
class Symbol;
}

namespace TransitionSystem {
class TS;
class Proposition;
std::shared_ptr<TS> product(const std::shared_ptr<TS> &ts, const std::shared_ptr<BuechiAutomata::NBA> &nba, const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol, const std::map<std::shared_ptr<Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL, const PowerSet<LTL::LTL_Base> &power_set);
}

namespace BuechiAutomata {

class State {
	public:
	State(bool is_initial_ = false): is_initial(is_initial_) {}
	bool get_is_initial() const;

	private:
	bool is_initial;
};

class Symbol {
};

class BA;
class NBA;

class BA {
	public:
	void make_nonblocking();

	protected:
	std::map<std::shared_ptr<State>, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>> delta;
	std::vector<std::shared_ptr<State>> states;
	std::vector<std::shared_ptr<Symbol>> alphabet;
	bool maded_nonblocking = false;

	friend std::shared_ptr<TransitionSystem::TS> TransitionSystem::product(const std::shared_ptr<TransitionSystem::TS> &ts, const std::shared_ptr<BuechiAutomata::NBA> &nba, const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol, const std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL, const PowerSet<LTL::LTL_Base> &power_set);
};

class GNBA: public BA {
	public:
	GNBA(const std::shared_ptr<LTL::LTL_Base> &phi, std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<Symbol>> &LTL2Symbol, const PowerSet<LTL::LTL_Base> &PropLTLs_power_set, const std::shared_ptr<LTL::LTL_Base> &True);

	private:
	std::vector<std::set<std::shared_ptr<State>>> F;

	friend class NBA;
};

class NBA: public BA {
	public:
	NBA(const std::shared_ptr<GNBA> &gnba);

	private:
	std::set<std::shared_ptr<State>> F;

	friend std::shared_ptr<TransitionSystem::TS> TransitionSystem::product(const std::shared_ptr<TransitionSystem::TS> &ts, const std::shared_ptr<BuechiAutomata::NBA> &nba, const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol, const std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL, const PowerSet<LTL::LTL_Base> &power_set);
};
}


#endif //THE_UNCONSOLED_BA_HPP
