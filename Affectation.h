/*
 * Affectation.h
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#ifndef AFFECTATION_H_
#define AFFECTATION_H_

#include <stdio.h>
#include "Variable.h"
#include "Expression.h"

class Affectation : public Expression {
public:
	Affectation(Variable* var, int type , Expression * e1, Expression * e2);
	Affectation(Variable* var, int type , Expression * e1);
	Affectation(Variable* var, int type, int cas2 );
	virtual ~Affectation();
	void print();
	int getType();
    string buildIR(CFG* cfg);

protected:
	Expression * exp1 = NULL;
	Expression * exp2 = NULL;
	Variable * variable;
	int typeExp;
	int cas; //0 :post incrementation ou 1: pre incrementation
};

#endif /* AFFECTATION_H_ */
