#include "map.h"

#include "data.map"
#include <string.h>

void map_load( int world, int level, Map * map )
{

  memcpy( map, &worlds[world][level], sizeof( Map ) );

} 

int testValue(Map * map , int x , int y)
  {
    return((*map) [y][x] ) ;
  }

int testColl(Map * map , int x , int y)
  {

    int value ;
    value =  testValue(map , x , y) ;
    if (value == 2 || value == 5 || value == 7) { return(0) ;}
    else              { return(1) ;}


  }

void debugMap(Map * map,int x,int y,int d)
{
  int temp;
  switch(d)
  {
    case 1 :
      x = x-1;
      break;
    case 2 :
      y = y-1;
      break;
    case 3 :
      x = x+1;
      break;
    case 4 :
      y = y+1;
      break;
  }
  temp = (*map) [y][x] + 1 ;
  if (temp > 9)
  {
    temp = 0;
  }
  (*map) [y][x] = temp;

}


void spawnXY (Map * map , int * persoX , int * persoY)
    {

        int y = 0 , x = 0 ,value  ;
        
        for ( y = 0; y < MAP_HEIGHT ; ++y)
        {

            for ( x = 0; x < MAP_WIDTH; ++x)
            {
                value = (*map) [y][x] ;  
                if      (value == 7)                    
                  {   
                  
                  (*persoX) = x  ;
                  (*persoY) = y  ;

                  }
            }

        }
        
    }
int checkMap (Map * map)
  {

        int y = 0 , x = 0 ,value,temp = 1  ;
        
        for ( y = 0; y < MAP_HEIGHT ; ++y)
        {

            for ( x = 0; x < MAP_WIDTH; ++x)
            {
                value = (*map) [y][x] ;  
                if (value == 3)  
                {
                  return 0;
                }
            }

        }

        return 1;
        
    }

void nextLvl( int * world , int * level )
{

  (*level) ++   ;
  if ((*level) > 10)
  {
    (*world) ++  ;
    (*level) = 0 ;
  }
}
