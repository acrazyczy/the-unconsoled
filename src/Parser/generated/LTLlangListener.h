
// Generated from LTLlang.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "LTLlangParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by LTLlangParser.
 */
class  LTLlangListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFormula_in_parentheses(LTLlangParser::Formula_in_parenthesesContext *ctx) = 0;
  virtual void exitFormula_in_parentheses(LTLlangParser::Formula_in_parenthesesContext *ctx) = 0;

  virtual void enterLogic_formula(LTLlangParser::Logic_formulaContext *ctx) = 0;
  virtual void exitLogic_formula(LTLlangParser::Logic_formulaContext *ctx) = 0;

  virtual void enterNot_formula(LTLlangParser::Not_formulaContext *ctx) = 0;
  virtual void exitNot_formula(LTLlangParser::Not_formulaContext *ctx) = 0;

  virtual void enterLogic_const(LTLlangParser::Logic_constContext *ctx) = 0;
  virtual void exitLogic_const(LTLlangParser::Logic_constContext *ctx) = 0;

  virtual void enterG_formula(LTLlangParser::G_formulaContext *ctx) = 0;
  virtual void exitG_formula(LTLlangParser::G_formulaContext *ctx) = 0;

  virtual void enterAtomic_proposition(LTLlangParser::Atomic_propositionContext *ctx) = 0;
  virtual void exitAtomic_proposition(LTLlangParser::Atomic_propositionContext *ctx) = 0;

  virtual void enterU_formula(LTLlangParser::U_formulaContext *ctx) = 0;
  virtual void exitU_formula(LTLlangParser::U_formulaContext *ctx) = 0;

  virtual void enterX_formula(LTLlangParser::X_formulaContext *ctx) = 0;
  virtual void exitX_formula(LTLlangParser::X_formulaContext *ctx) = 0;

  virtual void enterImplication_formula(LTLlangParser::Implication_formulaContext *ctx) = 0;
  virtual void exitImplication_formula(LTLlangParser::Implication_formulaContext *ctx) = 0;

  virtual void enterF_formula(LTLlangParser::F_formulaContext *ctx) = 0;
  virtual void exitF_formula(LTLlangParser::F_formulaContext *ctx) = 0;

  virtual void enterLogicConstant(LTLlangParser::LogicConstantContext *ctx) = 0;
  virtual void exitLogicConstant(LTLlangParser::LogicConstantContext *ctx) = 0;


};

