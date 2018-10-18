#include "Backend.h"
#include "Definition_fonction.h"
#include "Instruction.h"
#include "Expression.h"
#include "Parametre.h"
#include "compilateur.tab.h"
#include "Decla_multiple.h"
#include <list>
#include <map>
#include <string>
#include <string.h>
#include <iostream>
#include <typeinfo>
using namespace std;

Type symboleToType(int type){
    switch(type){
        case INT32: return Int32;
        case INT64: return Int64;
        case CHAR: return Char;
        case INT32_ARRAY: return Int32_array;
        case INT64_ARRAY: return Int64_array;
        case CHAR_ARRAY: return Char_array;
        default: return Void;
    }
}

extern int yyparse(list<Definition_fonction*>** resultat);
map<string,Definition_fonction*>* tableFonction;
map<string,int>* tableVariable;

int main(void){
	//var globale nécessaire a bison
    list<Definition_fonction*>* resultat;
    tableVariable = new map<string,int>();
    string put = "putchar";
    string get = "getchar";
    tableFonction = new map<string,Definition_fonction*>();
    (*tableFonction)[get]=new Definition_fonction(CHAR,strdup(get.c_str()),new list<Parametre*>(),NULL);
    list<Parametre*>* l = new list<Parametre*>();
    Parametre* p = new Parametre(CHAR,NULL);
    l->push_back(p);
    (*tableFonction)[put]=new Definition_fonction(VOID,strdup(put.c_str()),l,NULL);
    //parsing
    yyparse(&resultat);
    delete l;
    delete tableVariable;
    delete tableFonction;
    if(!resultat)
    {
    	return 0;
    }
    list<CFG>* fonctions = new list<CFG>();
    //on definit les diretives linkage
    CFG linkage;
    linkage.gen_asm_linker_directives(cout);
    //construction de l'IR puis de l'asm
    list<Definition_fonction*>::iterator itDefFunc;
    for(itDefFunc=resultat->begin(); itDefFunc!=resultat->end(); ++itDefFunc)
    {
		Definition_fonction* mainFunc = (*itDefFunc);
		// IR construction
		CFG cfgmain (mainFunc);
		BasicBlock bbmain (&cfgmain, cfgmain.new_BB_name());
		// function parameters
		list<Parametre*>* mainParams = mainFunc->getParams();
		list<Parametre*>::iterator itParams;
		int i=0;
		for (itParams=mainParams->begin(); itParams!=mainParams->end(); ++itParams){
			(*itParams)->buildIR_param(&cfgmain,i,mainParams->size());
			i++;
		}
		list<Instruction*>* mainInstructions = mainFunc->getBloc();
		list<Instruction*>::iterator it;
		for (it=mainInstructions->begin(); it!=mainInstructions->end(); ++it){
			(*it)->buildIR(&cfgmain);
		}
		fonctions->push_back(cfgmain);
		//Construction de l'ASM
		cfgmain.gen_asm(cout);
    }
    delete fonctions;
    return 0;
}

