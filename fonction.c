#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions.h"
#include <string.h>
#define TMAX 100

agenda_t ** creation(char nomfichier[])/*ne fonctionne pas*/
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

void sauvegarde (char nom[], agenda_t ** pag)/* fonctionne*/
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
        while((*courAgenda) != NULL)
        {
            printf("test1\n");
            *courAction = *((*courAgenda)->actions);
            while(*courAction != NULL)
            {
                printf("test2\n");
                fputs((*courAgenda)->date,fichier);
                fputs((*courAction)->moment,fichier);
                fputs((*courAction)->nom,fichier);
                fputs("\n",fichier);
                *courAction = (*courAction)->suivant;
            }
            *courAgenda = (*courAgenda)->suivant;
        }
    }
}

int supprime(char date[6],char moment[3], agenda_t ** pag) /*Ne fonctionne pas*/
{
    int code = 0;
    agenda_t * cour = (* pag);
    while ((cour != NULL) && (strcmp(cour->date,date)<0))
    {
        printf("coucou1 \n");
        cour = cour->suivant;
    }
    if (cour != NULL)
	{
		if (!strcmp(cour->date,date))
    	{
        	printf("coucou2 \n");
        	code = supprimer_action(moment, cour.actions);
    	}
	}
	
    return code;
}

int trouvemotif(char motif[], char nom[10]) /*fonctionne*/
{
    int i,j;
    int bool =0;
    int n = strlen(motif);
    if (n <= 10)
    {
        i = 0;
        j = 0;
       while(i<10 && j<n)
       {
           if(motif[j]==nom[i])
           {
               j ++;
           }
           i++;
       }
        if(j == n)
        {
            bool =1;
        }

    }
    return bool;
}

char *** liste_action(char motif[], agenda_t ** pag) /* fonctionne*/
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
        while(courAction != NULL && !trouvemotif(motif,courAction->nom))
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
