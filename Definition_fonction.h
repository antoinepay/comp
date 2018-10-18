

#ifndef DEFINITION_FONCTION_H_
#define DEFINITION_FONCTION_H_

#include "Parametre.h"
#include "Instruction.h"
#include <list>

class Definition_fonction {
public:
	Definition_fonction(int type2, char* var, list<Parametre*>* liste, list<Instruction*>* instr);
	void print();
	int getType();
	virtual ~Definition_fonction();
	char* getNom();
	list<Instruction*>* getBloc();
	list<Parametre*>* getParams();

protected :
	char* nom = NULL;
	int type;
	list<Parametre*>* params = NULL;
	list<Instruction*>* bloc = NULL;


};

#endif /* DEFINITION_FONCTION_H_ */
