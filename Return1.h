
#ifndef RETURN1_H_
#define RETURN1_H_

#include "Expression.h"
#include "Instruction.h"
#include <stdio.h>
#include <stdlib.h>

class Return1 : public Instruction {
public:
	Return1();
	Return1 (Expression* e);
	string buildIR(CFG* cfg);
	virtual void print();
	virtual ~Return1();

protected :
	Expression* e1 = NULL;
};

#endif /* RETURN1_H_ */
