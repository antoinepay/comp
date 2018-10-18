/*
 * Affectation.cpp
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#include "Affectation.h"
#include "compilateur.tab.h"
#include "Backend.h"
#include <string>

Affectation::Affectation(Variable* var, int type , Expression * e1, Expression * e2) {
	// TODO Auto-generated constructor stub
	exp1 = e1;
	exp2 = e2;
	variable = var;
	typeExp = type;

}

Affectation::Affectation(Variable* var, int type , Expression * e1) {
	// TODO Auto-generated constructor stub
	exp1 = e1;
	variable = var;
	typeExp = type;

}

Affectation::Affectation(Variable* var, int type, int cas2) {
	variable = var;
	typeExp = type;
	cas = cas2;
}

Affectation::~Affectation() {
	// TODO Auto-generated destructor stub
	if(exp1 != NULL){
		delete exp1;
	}
	if(exp2 != NULL){
		delete exp2;
	}
	delete variable;
}


void Affectation::print() {
	string symbole;
	switch(typeExp){
	case PLUSPLUS :
		symbole = "++";
		break;
	case MOINSMOINS :
		symbole = "--";
		break;
	case PLUSEGAL :
		symbole = "+=";
		break;
	case MOINSEGAL :
		symbole = "-=";
		break;
	case MULEGAL :
		symbole = "*=";
		break;
	case DIVEGAL :
		symbole = "/=";
		break;
	case MODULOEGAL :
		symbole = "%=";
		break;
	case EGAL :
		symbole = "=";
		break;
	}
	const char* s = symbole.c_str();
	if (exp2 == NULL && exp1 == NULL){
		if(cas == 0)
		{
			variable->print();
			printf("%s",s);
		}
		else
		{
			printf("%s",s);
			variable->print();
		}

	}
	else if (exp2 == NULL ) {
		if (typeExp == PLUSPLUS || typeExp == MOINSMOINS) {
			variable->print();
			printf("[");
			exp1->print();
			printf("]%s",s);
		}
		else {
			variable->print();
			printf(" %s ",s);
			exp1->print();
		}
	}
	else {
		variable->print();
		printf("[");
		exp1->print();
		printf("]%s",s);
		exp2->print();
	}
}

int Affectation::getType(){
	return variable->getType();
}

string Affectation::buildIR(CFG* cfg){
	if (exp2 == NULL && exp1 == NULL){ //incrementation d'une variable normale
		if(cas == 0) // var++
		{
			IRInstr::Operation t;
			if(typeExp == PLUSPLUS)
			{
				t = IRInstr::incq;
			}
			else
			{
				t = IRInstr::decq;
			}
			string reg = cfg->create_new_tempvar(symboleToType(variable->getType()));
			string reg1 = variable->buildIR(cfg);
			vector<string> params2;
			params2.push_back(reg);
			params2.push_back(reg1);
			cfg->current_bb->add_IRInstr(IRInstr::movq, symboleToType(variable->getType()), params2);
			vector<string> params;
			params.push_back(reg1);
			cfg->current_bb->add_IRInstr(t, symboleToType(variable->getType()), params);
			return reg;
		}
		else // ++var
		{
			IRInstr::Operation t;
			if(typeExp == PLUSPLUS)
			{
				t = IRInstr::incq;
			}
			else
			{
				t = IRInstr::decq;
			}
			string reg = variable->buildIR(cfg);
			vector<string> params;
			params.push_back(reg);
			cfg->current_bb->add_IRInstr(t, symboleToType(variable->getType()), params);
			return reg;
		}
	}
	else if (exp2 == NULL ) {
		if (typeExp == PLUSPLUS || typeExp == MOINSMOINS) { //incrementation d'une variable tableau
			return "";
		}
		else {// affectation d'une expression a une variable normale
			string right = exp1->buildIR(cfg);
			string left = variable->buildIR_Lvalue(cfg);
			string var = variable->buildIR(cfg);
			string reg = right;
			switch(typeExp){
				case PLUSEGAL :
				{
					reg = cfg->create_new_tempvar(symboleToType(typeExp));
					vector<string> params;
					params.push_back(reg);
					params.push_back(var);
					params.push_back(right);
					cfg->current_bb->add_IRInstr(IRInstr::add, symboleToType(typeExp), params);
					break;
				}
				case MOINSEGAL :
				{
					reg = cfg->create_new_tempvar(symboleToType(typeExp));
					vector<string> params;
					params.push_back(reg);
					params.push_back(var);
					params.push_back(right);
					cfg->current_bb->add_IRInstr(IRInstr::sub, symboleToType(typeExp), params);
					break;
				}
				case MULEGAL :
				{
					reg = cfg->create_new_tempvar(symboleToType(typeExp));
					vector<string> params;
					params.push_back(reg);
					params.push_back(var);
					params.push_back(right);
					cfg->current_bb->add_IRInstr(IRInstr::mul, symboleToType(typeExp), params);
					break;
				}
				case DIVEGAL :
				{
					reg = cfg->create_new_tempvar(symboleToType(typeExp));
					vector<string> params;
					params.push_back(reg);
					params.push_back(var);
					params.push_back(right);
					cfg->current_bb->add_IRInstr(IRInstr::div, symboleToType(typeExp), params);
					break;
				}
				case MODULOEGAL :
				{
					reg = cfg->create_new_tempvar(symboleToType(typeExp));
					vector<string> params;
					params.push_back(reg);
					params.push_back(var);
					params.push_back(right);
					cfg->current_bb->add_IRInstr(IRInstr::mod, symboleToType(typeExp), params);
					break;
				}
				default :
				{
					break;
				}
			}
			vector<string> params;
			params.push_back(left);
			params.push_back(reg);
			cfg->current_bb->add_IRInstr(IRInstr::wmem, symboleToType(typeExp), params);
			return reg;
		}
	}
	else {
		//affectation d'une expression a une variable tableau
		return "";
	}
    return "";
}
