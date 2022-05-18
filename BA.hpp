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
using LTL::LTL_Base;

class State {
	public:
	State(bool is_initial_ = false): is_initial(is_initial_) {}

	private:
	bool is_initial;
};

class Symbol {
};

class BA {
	public:

	protected:
	std::map<std::shared_ptr<State>, std::map<std::shared_ptr<Symbol>, std::set<std::shared_ptr<State>>>> delta;
	std::vector<std::shared_ptr<State>> states;
	std::vector<std::shared_ptr<Symbol>> alphabet;
};

class GNBA;

class NBA: public BA {
	public:
	NBA(std::shared_ptr<GNBA> gnba);

	private:
	std::set<std::shared_ptr<State>> F;
};

class GNBA: public BA {

	public:
	GNBA(std::shared_ptr<LTL_Base> phi, const std::vector<std::shared_ptr<LTL_Base>> &AP);

	private:
	std::vector<std::set<std::shared_ptr<State>>> F;

	friend class NBA;
};
}


#endif //THE_UNCONSOLED_BA_HPP
