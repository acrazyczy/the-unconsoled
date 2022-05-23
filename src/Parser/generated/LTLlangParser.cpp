
// Generated from LTLlang.g4 by ANTLR 4.10.1


#include "LTLlangListener.h"
#include "LTLlangVisitor.h"

#include "LTLlangParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct LTLlangParserStaticData final {
  LTLlangParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LTLlangParserStaticData(const LTLlangParserStaticData&) = delete;
  LTLlangParserStaticData(LTLlangParserStaticData&&) = delete;
  LTLlangParserStaticData& operator=(const LTLlangParserStaticData&) = delete;
  LTLlangParserStaticData& operator=(LTLlangParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag ltllangParserOnceFlag;
LTLlangParserStaticData *ltllangParserStaticData = nullptr;

void ltllangParserInitialize() {
  assert(ltllangParserStaticData == nullptr);
  auto staticData = std::make_unique<LTLlangParserStaticData>(
    std::vector<std::string>{
      "formula", "logicConstant"
    },
    std::vector<std::string>{
      "", "'!'", "'G'", "'F'", "'X'", "'->'", "'U'", "'('", "')'", "", "'/\\'", 
      "'\\/'", "'true'", "'false'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "Identifier", "AndOp", "OrOp", 
      "True", "False", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,14,37,2,0,7,0,2,1,7,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
  	1,0,1,0,1,0,1,0,1,0,1,0,3,0,22,8,0,1,0,1,0,1,0,1,0,1,0,1,0,5,0,30,8,0,
  	10,0,12,0,33,9,0,1,1,1,1,1,1,0,1,0,2,0,2,0,2,1,0,10,11,1,0,12,13,43,0,
  	21,1,0,0,0,2,34,1,0,0,0,4,5,6,0,-1,0,5,6,5,1,0,0,6,22,3,0,0,10,7,8,5,
  	2,0,0,8,22,3,0,0,9,9,10,5,3,0,0,10,22,3,0,0,8,11,12,5,4,0,0,12,22,3,0,
  	0,7,13,14,5,5,0,0,14,22,3,0,0,5,15,22,3,2,1,0,16,22,5,9,0,0,17,18,5,7,
  	0,0,18,19,3,0,0,0,19,20,5,8,0,0,20,22,1,0,0,0,21,4,1,0,0,0,21,7,1,0,0,
  	0,21,9,1,0,0,0,21,11,1,0,0,0,21,13,1,0,0,0,21,15,1,0,0,0,21,16,1,0,0,
  	0,21,17,1,0,0,0,22,31,1,0,0,0,23,24,10,6,0,0,24,25,7,0,0,0,25,30,3,0,
  	0,7,26,27,10,4,0,0,27,28,5,6,0,0,28,30,3,0,0,5,29,23,1,0,0,0,29,26,1,
  	0,0,0,30,33,1,0,0,0,31,29,1,0,0,0,31,32,1,0,0,0,32,1,1,0,0,0,33,31,1,
  	0,0,0,34,35,7,1,0,0,35,3,1,0,0,0,3,21,29,31
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ltllangParserStaticData = staticData.release();
}

}

LTLlangParser::LTLlangParser(TokenStream *input) : LTLlangParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

LTLlangParser::LTLlangParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  LTLlangParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ltllangParserStaticData->atn, ltllangParserStaticData->decisionToDFA, ltllangParserStaticData->sharedContextCache, options);
}

LTLlangParser::~LTLlangParser() {
  delete _interpreter;
}

const atn::ATN& LTLlangParser::getATN() const {
  return *ltllangParserStaticData->atn;
}

std::string LTLlangParser::getGrammarFileName() const {
  return "LTLlang.g4";
}

const std::vector<std::string>& LTLlangParser::getRuleNames() const {
  return ltllangParserStaticData->ruleNames;
}

const dfa::Vocabulary& LTLlangParser::getVocabulary() const {
  return ltllangParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LTLlangParser::getSerializedATN() const {
  return ltllangParserStaticData->serializedATN;
}


//----------------- FormulaContext ------------------------------------------------------------------

LTLlangParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LTLlangParser::FormulaContext::getRuleIndex() const {
  return LTLlangParser::RuleFormula;
}

void LTLlangParser::FormulaContext::copyFrom(FormulaContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Formula_in_parenthesesContext ------------------------------------------------------------------

LTLlangParser::FormulaContext* LTLlangParser::Formula_in_parenthesesContext::formula() {
  return getRuleContext<LTLlangParser::FormulaContext>(0);
}

LTLlangParser::Formula_in_parenthesesContext::Formula_in_parenthesesContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::Formula_in_parenthesesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormula_in_parentheses(this);
}
void LTLlangParser::Formula_in_parenthesesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormula_in_parentheses(this);
}

