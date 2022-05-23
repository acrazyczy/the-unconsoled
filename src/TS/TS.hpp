//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#ifndef THE_UNCONSOLED_TS_HPP
#define THE_UNCONSOLED_TS_HPP

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <stack>
#include <map>
#include <set>

#include "Tools.hpp"
#include "PowerSet.hpp"
#include "BA.hpp"

namespace TransitionSystem{

class State {
	public:
	void set_is_initial(bool is_initial_ = false);
	bool get_is_initial() const;
	private:
	bool is_initial;
};

class Action {
	public:
	Action(std::string name_): name(name_) {}
	std::string to_string() const;
	private:
	std::string name;
};

class Proposition {
	public:
	Proposition() = default;
	Proposition(std::string name_): name(name_) {}
	std::string to_string() const;
	private:
	std::string name;
};

class TS {
	public:
	bool persistence_checking(const std::set<std::shared_ptr<Proposition>> &F) const; // return whether all traces satisfying always negation F

	const std::vector<std::shared_ptr<Proposition>> &get_AP() const;
	std::map<std::string, std::shared_ptr<Proposition>> get_Name2Prop() const;
	private:
	std::vector<std::shared_ptr<State>> S;
	std::vector<std::shared_ptr<Action>> Act;
	std::vector<std::shared_ptr<Proposition>> AP;
	std::map<std::shared_ptr<State>, std::set<std::pair<std::shared_ptr<State>, std::shared_ptr<Action>>>> trans;
	std::map<std::shared_ptr<State>, std::set<std::shared_ptr<Proposition>>> L;

	size_t N_S, N_T;

	mutable bool cycle_found;
	mutable std::set<std::shared_ptr<State>> R, T, I;
	mutable std::stack<std::shared_ptr<State>> U, V;
	void reachable_cycle(const std::set<std::shared_ptr<Proposition>> &F, const std::shared_ptr<State> &s) const;
	bool cycle_check(const std::shared_ptr<State> &s) const;

	friend std::istream& operator>>(std::istream &is, std::shared_ptr<TS> ts);
	friend std::shared_ptr<TS> product(const std::shared_ptr<TS> &ts, const std::shared_ptr<BuechiAutomata::NBA> &nba, const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol, const std::map<std::shared_ptr<Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL, const PowerSet<LTL::LTL_Base> &power_set);
};

std::istream& operator>>(std::istream &is, std::shared_ptr<TS> ts);
std::shared_ptr<TS> product(const std::shared_ptr<TS> &ts, const std::shared_ptr<BuechiAutomata::NBA> &nba, const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> &LTL2Symbol, const std::map<std::shared_ptr<Proposition>, std::shared_ptr<LTL::LTL_Base>> &Prop2LTL, const PowerSet<LTL::LTL_Base> &power_set);
}

#endif //THE_UNCONSOLED_TS_HPP
