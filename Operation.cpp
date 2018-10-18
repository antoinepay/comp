/*
 * Operation.cpp
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#include "Operation.h"
#include "compilateur.tab.h"
#include "IR.h"
#include "Backend.h"
#include <vector>

Operation::Operation(int type, Expression * e1, Expression * e2) {
	// TODO Auto-generated constructor stub
	exp1 = e1;
	exp2 = e2;
	typeExp = type;
}

Operation::Operation(int type, Variable* v)
{
	exp2 = v;
	typeExp = type;
}


Operation::~Operation() {
	// TODO Auto-generated destructor stub
	if(exp1 != NULL)
	{
		delete exp1;
	}
	if(exp2 != NULL)
	{
		delete exp2;
	}
}

void Operation::print() {
	char symbole;
	switch(typeExp){
	case PLUS :
		symbole = '+';
		break;
	case MOINS :
		symbole = '-';
		break;
	case MUL :
		symbole = '*';
		break;
	case DIV :
		symbole = '/';
		break;
	case MODULO :
		symbole = '%';
		break;
	}
	if(exp1 != NULL)
	{
		exp1->print();
	}
	printf(" %c ",symbole);
	exp2->print();
}

int Operation::getType(){
	return INT32;
}

string Operation::buildIR(CFG* cfg){
	IRInstr::Operation t;
	switch(typeExp){
	case PLUS :
		t = IRInstr::add;
		break;
	case MOINS :
		t = IRInstr::sub;
		break;
	case MUL :
		t = IRInstr::mul;
		break;
	case DIV :
		t = IRInstr::div;
		break;
	case MODULO :
		t = IRInstr::mod;
		break;
	}
	if(exp1 == NULL)
	{// cas d'une variable négative ( -b par exemple)
		string reg = cfg->create_new_tempvar(symboleToType(exp2->getType()));
		string reg1 = exp2->buildIR(cfg);
		vector<string> params1;
		params1.push_back(reg);
		params1.push_back(reg1);
		cfg->current_bb->add_IRInstr(IRInstr::neg, symboleToType(exp2->getType()), params1);
		return reg;
	}
	else
	{//operation classique (a+1,2*4,...)
		string reg = cfg->create_new_tempvar(symboleToType(exp1->getType()));
		string reg1 = exp1->buildIR(cfg);
		string reg2 = exp2->buildIR(cfg);
		vector<string> params;
		params.push_back(reg);
		params.push_back(reg1);
		params.push_back(reg2);
		cfg->current_bb->add_IRInstr(t, symboleToType(exp2->getType()), params);
		return reg;
	}
}
