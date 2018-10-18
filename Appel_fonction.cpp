

#include "Appel_fonction.h"
#include "compilateur.tab.h"
#include "IR.h"
#include "Backend.h"

Appel_fonction::Appel_fonction(int type2, char * variable, list<Param_appel*>* params) {
	// TODO Auto-generated constructor stub
	liste = params;
	nom = variable;
	type=type2;
}

Appel_fonction::~Appel_fonction() {
	// TODO Auto-generated destructor stub
	int taille = liste->size();
	for(int i=0;i<taille;i++)
	{
		delete liste->front();
		liste->pop_front();
	}
	delete liste;
	delete nom;
}

int Appel_fonction::getType()
{
	return type;
}

list<Param_appel*>* Appel_fonction::getParams()
{
	return liste;
}

void Appel_fonction::print(){
	printf("%s(",nom);
	list<Param_appel*>::iterator it;
	list<Param_appel*>::iterator it2;
	it2 = liste->end();
	it2--;
	for(it=liste->begin(); it!=liste->end(); it++)
	{
		(*it)->print();
		if(it != it2)
		{
			printf(", ");
		}
	}
	printf(")");
}

string Appel_fonction::buildIR(CFG* cfg){
	list<Param_appel*>::iterator it;
	string reg = cfg->create_new_tempvar(symboleToType(type));
	vector<string> params;
	params.push_back(nom);//nom
	params.push_back(reg);//retour
	for(it=liste->begin(); it!=liste->end(); it++)
	{
		string valeur = (*it)->buildIR(cfg);
		params.push_back(valeur);
	}
	cfg->current_bb->add_IRInstr(IRInstr::call, symboleToType(type), params);
    return reg;
}
