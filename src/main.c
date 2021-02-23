#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "reseau.h"
#define EXIT_SUCESS 0
#define EXIT_FAILURE 1

/* 
    Commande de compilation avec gcc :
    gcc src/main.c -o bin/prog -I include -L lib -lmingw32
    gcc src/* -o prog -I include -L lib -lmingw32
*/ 


int main(int argc, char const *argv[])
{
	Reseau reseau = initReseau();
	closeReseau(reseau);
	return 0;
}