// Haotian Deng
// hdeng@clemson.edu
// Nov 26 2018 Final Project

#include"myimage.h"

class ImageProcess{
public:
	void adjustBrightness(MyImage& img, MyImage& area, double value);
	void adjustSaturation(MyImage& img, MyImage& area, double value);
	void adjustContrast(MyImage& img, MyImage& area, double value);
	void adjustWhitebalance(MyImage& img, MyImage& area, double value);
	void adjustHighlight(MyImage& img, MyImage& area, double value);
	void adjustShadow(MyImage& img, MyImage& area, double value);
};
