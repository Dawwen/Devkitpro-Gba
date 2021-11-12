#include "Video.h"
#include "stdlib.h"

#define DUCK_NB 10

int main()
{
	Video video;
	Sprite **sprites = (Sprite **)malloc(sizeof(Sprite*) * 256);
	uint16 speed[256];
	
	int i=1;

	for (int j = 0; j < DUCK_NB; j++)
	{
		sprites[j] = video.newSprite(2);
		sprites[j]->setX(rand() % 240);
		sprites[j]->setY(rand() % 160);
		speed[j] = rand() % 3 + 1;
	}

	sprites[127] = video.newSprite(2);
	sprites[127]->move(104,64);


	while(1)
	{	
		if (i % 2 == 0)
		{
			for (uint16 k = 0; k < DUCK_NB; k++)
			{
				sprites[k]->move(speed[k],0);
				if (sprites[k]->getX() >= 240)
				{
					sprites[k]->setY(rand() % 128);
					sprites[k]->setX(-32);
					speed[k] = rand() % 3 + 3;
				}
			}
		}


		
		video.loadSprite(i);

		// video.wait_vblank();
		i++;
	}
	return 1;
}
