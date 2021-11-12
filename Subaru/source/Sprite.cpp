#include "Sprite.h"


Sprite::Sprite(volatile obj_attrs * att, int index)
{
    this->x = 0;
    this->y = 0;
    
    this->obj_att = att;
    // Set object Attribute
    set_object_bpp(att, 0);
	set_object_palet(att, 0);

	set_object_shape(att, 0);
    set_object_tile(att, index);
	set_object_size(att, 2);
}

int Sprite::getX()
{
    return this->x;
}

int Sprite::getY()
{
    return this->y;
}

void Sprite::setX(int x)
{
    this->x = x;

    set_object_position(this->obj_att, this->x, this->y);
}

void Sprite::setY(int y)
{
    this->y = y;

    set_object_position(this->obj_att, this->x, this->y);
}

void Sprite::move(int dx, int dy)
{
    this->x = this->x + dx;
    this->y = this->y + dy;

    set_object_position(this->obj_att, this->x, this->y);
}