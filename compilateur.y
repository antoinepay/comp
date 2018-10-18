%code requires{
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>
#include <string.h>
#include <map>
#include "Affectation.h"
#include "Appel_fonction.h"
#include "Bit.h"
#include "Caractere.h"
#include "Comparaison.h"
#include "Decla_multiple.h"
#include "Decla_variable.h"
#include "Definition_fonction.h"
#include "Expression.h"
#include "For1.h"
#include "If1.h"
#include "Instruction.h"
#include "Logique.h"
#include "Nombre.h"
#include "Operation.h"
#include "Param_appel.h"
#include "Parametre.h"
#include "Return1.h"
#include "Variable.h"
#include "While1.h"
using namespace std;
}

%{
#include "compilateur.tab.h"
void yyerror(list<Definition_fonction*> **, const char *);
int yylex(void);
void check_type(int type1, int type2);
int checkIsArray(int type);
int typeToArray(int type);
int arrayToType(int type);
int check_variable_type(char* nom);
int check_function_type(char* nom) ;
void check_param_type(char* nom, list<Param_appel*>* params2);
void create_variable(char* nom, int type);
void create_function(char* nom,Definition_fonction* def);
void SemanticError(const char * msg);
void delete_variable(list<Instruction*>* liste);
void delete_param(list<Parametre*>* liste);
extern int yylineno;
extern map<string,int>* tableVariable;
extern map<string,Definition_fonction*>* tableFonction;
int typeActuel;
int typeFonctActuel;
char* nomFonc;
%}
%union {
   int ival;
   char cval;
   char* sval;
   Definition_fonction* def_fonction;
   list<Definition_fonction*>* liste;
   list<Instruction*>* listeInstruction;
   While1* instrWhile;
   For1* instrFor;
   If1* instrIF;
   Expression* expr;
   Instruction* instr;
   Operation* ope;
   Logique* log;
   Comparaison* comp;
   Bit* bit;
   Affectation* affect;
   Decla_multiple* decla_mult;
   list<Decla_variable*>* liste_decla_var;
   Decla_variable* decla_var;
   Appel_fonction* appel;
   list<Parametre*>* liste_param;
   list<Param_appel*>* liste_param_appel;
}


%token <ival> MOINSMOINS
%token <ival> PLUSPLUS
%token <ival> ETET
%token <ival> OUOU
%token <ival> SUPERIEURSUPERIEUR
%token <ival> INFERIEURINFERIEUR
%token <ival> SUPERIEUREGAL
%token <ival> INFERIEUREGAL
%token <ival> MODULOEGAL
%token <ival> DIVEGAL
%token <ival> MULEGAL
%token <ival> MOINSEGAL
%token <ival> NOTEGAL
%token <ival> PLUSEGAL
%token <ival> EGALEGAL
%token <ival> PLUS
%token <ival> MOINS
%token <ival> DIV
%token <ival> OPEN
%token <ival> CLOSE
%token <ival> MUL
%token <ival> MODULO
%token <ival> POINTVIRGULE
%token <ival> OPENCROCHET
%token <ival> CLOSECROCHET
%token <ival> OPENACCOLADE
%token <ival> CLOSEACCOLADE
%token <ival> VIRGULE
%token <ival> WHILE
%token <ival> FOR
%token <ival> IF
%token <ival> ELSE
%token <ival> EGAL
%token <ival> NOT
%token <ival> INFERIEUR
%token <ival> SUPERIEUR
%token <ival> OU
%token <ival> ET
%token <ival> VOID
%token <ival> INT32
%token <ival> INT64
%token <ival> CHAR
%token <ival> RETURN
%token <ival> ERROR
%token <ival> CHAR_ARRAY
%token <ival> INT32_ARRAY
%token <ival> INT64_ARRAY


%token <ival> ENTIER
%token <cval> CARACTERE
%token <sval> VARIABLE

