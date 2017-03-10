/*
 ______________________________________________________________________________________
|                                                                                      |
|                             ___________________                                      |
|                            |                   |                                     |
|                            |    structures.c   |                                     |
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
|					inserer_agenda
|
|	Cette fonction insère une semaine dans un agenda à partir de l'adresse du bloc
|	semaine à insérer et de l'adresse du pointeur d'agenda.
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
    int code = 0;
    if ((*pag) == NULL) 					/* agenda vide */
    {
        (*pag) = ag;						/* on insère en tant que première élément */
        (*pag)->suivant = NULL;
        code = 1;
    }
    else
    {
        agenda_t *prec = (*pag);				/* pointeur de la semaine précédente */
        while ((prec->suivant != NULL) && (strcmp(prec->suivant->date, ag->date) < 0)) /* tant qu'on n'est pas à la fin
	ou que la semaine qui suit la semaine précédente est strictement inférieure à la semaine à insérer */
	{
            prec = prec->suivant;				/* on avance le pointeur */
        }
        if (prec->suivant == NULL) 				/* si on est arrivé à la fin de l'agenda */
        {
            prec->suivant = ag;					/* on insère en tant que dernier élément */
            code = 1;
        }
        else
        {
            if (strcmp(ag->date, prec->suivant->date)) 		/* la semaine n'existe pas encore */
            {
                ag->suivant = prec->suivant;			/* on insère la semaine dans l'agenda en raccordant */
                prec->suivant = ag;
                code = 1;
            }
            else 						/* la semaine est déjà présente dans l'agenda */
            {
                code =inserer_action((*ag->actions),prec->suivant->actions);	/* on insère l'action dans la semaine présente */
            }
        }
    }
    return code;
}


/*
 _______________________________________________________________________________________
|					inserer_action
|
|	Cette fonction insère une action dans une semaine à partir de l'adresse du bloc
|	action à insérer et de l'adresse du pointeur d'actions de la semaine.
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
    if((*pac) == NULL)				/* si la liste des actions de la semaine est vide */
    {
        (*pac) = ac;				/* on insère en tant que premier élément */
        (*pac)->suivant = NULL;
        code = 1;
    }
    else					/* il y a déjà des actions dans la liste */
    {
        action_t *prec = (*pac);		/* pointeur d'action précédente */

        while ((prec->suivant != NULL) && (strcmp(prec->suivant->moment, ac->moment) < 0)) /* tant qu'on n'est pas à la fin
	et que l'action qui suit l'action précédente est strictement inférieure à l'action à insérer */
	{
            prec = prec->suivant;		/* on avance le pointeur */
        }
        if (prec->suivant == NULL) 		/* si on est à la fin de la liste d'actions */
        {
            prec->suivant = ac;			/* on insère en tant que dernier élément */
            ac->suivant =NULL;
            code = 1;
        }
        else
        {
            if (strcmp(ac->moment, prec->suivant->moment)) 	/* l'action n'existe pas dans la liste */
            {
                ac->suivant = prec->suivant;			/* on l'insère */
                prec->suivant = ac;
                code = 1;
            }
            else 				/* le moment de l'action à insérer est occupé */
            {
                code = -1;			/* on ne fait rien */
            }
        }
    }
    return code;
}


/*
 _______________________________________________________________________________________
|					supprimer_agenda
|
|	Cette fonction supprime une semaine d'un agenda à partir de la date de la semaine
|	et de l'adresse du pointeur d'agenda.
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
    agenda_t * prec = (* pag);				/* initialisation du pointeur précédent la semaine à supprimer */
    agenda_t * tmp = NULL;				/* pointeur temporaire n°1 (sert pour les semaines) */
    action_t * tmp2 = NULL;				/* pointeur temporaire n°2 (sert pour les actions) */
    
    if(!strcmp(prec->date,date))			/* cas où on supprime la 1ère semaine */
    {
        *pag = prec->suivant;				/* on raccorde la 2ème semaine au pointeur d'agenda */
        while (*prec->actions != NULL)			/* tant que la liste d'actions n'est pas vide */
        {
            tmp2 = (*prec->actions);			/* on garde en mémoire l'adresse du bloc action à libérer */
            (*prec->actions) = tmp2->suivant;		/* le pointeur passe à l'action suivante */
            free(tmp2);					/* on libère les blocs action */
        }
        free(prec);					/* on libère le bloc semaine */
        code = 1;
    }
    else 
    {
        while ((prec->suivant != NULL) && (strcmp(prec->suivant->date, date) < 0)) 	/* tant que l'on n'est pas
	à la fin de l'agenda et que la semaine qui suit la semaine précédente est strictement inférieure à la semaine
	à supprimer */
	{
            prec = prec->suivant;			/* on avance le pointeur */
        }
        if (!strcmp(prec->suivant->date, date)) 	/* si la semaine sur laquelle on s'est arrêté est celle à supprimer */
	{
            tmp = prec->suivant;			/* on garde en mémoire l'adresse du bloc semaine à libérer */
            prec->suivant = prec->suivant->suivant;	/* on raccorde la semaine précédente et suivante */
            while (*tmp->actions != NULL) 		/* tant que la liste d'actions de la semaine à supprimer n'est pas vide */
	    {
                tmp2 = (*tmp->actions);			/* on garde en mémoire l'adresse du bloc action à libérer */
                (*tmp->actions) = tmp2->suivant; 	/* on passe à l'action suivante */
                free(tmp2);				/* on libère le bloc action */
            }
            free(tmp);					/* on libère le bloc semaine */
            code = 1;
        }
    }
    return code;
}


/*
 _______________________________________________________________________________________
|					supprimer_action
|
|	Cette fonction supprime une action d'une semaine à partir du moment de l'action
|	et de l'adresse du pointeur d'actions de la semaine.
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
    action_t * prec = (* pac);				/* initialisation du pointeur de l'action précédent celle à supprimer */
    action_t * tmp = NULL;				/* pointeur temporaire qui gardera en mémoire le bloc action à supprimer */
    
    if (!strcmp(prec->moment ,moment)) 			/* si on supprime la 1ère action de la liste */
    {
        *pac = prec->suivant;				/* on raccorde la 2ème action au pointeur d'actions */
        free(prec);					/* on libère le bloc action */
        code = 1;
    }
    else 
    {
        while ((prec->suivant != NULL) && (strcmp(prec->suivant->moment, moment) < 0))	/* tant que l'on n'est pas à la fin
	de la liste d'actions et que l'action qui suit l'action précédente est strictement inférieure à l'action à supprimer */
	{
            prec = prec->suivant; 			/* on avance le pointeur précédent */
        }
        if (!strcmp(prec->suivant->moment, moment)) 	/* si l'action sur laquelle on s'est arrêté est celle à supprimer */
	{
            tmp = prec->suivant;			/* on garde en mémoire la bloc action à libérer */
            prec->suivant = prec->suivant->suivant;	/* on raccorde l'action suivante à la précédente */
            free(tmp);					/* on libère le bloc action */
            code = 1;
        }
    }
    return code;
}
