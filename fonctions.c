#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions.h"
#include <string.h>

agenda_t ** creation(char nomfichier[])
{
    char date[6];
    char moment[3];
    char nom[10];
    FILE * fichier = NULL;
    agenda_t ** pag = NULL;
    agenda_t * courAgenda = NULL;
    action_t * courAction = NULL;
    fichier = fopen(nomfichier, "r");
    if (fichier != NULL)
    {
        pag = (agenda_t **) malloc(sizeof(agenda_t *));
        (*pag) = (agenda_t *) malloc(sizeof(agenda_t));
        (*pag) = NULL;
        while (!feof(fichier))
        {
            courAgenda = (agenda_t *) malloc(sizeof(agenda_t));
            courAction = (action_t *) malloc(sizeof(action_t));
            fgets(date,7,fichier);
            fgets(moment,4,fichier);
            fgets(nom,11,fichier);
            strcpy(courAgenda->date,date);
            strcpy(courAction->moment,moment);
            strcpy(courAction->nom,nom);
            courAgenda->actions = &courAction;
            inserer_agenda(courAgenda,pag);
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

