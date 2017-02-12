#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"


void inserer_agenda(agenda_t * ag , agenda_t ** pag)
{
    if ((*pag) == NULL)
    {
        (*pag) = ag;
        (*pag)->suivant = NULL;
    }
    else
    {
        agenda_t *prec = (*pag);
        printf("ins0 \n");
        while ((prec->suivant != NULL) && (strcmp(prec->suivant->date, ag->date) < 0)) {
            printf("ins3 \n");
            prec = prec->suivant;
        }
        if (prec->suivant == NULL) {
            printf("ins2 \n");
            prec->suivant = ag;
        } else {
            if (strcmp(ag->date, prec->suivant->date)) {
                ag->suivant = prec->suivant;
                prec->suivant = ag;
            }/*ajouter else pour ajouter nouvelle action*/
        }
    }
}

void inserer_action(action_t * ac , action_t ** pac)
{
    if((*pac) == NULL)
    {
        (*pac) = ac;
        (*pac)->suivant = NULL;
    }
    else
    {
        action_t *prec = (*pac);

        while ((prec->suivant != NULL) && (strcmp(prec->suivant->moment, ac->moment) < 0)) {
            prec = prec->suivant;
        }
        if (prec->suivant == NULL) {
            prec->suivant = ac;
        } else {
            if (strcmp(ac->moment, prec->suivant->moment)) {
                ac->suivant = prec->suivant;
                prec->suivant = ac;
            }
        }
    }
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

