
#ifndef FOR1_H_
#define FOR1_H_

#include "Expression.h"
#include "Instruction.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>

class For1 : public Instruction {
public:
	For1(Expression* exp1, Expression* exp2, Expression* exp3, list<Instruction*>* liste);
	void print();
	string buildIR(CFG* cfg);
	virtual ~For1();

protected :
	Expression* e1 = NULL;
	Expression* e2 = NULL;
	Expression* e3 = NULL;
	list<Instruction*>* bloc = NULL;
};

#endif /* FOR1_H_ */
