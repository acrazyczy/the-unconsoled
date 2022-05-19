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
#include "TS.hpp"

namespace BA {
using LTL::LTL_Base;

class State {
	public:
	State(bool is_initial_ = false): is_initial(is_initial_) {}
	bool get_is_initial() const;

	private:
	bool is_initial;
};

class Symbol {
};

class BA {
	public:
	void make_nonblocking();
	bool has_maded_nonblocking() const;

	protected:
	std::map<std::shared_ptr<State>, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>> delta;
	std::vector<std::shared_ptr<State>> states;
	std::vector<std::shared_ptr<Symbol>> alphabet;
	bool maded_nonblocking;
};

class GNBA;

class NBA: public BA {
	public:
	NBA(const std::shared_ptr<GNBA> gnba);

	private:
	std::set<std::shared_ptr<State>> F;

	friend std::shared_ptr<TS> product(const std::shared_ptr<TS> ts, const std::shared_ptr<BA::NBA> nba, const std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<BA::Symbol>> &LTL2Symbol, const std::map<std::shared_ptr<TS::Proposition>, std::shared_ptr<LTL_Base>> &Prop2LTL, const PowerSet<LTL_Base> &power_set);
};

class GNBA: public BA {

	public:
	GNBA(std::shared_ptr<LTL_Base> phi, const std::vector<std::shared_ptr<LTL_Base>> &AP, std::map<std::shared_ptr<std::set<std::shared_ptr<LTL_Base>>>, std::shared_ptr<Symbol>> &LTL2Symbol, PowerSet<LTL_Base> &power_set);

	private:
	std::vector<std::set<std::shared_ptr<State>>> F;

	friend class NBA;
};
}


#endif //THE_UNCONSOLED_BA_HPP
