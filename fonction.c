/*
 ______________________________________________________________________________________
|                                                                                      |
|                              ___________________                                     |
|                             |                   |                                    |
|                             |    fonctions.c    |                                    |
|                             |___________________|                                    |
|                                                                                      |
|______________________________________________________________________________________|
	Ce fichier contient les fonctions de création, de sauvegarde, de suppression de
	l'agenda et la fonction qui met dans une liste contiguë les occurences d'une même
	action.
*/



#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions.h"
#include <string.h>
#define TMAX 100

agenda_t ** creation(char nomfichier[])/*ne fonctionne pas*/
{
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


/*
 _______________________________________________________________________________________
|							sauvegarde
|
|   Cette fonction sauvegarde l'agenda dans un fichier texte
|
|	entrées : 	- nom : nom du fichier de sauvegarde
|               - pag : adresse du pointeur d'agenda
|
|	sortie :	x
|
|			
*/

void sauvegarde (char nom[], agenda_t ** pag)
{
    FILE * fichier;                                                     /* initialisation du pointeur de fichier */
    agenda_t ** courAgenda =(agenda_t **) malloc(sizeof(agenda_t *));   /* allocation du pointeur courant des semaines */
    action_t ** courAction = (action_t **) malloc(sizeof(action_t *));  /* allocation du pointeur courant des actions */
    
    if ((*pag) != NULL )                                                /* si l'agenda n'est pas vide */
    {
        fichier = fopen(nom,"w");                                       /* on ouvre (et créé) le fichier en écriture */
        *courAgenda = (*pag);                                           /* on initialise le pointeur courant */
        while((*courAgenda) != NULL)                                    /* tant qu'on n'est pas à la fin de l'agenda */
        {
            *courAction = *((*courAgenda)->actions);
            while(*courAction != NULL)                                  /* tant qu'on n'est pas à la fin des actions */
            {
                fputs((*courAgenda)->date,fichier);                     /* on écrit la date de l'action */
                fputs((*courAction)->moment,fichier);                   /* puis le moment */
                fputs((*courAction)->nom,fichier);                      /* et enfin le nom */
                fputs("\n",fichier);                                    /* \n pour le retour à la ligne */
                *courAction = (*courAction)->suivant;                   /* on avance le pointeur courant des actions */
            }
            *courAgenda = (*courAgenda)->suivant;                       /* on avance le pointeur courant des semaines */
        }
    }
}


/*
 _______________________________________________________________________________________
|							supprime
|
|   Cette fonction supprime une action de l'agenda à l'aide sa date et moment
|
|	entrées : 	- date : date de l'action à supprimer
|				- moment : moment de l'action à supprimer
|               - pag : adresse du pointeur d'agenda
|
|	sortie :	- code : entier, code d'erreur issu des 2 fonctions supprimer_action et
|                       supprimer_agenda
|							1 si l'action a été supprimée
|							0 sinon
|
|
*/

int supprime(char date[6],char moment[3], agenda_t ** pag)
{
    int code = 0;                                           /* initialisation du code d'erreur */
    agenda_t * cour = (* pag);                              /* initialisation du pointeur courant */
    
    while ((cour != NULL) && (strcmp(cour->date,date)<0))   /* tant qu'on n'est pas à la fin et que la date est inférieure */
    {
        cour = cour->suivant;                               /* on avance le pointeur */
    }
    if (cour != NULL)                                       /* si on n'est pas à la fin */
    {
        code = supprimer_action(moment, cour->actions);     /* on supprime l'action */
        if ((*cour->actions) == NULL)                       /* si on vient de supprimer la dernière action de la semaine */
        {
            code = supprimer_agenda(date,pag);              /* on supprime aussi la semaine */
        }
    }

    return code;                                            /* on renvoie le code d'erreur */
}


/*
 _______________________________________________________________________________________
|							trouve_motif
|
|   Cette fonction retourne un booléen qui indique si le motif est dans le nom de l'action.
|
|	entrées : 	- motif : motif recherché
|				- nom : nom de l'action dans laquelle on recherche le motif
|
|	sortie :	- bool : entier, booléen 
|							1 si le motif est dans le nom
|							0 sinon
|
|
*/

int trouve_motif(char motif[], char nom[10])
{
    int i,j;
    int bool = 0;
    int n = strlen(motif);
    
    if (n <= 10)                    /* le motif ne doit pas être plus grand que 10 */
    {
        i = 0;                      /* parcourt le nom */
        j = 0;                      /* compte le nombre de caractères successifs égaux */
        while(i<10 && j<n)          /* tant que l'on est pas à la fin et que l'on n'a pas trouvé le motif */
        {
           if(motif[j]==nom[i])     /* tant que les caractères sont égaux, on incrémente */
           {
               j ++;
           }
           else                     /* le motif n'est pas présent / pas complet */
           {
                j = 0;
           }
           i++;
        }
        if(j == n)                  /* le motif a été trouvé */
        {
            bool = 1;
        }
        

    }
    return bool;
}


/*
 _______________________________________________________________________________________
|							liste_action
|
|   Cette fonction
|
|	entrées : 	- motif : motif recherché
|				- pag : adresse du pointeur d'agenda
|
|	sortie :	- tete : adresse? pointeur? de la tete
|							1 si le motif est dans le nom
|							0 sinon
|
|
*/

char *** liste_action(char motif[], agenda_t ** pag)
{
    char jour[9];
    int i;
    char * courListe;
    char *** tete = (char ***)malloc(2 * sizeof(char **));
    char ** deb = (char **) malloc(TMAX * sizeof(char[10]));
    char ** fin = deb;
    *deb = (char *) malloc(sizeof(char[10]));
    courListe = *deb;
    action_t * courAction;
    agenda_t * courAgenda = (*pag);
    while(courAgenda != NULL)
    {
        courAction = *(courAgenda ->actions);
        while(courAction != NULL && !trouve_motif(motif,courAction->nom))
        {
            courAction = courAction->suivant;
        }
        if (courAction != NULL)
        {

            strncpy(jour,courAgenda->date,6);
            strncpy(jour +6 ,courAction->moment,3);
            strcpy(courListe,jour);
            courListe += sizeof(char[10]);
            fin = &courListe;
        }
        courAgenda = courAgenda->suivant;
    }
    tete[0] = deb;
    tete[1] = fin;
    return(tete);
}
