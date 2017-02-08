#include <stdio.h>
#include <stdlib.h>
#include "structure.h"


void inserer_agenda(agenda_t * ag , agenda_t ** pag)
{
    agenda_t * prec = (* pag);
    while ((prec->suivant != NULL) && (prec->suivant->date < ag->date))
    {
        prec = prec->suivant;
    }
    if (ag->date != prec->suivant->date)
    {
        ag->suivant = prec->suivant;
        prec->suivant = ag;
    }
}

void inserer_action(action_t * ac , action_t ** pac)
{
    action_t * prec = (* pac);
    while ((prec->suivant != NULL) && (prec->suivant->moment < ac->moment))
    {
        prec = prec->suivant;
    }
    if (ac->moment != prec->suivant->moment)
    {
        ac->suivant = prec->suivant;
        prec->suivant = ac;
    }
}

int supprimer_agenda(char date[6], agenda_t ** pag)
{
    int code = 0;
    agenda_t * prec = (* pag);
    agenda_t * tmp = NULL;
    action_t * tmp2 = NULL;
    while ((prec->suivant != NULL) && (prec->suivant->date < date))
    {
        prec = prec->suivant;
    }
    if(prec->suivant->date == date)
    {
        tmp = prec->suivant;
        prec->suivant = prec->suivant->suivant;
        while (tmp->actions != NULL)
        {
            tmp2 = tmp->actions;
            tmp->actions = tmp2->suivant;
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
    while ((prec->suivant != NULL) && (prec->suivant->moment < moment))
    {
        prec = prec->suivant;
    }
    if(prec->suivant->moment == moment)
    {
        tmp = prec->suivant;
        prec->suivant = prec->suivant->suivant;
        free(tmp);
        code = 1;
    }
    return code;
}

