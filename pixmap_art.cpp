#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;
int main(int argc, char** argv)
{
	ppm_image image;
	image.load("../images/landscape.ppm");
	ppm_image gamma = image.gammaCorrect(0.6f);
	ppm_image swirl = gamma.swirl_color();
	swirl.save("art-work-1.ppm");
	ppm_image greyscale = swirl.grayscale();
	
	ppm_image blur = greyscale.blur();

	blur.save("after-blur.ppm");

	ppm_image earth;
	earth.load("../images/earth-ascii.ppm");

	int x = (int)(0.5f * (blur.width() - earth.width()));
	int y = (int)(0.5f * (blur.height() - earth.height()));
	ppm_image background = blur.subimage(x, y, earth.width(), earth.height());

	ppm_image blend = background.alpha_blend(earth, 0.5f);
	blur.replace(blend, x, y);

	blur.save("art-work.ppm");

}

