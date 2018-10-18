#include "For1.h"
#include "IR.h"
#include "Backend.h"

For1::For1(Expression* exp1, Expression* exp2, Expression* exp3, list<Instruction*>* liste) {
	// TODO Auto-generated constructor stub
	e1 = exp1;
	e2 = exp2;
	e3 = exp3;
	bloc = liste;
}

For1::~For1() {
	// TODO Auto-generated destructor stub
	delete e1;
	delete e2;
	delete e3;
	int taille = bloc->size();
	for(int i=0;i<taille;i++)
	{
		delete bloc->front();
		bloc->pop_front();
	}
	delete bloc;
}

string For1::buildIR(CFG* cfg)
{
	e1->buildIR(cfg);
	BasicBlock* testBB = new BasicBlock(cfg,cfg->new_BB_name());
	string test = e2->buildIR(cfg);
	BasicBlock* blocWhile = new BasicBlock(cfg,cfg->new_BB_name(),bloc);
	e3->buildIR(cfg);
	BasicBlock* after = new BasicBlock(cfg,cfg->new_BB_name());
	//jump inconditionnel
	vector<string> params;
	params.push_back(testBB->label);
	blocWhile->add_IRInstr(IRInstr::Operation::jmp, Int32, params);
	//jump conditionnel
	vector<string> params2;
	params2.push_back(test);
	params2.push_back("$0");
	testBB->add_IRInstr(IRInstr::Operation::cmp, Int32, params2);
	vector<string> params3;
	params3.push_back(blocWhile->label);
	testBB->add_IRInstr(IRInstr::Operation::jne, Int32, params3);
	vector<string> params4;
	params4.push_back(after->label);
	testBB->add_IRInstr(IRInstr::Operation::je, Int32, params4);
	return "";
}

void For1::print(){
	printf("for(");
	e1->print();
	printf(" ; ");
	e2->print();
	printf(" ; ");
	e3->print();
	printf(") {\n");
	list<Instruction*>::iterator it;
	for(it=bloc->begin(); it!=bloc->end(); it++)
	{
		(*it)->print();
		printf(";\n");
	}
	printf("}");
}
