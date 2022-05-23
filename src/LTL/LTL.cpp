//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#include "LTL.hpp"

namespace LTL {
std::set<std::shared_ptr<LTL_Base>> LTL_Base::get_closure() const {
	std::set<std::shared_ptr<LTL_Base>> ret{
		std::shared_ptr<LTL_Base>(const_cast<LTL_Base *>(this)),
		std::shared_ptr<LTL_Base>(new Negation(const_cast<LTL_Base *>(this))),
	};
	for (auto phi: get_children()) {
		std::set<std::shared_ptr<LTL_Base>> tmp(std::move(phi -> get_closure()));
		ret.insert(tmp.begin(), tmp.end());
	}
	return std::move(ret);
}

std::set<std::shared_ptr<LTL_Base>> Negation::get_closure() const {
	std::set<std::shared_ptr<LTL_Base>> ret{
		std::shared_ptr<LTL_Base>(const_cast<Negation *>(this))
	};
	for (auto phi: get_children()) {
		std::set<std::shared_ptr<LTL_Base>> tmp(std::move(phi -> get_closure()));
		ret.insert(tmp.begin(), tmp.end());
	}
	return std::move(ret);
}

std::vector<std::shared_ptr<LTL_Base>> Negation::get_children() const {
	return {phi};
}

std::string Negation::to_string() const {
	return "!(" + phi -> to_string() + ")";
}

std::vector<std::shared_ptr<LTL_Base>> Until::get_children() const {
	return {phi0, phi1};
}

std::string Until::to_string() const {
	return "(" + phi0 -> to_string() + ") U (" + phi1 -> to_string() + ")";
}

std::vector<std::shared_ptr<LTL_Base>> Next::get_children() const {
	return {phi};
}

std::string Next::to_string() const {
	return "X(" + phi -> to_string() + ")";
}

std::vector<std::shared_ptr<LTL_Base>> And::get_children() const {
	return {phi0, phi1};
}

std::string And::to_string() const {
	return "(" + phi0 -> to_string() + ") /\\ (" + phi1 -> to_string() + ")";
}

std::vector<std::shared_ptr<LTL_Base>> Variable::get_children() const {
	return {};
}

std::string Variable::to_string() const {
	return p -> to_string();
}
}