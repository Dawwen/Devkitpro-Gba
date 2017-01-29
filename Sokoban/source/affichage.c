#include "toolbox.h"
#include "affichage.h"
#include "import.h"

void drawnTiles (int x,int y,int color)
	{

	int a,b ;
    const  int xmodif = 16 , ymodif = 2 ;

	for (a = 0; a < TilesC; ++a)
        {
            for (b = 0; b < TilesC; ++b)
            {
                m3_plot(x * TilesC + b + xmodif , y * TilesC + a + ymodif , color) ;
            }
        }
	}

void drawnLCircle (int x,int y,int color)
    {
        int xtemp,ytemp                             ;
        const int  xmodif = 16 + 5 , ymodif = 2 + 5    ;  
        drawnTiles(x,y,CLR_LIME)                    ;
        for (ytemp = 0; ytemp < 3; ++ytemp)
        {
            for (xtemp = 0; xtemp < 3; ++xtemp)
            {
                m3_plot(x * TilesC + xmodif + xtemp , y * TilesC + ymodif + ytemp , color) ;
            }
        }
        
        
        
    }

void drawnBCircle (int x,int y,int color)
    {
        int xtemp,ytemp                     ;
        const  int xmodif = 16 , ymodif = 2    ;
        drawnTiles(x,y,CLR_LIME)            ;

        for (ytemp = 0; ytemp < 3; ++ytemp) {   m3_plot(x * TilesC + 3 + xmodif, y * TilesC + 5 + ytemp + ymodif , CLR_BLACK) ;   }
        for (ytemp = 0; ytemp < 3; ++ytemp) {   m3_plot(x * TilesC + 9 + xmodif, y * TilesC + 5 + ytemp + ymodif , CLR_BLACK) ;   }

        for (ytemp = 0; ytemp < 5; ++ytemp) 
            {   
                if (ytemp == 0 || ytemp == 4)   {   m3_plot(x * TilesC + 4 + xmodif, y * TilesC + 4 + ytemp + ymodif, CLR_BLACK)    ;}
                else                            {   m3_plot(x * TilesC + 4 + xmodif, y * TilesC + 4 + ytemp + ymodif, color )       ;}   
            }
        for (ytemp = 0; ytemp < 5; ++ytemp) 
            {   
                if (ytemp == 0 || ytemp == 4)   {   m3_plot(x * TilesC + 8 + xmodif, y * TilesC + 4 + ytemp + ymodif, CLR_BLACK)    ;}
                else                            {   m3_plot(x * TilesC + 8 + xmodif, y * TilesC + 4 + ytemp + ymodif, color )       ;}   
            }

        for (ytemp = 0; ytemp < 7; ++ytemp) 
        {
            for (xtemp = 0; xtemp < 3; ++xtemp)
            {
                if (ytemp == 0 || ytemp == 6)   {   m3_plot(x * TilesC + 5 + xtemp + xmodif, y * TilesC + 3 + ytemp + ymodif, CLR_BLACK) ;   }
                else                            {   m3_plot(x * TilesC + 5 + xtemp + xmodif, y * TilesC + 3 + ytemp + ymodif, color)     ;   }
            }
        }
        
        
    }

void drawnPerso (int x,int y,int d)
    {
        draw_bitmap( perso_bm[d-1], x + 16, y + 2 );
    }

void drawnIntroScreen ()
    {
        draw_bitmap( &IntroScreen , 0,0);
    }

void drawnLvlUpScreen ()
    {
        draw_bitmap( &LvlUpScreen , 0,0);
    }

void drawnDebug()
{
    draw_bitmap( &Debug , 0,0);
}

void clearDebug()
{
    int x,y;
    for (x = 0; x < 13; ++x)
    {
        for (y = 0; y < 13; ++y)
        {
            m3_plot(x,y,CLR_BLACK);
        }
    }
}

void clearScreen() 
    {
        int i,j ;
        for (i = 0; i < 240; ++i)
        {
            for (j = 0; j < 160; ++j)
            {
                m3_plot(i,j,CLR_BLACK) ;
            }
        }
    }

int converTiles (int value)
    {

    switch(value)
    {
        
        case 1  :
            return(CLR_BLACK)   ;
            break               ;

        case 2  :
            return(CLR_LIME)    ;
            break               ;

        case 3  :
            return(CLR_BLUE)    ; /*    diamant désactivé    */
            break               ;

        case 4  :
            return(CLR_RED)     ; /*    diamant activé    */
            break               ;

        case 5  :
            return(CLR_RED)     ; /*    Socle de diamant    */
            break               ;

        case 7  :
            return(CLR_LIME)  ; /*    Personnage    */
            break               ;

        case 8 :
            return(RGB15(12,12,12)) ;
            break                   ;

        default :
            return(CLR_MAG) ;

    }
   
    }


/*
void mapRefresh (Carte* pointeur)
    {

        int y = 0 , x = 0   ;
        int color , value   ;

        
        for ( y = 0; y < TabYMax ; ++y)
        {

            for ( x = 0; x < TabXMax; ++x)
            {
                value = (*pointeur).list[y * TabXMax + x]   ;  
                color = converTiles(value)                  ;
                if      (value == 7)                    {   drawnPerso(x,y,color)   ;}
                else if (value == 3 || value == 4 )     {   drawnBCircle(x,y,color) ;}
                else if (value == 5)                    {   drawnLCircle(x,y,color) ;}
                else                                    {   drawnTiles(x,y,color)   ;}
            }

        }
        
    }
*/

void mapRefresh (Carte * map , int xperso , int yperso, int dirperso)
    {

        int y = 0 , x = 0   ;
        int color , value   ;

        
        for ( y = 0; y < TabYMax ; ++y)
        {

            for ( x = 0; x < TabXMax; ++x)
            {
                value = (*map).list [y][x] ;
                color = converTiles(value)   ;  
                if (value == 3 || value == 4 )          {   drawnBCircle(x,y,color) ;}
                else if (value == 5)                    {   drawnLCircle(x,y,color) ;}
                else                                    {   drawnTiles(x,y,color)   ;}
            }

        }

        drawnPerso(xperso * TilesC ,yperso * TilesC,dirperso)   ;
        
    }