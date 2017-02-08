#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

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
        printf("1 \n");
        pag = (agenda_t **) malloc(sizeof(agenda_t *));
        printf("2 \n");
        while (!feof(fichier))
        {
            printf("coucou \n");
            courAgenda = (agenda_t *) malloc(sizeof(agenda_t));
            courAction = (action_t *) malloc(sizeof(action_t));
            printf("2 \n");
            fgets(date,6,fichier);
            fgets(moment,3,fichier);
            fgets(nom,10,fichier);
            courAgenda->date = date;
            courAction->moment = moment;
            courAction->nom = nom;
            courAgenda->actions = courAction;
            inserer_agenda(courAgenda,pag);
        }
        fclose(fichier);
    }
    return pag;
}