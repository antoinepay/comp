/*
 * Expression.h
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "Instruction.h"
#include <string>

using namespace std;

class Expression : public Instruction {
public:
	Expression();
	virtual void print(){};
	virtual int getType();
	virtual ~Expression();
	virtual int estConstante(){return 0;}
    virtual string buildIR(CFG* cfg){return "";};
};

#endif /* EXPRESSION_H_ */
