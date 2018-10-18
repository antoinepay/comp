
#ifndef DECLA_VARIABLE_H_
#define DECLA_VARIABLE_H_

#include "Expression.h"
#include "Variable.h"

class Decla_variable {
public:
	Decla_variable(Variable* var); // cas 1
	Decla_variable(Variable* var, Expression * exp); // cas 2
	Decla_variable(Variable* var, int val); // cas 3 tableau
	char* getNom();
	void print();
	string buildIR(CFG* cfg);
	virtual ~Decla_variable();

protected :
	Variable* nom;
	Expression* e1 = NULL;
	int cas;//permet de connaitre le constructeur utilise et savoir quelle action utilise dans les methodes
	int entier;
};

#endif /* DECLA_VARIABLE_H_ */
