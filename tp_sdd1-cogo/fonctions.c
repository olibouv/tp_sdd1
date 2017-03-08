#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions.h"
#include <string.h>

agenda_t ** creation(char nomfichier[])
{
    int cd;
    char date[6];
    char moment[3];
    char nom[10];
    FILE * fichier = NULL;
    agenda_t * tete = NULL;
    agenda_t ** pag = &tete;
    fichier = fopen(nomfichier, "r");
    if (fichier != NULL)
    {
        /*pag = (agenda_t **) malloc(sizeof(agenda_t *));
        tete = (agenda_t *) malloc(sizeof(agenda_t));*/
        while (!feof(fichier))
        {
            fgets(date,7,fichier);
            fgets(moment,4,fichier);
            fgets(nom,12,fichier);
            printf("%s %s %s \n",date,moment,nom);
            inserer(date,moment,nom,pag);
            printf("%s %s %s \n",(*pag)->date,(*(*pag)->actions)->moment,(*(*pag)->actions)->nom);
        }
        printf("%s %s %s \n",(*pag)->date,(*(*pag)->actions)->moment,(*(*pag)->actions)->nom);
    }
    printf("%s %s %s \n",(*pag)->date,(*(*pag)->actions)->moment,(*(*pag)->actions)->nom);
    fclose(fichier);
    printf("%s %s %s \n",(*pag)->date,(*(*pag)->actions)->moment,(*(*pag)->actions)->nom);/*Bug après fermeture du fichier WTF!!!!!*/
    return pag;
}

void sauvegarde (char nom[], agenda_t ** pag)
{
    FILE * fichier;
    agenda_t ** courAgenda =(agenda_t **) malloc(sizeof(agenda_t *));
    action_t ** courAction = (action_t **) malloc(sizeof(action_t *));
    if ((*pag) != NULL )
    {
        printf("coucou2 \n");
        fichier = fopen(nom,"w");
        *courAgenda = (*pag);
        printf("yo!\n");
        while((*courAgenda) != NULL)/*Pas d'entrée dans la boucle*/
        {
            printf("test1\n");
            *courAction = *((*courAgenda)->actions);
            while(*courAction != NULL)
            {
                printf("test2\n");
                fputs((*courAgenda)->date,fichier);
                fputs((*courAction)->moment,fichier);
                fputs((*courAction)->nom,fichier);
                *courAction = (*courAction)->suivant;
            }
            fputs("\n",fichier);
            *courAgenda = (*courAgenda)->suivant;
        }
    }
}

