#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "reseau.h"

/* 
    Commande de compilation avec gcc :
    gcc src/main.c -o bin/prog -I include -L lib -lmingw32
    gcc src/* -o prog -I include -L lib -lmingw32
*/ 


int main(int argc, char const *argv[])
{
	initReseau();
	return 0;
}