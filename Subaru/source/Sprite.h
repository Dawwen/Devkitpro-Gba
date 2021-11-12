#ifndef SPRITE_H
#define SPRITE_H

#include "toolbox.h"
#include "object.h"

class Sprite {
    private:
        int x;
        int y;
        volatile obj_attrs *obj_att;

    public:
        Sprite(volatile obj_attrs * att, int index);
        Sprite(volatile obj_attrs * att) : Sprite(att, 2) {};

        int getX();
        int getY();

        void setX(int x);
        void setY(int y);


        void move(int dx, int dy);
};
#endif