#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "structures.h"



/* Problème d'insertion !!!!!!!!!!!!!!!!!!!!!*/

int main()
{
    /*agenda_t ** pag = creation("test.txt");*/
    agenda_t *ag = (agenda_t *) malloc(sizeof(agenda_t));
    action_t *ac = (action_t *) malloc(sizeof(action_t));
    strcpy(ag->date, "123456");
    strcpy(ac->nom, "yo ça va ?");
    strcpy(ac->moment, "42");
    ac->suivant = NULL;
    ag->actions = &ac;
    agenda_t *ag1 = (agenda_t *) malloc(sizeof(agenda_t));
    action_t *ac1 = (action_t *) malloc(sizeof(action_t));
    strcpy(ag1->date, "654321");
    strcpy(ac1->nom, "coucoucou!");
    strcpy(ac1->moment, "24");
    ag1->suivant = NULL;
    ag1->actions = &ac1;
    action_t *ac2 = (action_t *) malloc(sizeof(action_t));
    strcpy(ac2->nom, "yoyoyoyoyo");
    strcpy(ac2->moment, "88");
    ac1->suivant = ac2;
    ag->suivant = ag1;
    agenda_t **pag2 = &ag;
    /*int cd = supprime("654321", "24", pag2);
    if (cd)
    {
        printf("suppresssion réussie \n");
    }
    else
    {
        printf("suppression ratée \n");
    }
    sauvegarde("test2.txt", pag2);*/
    /*printf("%s %s %s \n",(*pag)->date,(*(*pag)->actions)->moment,(*(*pag)->actions)->nom);
    printf("%s %s %s \n", (*pag)->suivant->date, (*(*pag)->suivant->actions)->moment, (*(*pag)->suivant->actions)->nom);*/
    char *** tete = liste_action("yo",pag2);
    printf(" %s \n %s \n", *tete[0], *(tete[0])+sizeof(char[10]));
    return 0;
}