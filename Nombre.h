
#ifndef NOMBRE_H_
#define NOMBRE_H_

#include "Expression.h"
#include <stdio.h>

class Nombre : public Expression {
public:
	Nombre(int entier);
	virtual void print();
	virtual ~Nombre();
	int getType();
	int estConstante(){return 1;}
    string buildIR(CFG* cfg);

protected :
	int val;

};

#endif /* NOMBRE_H_ */
