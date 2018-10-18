

#include "Definition_fonction.h"
#include "compilateur.tab.h"

Definition_fonction::Definition_fonction(int type2, char* var, list<Parametre*>* liste, list<Instruction*>* instr) {
	// TODO Auto-generated constructor stub
	type = type2;
	bloc = instr;
	params = liste;
	nom = var;
}

Definition_fonction::~Definition_fonction() {
	// TODO Auto-generated destructor stub
	int taille = params->size();
	for(int i=0;i<taille;i++)
	{
		delete params->front();
		params->pop_front();
	}
	delete params;
	taille = bloc->size();
	for(int i=0;i<taille;i++)
		{
			delete bloc->front();
			bloc->pop_front();
		}
		delete bloc;
	delete nom;
}

int Definition_fonction::getType()
{
	return type;
}

char* Definition_fonction::getNom(){
   return this->nom;
}

list<Instruction*>* Definition_fonction::getBloc(){
    return this->bloc;
}

list<Parametre*>* Definition_fonction::getParams(){return params;}

void Definition_fonction::print(){
	switch(type)
	{
		case INT32:
		{
			printf("int_32");
			break;
		}
		case INT64:
		{
			printf("int_64");
			break;
		}
		case CHAR:
		{
			printf("char");
			break;
		}
		case VOID:
		{
			printf("void");
			break;
		}
		default :
		{
			printf("default %i",type);
			break;
		}
	}
	printf(" %s(",nom);
	list<Parametre*>::iterator it;
	list<Parametre*>::iterator it2;
	it2 = params->end();
	it2--;
	for(it=params->begin(); it!=params->end(); it++)
	{
		(*it)->print();
		if(it != it2)
		{
			printf(", ");
		}
	}
	printf(") {\n");
	list<Instruction*>::iterator it3;
	for(it3=bloc->begin(); it3!=bloc->end(); it3++)
	{
		(*it3)->print();
		printf(";\n");
	}
	printf("}");
}
