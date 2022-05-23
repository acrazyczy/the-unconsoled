
// Generated from LTLlang.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "LTLlangParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by LTLlangParser.
 */
class  LTLlangVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LTLlangParser.
   */
    virtual std::any visitFormula_in_parentheses(LTLlangParser::Formula_in_parenthesesContext *context) = 0;

    virtual std::any visitLogic_formula(LTLlangParser::Logic_formulaContext *context) = 0;

    virtual std::any visitNot_formula(LTLlangParser::Not_formulaContext *context) = 0;

    virtual std::any visitLogic_const(LTLlangParser::Logic_constContext *context) = 0;

    virtual std::any visitG_formula(LTLlangParser::G_formulaContext *context) = 0;

    virtual std::any visitAtomic_proposition(LTLlangParser::Atomic_propositionContext *context) = 0;

    virtual std::any visitU_formula(LTLlangParser::U_formulaContext *context) = 0;

    virtual std::any visitX_formula(LTLlangParser::X_formulaContext *context) = 0;

    virtual std::any visitImplication_formula(LTLlangParser::Implication_formulaContext *context) = 0;

    virtual std::any visitF_formula(LTLlangParser::F_formulaContext *context) = 0;

    virtual std::any visitLogicConstant(LTLlangParser::LogicConstantContext *context) = 0;


};

