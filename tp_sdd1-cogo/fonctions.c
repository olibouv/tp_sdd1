#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions.h"
#include <string.h>

agenda_t ** creation(char nomfichier[])
{
    printf("42");
    char date[6];
    char moment[3];
    char nom[10];
    FILE * fichier = NULL;
    agenda_t * tete = NULL;
    agenda_t ** pag = &tete;
    printf("5");
    fichier = fopen(nomfichier, "r");
    printf("6");
    if (fichier != NULL)
    {
        printf("4");
        /*pag = (agenda_t **) malloc(sizeof(agenda_t *));*/
        tete = (agenda_t *) malloc(sizeof(agenda_t));
        printf("3");
        while (!feof(fichier))
        {
            fgets(date,7,fichier);
            fgets(moment,4,fichier);
            fgets(nom,11,fichier);
            printf("1");
            inserer(date,moment,nom,pag);
            printf("2");
        }
        fclose(fichier);
    }
    return pag;
}

void sauvegarde (char nom[], agenda_t ** pag)
{
    FILE * fichier;
    agenda_t * courAgenda;
    action_t * courAction;
    if ((*pag) != NULL )
    {
        fichier = fopen(nom,"w");
        courAgenda = (*pag);
        while(courAgenda != NULL)
        {
            courAction = (* courAgenda->actions);
            while(courAction != NULL)
            {
                fputs(courAgenda->date,fichier);
                fputs(courAction->moment,fichier);
                fputs(courAction->nom,fichier);
                courAction = courAction->suivant;
            }
            fputs("\n",fichier);
            courAgenda = courAgenda->suivant;
        }
    }
}

