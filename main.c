#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "fonction.h"





int main()
{
    agenda_t ** pag = creation("test.txt");
    printf("%s %s %s \n", (*pag)->date, (*pag)->actions->moment, (*pag)->actions->nom);
    return 0;
}