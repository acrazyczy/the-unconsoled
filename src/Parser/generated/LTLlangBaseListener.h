
// Generated from LTLlang.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "LTLlangListener.h"


/**
 * This class provides an empty implementation of LTLlangListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  LTLlangBaseListener : public LTLlangListener {
public:

  virtual void enterFormula_in_parentheses(LTLlangParser::Formula_in_parenthesesContext * /*ctx*/) override { }
  virtual void exitFormula_in_parentheses(LTLlangParser::Formula_in_parenthesesContext * /*ctx*/) override { }

  virtual void enterLogic_formula(LTLlangParser::Logic_formulaContext * /*ctx*/) override { }
  virtual void exitLogic_formula(LTLlangParser::Logic_formulaContext * /*ctx*/) override { }

  virtual void enterNot_formula(LTLlangParser::Not_formulaContext * /*ctx*/) override { }
  virtual void exitNot_formula(LTLlangParser::Not_formulaContext * /*ctx*/) override { }

  virtual void enterLogic_const(LTLlangParser::Logic_constContext * /*ctx*/) override { }
  virtual void exitLogic_const(LTLlangParser::Logic_constContext * /*ctx*/) override { }

  virtual void enterG_formula(LTLlangParser::G_formulaContext * /*ctx*/) override { }
  virtual void exitG_formula(LTLlangParser::G_formulaContext * /*ctx*/) override { }

  virtual void enterAtomic_proposition(LTLlangParser::Atomic_propositionContext * /*ctx*/) override { }
  virtual void exitAtomic_proposition(LTLlangParser::Atomic_propositionContext * /*ctx*/) override { }

  virtual void enterU_formula(LTLlangParser::U_formulaContext * /*ctx*/) override { }
  virtual void exitU_formula(LTLlangParser::U_formulaContext * /*ctx*/) override { }

  virtual void enterX_formula(LTLlangParser::X_formulaContext * /*ctx*/) override { }
  virtual void exitX_formula(LTLlangParser::X_formulaContext * /*ctx*/) override { }

  virtual void enterImplication_formula(LTLlangParser::Implication_formulaContext * /*ctx*/) override { }
  virtual void exitImplication_formula(LTLlangParser::Implication_formulaContext * /*ctx*/) override { }

  virtual void enterF_formula(LTLlangParser::F_formulaContext * /*ctx*/) override { }
  virtual void exitF_formula(LTLlangParser::F_formulaContext * /*ctx*/) override { }

  virtual void enterLogicConstant(LTLlangParser::LogicConstantContext * /*ctx*/) override { }
  virtual void exitLogicConstant(LTLlangParser::LogicConstantContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

