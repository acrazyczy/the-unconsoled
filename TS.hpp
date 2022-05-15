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
#include <map>
#include <set>

#include "Tools.hpp"

namespace TS{
class State {
	public:
	std::string to_string() const;
	void set_name(std::string name_);
	private:
	std::string name;
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
	std::vector<std::shared_ptr<State>> I;
	std::vector<std::shared_ptr<Action>> Act;
	std::vector<std::shared_ptr<Proposition>> AP;
	std::map<std::shared_ptr<State>, std::set<std::pair<std::shared_ptr<State>, std::shared_ptr<Action>>>> trans;
	std::map<std::shared_ptr<State>, std::set<std::shared_ptr<Proposition>>> L;

	size_t S, T;

	friend std::istream& operator>>(std::istream &is, TS &ts);
};

std::istream& operator>>(std::istream &is, TS &ts);
}

#endif //THE_UNCONSOLED_TS_HPP
