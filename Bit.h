/*
 * Bit.h
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#ifndef BIT_H_
#define BIT_H_

#include <stdio.h>

#include "Expression.h"

class Bit : public Expression{
public:
	Bit(int type, Expression * e1, Expression * e2);
	virtual ~Bit();
	void print();
	int getType();
        string buildIR(CFG* cfg);

protected:
	Expression * exp1;
	Expression * exp2;
	int typeExp;
};

#endif /* BIT_H_ */
