%{
#include <stdio.h>
#include <stdlib.h>
#include <list>
using namespace std;
#include "compilateur.tab.h"
%}
%option noyywrap
%option yylineno
entier    [0-9]+
caractere '.'
variable  [a-zA-Z][a-zA-Z0-9]*
commentaire1 "/*"([^*]|\*+[^*/])*\*+"/"
commentaire2 "//".*
%%
{commentaire1} { /* ignore */ }
{commentaire2} { /* ignore */ }
"#include".* { /* ignore */ }
[ \n\t]      { /* ignore */ }
{caractere}  { yylval.cval = yytext[1]; return CARACTERE; }
"'\\n'"		 { yylval.cval = '\n'; return CARACTERE; }
{entier}     { yylval.ival = atoi(yytext); return ENTIER; }
"=="		 { yylval.ival =EGALEGAL;return EGALEGAL; }
"!="		 { yylval.ival =NOTEGAL;return NOTEGAL; }
"+="		 { yylval.ival =PLUSEGAL;return PLUSEGAL; }
"-="		 { yylval.ival =MOINSEGAL;return MOINSEGAL; }
"*="		 { yylval.ival =MULEGAL;return MULEGAL; }
"/="		 { yylval.ival =DIVEGAL;return DIVEGAL; }
"%="		 { yylval.ival =MODULOEGAL;return MODULOEGAL; }
"<="		 { yylval.ival =INFERIEUREGAL;return INFERIEUREGAL; }
">="		 { yylval.ival =SUPERIEUREGAL;return SUPERIEUREGAL; }
"<<"		 { yylval.ival =INFERIEURINFERIEUR;return INFERIEURINFERIEUR; }
">>"		 { yylval.ival =SUPERIEURSUPERIEUR;return SUPERIEURSUPERIEUR; }
"||"		 { yylval.ival =OUOU;return OUOU; }
"&&"		 { yylval.ival =ETET;return ETET; }
"++"		 { yylval.ival =PLUSPLUS;return PLUSPLUS; }
"--"		 { yylval.ival =MOINSMOINS;return MOINSMOINS; }
"="			 { yylval.ival =EGAL;return EGAL; }
"%"			 { yylval.ival =MODULO;return MODULO; }
"+"          { yylval.ival =PLUS;return PLUS; }
"-"          { yylval.ival =MOINS;return MOINS; }
"/"          { yylval.ival =DIV;return DIV; }
"*"          { yylval.ival =MUL;return MUL; }
"("          { yylval.ival =OPEN;return OPEN; }
")"          { yylval.ival =CLOSE;return CLOSE; }
"["          { yylval.ival =OPENCROCHET;return OPENCROCHET; }
"]"			 { yylval.ival =CLOSECROCHET;return CLOSECROCHET; }
"{"          { yylval.ival =OPENACCOLADE;return OPENACCOLADE; }
"}"          { yylval.ival =CLOSEACCOLADE;return CLOSEACCOLADE; }
"&"          { yylval.ival =ET;return ET; }
"|"          { yylval.ival =OU;return OU; }
"!"          { yylval.ival = NOT;return NOT; }
">"          { yylval.ival =SUPERIEUR;return SUPERIEUR; }
"<"          { yylval.ival =INFERIEUR;return INFERIEUR; }
","          { yylval.ival =VIRGULE;return VIRGULE; }
";"          { yylval.ival = POINTVIRGULE;return POINTVIRGULE; }
"int32_t"    { yylval.ival = INT32;return INT32; }
"int64_t"    { yylval.ival = INT64;return INT64; }
"char"       { yylval.ival = CHAR;return CHAR; }
"void"       { yylval.ival = VOID;return VOID; }
"return"     { yylval.ival = RETURN;return RETURN; }
"while"		 { yylval.ival = WHILE;return WHILE; }
"for"		 { yylval.ival = FOR;return FOR; }
"if"		 { yylval.ival = IF;return IF; }
"else"		 { yylval.ival = ELSE;return ELSE; }
{variable}   { yylval.sval = strdup(yytext); return VARIABLE; }
. 			 { return ERROR;}
