#include "IR.h"
#include "Instruction.h"
#include <string>

// === IRInstr
IRInstr::IRInstr(BasicBlock* bblock, Operation operation, Type type, vector<string> parameters){
    bb = bblock;
    op = operation;
    t = type;
    params = parameters;
}

void IRInstr::gen_asm(ostream& o){
    switch(op){
        case ldconst:
        {
            o << "movq $" << params.back() << ", " << bb->cfg->IR_reg_to_asm(params.front()) << endl;
            break;
        }
        case movq:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax " << endl;
        	o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
        }
        case incq:
        {
        	o << "incq " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
        }
        case decq:
        {
        	o << "decq " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
        }
        case add:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "addq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
		}
        case sub:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "subq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
		}
        case mul:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "imulq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
		}
        case div:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "cqo " << endl;
			o << "idivq "  << bb->cfg->IR_reg_to_asm(params[2]) << endl;
			o << "movq " << "%rax , " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
		}
        case mod:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "cqo " << endl;
			o << "idivq "  << bb->cfg->IR_reg_to_asm(params[2]) << endl;
			o << "movq " << "%rdx , " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
		}
        case neg:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) <<" ,%rax" << endl;
        	o << "negq %rax" << endl;
        	o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
        	break;
        }
        case call:
        {
        	if(params[0].compare("putchar")==0)
        	{
        		o << "movq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rdi" <<  endl;
        		o << "call " << params[0] <<  endl;
        		return ;
        	}
        	unsigned int i;
        	for(i=2;i<params.size();i++)
        	{
        		o << "pushq " << bb->cfg->IR_reg_to_asm(params[i]) <<  endl;
        	}
        	o << "call " << params[0] <<  endl;
        	for(i=2;i<params.size();i++)
			{
        		o << "popq %rdi " <<  endl;
			}
        	o << "movq %rax ,  " << bb->cfg->IR_reg_to_asm(params[1]) <<  endl;
			break;
        }
        case ret:
        {
        	if(params.size()>0)
        	{
        		o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) <<", %rax" <<  endl;
        	}
        	bb->cfg->gen_asm_epilogue(o);
        	break;
        }
        case wmem:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) << ", %rdi" << endl;
			o << "movq %rax, (%rdi)" << endl;
			break;
        }
        case rmem:
		{
			o << "movq (" << bb->cfg->IR_reg_to_asm(params[1]) << "), %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
			break;
		}
        case cmp:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) << ", %rax"  << endl;
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rdi"  << endl;
        	o << "cmpq %rdi, %rax" << endl;
			break;
        }
        case cmove:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) << ", %rax " << endl;
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rdi " << endl;
        	o << "cmove %rdi , %rax " << endl;
        	o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0])  << endl;
        	break;
        }
        case cmovene:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) << ", %rax " << endl;
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rdi " << endl;
			o << "cmovne %rdi , %rax " << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0])  << endl;
			break;
		}
        case cmovel:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) << ", %rax " << endl;
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rdi " << endl;
			o << "cmovl %rdi , %rax " << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0])  << endl;
			break;
		}
        case cmovele:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) << ", %rax " << endl;
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rdi " << endl;
			o << "cmovle %rdi , %rax " << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0])  << endl;
			break;
		}
        case cmoveg:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) << ", %rax " << endl;
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rdi " << endl;
			o << "cmovg %rdi , %rax " << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0])  << endl;
			break;
		}
        case cmovege:
		{
			o << "movq " << bb->cfg->IR_reg_to_asm(params[0]) << ", %rax " << endl;
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rdi " << endl;
			o << "cmovge %rdi , %rax " << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << " "  << endl;
			break;
		}
        case jmp:
		{
			o << "jmp " << params[0] << endl;
			break;
		}
        case je:
        {
			o << "je " << params[0] << endl;
			break;
		}
        case jne:
		{
			o << "jne " << params[0] << endl;
			break;
		}
        case jl:
		{
			o << "jl " << params[0] << endl;
			break;
		}
        case jle:
		{
			o << "jle " << params[0] << endl;
			break;
		}
        case jg:
		{
			o << "jg " << params[0] << endl;
			break;
		}
        case jge:
		{
			o << "jge " << params[0] << endl;
			break;
		}
        case orq:
        {
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "orq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
        	break;
        }
        case orLog:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "orq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rax" << endl;
			o << "cmpq $0, %rax" << endl;
			o << "movq $0, %rdi " << endl;
			o << "cmove %rdi, %rax" << endl;
			o << "movq $1, %rdi " << endl;
			o << "cmovne %rdi, %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
        	break;
        }
        case andLog:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "andq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rax" << endl;
			o << "cmpq $0, %rax" << endl;
			o << "movq $0, %rdi " << endl;
			o << "cmove %rdi, %rax" << endl;
			o << "movq $1, %rdi " << endl;
			o << "cmovne %rdi, %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
        	break;
        }
        case andq:
        {
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "andq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
        	break;
        }
        case notq:
        {
        	o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
        	o << "notq %rax" << endl;
        	o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
        	break;
        }
        case salq:
        {
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "movq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rcx" << endl;
			o << "shlq %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
        	break;
        }
        case sarq:
        {
			o << "movq " << bb->cfg->IR_reg_to_asm(params[1]) << ", %rax" << endl;
			o << "movq " << bb->cfg->IR_reg_to_asm(params[2]) << ", %rcx" << endl;
			o << "shrq %rax" << endl;
			o << "movq %rax, " << bb->cfg->IR_reg_to_asm(params[0]) << endl;
            break;
        }
        default:
            break;
    }
}

