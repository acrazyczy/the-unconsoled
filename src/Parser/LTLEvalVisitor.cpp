//
// Created by crazy_cloud on 2022/5/23.
// @formatter:off
//

#include "LTLEvalVisitor.hpp"

namespace Parser {
std::any LTLEvalVisitor::visitFormula_in_parentheses(LTLlangParser::Formula_in_parenthesesContext *ctx) {
	return visit(ctx -> formula());
}

std::any LTLEvalVisitor::visitLogicConstant(LTLlangParser::LogicConstantContext *ctx) {
	return ctx -> True() != nullptr ? True : False;
}

std::any LTLEvalVisitor::visitLogic_formula(LTLlangParser::Logic_formulaContext *ctx) {
	std::shared_ptr<LTL_Base>
	    lhs = std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula().at(0))),
		rhs = std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula().at(1)));
	std::shared_ptr<LTL_Base> not_lhs, not_rhs;
	if (instanceof<LTL::Negation>(lhs)) not_lhs = lhs -> get_children().front();
	else not_lhs = std::make_shared<LTL::Negation>(lhs);
	if (instanceof<LTL::Negation>(rhs)) not_rhs = rhs -> get_children().front();
	else not_rhs = std::make_shared<LTL::Negation>(rhs);
	if (ctx -> AndOp() != nullptr)
		return std::dynamic_pointer_cast<LTL::LTL_Base>(std::make_shared<LTL::And>(lhs, rhs));
	else
		return std::dynamic_pointer_cast<LTL::LTL_Base>(std::make_shared<LTL::Negation>(std::make_shared<LTL::And>(not_lhs, not_rhs)));
}

std::any LTLEvalVisitor::visitNot_formula(LTLlangParser::Not_formulaContext *ctx) {
	std::shared_ptr<LTL_Base> val = std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula()));
	if (instanceof<LTL::Negation>(val)) return val -> get_children().front();
	else return std::dynamic_pointer_cast<LTL::LTL_Base>(std::make_shared<LTL::Negation>(val));
}

std::any LTLEvalVisitor::visitG_formula(LTLlangParser::G_formulaContext *ctx) {
	std::shared_ptr<LTL_Base> val = std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula()));
	std::shared_ptr<LTL_Base> not_child;
	if (instanceof<LTL::Negation>(val)) not_child = val -> get_children().front();
	else not_child = std::make_shared<LTL::Negation>(val);
	return std::dynamic_pointer_cast<LTL::LTL_Base>(std::make_shared<LTL::Negation>(std::make_shared<LTL::Until>(True, not_child)));
}

std::any LTLEvalVisitor::visitAtomic_proposition(LTLlangParser::Atomic_propositionContext *ctx) {
	return Prop2LTL.at(Name2Prop.at(ctx -> getText()));
}

std::any LTLEvalVisitor::visitU_formula(LTLlangParser::U_formulaContext *ctx) {
	return std::dynamic_pointer_cast<LTL::LTL_Base>(std::make_shared<LTL::Until>(
		std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula().at(0))),
		std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula().at(1)))
	));
}

std::any LTLEvalVisitor::visitX_formula(LTLlangParser::X_formulaContext *ctx) {
	return std::dynamic_pointer_cast<LTL::LTL_Base>(std::make_shared<LTL::Next>(std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula()))));
}

std::any LTLEvalVisitor::visitImplication_formula(LTLlangParser::Implication_formulaContext *ctx) {
	std::shared_ptr<LTL_Base> lhs = std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula().at(0))),
		rhs = std::any_cast<std::shared_ptr<LTL_Base>>(visit(ctx -> formula().at(1)));
	std::shared_ptr<LTL_Base> not_rhs;
	if (instanceof<LTL::Negation>(rhs)) not_rhs = rhs -> get_children().front();
	else not_rhs = std::make_shared<LTL::Negation>(rhs);
	return std::dynamic_pointer_cast<LTL::LTL_Base>(std::make_shared<LTL::Negation>(std::make_shared<LTL::And>(lhs, not_rhs)));
}

std::any LTLEvalVisitor::visitF_formula(LTLlangParser::F_formulaContext *ctx) {
	std::any tmp = visit(ctx -> formula());
	return std::dynamic_pointer_cast<LTL::LTL_Base>(std::make_shared<LTL::Until>(True, std::any_cast<std::shared_ptr<LTL_Base>>(tmp)));
}

}