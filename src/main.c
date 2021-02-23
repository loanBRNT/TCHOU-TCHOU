#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "pwd.h"

/* 
    Commande de compilation avec gcc :
    gcc src/main.c -o bin/prog -I include -L lib -lmingw32
    gcc src/* -o bin/prog -I include -L lib -lmingw32
*/ 


int main(int argc, char const *argv[])
{
	verifierPwdAdmin();
	return 0;
}