// === BasicBlock ===
BasicBlock::BasicBlock(CFG* cfg, string entry_label){
    this->cfg = cfg;
    this->label = entry_label;
    cfg->add_bb(this);
}

BasicBlock::BasicBlock(CFG* cfg, string entry_label,list<Instruction*>* instructions){
    this->cfg = cfg;
    this->label = entry_label;
    cfg->add_bb(this);
    list<Instruction*>::iterator it;
	for(it=instructions->begin(); it!=instructions->end(); it++)
	{
		(*it)->buildIR(cfg);
	}
}

void BasicBlock::gen_asm(ostream& o){
    vector<IRInstr*>::iterator it;
    o << endl << this->label << ":" << endl;
    for (it=instrs.begin(); it!=instrs.end(); ++it){
        (*it)->gen_asm(o);
    }
}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params){
    instrs.push_back(new IRInstr(this, op, t, params)) ;
}

// === CFG ===
CFG::CFG(Definition_fonction* ast) {
    this->ast = ast;
    this->nextBBnumber = 0;
    this->nextFreeSymbolIndex = -8;
}
CFG::CFG(){}

void CFG::add_bb(BasicBlock* bb){
    this->bbs.push_back(bb);
    current_bb = bb;
}

void CFG::gen_asm(ostream& o){
    gen_asm_prologue(o);
    vector<BasicBlock*>::iterator it;
    for (it=bbs.begin(); it!=bbs.end(); ++it){
        (*it)->gen_asm(o);
    }
    gen_asm_epilogue(o);
}

void CFG::gen_asm_prologue(ostream& o){
    o << ast->getNom() << ":" << endl;
    o << "pushq %rbp" << endl;
    o << "movq %rsp, %rbp" << endl;
    o << "addq $" << nextFreeSymbolIndex << ", %rsp" << endl;
}

void CFG::gen_asm_epilogue(ostream& o){
    o << "leave" << endl << "ret" << endl << endl;
}

void CFG::gen_asm_linker_directives(ostream& o){
    o << ".text" << endl;
    o << ".global main" << endl << endl;
}

void CFG::add_to_symbol_table(string name, Type t){
    this->SymbolType.insert(pair<string, Type>(name, t));
    this->SymbolIndex.insert(pair<string, int>(name, this->nextFreeSymbolIndex));
    this->nextFreeSymbolIndex -= 8;
}

string CFG::create_new_tempvar(Type t){
    string name = to_string(nextFreeSymbolIndex) + "tmp";
    add_to_symbol_table(name, t);
    return name;
}

string CFG::IR_reg_to_asm(string reg){
	if(reg[0]=='%' || reg[0]=='$')
	{
		return reg;
	}
    return to_string(get_var_index(reg))+"(%rbp)";
}

int CFG::get_var_index(string name){
    return SymbolIndex[name];
}

string CFG::new_BB_name()
{
	string s = ast->getNom();
	s+="_temp_";
	s+=to_string(nextBBnumber++);
	return s;
}
