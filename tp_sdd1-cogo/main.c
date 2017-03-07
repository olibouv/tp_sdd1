#include <stdio.h>
#include "fonctions.h"
#include "structures.h"



/* Problème d'insertion !!!!!!!!!!!!!!!!!!!!!*/

int main()
{
    printf("salut");
    agenda_t ** pag = creation("test.txt");
    /*printf("%s %s %s \n", (*pag)->date, (*(*pag)->actions)->moment, (*(*pag)->actions)->nom);
    printf("%s %s %s \n", (*pag)->suivant->date, (*(*pag)->suivant->actions)->moment, (*(*pag)->suivant->actions)->nom);*/
     return 0;

}