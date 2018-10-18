#include "Nombre.h"
#include "compilateur.tab.h"
#include "IR.h"

Nombre::Nombre(int entier)
{
	val=entier;
}

void Nombre::print()
{
	printf("%i",val);
}

Nombre::~Nombre()
{

}

int Nombre::getType()
{
	return INT32;
}

string Nombre::buildIR(CFG* cfg){
	string reg = cfg->create_new_tempvar(Int32);
	vector<string> params;
	params.push_back(reg);
	params.push_back(to_string(val));
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, Int32, params);
	return reg;
}
