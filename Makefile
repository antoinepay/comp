.PHONY:$(CLEAN)
CLEAN=clean
#compilateur
CC=g++
#flags a la compilation
CFLAGS=-Wall -g -std=c++11 #-Wno-deprecated-register
#flags a l'edition des liens
LDFLAGS=
#fichier headers
dirS=
HEAD = Affectation.h Appel_fonction.h Bit.h Caractere.h Comparaison.h Decla_multiple.h Decla_variable.h Definition_fonction.h Expression.h For1.h If1.h Instruction.h Logique.h Nombre.h Operation.h Param_appel.h Parametre.h Return1.h Variable.h While1.h Backend.h
INT=   Affectation.h Appel_fonction.h Bit.h Caractere.h Comparaison.h Decla_multiple.h Decla_variable.h Definition_fonction.h Expression.h For1.h If1.h Instruction.h Logique.h Nombre.h Operation.h Param_appel.h Parametre.h Return1.h Variable.h While1.h Backend.h IR.h
CFILE = compilateur.tab.c lex.yy.c
#fichiers source a compiler
SRCS=$(INT:.h=.cpp)
#fichiers objets
CPP= $(SRCS:.cpp=.o)
C= $(CFILE:.c=.o)
OBJS =$(CPP) $(C) 
#nom de l'executable
EXE=$(dirS)compilateur
LIBS=
ifeq ($(OS),Windows_NT)
	REMOVE=del /f $(OBJS) $(EXE).exe
else
	REMOVE=rm -f $(OBJS) $(EXE)
endif

All : a b $(EXE)

a : 
	flex compilateur.l

b : 
	bison -v --defines=compilateur.tab.h compilateur.y
#construit l'executable a partir des objets
$(EXE) : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

#cree les fichiers objets a partir des sources	
%.o : %.c $(HEAD)
	$(CC) -c $< -o $@ $(CFLAGS)
#cree les fichiers objets a partir des sources
%.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

#cible pour nettoyage du projet
$(CLEAN):
	$(REMOVE)

#dependances

Affectation.o : Expression.h Variable.h compilateur.tab.h Backend.h
Appel_fonction.o : Expression.h Param_appel.h compilateur.tab.h IR.h Backend.h
Bit.o : Expression.h compilateur.tab.h IR.h Backend.h
Comparaison.o : Expression.h compilateur.tab.h IR.h Backend.h
Caractere.o : Expression.h compilateur.tab.h IR.h
Decla_multiple.o : Expression.h Instruction.h Decla_variable.h compilateur.tab.h
Decla_variable.o : Expression.h Variable.h compilateur.tab.h Backend.h
Definition_fonction.o : Instruction.h Parametre.h compilateur.tab.h
Expression.o : Instruction.h compilateur.tab.h IR.h
For1.o : Expression.h Instruction.h IR.h Backend.h
If1.o :  Expression.h Instruction.h IR.h Backend.h
Instruction.o : IR.h
Logique.o :  Expression.h compilateur.tab.h IR.h Backend.h
Nombre.o : Expression.h compilateur.tab.h IR.h
Operation.o :  Expression.h compilateur.tab.h Backend.h IR.h
Parametre.o : Expression.h Variable.h compilateur.tab.h IR.h Backend.h
Param_appel.o : Expression.h IR.h Backend.h
Return1.o :  Expression.h Instruction.h IR.h Backend.h
While1.o :  Expression.h Instruction.h IR.h Backend.h
Variable.o : Expression.h IR.h Backend.h compilateur.tab.h
Backend.o : compilateur.tab.h IR.h Definition_fonction.h Instruction.h Decla_multiple.h Parametre.h Expression.h
IR.o : Definition_fonction.h Instruction.h

