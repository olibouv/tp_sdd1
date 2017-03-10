/*
 ______________________________________________________________________________________
|                                                                                      |
|                             ___________________                                      |
|                            |                   |                                     |
|                            |    structure.c    |                                     |
|                            |___________________|                                     |
|                                                                                      |
|______________________________________________________________________________________|

	Ce fichier contient les fonctions usuelles pour la manipulation d'agenda.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

/*
 _______________________________________________________________________________________
|							inserer_agenda
|
|	entrées : 	- ag : adresse du bloc semaine à insérer
|			- pag : adresse du pointeur d'agenda dans lequel insérer
|
|	sortie :	- code : entier, code d'erreur 
|					1 si l'insertion s'est bien passée
|					0 sinon
*/

int inserer_agenda(agenda_t * ag, agenda_t ** pag)
{
    printf("coucou \n");
    int code = 0;
    if ((*pag) == NULL) /*liste vide*/
    {
        (*pag) = ag;
        (*pag)->suivant = NULL;
        code = 1;
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
            code = 1;
        }
        else
        {
            if (strcmp(ag->date, prec->suivant->date)) /* insertion normale*/
            {
                ag->suivant = prec->suivant;
                prec->suivant = ag;
                code = 1;
            }
            else /* element deja present*/
            {
                code =inserer_action((*ag->actions),prec->suivant->actions);
            }
        }


    }
    return code;
}


/*
 _______________________________________________________________________________________
|							inserer_action
|
|	entrées : 	- ac : adresse du bloc action à insérer
|			- pac : adresse du pointeur d'actions dans lequel insérer
|
|	sortie :	- code : entier, code d'erreur 
|					1 si l'insertion s'est bien passée
|					-1 si le moment était déjà occupé (on ne fait rien)
|					0 sinon
*/

int inserer_action(action_t * ac, action_t ** pac)
{
    int code = 0;
    if((*pac) == NULL)
    {
        (*pac) = ac;
        (*pac)->suivant = NULL;
        code = 1;
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
            code = 1;
        }
        else
        {
            if (strcmp(ac->moment, prec->suivant->moment)) /*insertion normale*/
            {
                ac->suivant = prec->suivant;
                prec->suivant = ac;
                code = 1;
            }
            else /*moment deja occupe*/
            {
                code = -1;
            }
        }
    }
    return code;
}


/*
 _______________________________________________________________________________________
|							inserer
|
|	entrées : 	- date (année + semaine): date de l'action à insérer
|				- moment (jour + heure) : moment de l'action à insérer
|				- nom : nom de l'action à insérer
|				- pag : adresse du pointeur d'agenda dans lequel insérer
|
|	sortie :	- inserer_agenda
*/

int inserer(char date[6], char moment[3], char nom[10], agenda_t ** pag)
{
    agenda_t * ag = (agenda_t *) malloc(sizeof(agenda_t));
    action_t * ac = (action_t *) malloc(sizeof(action_t));
    strcpy(ag->date, date);
    strcpy(ac->moment, moment);
    strcpy(ac->nom, nom);
    ag->actions = &ac;
    return (inserer_agenda(ag,pag));
}


/*
 _______________________________________________________________________________________
|							supprimer_agenda
|
|	entrées : 	- date (année + semaine): date de la semaine à supprimer
|			- pag : adresse du pointeur d'agenda dans lequel supprimer
|
|	sortie :	- code : entier, code d'erreur
|					1 si la suppression s'est bien passée
|					0 sinon
*/

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


/*
 _______________________________________________________________________________________
|							supprimer_action
|
|	entrées : 	- moment (jour + heure): moment de l'action à supprimer
|			- pac : adresse du pointeur d'actions dans lequel supprimer
|
|	sortie :	- code : entier, code d'erreur
|					1 si la suppression s'est bien passée
|					0 sinon
*/

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
