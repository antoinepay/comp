
#include "Return1.h"
#include "IR.h"
#include "Backend.h"
#include <vector>

Return1::Return1(Expression* e) {
	// TODO Auto-generated constructor stub
	e1 = e;
}

Return1::Return1() {
	// TODO Auto-generated constructor stub
}

Return1::~Return1() {
	// TODO Auto-generated destructor stub
	if(e1 != NULL)
	{
		delete e1;
	}
}

string Return1::buildIR(CFG* cfg)
{
	vector<string> params;
	if(e1 != NULL)
	{
		string reg = e1->buildIR(cfg);
		params.push_back(reg);
		cfg->current_bb->add_IRInstr(IRInstr::ret, symboleToType(e1->getType()), params);
	}
	cfg->current_bb->add_IRInstr(IRInstr::ret, Void, params);
	return "";
}

void Return1::print(){
	printf("return ");
	if(e1 != NULL)
	{
		e1->print();
	}
	printf(";");
}
