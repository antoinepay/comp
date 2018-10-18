/*
 * Operation.h
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#ifndef OPERATION_H_
#define OPERATION_H_

#include <stdio.h>

#include "Expression.h"
#include "Variable.h"

class Operation : public Expression {
public:
	Operation(int type, Expression * e1, Expression * e2);
	Operation(int type, Variable* v);
	int getType();
	virtual ~Operation();
	void print();
    string buildIR(CFG* cfg);

protected:
	Expression * exp1;
	Expression * exp2;
	int typeExp;
};

#endif /* OPERATION_H_ */
