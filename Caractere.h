
#ifndef CARACTERE_H_
#define CARACTERE_H_

#include "Expression.h"

#include <stdio.h>

class Caractere : public Expression {
public:
	Caractere(char car);
	virtual void print();
	int getType();
	int estConstante(){return 1;}
	virtual ~Caractere(){};
    string buildIR(CFG* cfg);

protected :
	char val;

};

#endif /* CARACTERE_H_ */
