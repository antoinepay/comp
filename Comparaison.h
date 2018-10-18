/*
 * Comparaison.h
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#ifndef COMPARAISON_H_
#define COMPARAISON_H_

#include <stdio.h>

#include "Expression.h"


class Comparaison : public Expression {
public:
	Comparaison(int type, Expression* e1, Expression* e2);
	int getType();
	virtual ~Comparaison();
	void print();
        string buildIR(CFG* cfg);

protected:
	Expression * exp1;
	Expression * exp2;
	int typeExp;
};

#endif /* COMPARAISON_H_ */
