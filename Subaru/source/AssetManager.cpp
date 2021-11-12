#include "AssetManager.h"
// #include <stdio.h>
// #include <stdlib.h>
#include "object.h"

#include <math.h>

#define TILE_SIZE 8


// DMA HEADER

typedef struct DMA_REC
{
    const void *src;
    void *dst;
    uint32 cnt;
} DMA_REC;

#define REG_DMA ((volatile DMA_REC*)0x040000B0)

//! General DMA copier
inline void dma_cpy(void *dst, const void *src, uint16 count, int ch, uint16 mode)
{
    REG_DMA[3].cnt = 0; // shut off any previous transfer
    REG_DMA[3].src = src;
    REG_DMA[3].dst = dst;
    REG_DMA[3].cnt = 1 << 31 | 1 << 0x1A | count;
}
// DMA HEADER END





extern void*  __start_info[];
extern void*  __stop_info[];

AssetManager::AssetManager()
{
    t_sprite_data* offset= (t_sprite_data*)__start_info;
    this->data = offset;
    
    // Set object
    // volatile obj_attrs *att = oam_mem;
    this->sprites = (SpriteRessource **)malloc(sizeof(SpriteRessource*) * 2);
    this->sprites[0] = new SpriteRessource(offset);
    offset = (t_sprite_data*)this->sprites[0]->getNext();
    this->sprites[1] = new SpriteRessource(offset);
    sprites_length = 1;
}


void AssetManager::drawSprite(int *buffer, int index)
{
    // SpriteRessource &s = *(this->sprites);
    // s.drawSprite(buffer, index);
}

void AssetManager::loadAnimation()
{
    int palet_offset = 0;
    int tileset_offset = 0;

    for (int i=0; i < sprites_length; i++)
    {
        SpriteRessource *s = this->sprites[i];
        
        // Load palet        
        uint16 *data = s->getPalet();
        for (int k = 0; k < s->getPaletSize(); k++)
        {
            object_palet_mem[k + palet_offset] = data[k];
        }
        this->loadSprite(*s, 0, &tileset_offset, palet_offset);
        palet_offset += s->getPaletSize();
    }
}

void AssetManager::loadSprite(SpriteRessource &s, int index, int *tileset_offset, int palet_offset)
{
    uint16 *start_tile_mem   = (uint16 *)OBJECT_TILE_MEMORY[4][2];
    start_tile_mem = &(start_tile_mem[*tileset_offset]);

    // Load sprite
    // int frame = s.getAnimation(index);
    uint16 *data = s.getAnimationFrame(index); 
    int width = s.getWidth(), height = s.getHeight();

    // TODO: faire avec plusieurs palet
    // for (int i = 0; i < width*height / 4; i++)
    // {
    //     *start_tile_mem = data[i]; 
    //     start_tile_mem++;
    // }

    dma_cpy(start_tile_mem, data, width*height / 2, 3, 0);


    // Suppose the tile is a square
    // int nb_Tiles_Line = sqrt(width * height / (TILE_SIZE * TILE_SIZE));
    // // // For every line of tile
    // for (int i=0; i < nb_Tiles_Line; i++)
    // {
    //     // For every tile in the line
    //     for (int  j = 0; j < nb_Tiles_Line; j++)
    //     {
    //         // For each pixel in the tile
    //         for (int k = 0; k < TILE_SIZE / 4 * TILE_SIZE; k++)
    //         {
    //             int x = (k * 4) % TILE_SIZE + j * TILE_SIZE;
    //             int y = (k * 4) / TILE_SIZE + i * TILE_SIZE;

    //             uint16 value = 0;
    //             for (int l=0; l < 4; l++)
    //             {
    //                 int v = data[ y * width + x + l];
    //                 if (v != 0)
    //                     v += palet_offset;
    //                 value |= v << l * 4;//data[ y * width + x + l]
    //             }

    //             *start_tile_mem = value; 
    //             start_tile_mem++;
    //         }
    //     }
    // }
    *tileset_offset += width*height / 4;
}

void AssetManager::loadSprite(int index)
{
    int tileset_offset = 0;
    int palet_offset = 0;
    for (int i=0; i < sprites_length; i++)
    {
        SpriteRessource *s = this->sprites[i];
        this->loadSprite(*s, index, &tileset_offset, palet_offset);
        palet_offset += s->getPaletSize();
    }
}




volatile unsigned short* bg0_control = (volatile unsigned short*) 0x4000008;
volatile unsigned short* bg_palette = (volatile unsigned short*) 0x5000000;

/* return a pointer to one of the 4 character blocks (0-3) */
static inline volatile unsigned short* char_block(unsigned long block) {
	/* they are each 16K big */
	return (volatile unsigned short*) (0x6000000 + (block * 0x4000));
}
static inline volatile unsigned short* screen_block(unsigned long block) {
	/* they are each 2K big */
	return (volatile unsigned short*) (0x6000000 + (block * 0x800));
}

void AssetManager::loadBackground()
{

	/* set all control the bits in this register */
	*bg0_control = 0 |	/* priority, 0 is highest, 3 is lowest */
		(3 << 2)  |		/* the char block the image data is stored in */
		(0 << 6)  |		/* the mosaic flag */
		(1 << 7)  |		/* color mode, 0 is 16 colors, 1 is 256 colors */ ////////////////////////////////HAS BEEN CHANGED
		(0 << 8) |		/* the screen block the tile data is stored in */
		(1 << 13) |		/* wrapping flag */
		(0 << 14);		/* bg size, 0 is 256x256 */

    // Set the tileset
	volatile unsigned short* dest = char_block(3);
	for (int i = 0; i < 4*8; i++)
	{
		dest[i] = 0x0303;
	}
    dest += 32;

    int offset = 3;
    //                  nb_tile * x * y
    for (int i = 0; i < 30*4*8; i++) { //128
        int tile = i / (8 * 4);
		// dest[i] = 4 << 8 | 3;
		dest[i] = offset + ( 8 * tile + (2 * (i % 4) + 1)) % 186  << 8 | offset + ( 8 * tile + (2 * (i % 4))) % 186;
		// dest[i] = (line * 8 + 2 * off + 4) << 8 | (line * 8 + 2 * off + 4);
	}

    bg_palette[3] = 0xffff;
    for (int i = 4; i < 128; i++)
    {
        bg_palette[i] = i % 32;
    }
    // Set the tilemap
    volatile unsigned short* data = screen_block(0);
    // int size = 30*20;
	// for (int i = 0; i < size; i++) {
	// 	data[(i/30)*32 + i%30] = 0;//i/30 + 2;//0;
	// }
    int size = 30*20;
	for (int i = 0; i < size; i++) {
		data[(i/30)*32 + i%30] = 1 + (i % 30);
	}
}

void AssetManager::changePalet(int index, uint16 color)
{
    bg_palette[index] = color;
}