std::any LTLlangParser::Formula_in_parenthesesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitFormula_in_parentheses(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Logic_formulaContext ------------------------------------------------------------------

std::vector<LTLlangParser::FormulaContext *> LTLlangParser::Logic_formulaContext::formula() {
  return getRuleContexts<LTLlangParser::FormulaContext>();
}

LTLlangParser::FormulaContext* LTLlangParser::Logic_formulaContext::formula(size_t i) {
  return getRuleContext<LTLlangParser::FormulaContext>(i);
}

tree::TerminalNode* LTLlangParser::Logic_formulaContext::AndOp() {
  return getToken(LTLlangParser::AndOp, 0);
}

tree::TerminalNode* LTLlangParser::Logic_formulaContext::OrOp() {
  return getToken(LTLlangParser::OrOp, 0);
}

LTLlangParser::Logic_formulaContext::Logic_formulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::Logic_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic_formula(this);
}
void LTLlangParser::Logic_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic_formula(this);
}

std::any LTLlangParser::Logic_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitLogic_formula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Not_formulaContext ------------------------------------------------------------------

LTLlangParser::FormulaContext* LTLlangParser::Not_formulaContext::formula() {
  return getRuleContext<LTLlangParser::FormulaContext>(0);
}

LTLlangParser::Not_formulaContext::Not_formulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::Not_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNot_formula(this);
}
void LTLlangParser::Not_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNot_formula(this);
}

std::any LTLlangParser::Not_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitNot_formula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Logic_constContext ------------------------------------------------------------------

LTLlangParser::LogicConstantContext* LTLlangParser::Logic_constContext::logicConstant() {
  return getRuleContext<LTLlangParser::LogicConstantContext>(0);
}

LTLlangParser::Logic_constContext::Logic_constContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::Logic_constContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic_const(this);
}
void LTLlangParser::Logic_constContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic_const(this);
}

std::any LTLlangParser::Logic_constContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitLogic_const(this);
  else
    return visitor->visitChildren(this);
}
//----------------- G_formulaContext ------------------------------------------------------------------

LTLlangParser::FormulaContext* LTLlangParser::G_formulaContext::formula() {
  return getRuleContext<LTLlangParser::FormulaContext>(0);
}

LTLlangParser::G_formulaContext::G_formulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::G_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterG_formula(this);
}
void LTLlangParser::G_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitG_formula(this);
}

std::any LTLlangParser::G_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitG_formula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Atomic_propositionContext ------------------------------------------------------------------

tree::TerminalNode* LTLlangParser::Atomic_propositionContext::Identifier() {
  return getToken(LTLlangParser::Identifier, 0);
}

LTLlangParser::Atomic_propositionContext::Atomic_propositionContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::Atomic_propositionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtomic_proposition(this);
}
void LTLlangParser::Atomic_propositionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtomic_proposition(this);
}

std::any LTLlangParser::Atomic_propositionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitAtomic_proposition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- U_formulaContext ------------------------------------------------------------------

std::vector<LTLlangParser::FormulaContext *> LTLlangParser::U_formulaContext::formula() {
  return getRuleContexts<LTLlangParser::FormulaContext>();
}

LTLlangParser::FormulaContext* LTLlangParser::U_formulaContext::formula(size_t i) {
  return getRuleContext<LTLlangParser::FormulaContext>(i);
}

LTLlangParser::U_formulaContext::U_formulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::U_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterU_formula(this);
}
void LTLlangParser::U_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitU_formula(this);
}

std::any LTLlangParser::U_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitU_formula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- X_formulaContext ------------------------------------------------------------------

LTLlangParser::FormulaContext* LTLlangParser::X_formulaContext::formula() {
  return getRuleContext<LTLlangParser::FormulaContext>(0);
}

LTLlangParser::X_formulaContext::X_formulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::X_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterX_formula(this);
}
void LTLlangParser::X_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitX_formula(this);
}

std::any LTLlangParser::X_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitX_formula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Implication_formulaContext ------------------------------------------------------------------

LTLlangParser::FormulaContext* LTLlangParser::Implication_formulaContext::formula() {
  return getRuleContext<LTLlangParser::FormulaContext>(0);
}

