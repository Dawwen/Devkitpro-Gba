#ifndef RGB_H
#define RGB_H

#include "toolbox.h"

class RGB
{
	private:
		uint16 rgb_data[186];

	public:
		RGB();
		uint16 getValue(int i);
};

#endif
