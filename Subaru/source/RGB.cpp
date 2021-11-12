#include "RGB.h"

RGB::RGB()
{
	unsigned char rgb[3];
    int index = 0;
	bool state = 0;
	
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 31;
	
	for (int i=0; i < 186; i++)
	{
		if (state && rgb[index] == 0)
		{
			index = (index + 2) % 3;
			state = false;
		}
		if (!state && rgb[index] == 31)
		{
			index = (index + 2) % 3;
			state = true;
		}
		
		
		if (state)
		{
			rgb[index]--;
		}
		else
		{
			rgb[index]++;
		}
		
		
		rgb_data[i] =  rgb[2] << 10 | rgb[1] << 5 | rgb[0];
	}
}
	
uint16 RGB::getValue(int i)
{	
	return rgb_data[i % 186];
}
