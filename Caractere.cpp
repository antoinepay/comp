#include "Caractere.h"
#include "compilateur.tab.h"
#include "IR.h"

#include <vector>
#include <string>
#include "IR.h"
using namespace std;


Caractere::Caractere(char car)
{
	val=car;
}

void Caractere::print()
{
	printf("%c",val);
}

int Caractere::getType()
{
	return CHAR;
}

string Caractere::buildIR(CFG* cfg){
    string reg = cfg->create_new_tempvar(Char);
    vector<string> params;
    params.push_back(reg);
    params.push_back(to_string(int(val)));
    cfg->current_bb->add_IRInstr(IRInstr::ldconst, Char, params);
    return reg;
}
