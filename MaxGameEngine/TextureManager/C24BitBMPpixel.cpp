// Written by Michael Feeney, Fanshawe College, 2006

#include "C24BitBMPpixel.h"

// Default constructor - all zeros
C24BitBMPpixel::C24BitBMPpixel()
: redPixel(0), greenPixel(0), bluePixel(0)
{
	return;
}

C24BitBMPpixel::C24BitBMPpixel(uchar red, uchar green, uchar blue)
: redPixel(red), greenPixel(green), bluePixel(blue)
{
	return;
}

C24BitBMPpixel::~C24BitBMPpixel()
{
	return;
}

// Default constructor - all zeros
C32BitBMPpixel::C32BitBMPpixel()
: redPixel(0), greenPixel(0), bluePixel(0), alphaPixel(1)
{
	return;
}

C32BitBMPpixel::C32BitBMPpixel(uchar red, uchar green, uchar blue)
: redPixel(red), greenPixel(green), bluePixel(blue), alphaPixel(1)
{
	return;
}

C32BitBMPpixel::C32BitBMPpixel(uchar red, uchar green, uchar blue, uchar aplha)
: redPixel(red), greenPixel(green), bluePixel(blue), alphaPixel(aplha)
{
	return;
}

C32BitBMPpixel::~C32BitBMPpixel()
{
	return;
}
