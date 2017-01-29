#ifndef map_H
#define map_H


#define MAP_WIDTH 16
#define MAP_HEIGHT 12
#define MAP_COUNT 10

#define WORLD_COUNT 3


typedef unsigned char CASE;

typedef  CASE Map[MAP_HEIGHT][MAP_WIDTH];

typedef Map World[MAP_COUNT];

void map_load( int world, int level, Map * map ); 
int testValue(Map * map , int x , int y) ;
int testColl(Map * map , int x , int y)	;
void spawnXY (Map * map , int * persoX , int * persoY);
int checkMap (Map * map);
void debugMap(Map * map,int x,int y,int d);

#endif