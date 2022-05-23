//
// Created by crazy_cloud on 2022/5/23.
// @formatter:off
//

#ifndef THE_UNCONSOLED_LTLEVALVISITOR_HPP
#define THE_UNCONSOLED_LTLEVALVISITOR_HPP

#include <memory>
#include <string>

#include "LTLlangBaseVisitor.h"
#include "LTL.hpp"
#include "TS.hpp"

namespace Parser {
using LTL::LTL_Base;

class LTLEvalVisitor: public LTLlangBaseVisitor {
public:
	LTLEvalVisitor(const std::map<std::string, std::shared_ptr<TS::Proposition>> &Name2Prop_,
				   const std::map<std::shared_ptr<TS::Proposition>, std::shared_ptr<LTL_Base>> &Prop2LTL_,
				   const std::shared_ptr<LTL_Base> True_)
				   : Name2Prop(Name2Prop_), Prop2LTL(Prop2LTL_), True(True_), False(std::make_shared<LTL::Negation>(True_)){}

//	virtual std::any visitFormula_in_parentheses(LTLlangParser::Formula_in_parenthesesContext *ctx) override;

	virtual std::any visitLogicConstant(LTLlangParser::LogicConstantContext *ctx) override;

	virtual std::any visitLogic_formula(LTLlangParser::Logic_formulaContext *ctx) override;

	virtual std::any visitNot_formula(LTLlangParser::Not_formulaContext *ctx) override;

	virtual std::any visitG_formula(LTLlangParser::G_formulaContext *ctx) override;

	virtual std::any visitAtomic_proposition(LTLlangParser::Atomic_propositionContext *ctx) override;

	virtual std::any visitU_formula(LTLlangParser::U_formulaContext *ctx) override;

	virtual std::any visitX_formula(LTLlangParser::X_formulaContext *ctx) override;

	virtual std::any visitImplication_formula(LTLlangParser::Implication_formulaContext *ctx) override;

	virtual std::any visitF_formula(LTLlangParser::F_formulaContext *ctx) override;
private:
	const std::map<std::string, std::shared_ptr<TS::Proposition>> &Name2Prop;
	const std::map<std::shared_ptr<TS::Proposition>, std::shared_ptr<LTL_Base>> &Prop2LTL;
	const std::shared_ptr<LTL_Base> True;
	std::shared_ptr<LTL_Base> False;
};
}


#endif //THE_UNCONSOLED_LTLEVALVISITOR_HPP
