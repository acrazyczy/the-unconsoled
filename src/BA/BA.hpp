//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#ifndef THE_UNCONSOLED_BA_HPP
#define THE_UNCONSOLED_BA_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <set>

#include "LTL.hpp"
#include "PowerSet.hpp"

namespace BuechiAutomata {
class NBA;
class State;
class Symbol;
}

namespace TransitionSystem {
class State;
class TS;
class Proposition;
std::shared_ptr<TS> product(
	const std::shared_ptr<TS> &ts,
	const std::shared_ptr<BuechiAutomata::NBA> &nba,
	const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol,
	const std::map<std::shared_ptr<Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL,
	const PowerSet<LTL::LTL_Base> &power_set,
	std::set<std::shared_ptr<Proposition>> &F_Props,
	std::map<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, std::shared_ptr<BuechiAutomata::State>>> &s2s_state
);

std::set<std::shared_ptr<TransitionSystem::State>> get_entries(
	const std::shared_ptr<TransitionSystem::State> &src_s,
	const std::shared_ptr<TransitionSystem::TS> &ts,
	const std::shared_ptr<BuechiAutomata::NBA> &nba,
	const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol,
	const std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL,
	const PowerSet<LTL::LTL_Base> &power_set,
	const std::map<std::pair<std::shared_ptr<TransitionSystem::State>, std::shared_ptr<BuechiAutomata::State>>, std::shared_ptr<TransitionSystem::State>> &sstate2s
);
}

namespace BuechiAutomata {

class State {
	public:
	explicit State(bool is_initial_ = false): is_initial(is_initial_) {}
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
	std::shared_ptr<State> make_nonblocking();

	protected:
	std::map<std::shared_ptr<State>, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>> delta;
	std::vector<std::shared_ptr<State>> states;
	std::vector<std::shared_ptr<Symbol>> alphabet;
	bool maded_nonblocking = false;

	friend std::shared_ptr<TransitionSystem::TS> TransitionSystem::product(
		const std::shared_ptr<TransitionSystem::TS> &ts,
		const std::shared_ptr<BuechiAutomata::NBA> &nba,
		const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol,
		const std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL,
		const PowerSet<LTL::LTL_Base> &power_set,
		std::set<std::shared_ptr<TransitionSystem::Proposition>> &F_Props,
		std::map<std::shared_ptr<TransitionSystem::State>, std::pair<std::shared_ptr<TransitionSystem::State>, std::shared_ptr<BuechiAutomata::State>>> &s2s_state
	);

	friend std::set<std::shared_ptr<TransitionSystem::State>> TransitionSystem::get_entries(
		const std::shared_ptr<TransitionSystem::State> &src_s,
		const std::shared_ptr<TransitionSystem::TS> &ts,
		const std::shared_ptr<BuechiAutomata::NBA> &nba,
		const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol,
		const std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL,
		const PowerSet<LTL::LTL_Base> &power_set,
		const std::map<std::pair<std::shared_ptr<TransitionSystem::State>, std::shared_ptr<BuechiAutomata::State>>, std::shared_ptr<TransitionSystem::State>> &sstate2s
	);
};

class GNBA: public BA {
	public:
	GNBA(const std::shared_ptr<LTL::LTL_Base> &phi, std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<Symbol>> &LTL2Symbol, std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<State>> &set2state, const PowerSet<LTL::LTL_Base> &PropLTLs_power_set, const std::shared_ptr<LTL::LTL_Base> &True);


	private:
	std::vector<std::set<std::shared_ptr<State>>> F;

	friend class NBA;
	friend std::string to_string(std::shared_ptr<GNBA> gnba, const std::map<std::shared_ptr<State>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &state2set, const std::map<std::shared_ptr<Symbol>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &Symbol2LTL);
};

class NBA: public BA {
	public:
	NBA(const std::shared_ptr<GNBA> &gnba, std::map<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, size_t>> &state2state_index);

	private:
	std::set<std::shared_ptr<State>> F;

	friend std::shared_ptr<TransitionSystem::TS> TransitionSystem::product(
		const std::shared_ptr<TransitionSystem::TS> &ts,
		const std::shared_ptr<BuechiAutomata::NBA> &nba,
		const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol,
		const std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL,
		const PowerSet<LTL::LTL_Base> &power_set,
		std::set<std::shared_ptr<TransitionSystem::Proposition>> &F_Props,
		std::map<std::shared_ptr<TransitionSystem::State>, std::pair<std::shared_ptr<TransitionSystem::State>, std::shared_ptr<BuechiAutomata::State>>> &s2s_state
	);

	friend std::set<std::shared_ptr<TransitionSystem::State>> TransitionSystem::get_entries(
		const std::shared_ptr<TransitionSystem::State> &src_s,
		const std::shared_ptr<TransitionSystem::TS> &ts,
		const std::shared_ptr<BuechiAutomata::NBA> &nba,
		const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol,
		const std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL,
		const PowerSet<LTL::LTL_Base> &power_set,
		const std::map<std::pair<std::shared_ptr<TransitionSystem::State>, std::shared_ptr<BuechiAutomata::State>>, std::shared_ptr<TransitionSystem::State>> &sstate2s
	);
	friend std::string to_string(std::shared_ptr<NBA> nba, const std::map<std::shared_ptr<State>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &state2set, const std::map<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, size_t>> &state2state, const std::map<std::shared_ptr<Symbol>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &Symbol2LTL);
};

std::string to_string(std::shared_ptr<GNBA> gnba, const std::map<std::shared_ptr<State>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &state2set, const std::map<std::shared_ptr<Symbol>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &Symbol2LTL);
std::string to_string(std::shared_ptr<NBA> nba, const std::map<std::shared_ptr<State>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &state2set, const std::map<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, size_t>> &state2state, const std::map<std::shared_ptr<Symbol>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> &Symbol2LTL);
}

#endif //THE_UNCONSOLED_BA_HPP
