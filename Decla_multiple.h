
#ifndef DECLA_MULTIPLE_H_
#define DECLA_MULTIPLE_H_

#include "Expression.h"
#include "Instruction.h"
#include "Decla_variable.h"
#include <list>

class Decla_multiple : public Instruction {
public:
	Decla_multiple(int typeVar, list<Decla_variable*>* listeVar);
	void print();
	int getType();
	list<char*>* getNom();
	string buildIR(CFG* cfg);
    list<Decla_variable*>* getListe();
    list<char*>* getVariableDeclare();//utile car methode herite
	virtual ~Decla_multiple();

protected :
	int type;
	list<Decla_variable*>* liste = NULL;
};

#endif /* DECLA_MULTIPLE_H_ */
