
#ifndef class_H

#define class_H
#define TabVMax			192
#define TabXMax			16
#define TabYMax			12

#include "map.h"

typedef struct Perso Perso ; 	
typedef struct Carte Carte ; 

struct Perso
        {
            int x            ;
            int y          	 ;
            int direction  	 ;
        }              	     ; 

struct Carte
     {
            int level         ;
            int world       ;
            Map list	;    
     }                      ;

void initPerso (Perso* pointeur) ;
void initCarte (Carte* pointeur, int world,  int level); 


#endif // class_H