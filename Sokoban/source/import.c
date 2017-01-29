#include "import.h"


Bitmap PersoUp =
#include "Bitmap/PersoUp.bmp.bit"
;

Bitmap PersoDown =
#include "Bitmap/PersoDown.bmp.bit"
;

Bitmap PersoRight =
#include "Bitmap/PersoRight.bmp.bit"
;

Bitmap PersoLeft =
#include "Bitmap/PersoLeft.bmp.bit"
;

const Bitmap Debug =
#include "Bitmap/Debug.bmp.bit"
;

const Bitmap IntroScreen =
#include "Bitmap/IntroScreen.bmp.bit"
;
const Bitmap LvlUpScreen =
#include "Bitmap/LvlUpScreen.bmp.bit"
;


Bitmap * perso_bm[4] = {
	&PersoLeft,
	&PersoUp,
	&PersoRight,
	&PersoDown,
};

