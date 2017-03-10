/*
 ______________________________________________________________________________________
|                                                                                      |
|                              ___________________                                     |
|                             |                   |                                    |
|                             |    fonctions.h    |                                    |
|                             |___________________|                                    |
|                                                                                      |
|______________________________________________________________________________________|
	Ce fichier contient les prototypes fonctions utilisées dans ce TP.
*/



#ifndef FONCTION
#define FONCTION

#include "structures.h"

agenda_t ** creation(char nomfichier[]);

void sauvegarde (char nom[], agenda_t ** pag);

int supprime (char date[6],char moment[3], agenda_t ** pag);

int trouve_motif(char motif[], char nom[10]);
char *** liste_action(char motif[], agenda_t ** pag);

#endif