%type <expr> expression
%type <liste> programme
%type <def_fonction> definition_fonction
%type <instr> instruction
%type <listeInstruction> bloc_ou_instruction
%type <listeInstruction> bloc
%type <listeInstruction> liste_instruction
%type <instrWhile> while
%type <instrFor> for
%type <instrIF> if
%type <listeInstruction> else
%type <comp> comparaison
%type <bit> bit
%type <log> logique
%type <ope> operation
%type <affect> affectation
%type <decla_mult> declaration_multiple
%type <liste_decla_var> declaration_rec
%type <decla_var> declaration_variable
%type <appel> appel_fonction
%type <liste_param_appel> param_appel_fonction
%type <liste_param_appel> parametres_appel
%type <liste_param> param_fonction
%type <liste_param> parametres
%type <ival> type
%type <ival> type_variable
%type <sval> nom

%left VIRGULE
%left EGAL PLUSEGAL MOINSEGAL MULEGAL DIVEGAL MODULOEGAL
%left OUOU
%left ETET
%left OU
%left ET
%left EGALEGAL NOTEGAL
%left INFERIEUR INFERIEUREGAL SUPERIEUR SUPERIEUREGAL
%left INFERIEURINFERIEUR SUPERIEURSUPERIEUR
%left MOINS PLUS
%left MUL DIV MODULO
%left NOT PLUSPLUS MOINSMOINS 

%parse-param {  list<Definition_fonction*>** resultat }

%%

axiome : programme { *resultat = $1; }
	   ;

programme : programme definition_fonction { $$ = $1; $$->push_back($2); }
		  | { $$ = new list<Definition_fonction*>(); }
       	  ;

definition_fonction : type nom OPEN param_fonction CLOSE bloc { $$ = new Definition_fonction($1,$2,$4,$6); delete_param($4); }
					;
nom : VARIABLE {$$=$1; nomFonc=$1; };

instruction : while { $$ = $1; }
			| for { $$ = $1; }
			| if { $$ = $1; }
			| declaration_multiple POINTVIRGULE { $$ = $1; }
			| expression POINTVIRGULE { $$ = $1; }
			| RETURN expression POINTVIRGULE { $$ = new Return1($2); check_type(typeFonctActuel,$2->getType()); }
			| RETURN POINTVIRGULE { $$ = new Return1(); check_type(typeFonctActuel,VOID); }
			;

bloc_ou_instruction : bloc { $$ = $1; }
					| instruction { $$ = new list<Instruction*>(); $$->push_back($1); delete_variable($$); }
					;

bloc : OPENACCOLADE liste_instruction CLOSEACCOLADE { $$ = $2; delete_variable($2);}
	 ;

liste_instruction : liste_instruction instruction { $$ = $1; $$->push_back($2); }
				  |  { $$ = new list<Instruction*>(); } //epsilon
				  ; 

while : WHILE OPEN expression CLOSE bloc_ou_instruction { $$ = new While1($3,$5);check_type(INT32,$3->getType()); }
	  ;
	  
for : FOR OPEN expression POINTVIRGULE expression POINTVIRGULE expression CLOSE bloc_ou_instruction { $$ = new For1($3,$5,$7,$9);check_type(INT32,$3->getType());check_type(INT32,$5->getType());check_type(INT32,$7->getType()); }
	;
	
if : IF OPEN expression CLOSE bloc_ou_instruction else { $$ = new If1($3,$5,$6);check_type(INT32,$3->getType()); }
   ;

else : ELSE bloc_ou_instruction { $$ = $2; }
	 |  { $$ = new list<Instruction*>(); } //epsilon
	 ;

