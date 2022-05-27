#include <iostream>
#include <memory>

#include "antlr4-runtime.h"
#include "LTLlangLexer.h"
#include "LTLlangParser.h"

#include "LTLEvalVisitor.hpp"
#include "PowerSet.hpp"
#include "LTL.hpp"
#include "TS.hpp"
#include "BA.hpp"

int main()
{
	// bind stdin to file
	std::ifstream in("input.txt");
	std::cin.rdbuf(in.rdbuf());

	// bind stderr to file
	std::ofstream err("log.txt");
	std::cerr.rdbuf(err.rdbuf());

	// input TransitionSystem
	std::shared_ptr<TransitionSystem::TS> ts = std::make_shared<TransitionSystem::TS>();
	std::cin >> ts;

	// build the proposition mapping table
	std::map<std::string, std::shared_ptr<TransitionSystem::Proposition>> Name2Prop = std::move(ts -> get_Name2Prop());
	std::map<std::shared_ptr<TransitionSystem::Proposition>, std::shared_ptr<LTL::LTL_Base>> Prop2LTL;
	std::vector<std::shared_ptr<LTL::LTL_Base>> PropLTLs;
	for (auto [name, prop]: Name2Prop) {
		std::shared_ptr<LTL::LTL_Base> ltl(new LTL::Variable(prop));
		PropLTLs.emplace_back(ltl), Prop2LTL.emplace(prop, ltl);
	}
	std::shared_ptr<LTL::LTL_Base> True(new LTL::LTL_Base);

	// input LTL formula
	antlr4::ANTLRInputStream input(std::cin);
	LTLlangLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	tokens.fill();
	LTLlangParser parser(&tokens);
	antlr4::tree::ParseTree* tree = parser.formula();
	Parser::LTLEvalVisitor visitor(Name2Prop, Prop2LTL, True);
	std::shared_ptr<LTL::LTL_Base> root = std::any_cast<std::shared_ptr<LTL::LTL_Base>>(visitor.visit(tree));
	std::shared_ptr<LTL::LTL_Base> LTL_root;
	if (instanceof<LTL::Negation>(root)) LTL_root = *root -> get_children().begin();
	else LTL_root = std::make_shared<LTL::Negation>(root);

	// build the symbol mapping table
	PowerSet<LTL::LTL_Base> PropLTLs_power_set(PropLTLs);
	std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> LTL2Symbol;

	// convert LTL formula to GNBA
	std::shared_ptr<BuechiAutomata::GNBA> gnba = std::make_shared<BuechiAutomata::GNBA>(LTL_root, LTL2Symbol, PropLTLs_power_set, True);
	gnba -> make_nonblocking();

	// convert GNBA to NBA
	std::shared_ptr<BuechiAutomata::NBA> nba(new BuechiAutomata::NBA(gnba));

	// construction production of TransitionSystem and NBA
	std::shared_ptr<TransitionSystem::TS> production = TransitionSystem::product(ts, nba, LTL2Symbol, Prop2LTL, PropLTLs_power_set);

	// testing LTL property
	std::vector<std::shared_ptr<TransitionSystem::Proposition>> AP = ts -> get_AP();
	bool result = production -> persistence_checking(std::set<std::shared_ptr<TransitionSystem::Proposition>>(AP.begin(), AP.end()));

	if (result) std::cout << "TransitionSystem models varphi." << std::endl;
	else std::cout << "TransitionSystem doesn't model varphi." << std::endl;

	return 0;
}
