/*
 ______________________________________________________________________________________
|                                                                                      |
|                             ___________________                                      |
|                            |                   |                                     |
|                            |    structure.h    |                                     |
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
    char                nom[10];				/* Le nom est sur 10 caractère obligatoirement */
    struct action     * suivant ;
} action_t;

typedef struct agenda
{
    char                 date[6];				/* La date est au format année+semaine */
    action_t          ** actions;
    struct agenda      * suivant;
} agenda_t ;

/*
 _______________________________________________________________________________________
|	Les prototypes suivant correspondent aux fonctions usuelles de manipulation de
|l'agenda :
|		- inserer : elle prend en paramètres une date, un moment, un nom d'activité ainsi
|					qu'une adresse de pointeur d'agenda et insère l'activité dans
|					l' agenda.
|					Elle fait appel à inserer_agenda et inserer_action, qui insèrent
|					respectivement : 
|							- une semaine dans un agenda ( à partir de l'adresse du
|					pointeur d'agenda et de l'adresse du bloc semaine )
|							- une action dans une semaine ( à partir de l'adresse du
|					pointeur d'action et de l'adresse du bloc action )
|
|		- supprimer_agenda : elle prend en paramètres une date et une adresse de pointeur
|							d'agenda et supprime la semaine de l'agenda qui correspond à
|							la date.
|
|		- supprimer_action : elle prend en paramètres un moment et une adresse de pointeur
|							d'actions et supprime l'action de la semaine qui correspond
|							au moment.
|
*/

int inserer_agenda(agenda_t * ag, agenda_t ** pag);
int inserer_action(action_t * ac, action_t ** pac);
int inserer(char date[6], char moment[3], char nom[10], agenda_t ** pag);
int supprimer_agenda(char date[6], agenda_t ** pag);
int supprimer_action(char moment[3], action_t ** pac);

#endif
