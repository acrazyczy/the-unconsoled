//
// Created by crazy_cloud on 2022/5/15.
// @formatter:off
//

#ifndef THE_UNCONSOLED_POWERSET_HPP
#define THE_UNCONSOLED_POWERSET_HPP

#include <memory>
#include <set>
#include <map>

template <typename T>
class PowerSet {
	public:
	private:
	std::map<T, size_t> atom;
	std::map<size_t, std::shared_ptr<std::set<T>>> subsets;
};



#endif //THE_UNCONSOLED_POWERSET_HPP
