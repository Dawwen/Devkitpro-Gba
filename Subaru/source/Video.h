
#ifndef VIDEO_H
#define VIDEO_H

#include "toolbox.h"
#include "AssetManager.h"
#include "RGB.h"
#include "Sprite.h"


class Video
{
	private:
		AssetManager *assets;
        RGB *rgb;
		int obj_attributes_length; 

		uint16 spriteLength;
		Sprite **sprites;

//		vuint16 *data;
	public:
		Video();
		void wait_vblank();
		void loadSprite(int index);
		Sprite *newSprite(int index);
};

#endif
