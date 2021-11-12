#include "Video.h"
#include "object.h"
#include "stdlib.h"

volatile unsigned short* scanline_counter = (volatile unsigned short*) 0x4000006;

Video::Video()  {
	REG_DISPLAY = DISP_MODE_0 | DISP_BG0 | DISP_OBJ_MEM | DISP_1D_SPRITE;// | DISP_OBJ_MEM | DISP_BG0  ;
	this->assets = new AssetManager();
	this->rgb = new RGB();
    this->obj_attributes_length = 0;
	


	this->spriteLength = 0;
	this->sprites = (Sprite **)malloc(sizeof(Sprite*) * 256);
	
	this->assets->loadAnimation();
	this->assets->loadBackground();
}


void Video::loadSprite(int index)
{
	this->assets->loadSprite(index / 4);
	for (uint16 i = 0; i < 186; i++)
	{
		this->assets->changePalet(3 + i, rgb->getValue(1 * index + i));
	}
}


Sprite *Video::newSprite(int i)
{
	volatile obj_attrs *att = &oam_mem[obj_attributes_length];
	Sprite *sprite = new Sprite(att, i);
	obj_attributes_length++;
	return sprite;
}


void Video::wait_vblank()
{
	/* wait until all 160 lines have been updated */
	while (*scanline_counter >= 160);
	while (*scanline_counter < 160);
}
