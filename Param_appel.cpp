
#include "Param_appel.h"
#include "IR.h"
#include "Backend.h"

Param_appel::Param_appel(Expression* v) {
	// TODO Auto-generated constructor stub
	e1 = v;
}


Param_appel::~Param_appel() {
	// TODO Auto-generated destructor stub
	delete e1;
}

int Param_appel::getType()
{
	return e1->getType();
}

string Param_appel::buildIR(CFG* cfg)
{
	return e1->buildIR(cfg);
}

void Param_appel::print(){
	e1->print();
}
