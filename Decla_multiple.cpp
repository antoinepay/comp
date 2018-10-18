

#include "Decla_multiple.h"
#include <stdio.h>
#include <string>
#include "compilateur.tab.h"

Decla_multiple::Decla_multiple(int typeVar, list<Decla_variable*>* listeVar) {
	// TODO Auto-generated destructor stub
	type = typeVar;
	liste = listeVar;
}

list<Decla_variable*>* Decla_multiple::getListe(){
    return this->liste;
}

string Decla_multiple::buildIR(CFG* cfg)
{
	list<Decla_variable*>::iterator it;
	for(it=liste->begin(); it!=liste->end(); it++)
	{
		(*it)->buildIR(cfg);
	}
	return "";
}

void Decla_multiple::print(){
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
	printf("%s ", s);
	list<Decla_variable*>::iterator it;
	list<Decla_variable*>::iterator it2;
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
}

int Decla_multiple::getType()
{
	return type;
}

list<char*>* Decla_multiple::getVariableDeclare()
{
	return getNom();
}

list<char*>* Decla_multiple::getNom()
{
	list<char*>* l = new list<char*>();
	list<Decla_variable*>::iterator it;
	for(it=liste->begin(); it!=liste->end(); it++)
	{
		l->push_back((*it)->getNom());
	}
	return l;
}


Decla_multiple::~Decla_multiple() {
	// TODO Auto-generated destructor stub
	int taille = liste->size();
	for(int i=0;i<taille;i++)
	{
		delete liste->front();
		liste->pop_front();
	}
	delete liste;
}
