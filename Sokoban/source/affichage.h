#ifndef affichage_H
#define affichage_H

#include "class.h"
#include "map.h"
#include "bitmap.h"

#define TilesC        	13
#define Middle		TilesC/2 + 1



void drawnTiles (int x,int y,int color) 	;
void drawnLCircle (int x,int y,int color)	;
void drawnBCircle (int x,int y,int color)	;
void drawnPerso (int x,int y,int d)		;
void clearScreen() 						;
void drawnIntroScreen ()				;
void drawnLvlUpScreen ()				;
//void mapRefresh (Carte* pointeur)			;
void mapRefresh (Carte * map , int xperso , int yperso, int dirperso) ;
int converTiles (int value)					;
void clearDebug();
void drawnDebug();

#endif // affichage_H