LTLlangParser::Implication_formulaContext::Implication_formulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::Implication_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImplication_formula(this);
}
void LTLlangParser::Implication_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImplication_formula(this);
}

std::any LTLlangParser::Implication_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitImplication_formula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- F_formulaContext ------------------------------------------------------------------

LTLlangParser::FormulaContext* LTLlangParser::F_formulaContext::formula() {
  return getRuleContext<LTLlangParser::FormulaContext>(0);
}

LTLlangParser::F_formulaContext::F_formulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLlangParser::F_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterF_formula(this);
}
void LTLlangParser::F_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitF_formula(this);
}

std::any LTLlangParser::F_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitF_formula(this);
  else
    return visitor->visitChildren(this);
}

LTLlangParser::FormulaContext* LTLlangParser::formula() {
   return formula(0);
}

LTLlangParser::FormulaContext* LTLlangParser::formula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LTLlangParser::FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, parentState);
  LTLlangParser::FormulaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 0;
  enterRecursionRule(_localctx, 0, LTLlangParser::RuleFormula, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(21);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LTLlangParser::T__0: {
        _localctx = _tracker.createInstance<Not_formulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(5);
        match(LTLlangParser::T__0);
        setState(6);
        formula(10);
        break;
      }

      case LTLlangParser::T__1: {
        _localctx = _tracker.createInstance<G_formulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(7);
        match(LTLlangParser::T__1);
        setState(8);
        formula(9);
        break;
      }

      case LTLlangParser::T__2: {
        _localctx = _tracker.createInstance<F_formulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(9);
        match(LTLlangParser::T__2);
        setState(10);
        formula(8);
        break;
      }

      case LTLlangParser::T__3: {
        _localctx = _tracker.createInstance<X_formulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(11);
        match(LTLlangParser::T__3);
        setState(12);
        formula(7);
        break;
      }

      case LTLlangParser::T__4: {
        _localctx = _tracker.createInstance<Implication_formulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(13);
        match(LTLlangParser::T__4);
        setState(14);
        formula(5);
        break;
      }

      case LTLlangParser::True:
      case LTLlangParser::False: {
        _localctx = _tracker.createInstance<Logic_constContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(15);
        logicConstant();
        break;
      }

      case LTLlangParser::Identifier: {
        _localctx = _tracker.createInstance<Atomic_propositionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(16);
        match(LTLlangParser::Identifier);
        break;
      }

      case LTLlangParser::T__6: {
        _localctx = _tracker.createInstance<Formula_in_parenthesesContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(17);
        match(LTLlangParser::T__6);
        setState(18);
        formula(0);
        setState(19);
        match(LTLlangParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(31);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(29);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<Logic_formulaContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(23);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(24);
          antlrcpp::downCast<Logic_formulaContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == LTLlangParser::AndOp

          || _la == LTLlangParser::OrOp)) {
            antlrcpp::downCast<Logic_formulaContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(25);
          formula(7);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<U_formulaContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(26);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(27);
          match(LTLlangParser::T__5);
          setState(28);
          formula(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(33);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicConstantContext ------------------------------------------------------------------

LTLlangParser::LogicConstantContext::LogicConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LTLlangParser::LogicConstantContext::True() {
  return getToken(LTLlangParser::True, 0);
}

tree::TerminalNode* LTLlangParser::LogicConstantContext::False() {
  return getToken(LTLlangParser::False, 0);
}


size_t LTLlangParser::LogicConstantContext::getRuleIndex() const {
  return LTLlangParser::RuleLogicConstant;
}

void LTLlangParser::LogicConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicConstant(this);
}

void LTLlangParser::LogicConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLlangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicConstant(this);
}


std::any LTLlangParser::LogicConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLlangVisitor*>(visitor))
    return parserVisitor->visitLogicConstant(this);
  else
    return visitor->visitChildren(this);
}

LTLlangParser::LogicConstantContext* LTLlangParser::logicConstant() {
  LogicConstantContext *_localctx = _tracker.createInstance<LogicConstantContext>(_ctx, getState());
  enterRule(_localctx, 2, LTLlangParser::RuleLogicConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    _la = _input->LA(1);
    if (!(_la == LTLlangParser::True

    || _la == LTLlangParser::False)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool LTLlangParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 0: return formulaSempred(antlrcpp::downCast<FormulaContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LTLlangParser::formulaSempred(FormulaContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 6);
    case 1: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void LTLlangParser::initialize() {
  std::call_once(ltllangParserOnceFlag, ltllangParserInitialize);
}
