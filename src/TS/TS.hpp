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

namespace TS{
using LTL::LTL_Base;

class State {
	public:
	void set_is_initial(bool is_initial_ = false);
	bool get_is_initial() const;
	private:
	bool is_initial;
};

class Action {
	public:
	std::string to_string() const;
	void set_name(std::string name_);
	private:
	std::string name;
};

class Proposition {
	public:
	std::string to_string() const;
	void set_name(std::string name_);
	private:
	std::string name;
};

class TS {
	public:
	bool persistence_checking(std::set<std::shared_ptr<Proposition>> F) const; // return whether all traces satisfying always negation F
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
	void reachable_cycle(std::set<std::shared_ptr<Proposition>> F, std::shared_ptr<State> s) const;
	bool cycle_check(std::set<std::shared_ptr<Proposition>> F, std::shared_ptr<State> s) const;

	friend std::istream& operator>>(std::istream &is, std::shared_ptr<TS> ts);
	friend std::shared_ptr<TS> product(const std::shared_ptr<TS> ts, const std::shared_ptr<BA::NBA> nba, const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<BA::Symbol>> &LTL2Symbol, const std::map<std::shared_ptr<Proposition>, std::shared_ptr<LTL_Base>> &Prop2LTL, const PowerSet<LTL_Base> &power_set);
};
}

#endif //THE_UNCONSOLED_TS_HPP
