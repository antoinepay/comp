

#include "Decla_variable.h"
#include <stdio.h>
#include "compilateur.tab.h"
#include "Backend.h"

Decla_variable::Decla_variable(Variable* var) {
	// TODO Auto-generated destructor stub
	nom = var;
	cas = 1;
}

Decla_variable::Decla_variable(Variable* var, Expression * exp) {
	// TODO Auto-generated destructor stub
	nom = var;
	e1 = exp;
	cas = 2;
}

Decla_variable::Decla_variable(Variable* var, int val) {
	// TODO Auto-generated destructor stub
	nom = var;
	entier = val;
	cas = 3;
}

void Decla_variable::print(){
	nom->print();
	if(cas == 2 )
	{
		printf(" = ");
		e1->print();
	}
	else if(cas == 3 )
	{
		printf("[%i]",entier);
	}
}

char* Decla_variable::getNom()
{
	return nom->getVal();
}

string Decla_variable::buildIR(CFG* cfg)
{
	cfg->add_to_symbol_table(nom->getVal(), symboleToType(nom->getType()));
	if(cas == 1) return "";
	else if(cas == 2)
	{
		string right = e1->buildIR(cfg);
		string left = nom->buildIR_Lvalue(cfg);
		vector<string> params;
		params.push_back(left);
		params.push_back(right);
		cfg->current_bb->add_IRInstr(IRInstr::wmem, symboleToType(nom->getType()), params);
		return right;
	}
	else
	{
		//TODO : tableau
		return "";
	}
}


Decla_variable::~Decla_variable() {
	// TODO Auto-generated destructor stub
	delete nom;
	if(e1 != NULL)
	{
		delete e1;
	}
}
