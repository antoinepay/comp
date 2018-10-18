

#ifndef APPEL_FONCTION_H_
#define APPEL_FONCTION_H_

#include <stdio.h>

#include "Expression.h"
#include "Param_appel.h"
#include <list>

class Appel_fonction : public Expression {
public:
	Appel_fonction(int type2, char * variable, list<Param_appel*>* params);
	int getType();
	list<Param_appel*>* getParams();
	virtual ~Appel_fonction();
	void print();
    string buildIR(CFG* cfg);

protected:
	list<Param_appel*>* liste = NULL;
	char* nom = NULL;
	int type;
};

#endif /* APPEL_FONCTION_H_ */
