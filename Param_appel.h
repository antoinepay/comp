

#ifndef PARAM_APPEL_H_
#define PARAM_APPEL_H_

#include <stdio.h>
#include "Expression.h"

class Param_appel {
public:
	Param_appel(Expression* v);
	int getType();
	string buildIR(CFG* cfg);
	virtual ~Param_appel();
	void print();

protected:
	Expression* e1;
};

#endif /* PARAM_APPEL_H_ */
