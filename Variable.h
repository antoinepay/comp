
#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "Expression.h"
#include <stdlib.h>

class Variable : public Expression {
public:
	Variable(int type2, char* str);

	Variable(int type2, char* str, Expression* e);

	void print();

	int getType();

	char* getVal();

	virtual ~Variable();

	string buildIR(CFG* cfg);

	string buildIR_Rvalue(CFG* cfg);

	string buildIR_Lvalue(CFG* cfg);

protected :
	char* val;
	int type;
	Expression* e1=NULL;

};

#endif /* VARIABLE_H_ */
