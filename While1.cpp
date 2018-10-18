#include "While1.h"
#include "IR.h"
#include "Backend.h"

While1::While1(Expression* exp1, list<Instruction*>* liste) {
	// TODO Auto-generated constructor stub
	e1 = exp1;
	bloc = liste;
}

While1::~While1() {
	// TODO Auto-generated destructor stub
	delete e1;
	int taille = bloc->size();
	for(int i=0;i<taille;i++)
	{
		delete bloc->front();
		bloc->pop_front();
	}
	delete bloc;
}

string While1::buildIR(CFG* cfg)
{
	BasicBlock* testBB = new BasicBlock(cfg,cfg->new_BB_name());
	string test = e1->buildIR(cfg);
	BasicBlock* blocWhile = new BasicBlock(cfg,cfg->new_BB_name(),bloc);
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

void While1::print(){
	printf("while(");
	e1->print();
	printf(") {\n");
	list<Instruction*>::iterator it;
	for(it=bloc->begin(); it!=bloc->end(); it++)
	{
		(*it)->print();
		printf("\n");
	}
	printf("}");
}
