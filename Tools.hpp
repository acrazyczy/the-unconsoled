//
// Created by crazy_cloud on 2022/5/9.
// @formatter:off
//

#ifndef THE_UNCONSOLED_TOOLS_HPP
#define THE_UNCONSOLED_TOOLS_HPP

#include <iterator>
#include <sstream>
#include <memory>

template<typename Base, typename T>
inline bool instanceof(const std::shared_ptr<T> ptr) {
	return ptr.get() != nullptr && std::dynamic_pointer_cast<Base>(ptr).get() != nullptr;
}

template<class T>
static void read_line(std::istream &is, std::vector<T> &vec) {
	std::string line;
	std::getline(is, line);
	std::istringstream iss(line);
	std::copy(std::istream_iterator<T>(iss), std::istream_iterator<T>(), std::back_inserter(vec));
}

#endif //THE_UNCONSOLED_TOOLS_HPP
