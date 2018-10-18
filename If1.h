
#ifndef IF1_H_
#define IF1_H_

#include "Expression.h"
#include "Instruction.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>

class If1 : public Instruction {
public:
	If1(Expression* e, list<Instruction*>* instrIf, list<Instruction*>* instrElse);
	string buildIR(CFG* cfg);
	void print();
	virtual ~If1();

protected :
	Expression* e1 = NULL;
	list<Instruction*>* instructionsIf = NULL;
	list<Instruction*>* instructionElse = NULL;
};

#endif /* IF1_H_ */
