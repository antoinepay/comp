
#include "Parametre.h"
#include <string>
#include "compilateur.tab.h"
#include "Backend.h"
#include "IR.h"

Parametre::Parametre(int type2, Variable* v) {
	// TODO Auto-generated constructor stub
	type = type2;
	nom = v;
}

Parametre::~Parametre() {
	// TODO Auto-generated destructor stub
	delete nom;
}

int Parametre::getType(){return type;}

char* Parametre::getNomVal(){return nom->getVal();}

string Parametre::buildIR_param(CFG* cfg,int indice,int taille)
{
	cfg->add_to_symbol_table(getNomVal(), symboleToType(type));
	int offset = (taille - indice) * 8 + 8; //+8 a cause du return adress
	vector<string> params;
	params.push_back(getNomVal());
	string off = to_string(offset);
	params.push_back(off);
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, symboleToType(type), params);
	vector<string> params2;
	params2.push_back("%rax");
	params2.push_back(getNomVal());
	params2.push_back("%rbp");
	cfg->current_bb->add_IRInstr(IRInstr::add, symboleToType(type), params2);
	vector<string> params3;
	params3.push_back(getNomVal());
	params3.push_back("%rax");
	cfg->current_bb->add_IRInstr(IRInstr::rmem, symboleToType(type), params3);
	return getNomVal();
}

void Parametre::print(){
	string typeVar;
	switch(type)
	{
		case INT32:
		{
			typeVar = "int_32";
			break;
		}
		case INT64:
		{
			typeVar = "int_64";
			break;
		}
		case CHAR:
		{
			typeVar = "char";
			break;
		}
	}
	const char* s = typeVar.c_str();
	printf("%s", s);
	nom->print();
}
