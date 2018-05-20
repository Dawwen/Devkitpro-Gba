#include "perso.h"



void persoMoveUp(Map * map , int * xperso , int * yperso , int * direction)
	{

		int dir = (*direction);

		if (dir != 2 )
		{
			(*direction) = 2 ;
		}
		else
		{
			int value ;
			value = testColl(map , (*xperso) , (*yperso) - 1 ) ;

			if ( value == 0)
			{
				(*yperso) = (*yperso) - 1	;
			}
			else
			{
				persoPush(map ,xperso,yperso,direction);
			}
		}

	}

void persoMoveDown(Map * map , int * xperso , int * yperso , int * direction)
	{
		int dir = (*direction);

		if (dir != 4 )
		{
			(*direction) = 4 ;
		}
		else
		{
			int value ;
			value = testColl(map , (*xperso) , (*yperso) + 1 ) ;

			if ( value == 0)
			{
				(*yperso) = (*yperso) + 1	;
			}
			else
			{
				persoPush(map,xperso,yperso,direction);
			}
		}


	}

void persoMoveLeft(Map * map , int * xperso , int * yperso , int * direction)
	{

		int dir = (*direction);

		if (dir != 1 )
		{
			(*direction) = 1 ;
		}
		else
		{
			int value ;
			value = testColl(map , (*xperso) - 1 , (*yperso) ) ;

			if ( value == 0)
			{
				(*xperso) = (*xperso) - 1	;
			}
			else
			{
				persoPush(map,xperso,yperso,direction);
			}

		}


	}

void persoMoveRight(Map * map , int * xperso , int * yperso , int * direction)
	{
		int dir = (*direction);

		if (dir != 3 )
		{
			(*direction) = 3 ;
		}
		else
		{
			int value ;
			value = testColl(map , (*xperso) + 1 , (*yperso) ) ;

			if ( value == 0)
			{
				(*xperso) = (*xperso) + 1	;
			}
			else
			{
				persoPush(map,xperso,yperso,direction);
			}
		}

	}

void persoPush(Map * map , int * xperso , int * yperso , int * direction)
{

	int dir ,x1,x2,y1,y2,value;
	int Push = 0;
	dir = (*direction) ;

	switch(dir)
		{
			case 1 :

				x1 = (*xperso) -1 	;
				x2 = (*xperso) -2	;
				y1 = (*yperso)		;
				y2 = (*yperso)		;
				break			;

			case 2 :

				x1 = (*xperso)	 	;
				x2 = (*xperso)		;
				y1 = (*yperso) -1	;
				y2 = (*yperso) -2	;
				break			;

			case 3 :

				x1 = (*xperso) +1 	;
				x2 = (*xperso) +2	;
				y1 = (*yperso)		;
				y2 = (*yperso)		;
				break			;

			case 4 :

				x1 = (*xperso)  	;
				x2 = (*xperso) 		;
				y1 = (*yperso) +1	;
				y2 = (*yperso) +2	;
				break			;
		}

	value = testValue(map , x1 , y1 ) ;

	if ( value == 3 )
	{
		value = testValue(map , x2 , y2 ) ;

		switch(value)
		{
			case 2 :
				(*map) [y1][x1] = 2 ;
				(*map) [y2][x2] = 3 ;
				Push = 1;
				break	;

			case 5 :
				(*map) [y1][x1] = 2 ;
				(*map) [y2][x2] = 4 ;
				Push = 1;
				break;

			case 7 :
				(*map) [y1][x1] = 2 ;
				(*map) [y2][x2] = 3 ;
				Push = 1;
				break;
		}
	}

	else if (value ==4 )
	{
		value = testValue(map , x2 , y2 ) ;
		switch(value)
		{
			case 2 :
				(*map) [y1][x1] = 5 ;
				(*map) [y2][x2] = 3 ;
				Push = 1;
				break;

			case 5 :
				(*map) [y1][x1] = 5 ;
				(*map) [y2][x2] = 4 ;
				Push = 1;
				break;
		}
	}


	if (Push == 1)
	{
		switch(dir)
		{
			case 1 :
				(*xperso) = (*xperso) - 1;
				break;
			case 2 :
				(*yperso) = (*yperso) - 1;
				break;
			case 3 :
				(*xperso) = (*xperso) + 1;
				break;
			case 4 :
				(*yperso) = (*yperso) + 1;
				break;
		}
	}



}
