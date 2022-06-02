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

	size_t Q0, Q1;
	std::vector<int> qtmp;
	read_data_from_a_line(std::cin, qtmp), Q0 = qtmp.front(), Q1 = qtmp.back();

	for (size_t q = 0, src;q < Q0 + Q1;++ q) {
		// input LTL formula
		std::string formula;
		if (q >= Q0) std::cin >> src;
		std::getline(std::cin, formula);
		std::istringstream formula_stream(formula);
		antlr4::ANTLRInputStream input(formula_stream);
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

		// convert LTL formula to GNBA
		std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::Symbol>> LTL2Symbol;
		std::map<std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>, std::shared_ptr<BuechiAutomata::State>> set2gnba_state;
		std::shared_ptr<BuechiAutomata::GNBA> gnba = std::make_shared<BuechiAutomata::GNBA>(LTL_root, LTL2Symbol, set2gnba_state, PropLTLs_power_set, True);

		std::map<std::shared_ptr<BuechiAutomata::Symbol>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> Symbol2LTL;
		for (auto [set, symbol]: LTL2Symbol) Symbol2LTL.emplace(symbol, set);
		std::map<std::shared_ptr<BuechiAutomata::State>, std::shared_ptr<std::set<std::shared_ptr<LTL::LTL_Base>>>> gnba_state2set;
		for (auto [set, state]: set2gnba_state) gnba_state2set.emplace(state, set);

		std::cerr << BuechiAutomata::to_string(gnba, gnba_state2set, Symbol2LTL) << std::endl << std::endl;

		std::shared_ptr<BuechiAutomata::State> trap = gnba -> make_nonblocking();
		gnba_state2set.emplace(trap, std::make_shared<std::set<std::shared_ptr<LTL::LTL_Base>>>());

		// convert GNBA to NBA
		std::map<std::shared_ptr<BuechiAutomata::State>, std::pair<std::shared_ptr<BuechiAutomata::State>, size_t>> nba_state2gnba_state;
		std::shared_ptr<BuechiAutomata::NBA> nba(new BuechiAutomata::NBA(gnba, nba_state2gnba_state));
		std::cerr << BuechiAutomata::to_string(nba, gnba_state2set, nba_state2gnba_state, Symbol2LTL) << std::endl << std::endl;

		// construction production of TransitionSystem and NBA
		std::map<std::shared_ptr<TransitionSystem::State>, std::pair<std::shared_ptr<TransitionSystem::State>, std::shared_ptr<BuechiAutomata::State>>> s2s_nba_state;
		std::set<std::shared_ptr<TransitionSystem::Proposition>> F_props;
		std::shared_ptr<TransitionSystem::TS> production = TransitionSystem::product(ts, nba, LTL2Symbol, Prop2LTL, PropLTLs_power_set, F_props, s2s_nba_state);
		std::cerr << TransitionSystem::to_string(production, Symbol2LTL, s2s_nba_state, nba_state2gnba_state, gnba_state2set) << std::endl << std::endl;

		// testing LTL property
		bool result;
		if (q < Q0) result = production -> persistence_checking(F_props);
		else {
			std::shared_ptr<TransitionSystem::State> src_s = ts -> get_state(src);
			std::map<std::pair<std::shared_ptr<TransitionSystem::State>, std::shared_ptr<BuechiAutomata::State>>, std::shared_ptr<TransitionSystem::State>> s_nba_state2s;
			for (auto [s, s_nba_state]: s2s_nba_state) s_nba_state2s. emplace(s_nba_state, s);
			std::set<std::shared_ptr<TransitionSystem::State>> entries = std::move(TransitionSystem::get_entries(src_s, ts, nba, LTL2Symbol, Prop2LTL, PropLTLs_power_set, s_nba_state2s));
			result = production -> persistence_checking(F_props, entries);
		}

		if (result) std::cout << "TransitionSystem models varphi." << std::endl;
		else std::cout << "TransitionSystem doesn't model varphi." << std::endl;
	}

	return 0;
}
