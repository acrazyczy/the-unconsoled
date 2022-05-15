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
#include "TS.hpp"

namespace LTL {
class LTL_Base {
	public:

	virtual std::vector<std::shared_ptr<LTL_Base>> get_children() const;
	virtual std::string to_string() const;
	std::set<std::shared_ptr<LTL_Base>> get_closure() const;
};

class Negation: public LTL_Base {
	public:

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;
	std::set<std::shared_ptr<LTL_Base>> get_closure() const;

	private:

	std::shared_ptr<LTL_Base> phi;
};

class Until: public LTL_Base {
	public:

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;

	private:

	std::shared_ptr<LTL_Base> phi0, phi1;
};

class Next: public LTL_Base{
	public:

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;

	private:

	std::shared_ptr<LTL_Base> phi;
};

class And: public LTL_Base {
	public:

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;

	private:

	std::shared_ptr<LTL_Base> phi0, phi1;
};

class Variable: public LTL_Base {
	public:

	std::vector<std::shared_ptr<LTL_Base>> get_children() const override;
	std::string to_string() const override;

	private:

	std::shared_ptr<TS::Proposition> p;
};

}


#endif //THE_UNCONSOLED_LTL_HPP
