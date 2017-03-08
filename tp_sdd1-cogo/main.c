#include <stdio.h>
#include "fonctions.h"
#include "structures.h"



/* Problème d'insertion !!!!!!!!!!!!!!!!!!!!!*/

int main()
{
    agenda_t ** pag = creation("test.txt");
    sauvegarde("test2.txt",pag);
    printf("%s %s %s \n",(*pag)->date,(*(*pag)->actions)->moment,(*(*pag)->actions)->nom);
    /*printf("%s %s %s \n", (*pag)->suivant->date, (*(*pag)->suivant->actions)->moment, (*(*pag)->suivant->actions)->nom);*/
     return 0;

}