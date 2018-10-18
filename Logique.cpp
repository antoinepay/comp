/*
 * Logique.cpp
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#include "Logique.h"
#include "IR.h"
#include "Backend.h"
#include "compilateur.tab.h"

#include <string>
#include <vector>


Logique::Logique(int type, Expression * e1, Expression * e2) {
	// TODO Auto-generated constructor stub
	exp1 = e1;
	exp2 = e2;
	typeExp = type;
}

Logique::Logique(int type, Expression * e1) {
	// TODO Auto-generated constructor stub
	exp1 = e1;
	typeExp = type;
}

Logique::~Logique() {
	// TODO Auto-generated destructor stub
	delete exp1;
	delete exp2;
}

void Logique::print() {
	string symbole;
	switch(typeExp){
	case NOT :
		symbole = "!";
		break;
	case OUOU :
		symbole = "||";
		break;
	case ETET :
		symbole = "&&";
		break;
	}
	const char* s = symbole.c_str();
	if (exp2 == NULL){
		exp1->print();
		printf(" %s \n",s);
	}
	else{
		exp1->print();
		printf(" %s ",s);
		exp2->print();
	}

}

int Logique::getType(){
	return INT32;
}

string Logique::buildIR(CFG* cfg){
	vector<string> params;
	IRInstr::Operation t;
	switch(typeExp)
	{
		case NOT :
		{
			t = IRInstr::notq;
			break;
		}
		case OUOU :
		{
			t = IRInstr::orLog;
			break;
		}
		case ETET :
		{
			t = IRInstr::andLog;
			break;
		}
	}
	string reg = cfg->create_new_tempvar(symboleToType(exp1->getType()));
	string reg1 = exp1->buildIR(cfg);
	params.push_back(reg);
	if(exp2 == NULL)
	{
		params.push_back(reg1);
	}
	else
	{
		string reg2 = exp2->buildIR(cfg);
		params.push_back(reg1);
		params.push_back(reg2);
	}
	cfg->current_bb->add_IRInstr(t, Int32, params);
	return reg;
}
