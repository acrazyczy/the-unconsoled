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
	PowerSet(const std::vector<std::shared_ptr<T>> &universe_) {
		for (size_t i = 0;i < universe_.size();++ i)
			universe.emplace(universe_.at(i), i);
		std::set<std::shared_ptr<T>> tmp;
		generate_subsets(tmp, universe_, 0);
	}

	std::shared_ptr<std::set<std::shared_ptr<T>>> get_subset(const std::vector<std::shared_ptr<T>> &s) const {
		size_t v = 0;
		for (auto x: s) v |= 1 << universe.at(x);
		return subsets.at(v);
	}

	std::set<std::shared_ptr<std::set<std::shared_ptr<T>>>> get_subsets() const;

	private:
	std::map<std::shared_ptr<T>, size_t> universe;
	std::map<size_t, std::shared_ptr<std::set<std::shared_ptr<T>>>> subsets;

	void generate_subsets(std::set<std::shared_ptr<T>> &s, const std::vector<std::shared_ptr<T>> &universe_, size_t i, size_t v) {
		if (i == universe_.size()) {
			subsets.emplace(v, s);
			return;
		}
		generate_subsets(s, universe_, i + 1, v);
		s.insert(universe_.at(i));
		generate_subsets(s, universe_, i + 1, v | (1 << i));
		s.erase(universe_.at(i));
	}
};



#endif //THE_UNCONSOLED_POWERSET_HPP
