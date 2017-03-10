#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "structures.h"
#deifne TMAX 100



int main()                                                                                      
{   
    printf("test sauvegarde agenda vide : pas de testvide.txt \n");
    agenda_t * vide = NULL;                                        
    agenda_t ** pvide = &vide;                                     
    sauvegarde("testvide.txt",pvide);                              
    printf("test creation : résultat testcreation.txt \n");                                     
    agenda_t ** pag = creation("test.txt");                                                     
    sauvegarde("testcreation.txt",pag);                                                         
    /*creation manuelle d'un agenda*/                                                           
    agenda_t *ag = (agenda_t *) malloc(sizeof(agenda_t));                                       
    action_t *ac = (action_t *) malloc(sizeof(action_t));                                       
    strcpy(ag->date, "200405");                                                                 
    strcpy(ac->nom, "TPs de SDD");                                                              
    strcpy(ac->moment, "112");                                                                  
    ac->suivant = NULL;                                                                         
    ag->actions = &ac;                                                                          
    agenda_t *ag1 = (agenda_t *) malloc(sizeof(agenda_t));                                      
    action_t *ac1 = (action_t *) malloc(sizeof(action_t));                                      
    strcpy(ag1->date, "201842");                                                                
    strcpy(ac1->nom, "TPs de CSN");                                                             
    strcpy(ac1->moment, "420");                                                                 
    ag1->suivant = NULL;                                                                        
    ag1->actions = &ac1;                                                                        
    action_t *ac2 = (action_t *) malloc(sizeof(action_t));                                      
    strcpy(ac2->nom, "Cours de C#");                                                            
    strcpy(ac2->moment, "518");                                                                 
    ac1->suivant = ac2;                                                                         
    ag->suivant = ag1;                                                                          
    agenda_t **pag2 = &ag;                                                                      
    /*printf("test creation liste contigue motif présent : \n");                                
    char *** tete1 = liste_action("TPs",pag2);                                                  
    char * cour = (char *) malloc(sizeof(char[10]));                                            
    for (cour = *tete1[1]; cour < *tete1[2]; cour+=sizeof(char[10]))                            
    {                                                                                           
        printf(" %s \n ", cour);                                                                
    }                                                                                           
    printf("test creation liste contigue motif inexistant : \n");                               
    for (cour = *tete1[1]; cour < *tete1[2]; cour+=sizeof(char[10]))                            
    {                                                                                           
      printf(" %s \n ", cour);                                                                  
    }  */                                                                                       
    printf("test suppression élément inexistant :\n");                                          
    int cd1 = supprime("000000","00",pag2);                                                     
    if (cd1)                                                                                    
    {                                                                                           
        printf("suppression réussie\n");                                                        
    }                                                                                           
    else                                                                                        
    {                                                                                           
        printf("suppression ratée\n");                                                          
    }                                                                                           
    sauvegarde("testsup1.txt", pag2);                                                           
    printf("sauvegarde testsup1.txt \n");                                                       
    printf("test suppression élément existant :\n");                                            
    int cd2 = supprime("201842", "420", pag2);                                                  
    if (cd2)                                                                                    
    {                                                                                           
        printf("suppression réussie \n");                                                       
    }                                                                                           
    else                                                                                        
    {                                                                                           
        printf("suppression ratée \n");                                                         
    }                                                                                           
    sauvegarde("testsup2.txt", pag2);                                                           
    printf("sauvegarde testsup2.txt \n");                                                       
    return 0;                                                                                   
}                                                                                               
