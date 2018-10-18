#include "Variable.h"
#include "IR.h"
#include "Backend.h"
#include "compilateur.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

Variable::Variable(int type2, char* str)
{
	val=str;
	type=type2;
};

Variable::Variable(int type2, char* str, Expression* e)
{
	val=str;
	e1=e;
	type=type2;
}

void Variable::print()
{
	if(e1==NULL)//variable normale
	{
		printf("%s",val);
	}
	else //variable tableau
	{
		printf("%s[",val);
		e1->print();
		printf("]");
	}

}

int Variable::getType()
{
	return type;
}

char* Variable::getVal()
{
	return val;
}

Variable::~Variable()
{
	if(e1!=NULL)
	{
		delete e1;
	}
	delete val;
}

string Variable::buildIR(CFG* cfg){
	return buildIR_Rvalue(cfg);
}

string Variable::buildIR_Rvalue(CFG* cfg) {
	string retour = val;
	return retour;
}

string Variable::buildIR_Lvalue(CFG* cfg) {
	string reg = cfg->create_new_tempvar(symboleToType(type));
	int offset = cfg->get_var_index(val);
	vector<string> params;
	params.push_back(reg);
	string off = to_string(offset);
	params.push_back(off);
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, symboleToType(type), params);
	vector<string> params2;
	params2.push_back(reg);
	params2.push_back(reg);
	params2.push_back("%rbp");
	cfg->current_bb->add_IRInstr(IRInstr::add, symboleToType(type), params2);
	return reg;
}
