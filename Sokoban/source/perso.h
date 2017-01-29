#ifndef perso_H
#define perso_H

#include "map.h"

void persoMoveUp(Map * map , int * xperso , int * yperso , int * direction) ;
void persoMoveDown(Map * map , int * xperso , int * yperso , int * direction) ;
void persoMoveLeft(Map * map , int * xperso , int * yperso , int * direction) ;
void persoMoveRight(Map * map , int * xperso , int * yperso , int * direction) ;
void persoPush(Map * map , int * xperso , int * yperso , int * direction);


#endif