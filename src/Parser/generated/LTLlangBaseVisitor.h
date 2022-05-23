
// Generated from LTLlang.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "LTLlangVisitor.h"


/**
 * This class provides an empty implementation of LTLlangVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LTLlangBaseVisitor : public LTLlangVisitor {
public:

  virtual std::any visitFormula_in_parentheses(LTLlangParser::Formula_in_parenthesesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogic_formula(LTLlangParser::Logic_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNot_formula(LTLlangParser::Not_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogic_const(LTLlangParser::Logic_constContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitG_formula(LTLlangParser::G_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAtomic_proposition(LTLlangParser::Atomic_propositionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitU_formula(LTLlangParser::U_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitX_formula(LTLlangParser::X_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImplication_formula(LTLlangParser::Implication_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitF_formula(LTLlangParser::F_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicConstant(LTLlangParser::LogicConstantContext *ctx) override {
    return visitChildren(ctx);
  }


};

