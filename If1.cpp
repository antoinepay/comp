#include "If1.h"
#include "IR.h"
#include "Backend.h"

If1::If1(Expression* e, list<Instruction*>* instrIf, list<Instruction*>* instrElse) {
	// TODO Auto-generated constructor stub
	e1 = e;
	instructionsIf = instrIf;
	instructionElse = instrElse;
}

If1::~If1() {
	// TODO Auto-generated destructor stub
	delete e1;
	int taille = instructionsIf->size();
	for(int i=0;i<taille;i++)
	{
		delete instructionsIf->front();
		instructionsIf->pop_front();
	}
	delete instructionsIf;
	if(!instructionElse->empty())
	{
		int taille = instructionElse->size();
		for(int i=0;i<taille;i++)
		{
			delete instructionElse->front();
			instructionElse->pop_front();
		}
		delete instructionElse;
	}
}

string If1::buildIR(CFG* cfg)
{
	string test = e1->buildIR(cfg);
	BasicBlock* testBB = cfg->current_bb;
	//then
	BasicBlock* thenBB = new BasicBlock(cfg,cfg->new_BB_name(),instructionsIf);
	BasicBlock* afterThen = cfg->current_bb;
	//else
	BasicBlock* elseBB = new BasicBlock(cfg,cfg->new_BB_name(),instructionElse);
	BasicBlock* afterElse = cfg->current_bb;
	//after
	BasicBlock* afterBB = new BasicBlock(cfg,cfg->new_BB_name(),new list<Instruction*>());
	vector<string> params;
	params.push_back(test);
	params.push_back("$0");
	testBB->add_IRInstr(IRInstr::Operation::cmp, Int32, params);
	vector<string> params2;
	params2.push_back(thenBB->label);
	testBB->add_IRInstr(IRInstr::Operation::jne, Int32, params2);
	vector<string> params3;
	params3.push_back(elseBB->label);
	testBB->add_IRInstr(IRInstr::Operation::je, Int32, params3);
	vector<string> params4;
	params4.push_back(afterBB->label);
	afterThen->add_IRInstr(IRInstr::Operation::jmp, Int32, params4);
	vector<string> params5;
	params5.push_back(afterBB->label);
	afterElse->add_IRInstr(IRInstr::Operation::jmp, Int32, params5);
	return "";
}

void If1::print(){
	printf("if(");
	e1->print();
	printf(") {");
	list<Instruction*>::iterator it;
	for(it=instructionsIf->begin(); it!=instructionsIf->end(); it++)
	{
		(*it)->print();
		printf("\n");
	}
	printf("}");
	if(!instructionElse->empty())
	{
		printf("\n");
		list<Instruction*>::iterator it;
		for(it=instructionElse->begin(); it!=instructionElse->end(); it++)
		{
			(*it)->print();
			printf("\n");
		}
		printf("}");
	}
}
