
#ifndef WHILE1_H_
#define WHILE1_H_

#include "Expression.h"
#include "Instruction.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>

class While1 : public Instruction {
public:
	While1(Expression* exp1, list<Instruction*>* liste);
	void print();
	virtual ~While1();
	string buildIR(CFG* cfg);

protected :
	Expression* e1 = NULL;
	list<Instruction*>* bloc = NULL;
};

#endif /* WHILE1_H_ */
