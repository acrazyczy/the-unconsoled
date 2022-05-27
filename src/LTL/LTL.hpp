//
// Created by crazy_cloud on 2022/4/25.
// @formatter:off
//

#ifndef THE_UNCONSOLED_LTL_HPP
#define THE_UNCONSOLED_LTL_HPP

#include <memory>
#include <string>
#include <vector>
#include <set>

#include "Tools.hpp"

namespace TransitionSystem {
class Proposition;
}

namespace LTL {
class LTL_Base {
	public:

	virtual std::vector<std::shared_ptr<LTL_Base>> get_children() const {return std::vector<std::shared_ptr<LTL_Base>>();}
	virtual std::string to_string() const {return "true";}
	virtual std::set<std::shared_ptr<LTL_Base>> get_closure(std::shared_ptr<LTL_Base> tptr) const;
};

class Negation: public LTL_Base {
	public:
	Negation(std::shared_ptr<LTL_Base> phi_): phi(phi_) {}

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;
	std::set<std::shared_ptr<LTL_Base>> get_closure(std::shared_ptr<LTL_Base> tptr) const;

	private:

	std::shared_ptr<LTL_Base> phi;
};

class Until: public LTL_Base {
	public:
	Until(std::shared_ptr<LTL_Base> phi0_, std::shared_ptr<LTL_Base> phi1_): phi0(phi0_), phi1(phi1_) {}

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;

	private:

	std::shared_ptr<LTL_Base> phi0, phi1;
};

class Next: public LTL_Base {
	public:
	Next(std::shared_ptr<LTL_Base> phi_): phi(phi_) {}

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;

	private:

	std::shared_ptr<LTL_Base> phi;
};

class And: public LTL_Base {
	public:
	And(std::shared_ptr<LTL_Base> phi0_, std::shared_ptr<LTL_Base> phi1_): phi0(phi0_), phi1(phi1_) {}

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;

	private:

	std::shared_ptr<LTL_Base> phi0, phi1;
};

class Variable: public LTL_Base {
	public:
	Variable(std::shared_ptr<TransitionSystem::Proposition> p_): p(p_) {}

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;

	private:

	std::shared_ptr<TransitionSystem::Proposition> p;
};

}


#endif //THE_UNCONSOLED_LTL_HPP
