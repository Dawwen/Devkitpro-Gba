#include "class.h"

void initPerso (Perso* pointeur) 
	{

		(*pointeur).x = 0			;
		(*pointeur).y = 0			;
		(*pointeur).direction = 1 	;

	}

void initCarte (Carte* pointeur, int world,  int level) 
	{
		(*pointeur).level = level;
		(*pointeur).world = world;
		map_load( world, level, &pointeur->list) ;
	}