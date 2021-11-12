#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "data.h"
#include "toolbox.h"
#include "SpriteRessource.h"

class AssetManager {
    private:
        t_sprite_data *data;
        int sprites_length;
        SpriteRessource **sprites;
    
    public:
        AssetManager();
        void loadAnimation();
        void drawSprite(int *buffer, int index);
        void loadSprite(SpriteRessource& s, int index, int*tileset_offset, int palet_offset);
        void loadSprite(int index);
        void loadBackground();
        void changePalet(int index, uint16 color);

};

#endif