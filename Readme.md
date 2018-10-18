Compile
========
`make`

Run
========
Compile your program using our amazing compiler (better than gcc) : `/h4111comp.sh your/file.c`
The generated binary will be called main : `./main`

Don't Works :(
==============
* Opérateurs (opérations bit à bit) : <<, >>, &
* Différence avec l’abi x86 -64 : tous les paramètres sont dans la pile dans l’ordre d’apparition gauche à droite (sauf pour putchar)
* Optimisation de l’IR

Works
=======
* Constantes : entier et caractère
* Déclaration de variables
* Affectation de variable  a=1 mais aussi a++, a--, ++a, --a, a+=, a-=, a/=, a*=, a%=
* Définition de fonction
* Appel de fonction(récursivité possible) avec nombres de paramètres “illimités”
* Liens vers putchar et getchar
* Conditions : if, else
* Boucles : while, for
* Opérateurs de calculs : +, -, /, *, %
* Opérateurs logiques : && , || , not
* Return simple ou multiple dans une fonction
* Opérateur de comparaison : <, <=, >, >=, ==, !=




**Made by Veloc'IFraptor hepta H4111**

* Antoine Payan
* Hugo David-Boyet
* Joachim Dorel
* Luc Cristol
* Ludovic Cros
* Pierre Jaglin
* Théophile Sayer
