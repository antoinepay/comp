/*
 * Comparaison.cpp
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#include "Comparaison.h"
#include "compilateur.tab.h"
#include "IR.h"
#include "Backend.h"

#include <string>
#include <vector>

Comparaison::Comparaison(int type, Expression * e1, Expression * e2) {
	// TODO Auto-generated constructor stub
	exp1 = e1;
	exp2 = e2;
	typeExp = type;

}

Comparaison::~Comparaison() {
	// TODO Auto-generated destructor stub
	delete exp1;
	delete exp2;
}

int Comparaison::getType()
{
	return INT32;
}

void Comparaison::print() {
	string symbole;
	switch(typeExp){
	case EGALEGAL :
		symbole = "==";
		break;
	case INFERIEUREGAL :
		symbole = "<=" ;
		break;
	case SUPERIEUREGAL :
		symbole = ">=" ;
		break;
	case NOTEGAL :
		symbole = "!=" ;
		break;
	case SUPERIEUR :
		symbole = ">" ;
		break;
	case INFERIEUR :
		symbole = "<";
		break;
	}
	exp1->print();
	const char* s = symbole.c_str();
	printf(" %s ",s);
	exp2->print();
}

string Comparaison::buildIR(CFG* cfg){
	string reg = cfg->create_new_tempvar(symboleToType(exp1->getType()));
	string reg1 = exp1->buildIR(cfg);
	string reg2 = exp2->buildIR(cfg);
	vector<string> params;
	params.push_back(reg1);
	params.push_back(reg2);
	cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp, Int32, params);
	switch(typeExp)
	{
		case EGALEGAL :
		{
			vector<string> params2;
			params2.push_back(reg);
			params2.push_back("$1");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmove, Int32, params2);
			vector<string> params3;
			params3.push_back(reg);
			params3.push_back("$0");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmovene, Int32, params3);
			break;
		}
		case INFERIEUREGAL :
		{
			vector<string> params2;
			params2.push_back(reg);
			params2.push_back("$1");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmovele, Int32, params2);
			vector<string> params3;
			params3.push_back(reg);
			params3.push_back("$0");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmoveg, Int32, params3);
			break;
		}
		case SUPERIEUREGAL :
		{
			vector<string> params2;
			params2.push_back(reg);
			params2.push_back("$1");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmovege, Int32, params2);
			vector<string> params3;
			params3.push_back(reg);
			params3.push_back("$0");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmovel, Int32, params3);
			break;
		}
		case NOTEGAL :
		{
			vector<string> params2;
			params2.push_back(reg);
			params2.push_back("$1");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmovene, Int32, params2);
			vector<string> params3;
			params3.push_back(reg);
			params3.push_back("$0");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmove, Int32, params3);
			break;
		}
		case SUPERIEUR :
		{
			vector<string> params2;
			params2.push_back(reg);
			params2.push_back("$1");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmoveg, Int32, params2);
			vector<string> params3;
			params3.push_back(reg);
			params3.push_back("$0");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmovele, Int32, params3);
			break;
		}
		case INFERIEUR :
		{
			vector<string> params2;
			params2.push_back(reg);
			params2.push_back("$1");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmovel, Int32, params2);
			vector<string> params3;
			params3.push_back(reg);
			params3.push_back("$0");
			cfg->current_bb->add_IRInstr(IRInstr::Operation::cmovege, Int32, params3);
			break;
		}
	}
    return reg;
}
