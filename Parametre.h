

#ifndef PARAMETRE_H_
#define PARAMETRE_H_

#include <stdio.h>
#include "Variable.h"

class Parametre {
public:
	Parametre(int type2, Variable* v);
	virtual ~Parametre();
	void print();
    int getType();
    char* getNomVal();
    string buildIR_param(CFG* cfg, int indice, int taille);

protected:
	int type;
	Variable* nom;
};

#endif /* PARAMETRE_H_ */
