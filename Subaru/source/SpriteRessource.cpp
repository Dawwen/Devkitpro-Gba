#include "SpriteRessource.h"


SpriteRessource::SpriteRessource(t_sprite_data *data)
{
    this->width = data->X;
    this->height = data->Y;

    this->atlas_length = data->atlas_length;
    this->palet_length = data->palet_length;
    this->animation_length = data->ani_length;
    
    this->atlas = data->data;
    this->palet = data->data + (data->X * data->Y * data-> atlas_length / 4);
    this->animation = data->data + (data->X * data->Y * data-> atlas_length / 4) + data->palet_length;
}

void SpriteRessource::drawSprite(int *buffer, int index)
{
    int frame = this->animation[index % this->animation_length];
    uint16 *offset = this->atlas + this->width * this->height * frame;

    for (int i=0; i < this->width * this->height; i++)
    {
        buffer[i] = this->palet[offset[i]];
    }
}


uint16* SpriteRessource::getSprite(int index)
{
    uint16 *offset = this->atlas + this->width * this->height * index;
    return offset;
}

uint16* SpriteRessource::getPalet()
{
    return this->palet;
}

int SpriteRessource::getAnimationLength()
{
    return this->animation_length;
}

uint16* SpriteRessource::getAnimationFrame(int i)
{
    int frame = this->animation[i % this->animation_length];
    return &(this->atlas[frame * this->width * this->height / 4]);
}


int SpriteRessource::getPaletSize()
{
    return this->palet_length;
}

int SpriteRessource::getWidth()
{
    return this->width;
}

int SpriteRessource::getHeight()
{
    return this->height;
}

void* SpriteRessource::getNext()
{
    return this->atlas + (this->width * this->height * this->atlas_length) + this->palet_length + this->animation_length;
}