expression : operation { $$ = $1; }
		   | comparaison { $$ = $1; }
		   | logique { $$ = $1; }
		   | affectation { $$ = $1; }
		   | bit { $$ = $1; }
		   | ENTIER { $$ = new Nombre($1); }
		   | CARACTERE { $$ = new Caractere($1); }
		   | MOINS ENTIER { $$ = new Nombre(-$2); }
		   | VARIABLE OPENCROCHET expression CLOSECROCHET {
		   		int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				} 
				check_type(INT32,$3->getType());
				$$ = new Variable(type,$1,$3); }
		   | VARIABLE { int type=check_variable_type($1); $$ = new Variable(type,$1); }
		   | appel_fonction { $$ = $1; }
		   | OPEN expression CLOSE { $$ = $2; }
		   ;

comparaison : expression EGALEGAL expression { $$ = new Comparaison($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
			| expression NOTEGAL expression { $$ = new Comparaison($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
			| expression INFERIEUR expression { $$ = new Comparaison($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
			| expression SUPERIEUR expression { $$ = new Comparaison($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
			| expression INFERIEUREGAL expression { $$ = new Comparaison($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
			| expression SUPERIEUREGAL expression { $$ = new Comparaison($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
			;

bit : expression OU expression { $$ = new Bit($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
	| expression ET expression { $$ = new Bit($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
	| expression INFERIEURINFERIEUR expression { $$ = new Bit($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
	| expression SUPERIEURSUPERIEUR expression { $$ = new Bit($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
	;
	
logique : NOT expression { $$ = new Logique($1,$2);check_type(INT32,$2->getType()); }
		| expression OUOU expression { $$ = new Logique($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
		| expression ETET expression { $$ = new Logique($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
		;

operation : expression PLUS expression { $$ = new Operation($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
     | expression MUL expression  { $$ = new Operation($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
     | expression DIV expression  { $$ = new Operation($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
     | expression MOINS expression { $$ = new Operation($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
     | expression MODULO expression { $$ = new Operation($2,$1,$3);check_type(INT32,$1->getType());check_type(INT32,$3->getType()); }
     | MOINS VARIABLE {  int type=check_variable_type($2); check_type(INT32,type); $$ = new Operation($1,new Variable(type,$2)); }
     ;

affectation : VARIABLE PLUSPLUS { 
				int type=check_variable_type($1);
				check_type(INT32,type);
				$$ = new Affectation(new Variable(type,$1),$2,0); }
			| VARIABLE MOINSMOINS { 
				int type=check_variable_type($1);
				check_type(INT32,type);
				$$ = new Affectation(new Variable(type,$1),$2,0); }
			| MOINSMOINS VARIABLE { 
				int type=check_variable_type($2);
				check_type(INT32,type);
				$$ = new Affectation(new Variable(type,$2),$1,1); }
			| PLUSPLUS VARIABLE { 
				int type=check_variable_type($2);
				check_type(INT32,type);
				$$ = new Affectation(new Variable(type,$2),$1,1); }
			| VARIABLE PLUSEGAL expression { 
				int type=check_variable_type($1);
				check_type(type,$3->getType());
				$$ = new Affectation(new Variable(type,$1),$2,$3); }
			| VARIABLE MOINSEGAL expression { 
				int type=check_variable_type($1);
				check_type(type,$3->getType());
				$$ = new Affectation(new Variable(type,$1),$2,$3); }
			| VARIABLE MULEGAL expression { 
				int type=check_variable_type($1);
				check_type(type,$3->getType());
				$$ = new Affectation(new Variable(type,$1),$2,$3); }
			| VARIABLE DIVEGAL expression { 
				int type=check_variable_type($1);
				check_type(type,$3->getType());
				$$ = new Affectation(new Variable(type,$1),$2,$3); }
			| VARIABLE MODULOEGAL expression { 
				int type=check_variable_type($1);
				check_type(type,$3->getType());
				$$ = new Affectation(new Variable(type,$1),$2,$3); }
			| VARIABLE EGAL expression { 
				int type=check_variable_type($1);
				check_type(type,$3->getType());
				$$ = new Affectation(new Variable(type,$1),$2,$3); }
			| VARIABLE OPENCROCHET expression CLOSECROCHET EGAL expression { 
				int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				}
				check_type(INT32,$3->getType());
				check_type(arrayToType(type),$6->getType());
				$$ = new Affectation(new Variable(type,$1),$5,$3,$6); }
			| VARIABLE OPENCROCHET expression CLOSECROCHET PLUSPLUS { 
				int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				}
				check_type(INT32,$3->getType());
				$$ = new Affectation(new Variable(type,$1),$5,$3); }
			| VARIABLE OPENCROCHET expression CLOSECROCHET MOINSMOINS { 
				int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				}
				check_type(INT32,$3->getType());
				$$ = new Affectation(new Variable(type,$1),$5,$3); }
			| VARIABLE OPENCROCHET expression CLOSECROCHET PLUSEGAL expression { 
				int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				}
				check_type(INT32,$3->getType());
				check_type(arrayToType(type),$6->getType());
				$$ = new Affectation(new Variable(type,$1),$5,$3,$6); }
			| VARIABLE OPENCROCHET expression CLOSECROCHET MOINSEGAL expression { 
				int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				}
				check_type(INT32,$3->getType());
				check_type(arrayToType(type),$6->getType());
				$$ = new Affectation(new Variable(type,$1),$5,$3,$6); }
			| VARIABLE OPENCROCHET expression CLOSECROCHET MULEGAL expression { 
				int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				}
				check_type(INT32,$3->getType());
				check_type(arrayToType(type),$6->getType());
				$$ = new Affectation(new Variable(type,$1),$5,$3,$6); }
			| VARIABLE OPENCROCHET expression CLOSECROCHET DIVEGAL expression { 
				int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				}
				check_type(INT32,$3->getType());
				check_type(arrayToType(type),$6->getType());
				$$ = new Affectation(new Variable(type,$1),$5,$3,$6); }
			| VARIABLE OPENCROCHET expression CLOSECROCHET MODULOEGAL expression { 
				int type=check_variable_type($1);
				if(!checkIsArray(type))
				{
					check_type(type,typeToArray(type));
				}
				check_type(INT32,$3->getType());
				check_type(arrayToType(type),$6->getType());
				$$ = new Affectation(new Variable(type,$1),$5,$3,$6); }
			;

declaration_multiple : type_variable declaration_rec { $$ = new Decla_multiple($1,$2); }
					 ;
					 
declaration_rec : declaration_rec VIRGULE declaration_variable { $$ = $1; $$->push_back($3); }
				| declaration_variable { $$ = new list<Decla_variable*>(); $$->push_back($1); }
				;

declaration_variable : VARIABLE { $$ = new Decla_variable(new Variable(typeActuel,$1)); create_variable($1,typeActuel); }
					 | VARIABLE EGAL expression { $$ = new Decla_variable(new Variable(typeActuel,$1),$3); create_variable($1,typeActuel); check_type(typeActuel,$3->getType()); }
					 | VARIABLE OPENCROCHET ENTIER CLOSECROCHET { int type=typeToArray(typeActuel); $$ = new Decla_variable(new Variable(type,$1),$3); create_variable($1,type); }
					 ;

appel_fonction : VARIABLE OPEN param_appel_fonction CLOSE { int type= check_function_type($1); $$ = new Appel_fonction(type,$1,$3); check_param_type($1,$$->getParams()); }
			   ;

param_appel_fonction : parametres_appel { $$ = $1; }
					 | { $$ = new list<Param_appel*>();} //epsylon
					 ;
					 
parametres_appel : expression { $$ = new list<Param_appel*>(); $$->push_back(new Param_appel($1)); }
				 | parametres_appel VIRGULE expression { $$ = $1; $$->push_back(new Param_appel($3)); }
				 ;

param_fonction : parametres { $$ = $1; create_function(nomFonc,new Definition_fonction(typeFonctActuel,strdup(nomFonc),$$,NULL)); }
			   | VOID { $$ = new list<Parametre*>(); create_function(nomFonc,new Definition_fonction(typeFonctActuel,strdup(nomFonc),$$,NULL));}
			   |  { $$ = new list<Parametre*>(); create_function(nomFonc,new Definition_fonction(typeFonctActuel,strdup(nomFonc),$$,NULL));} //epsilon
			   ;

parametres : type_variable VARIABLE { $$ = new list<Parametre*>(); create_variable($2,$1);  $$->push_back(new Parametre($1,new Variable($1,$2))); }
		   | type_variable VARIABLE OPENCROCHET CLOSECROCHET { $$ = new list<Parametre*>(); create_variable($2,$1); $$->push_back(new Parametre($1,new Variable($1,$2,new Expression()))); }
		   | parametres VIRGULE type_variable VARIABLE { $$ = $1; create_variable($4,$3); $$->push_back(new Parametre($3,new Variable($3,$4))); }
		   | parametres VIRGULE type_variable VARIABLE OPENCROCHET CLOSECROCHET { $$ = $1; create_variable($4,$3); $$->push_back(new Parametre($3,new Variable($3,$4,new Expression()))); }
		   ;

type : type_variable { $$ = $1; typeFonctActuel= $1; }
	 | VOID { $$ = $1; typeFonctActuel=$1; }
	 ;

type_variable : INT32 { $$ = $1; typeActuel= INT32; }
			  | INT64 { $$ = $1; typeActuel= INT64;}
			  | CHAR { $$ = $1; typeActuel= CHAR;}
			  ;

%%


void create_function(char* nom,Definition_fonction* def)
{
	map<string,Definition_fonction*>::iterator it;
	it = tableFonction->find(nom);
	if(it != tableFonction->end())
	{
		string s = "Semantic error line ";
		s+=to_string(yylineno);
		s+=" : Multiple declaration of function ";
		s+=nom;
		SemanticError(s.c_str());
	}
	(*tableFonction)[nom]=def;
}

void delete_param(list<Parametre*>* liste)
{
	list<Parametre*>::iterator it;
	for(it=liste->begin(); it!=liste->end(); it++)
	{
		tableVariable->erase((*it)->getNomVal());
	}
}

void delete_variable(list<Instruction*>* liste)
{
	list<Instruction*>::iterator it;
	list<char*>::iterator it2;
	for(it=liste->begin(); it!=liste->end(); it++)
	{
		list<char*>* vars = (*it)->getVariableDeclare();
		for(it2=vars->begin(); it2!=vars->end(); it2++)
		{
			tableVariable->erase(*it2);
			(*it2)=NULL;
		}
		delete vars;
	}
}

void create_variable(char* nom, int type) 
{
	map<string,int>::iterator it;
	it = tableVariable->find(nom);
	if(it != tableVariable->end())
	{
		string s = "Semantic error line ";
		s+=to_string(yylineno);
		s+=" : Multiple declaration of variable ";
		s+=nom;
		SemanticError(s.c_str());
	}
	(*tableVariable)[nom]=type;
}

void check_param_type(char* nom, list<Param_appel*>* params2)
{
	map<string,Definition_fonction*>::iterator it;
	it = tableFonction->find(nom);
	string nomS = string(nom);
	if(it == tableFonction->end())
	{
		string s = "Semantic error line ";
		s+=to_string(yylineno);
		s+=" : function ";
		s+=nom;
		s+=" has not been declared";
		SemanticError(s.c_str());
	}
	list<Parametre*>* params1 = it->second->getParams();
	if(params1->size()!=params2->size())
	{
		string s = "Semantic error line ";
		s+=to_string(yylineno);
		s+=" : function ";
		s+=nom;
		s+=" expected ";
		s+=params1->size();
		s+=" parameters and received ";
		s+=params2->size();
		SemanticError(s.c_str());
	}
	list<Parametre*>::iterator it2;
	list<Param_appel*>::iterator it3;
	it3=params2->begin();
	if(nomS.compare("putchar")==0)
	{
		int type = params2->front()->getType();
		if(type == INT32 || type == INT64 || type == CHAR)
		{
			return ;
		}
	}
	for(it2=params1->begin(); it2!=params1->end(); it2++)
	{
		check_type((*it2)->getType(),(*it3)->getType());
		it3++;
	}
}

int check_function_type(char* nom) 
{
	map<string,Definition_fonction*>::iterator it;
	it = tableFonction->find(nom);
	if(it == tableFonction->end())
	{
		string s = "Semantic error line ";
		s+=to_string(yylineno);
		s+=" : function ";
		s+=nom;
		s+=" has not been declared";
		SemanticError(s.c_str());
	}
	return it->second->getType();
}

int check_variable_type(char* nom) 
{
	map<string,int>::iterator it;
	it = tableVariable->find(nom);
	if(it == tableVariable->end())
	{
		string s = "Semantic error line ";
		s+=to_string(yylineno);
		s+=" : variable ";
		s+=nom;
		s+=" has not been declared";
		SemanticError(s.c_str());
	}
	return it->second;
}

int arrayToType(int type)
{
	if(type == INT32_ARRAY) return INT32;
	if(type == INT64_ARRAY) return INT64;
	if(type == CHAR_ARRAY) return CHAR;
	return ERROR;
}

int typeToArray(int type)
{
	if(type == INT32) return INT32_ARRAY;
	if(type == INT64) return INT64_ARRAY;
	if(type == CHAR) return CHAR_ARRAY;
	return ERROR;
}

int checkIsArray(int type)
{
	return type == INT32_ARRAY || type == INT64_ARRAY || type == CHAR_ARRAY;
}

void check_type(int type1, int type2) 
{
	string typeVar1;
	string typeVar2;
	switch(type1)
	{
		case INT32:
		{
			typeVar1 = "int_32";
			break;
		}
		case INT64:
		{
			typeVar1 = "int_64";
			break;
		}
		case CHAR:
		{
			typeVar1 = "char";
			break;
		}
		case VOID:
		{
			typeVar1 = "void";
			break;
		}
		case INT32_ARRAY :
		{
			typeVar1 = "int_32 []";
			break;
		}
		case INT64_ARRAY :
		{
			typeVar1 = "int_64 []";
			break;
		}
		case CHAR_ARRAY :
		{
			typeVar1 = "char []";
			break;
		}
	}
	switch(type2)
	{
		case INT32:
		{
			typeVar2 = "int_32";
			break;
		}
		case INT64:
		{
			typeVar2 = "int_64";
			break;
		}
		case CHAR:
		{
			typeVar2 = "char";
			break;
		}
		case VOID:
		{
			typeVar2 = "void";
			break;
		}
		case INT32_ARRAY :
		{
			typeVar1 = "int_32 []";
			break;
		}
		case INT64_ARRAY :
		{
			typeVar1 = "int_64 []";
			break;
		}
		case CHAR_ARRAY :
		{
			typeVar1 = "char []";
			break;
		}
	}
	if(type1 != type2 && !((type1 == INT32 || type1 == INT64 || type1 == CHAR) && (type2 == INT32 || type2 == INT64 || type2 == CHAR)))
	{
		string s = "Semantic error line ";
		s+=to_string(yylineno);
		s+=" : expected ";
		s+=typeVar1;
		s+=" , given ";
		s+=typeVar2;
		SemanticError(s.c_str());
	}
}

void SemanticError(const char * msg) {
	printf("%s\n",msg);
    exit(0);
}

void yyerror(list<Definition_fonction*>** res, const char * msg) {
    printf("Syntax error line %i : %s\n",yylineno,msg);
    exit(0);
}
