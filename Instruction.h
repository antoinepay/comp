/*
 * Instruction.h
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <list>
#include <string>
using namespace std;

class CFG;

class Instruction {
public:
	Instruction();
	virtual void print(){};
	virtual list<char*>* getVariableDeclare(){return new list<char*>();};
	virtual string buildIR(CFG* cfg){return "";};
	virtual ~Instruction();
};

#endif /* INSTRUCTION_H_ */
