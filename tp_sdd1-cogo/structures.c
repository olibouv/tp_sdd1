#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"


int inserer_agenda(agenda_t * ag , agenda_t ** pag)
{
    printf("coucou \n");
    int cd = 0;
    if ((*pag) == NULL) /*liste vide*/
    {
        (*pag) = ag;
        (*pag)->suivant = NULL;
        cd = 1;
    }
    else
    {
        agenda_t *prec = (*pag);
        while ((prec->suivant != NULL) && (strcmp(prec->suivant->date, ag->date) < 0)) {
            prec = prec->suivant;
        }
        if (prec->suivant == NULL) /* fin de liste*/
        {
            prec->suivant = ag;
            cd = 1;
        }
        else
        {
            if (strcmp(ag->date, prec->suivant->date)) /* insertion normale*/
            {
                ag->suivant = prec->suivant;
                prec->suivant = ag;
                cd = 1;
            }
            else /* element deja present*/
            {
                cd =inserer_action((*ag->actions),prec->suivant->actions);
            }
        }


    }
    return cd;
}

int inserer_action(action_t * ac , action_t ** pac)
{
    int cd = 0;
    if((*pac) == NULL)
    {
        (*pac) = ac;
        (*pac)->suivant = NULL;
        cd = 1;
    }
    else
    {
        action_t *prec = (*pac);

        while ((prec->suivant != NULL) && (strcmp(prec->suivant->moment, ac->moment) < 0)) {
            prec = prec->suivant;
        }
        if (prec->suivant == NULL) /*insertion fin*/
        {
            prec->suivant = ac;
            ac->suivant =NULL;
            cd = 1;
        }
        else
        {
            if (strcmp(ac->moment, prec->suivant->moment)) /*insertion normale*/
            {
                ac->suivant = prec->suivant;
                prec->suivant = ac;
                cd = 1;
            }
            else /*moment deja occupe*/
            {
                cd = -1;
            }
        }
    }
    return cd;
}

int inserer(char date[6],char moment[3], char nom[10], agenda_t ** pag)
{
    agenda_t * ag = (agenda_t *) malloc(sizeof(agenda_t));
    action_t * ac = (action_t *) malloc(sizeof(action_t));
    strcpy(ag->date, date);
    strcpy(ac->moment, moment);
    strcpy(ac->nom, nom);
    ag->actions = &ac;
    return (inserer_agenda(ag,pag));
}

int supprimer_agenda(char date[6], agenda_t ** pag)
{
    int code = 0;
    agenda_t * prec = (* pag);
    agenda_t * tmp = NULL;
    action_t * tmp2 = NULL;
    while ((prec->suivant != NULL) && (strcmp(prec->suivant->date,date)<0))
    {
        prec = prec->suivant;
    }
    if (!strcmp(prec->suivant->date, date))
    {
        tmp = prec->suivant;
        prec->suivant = prec->suivant->suivant;
        while (tmp->actions != NULL)
        {
            tmp2 = (*tmp->actions);
            (*tmp->actions) = tmp2->suivant;
            free(tmp2);
        }
        free(tmp);
        code = 1;
    }
    return code;
}

int supprimer_action(char moment[3], action_t ** pac)
{
    int code = 0;
    action_t * prec = (* pac);
    action_t * tmp = NULL;
    while ((prec->suivant != NULL) && (strcmp(prec->suivant->moment, moment)<0))
    {
        prec = prec->suivant;
    }
    if(!strcmp(prec->suivant->moment, moment))
    {
        tmp = prec->suivant;
        prec->suivant = prec->suivant->suivant;
        free(tmp);
        code = 1;
    }
    return code;
}

