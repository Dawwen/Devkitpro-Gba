#include "toolbox.h"
#include "class.h"
#include "perso.h"
#include "affichage.h"
#include "map.h"
#include "input.h"

#include "bitmap.h"


int main()  {

    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;

    drawnIntroScreen() ;
    int comp ;
    while(1)
    {
        key_poll()  ;
        if (key_hit(KEY_START))
        {
            break   ;
        }
    }
    clearScreen()           ;
    int refresh,check,debug =0 ;
    Perso hero              ;
    Carte map               ;
    initPerso(&hero)        ;
    initCarte(&map, 0, 0)         ;



    while (1) {
        initCarte(&map, map.world, map.level)           ;
        spawnXY( &map.list , &hero.x , &hero.y )        ;

        mapRefresh( &map , hero.x , hero.y ,hero.direction)            ;

        while (1)
        {
            key_poll()              ;

            if (key_was_down(KEY_R) && key_hit(KEY_B))
            {
                debug++;
                if (debug > 1)
                {
                    debug = 0;
                }
                refresh = 1;
            }
            if (key_hit(KEY_L) && debug == 1)
            {
                nextLvl(&map.world,&map.level) ;
                break;
            }
            if (key_hit(KEY_B) && debug == 1)
            {
                debugMap(&map.list ,hero.x,hero.y,hero.direction);
                refresh = 1;
            }
            else if (key_hit(KEY_A))
            {
                persoPush( &map.list , &hero.x , &hero.y , &hero.direction ) ;
                refresh = 1 ;
                check = 1   ;
            }
            else if (key_hit(KEY_SELECT))
            {
                initCarte(&map, map.world, map.level)           ;
                spawnXY( &map.list , &hero.x , &hero.y )        ;
                refresh = 1 ;
            }


            else if (key_hit(KEY_UP))
            {
                persoMoveUp( &map.list , &hero.x , &hero.y , &hero.direction ) ;
                refresh = 1 ;
		check = 1;
            }
            else if (key_hit(KEY_DOWN))
            {
                persoMoveDown( &map.list , &hero.x , &hero.y , &hero.direction) ;
                refresh = 1 ;
		check = 1;
            }
            else if (key_hit(KEY_LEFT))
            {
                persoMoveLeft( &map.list , &hero.x , &hero.y , &hero.direction) ;
                refresh = 1 ;
		check = 1;
            }
            else if (key_hit(KEY_RIGHT))
            {
                persoMoveRight( &map.list , &hero.x , &hero.y , &hero.direction) ;
                refresh = 1 ;
		check = 1;
            }

            if (check == 1)
            {
                check = 0 ;
                if (checkMap(&map.list))
                {
                    drawnLvlUpScreen()  ;
                    while(1)
                    {
                        key_poll()  ;
                        if (key_hit(KEY_A) || key_hit(KEY_START) || key_hit(KEY_LEFT) || key_hit(KEY_RIGHT) || key_hit(KEY_UP) || key_hit(KEY_DOWN) )
                        {
                            break   ;
                        }
                    }
                    clearScreen()       ;
                    nextLvl(&map.world,&map.level) ;
                    break   ;
                }

            }
            if (refresh == 1)
            {
                refresh = 0 ;
                if (debug == 1)
                {
                    drawnDebug();
                }
                else
                {
                    clearDebug();
                }

                mapRefresh( &map , hero.x , hero.y ,hero.direction)            ;

            }

        }

    };
    return 0;
}
