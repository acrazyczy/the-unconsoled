//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#include "TS.hpp"

#include <memory>

namespace TS {

void State::set_name(std::string name_) {name = name_;}
std::string State::to_string() const {return name;}

void Action::set_name(std::string name_) {name = name_;}
std::string Action::to_string() const {return name;}

void Proposition::set_name(std::string name_) {name = name_;}
std::string Proposition::to_string() const {return name;}

std::istream& operator>>(std::istream &is, TS &ts) {
	is >> ts.S >> ts.T;
	for (size_t x = 0;x < ts.S;++ x) {
		std::shared_ptr<State> s(new State);
		ts.I.push_back(s);
		ts.trans.emplace(s, std::set<std::pair<std::shared_ptr<State>, std::shared_ptr<Action>>>());
		ts.L.emplace(s, std::set<std::shared_ptr<Proposition>>());
	}
	std::vector<std::string> string_vector;
	read_line(is, string_vector);
	for (size_t x = 0;x < ts.S;++ x) ts.I[x] -> set_name(string_vector[x]);
	string_vector.clear();
	read_line(is, string_vector);
	for (size_t x = 0;x < ts.S;++ x) ts.Act[x] -> set_name(string_vector[x]);
	string_vector.clear();
	read_line(is, string_vector);
	for (size_t x = 0;x < ts.S;++ x) ts.AP[x] -> set_name(string_vector[x]);
	for (size_t t = 0, i, j, k;t < ts.T;++ t) {
		is >> i >> k >> j;
		ts.trans[ts.I[i]].emplace(ts.I[j], ts.Act[k]);
	}
	std::vector<size_t> size_t_vector;
	for (auto s: ts.I) {
		auto& L = ts.L[s];
		read_line(is, size_t_vector);
		std::for_each(size_t_vector.begin(), size_t_vector.end(), [&](const auto& item){L.insert(ts.AP[item]);});
	}
	return is;
}

}