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
	PowerSet(const std::vector<std::shared_ptr<T>> &universe);

	std::set<std::shared_ptr<T>> get_universe() const;
	std::shared_ptr<std::set<std::shared_ptr<T>>> get_subset(const std::vector<std::shared_ptr<T>> &s) const;
	std::set<std::shared_ptr<std::set<std::shared_ptr<T>>>> get_subsets() const;
	private:
	std::map<std::shared_ptr<T>, size_t> universe;
	std::map<size_t, std::shared_ptr<std::set<std::shared_ptr<T>>>> subsets;
};



#endif //THE_UNCONSOLED_POWERSET_HPP
