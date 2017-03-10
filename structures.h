/*
 ______________________________________________________________________________________
|                                                                                      |
|                             ___________________                                      |
|                            |                   |                                     |
|                            |    structures.h   |                                     |
|                            |___________________|                                     |
|                                                                                      |
|______________________________________________________________________________________|

	Ce fichier contient les structures utiles à l'agenda, ainsi que les prototypes des 
fonctions usuelles.

*/


#ifndef STRUCTURE
#define STRUCTURE

/*
 _______________________________________________________________________________________
|	action_t est la structure des actions de la semaine
|	agenda_t est la structure de l'agenda avec les semaines
|
*/

typedef struct action
{
    char                moment[3];       		/* Le moment est au format jour+heure */
    char                nom[10];			/* Le nom est sur 10 caractère obligatoirement */
    struct action     * suivant ;
} action_t;

typedef struct agenda
{
    char                 date[6];			/* La date est au format année+semaine */
    action_t          ** actions;
    struct agenda      * suivant;
} agenda_t ;

/*
 _______________________________________________________________________________________
|	Les prototypes suivant correspondent aux fonctions usuelles de manipulation de
|l'agenda :
|	- inserer_agenda : elle prend en paramètres une adresse de bloc semaine et une
|			adresse de pointeur d'agenda et insère la semaine dans l'agenda.
|
|	- inserer_action : elle prend en paramètres une adresse de bloc action et une
|			adresse de pointeur d'actions et insère l'action dans la semaine.
|
|	- supprimer_agenda : elle prend en paramètres une date et une adresse de pointeur
|			d'agenda et supprime la semaine de l'agenda qui correspond à la date.							
|
|	- supprimer_action : elle prend en paramètres un moment et une adresse de pointeur
|			d'actions et supprime l'action de la semaine qui correspond au moment.
|							
*/

int inserer_agenda(agenda_t * ag, agenda_t ** pag);
int inserer_action(action_t * ac, action_t ** pac);

int supprimer_agenda(char date[6], agenda_t ** pag);
int supprimer_action(char moment[3], action_t ** pac);

#endif
