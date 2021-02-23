#include <stdio.h>
#include <stdlib.h>
#include "main.h"
<<<<<<< HEAD
#include "pwd.h"
=======
#include "reseau.h"
>>>>>>> cd4b0ee987faa3f14ed7068bb38bca88cc6d0baf

/* 
    Commande de compilation avec gcc :
    gcc src/main.c -o bin/prog -I include -L lib -lmingw32
    gcc src/* -o prog -I include -L lib -lmingw32
*/ 


int main(int argc, char const *argv[])
{
<<<<<<< HEAD
	verifierPwdAdmin();
=======
	initReseau();
>>>>>>> cd4b0ee987faa3f14ed7068bb38bca88cc6d0baf
	return 0;
}