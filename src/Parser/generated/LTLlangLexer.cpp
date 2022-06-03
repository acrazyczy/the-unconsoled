
// Generated from LTLlang.g4 by ANTLR 4.10.1


#include "LTLlangLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct LTLlangLexerStaticData final {
  LTLlangLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LTLlangLexerStaticData(const LTLlangLexerStaticData&) = delete;
  LTLlangLexerStaticData(LTLlangLexerStaticData&&) = delete;
  LTLlangLexerStaticData& operator=(const LTLlangLexerStaticData&) = delete;
  LTLlangLexerStaticData& operator=(LTLlangLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag ltllanglexerLexerOnceFlag;
LTLlangLexerStaticData *ltllanglexerLexerStaticData = nullptr;

void ltllanglexerLexerInitialize() {
  assert(ltllanglexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<LTLlangLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "Identifier", 
      "AndOp", "OrOp", "True", "False", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,14,72,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,1,0,
  	1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,
  	8,1,9,1,9,1,9,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,13,4,13,67,8,13,11,13,12,13,68,1,13,1,13,0,0,14,1,1,
  	3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,1,0,
  	2,1,0,97,122,3,0,9,10,13,13,32,32,72,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,
  	0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,
  	17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,
  	0,0,0,1,29,1,0,0,0,3,31,1,0,0,0,5,33,1,0,0,0,7,35,1,0,0,0,9,37,1,0,0,
  	0,11,40,1,0,0,0,13,42,1,0,0,0,15,44,1,0,0,0,17,46,1,0,0,0,19,48,1,0,0,
  	0,21,51,1,0,0,0,23,54,1,0,0,0,25,59,1,0,0,0,27,66,1,0,0,0,29,30,5,33,
  	0,0,30,2,1,0,0,0,31,32,5,71,0,0,32,4,1,0,0,0,33,34,5,70,0,0,34,6,1,0,
  	0,0,35,36,5,88,0,0,36,8,1,0,0,0,37,38,5,45,0,0,38,39,5,62,0,0,39,10,1,
  	0,0,0,40,41,5,85,0,0,41,12,1,0,0,0,42,43,5,40,0,0,43,14,1,0,0,0,44,45,
  	5,41,0,0,45,16,1,0,0,0,46,47,7,0,0,0,47,18,1,0,0,0,48,49,5,47,0,0,49,
  	50,5,92,0,0,50,20,1,0,0,0,51,52,5,92,0,0,52,53,5,47,0,0,53,22,1,0,0,0,
  	54,55,5,116,0,0,55,56,5,114,0,0,56,57,5,117,0,0,57,58,5,101,0,0,58,24,
  	1,0,0,0,59,60,5,102,0,0,60,61,5,97,0,0,61,62,5,108,0,0,62,63,5,115,0,
  	0,63,64,5,101,0,0,64,26,1,0,0,0,65,67,7,1,0,0,66,65,1,0,0,0,67,68,1,0,
  	0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,70,1,0,0,0,70,71,6,13,0,0,71,28,1,
  	0,0,0,2,0,68,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ltllanglexerLexerStaticData = staticData.release();
}

}

LTLlangLexer::LTLlangLexer(CharStream *input) : Lexer(input) {
  LTLlangLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *ltllanglexerLexerStaticData->atn, ltllanglexerLexerStaticData->decisionToDFA, ltllanglexerLexerStaticData->sharedContextCache);
}

LTLlangLexer::~LTLlangLexer() {
  delete _interpreter;
}

std::string LTLlangLexer::getGrammarFileName() const {
  return "LTLlang.g4";
}

const std::vector<std::string>& LTLlangLexer::getRuleNames() const {
  return ltllanglexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& LTLlangLexer::getChannelNames() const {
  return ltllanglexerLexerStaticData->channelNames;
}

const std::vector<std::string>& LTLlangLexer::getModeNames() const {
  return ltllanglexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& LTLlangLexer::getVocabulary() const {
  return ltllanglexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LTLlangLexer::getSerializedATN() const {
  return ltllanglexerLexerStaticData->serializedATN;
}

const atn::ATN& LTLlangLexer::getATN() const {
  return *ltllanglexerLexerStaticData->atn;
}




void LTLlangLexer::initialize() {
  std::call_once(ltllanglexerLexerOnceFlag, ltllanglexerLexerInitialize);
}
