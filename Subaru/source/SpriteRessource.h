#ifndef SPRITE_RESSOURCE_H
#define SPRITE_RESSOURCE_H

#include "data.h"
#include "toolbox.h"

class SpriteRessource {
    private:
        // int x;
        // int y;
        // volatile obj_attrs *obj_att;

        int width;
        int height;
        int atlas_length;
        uint16 *atlas;
        int palet_length;
        uint16 *palet;
        int animation_length;
        uint16 *animation;

    public:
        SpriteRessource(t_sprite_data *sprite);
        void drawSprite(int *buffer, int index);
        uint16* getSprite(int index);
        uint16* getPalet();
        int getPaletSize();
        int getAnimationLength();
        uint16* getAnimationFrame(int i);
        int getWidth();
        int getHeight();
        void* getNext();
};

#endif