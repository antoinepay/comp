/*
 * Bit.cpp
 *
 *  Created on: 20 mars 2017
 *      Author: Pierre
 */

#include "Bit.h"
#include "compilateur.tab.h"
#include "IR.h"
#include "Backend.h"

#include <string>
#include <vector>

Bit::Bit(int type, Expression * e1, Expression * e2) {
	// TODO Auto-generated constructor stub
	exp1 = e1;
	exp2 = e2;
	typeExp = type;
}

Bit::~Bit() {
	// TODO Auto-generated destructor stub
	delete exp1;
	delete exp2;
}

void Bit::print(){
	string symbole;
	switch(typeExp){
	case OU :
		symbole = "|";
		break;
	case ET :
		symbole = "&";
		break;
	case INFERIEURINFERIEUR :
		symbole = "<<";
		break;
	case SUPERIEURSUPERIEUR :
		symbole = ">>";
		break;
	}
	exp1->print();
	const char* s = symbole.c_str();
	printf(" %s ",s);
	exp2->print();
}

int Bit::getType(){
	return INT32;
}

string Bit::buildIR(CFG* cfg){
	string reg = cfg->create_new_tempvar(symboleToType(exp1->getType()));
	string reg1 = exp1->buildIR(cfg);
	string reg2 = exp2->buildIR(cfg);
	vector<string> params;
	IRInstr::Operation t;
	switch(typeExp){
	case OU :
		t = IRInstr::orq;
		break;
	case ET :
		t = IRInstr::andq;
		break;
	case INFERIEURINFERIEUR :
		t = IRInstr::salq;
		break;
	case SUPERIEURSUPERIEUR :
		t = IRInstr::sarq;
		break;
	}
	params.push_back(reg);
	params.push_back(reg1);
	params.push_back(reg2);
	cfg->current_bb->add_IRInstr(t, Int32, params);
	return reg;
}
