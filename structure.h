#ifndef STRUCTURE
#define STRUCTURE

typedef struct action
{
    char                moment[3];
    char                nom[10];
    struct action     * suivant ;
} action_t;

typedef struct agenda
{
    char                date[6];
    action_t          * actions;
    struct agenda     * suivant;
} agenda_t ;

void inserer_agenda(agenda_t * ag , agenda_t ** pag);
void inserer_action(action_t * ac , action_t ** pac);
int supprimer_agenda(char date[6], agenda_t ** pag);
int supprimer_action(char moment[3], action_t ** pac);

#endif