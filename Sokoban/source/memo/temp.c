#include "toolbox.h"
#include "affichage.h"


typedef COLOR BitmapTile [TilesC][TilesC];

typedef bool MonoBitmapTile [TilesC][TilesC];

void drawnBitmap (int x,int y,BitmapTile * b)
{

	int i,j;
	for (i = 0; i < TilesC; ++i)
	{
		for (j = 0; j < TilesC; ++j)
		{
			m3_plot( x*TilesC+j, y*TilesC+i, (*b)[i][j]) ;
		}
	}
}

void drawnMonoBitmap (int x,int y,MonoBitmapTile * b, COLOR c)
{

	int i,j;
	for (i = 0; i < TilesC; ++i)
	{
		for (j = 0; j < TilesC; ++j)
		{
			m3_plot( x*TilesC+j, y*TilesC+i, (*b)[i][j]) ;
		}
	}
}

BitmapTile TRIANGLE = { 
	{CLR_BLACK},
	{CLR_YELLOW, CLR_YELLOW, CLR_YELLOW, CLR_YELLOW } ,
	{CLR_YELLOW, CLR_BLACK, CLR_BLACK, CLR_YELLOW } ,
	{CLR_YELLOW, CLR_BLACK, CLR_BLACK, CLR_YELLOW } ,
	{CLR_YELLOW, CLR_YELLOW, CLR_YELLOW, CLR_YELLOW } ,
	{CLR_BLACK, CLR_BLACK, CLR_BLACK, CLR_YELLOW } ,
	{CLR_BLACK, CLR_BLACK, CLR_BLACK, CLR_YELLOW } ,
	{CLR_BLACK, CLR_BLACK, CLR_BLACK, CLR_YELLOW } 
	};

MonoBitmapTile TRIANGLE = { 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};


void mapRefresh2 (Carte* pointeur)
    {

        int y = 0 , x = 0   ;
        int color , value   ;

        for ( y = 0; y < TabYMax ; ++y)
        {

            for ( x = 0; x < TabXMax; ++x)
            {
            	drawnBitmap( x,y, &TRIANGLE );
            }

        }
    }