/*
 * Logique.h
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#ifndef LOGIQUE_H_
#define LOGIQUE_H_

#include <stdio.h>

#include "Expression.h"

class Logique : public Expression {
public:
	Logique(int type, Expression * e1, Expression * e2);
	Logique(int type, Expression * e1);
	virtual ~Logique();
	void print();
	int getType();
        string buildIR(CFG* cfg);

protected:
	Expression * exp1 = NULL;
	Expression * exp2 = NULL;
	int typeExp;
};

#endif /* LOGIQUE_H_ */
