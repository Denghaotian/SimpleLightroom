// Haotian Deng
// hdeng@clemson.edu
// Nov 26 2018 Final Project

#include"myimage.h"
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<vector>
#include"fileio.h"
#include"imageprocess.h"
#include <string>

class Manager{
public:
	bool parseArgs(int argc, char** argv);
	void run();
	bool save();
	void resetImage();
	void undo();
	bool canWrite();
	void print();
	//output image data to displaying buffer
	void display(float* des);
	//initialize the display buffer and windowsize 
	void prepare(int& wid, int& hei, int& c);

	void setMode(int i);
    void setUseBrush(int i);//key
	
	void adjust(double value);

	void displayOriginal(float* des);


	Manager():
		writeFlag(false),
		mode(1),
	

		maskImage(MyImage()),
		imageFilename(new char[0]),
		resultFilename(new char[0]),
		
		originImage(MyImage()),
		resultImage(MyImage()),
		historyImages(std::vector<MyImage>()),
		ip(ImageProcess())
	{}
	~Manager(){}

private:
	bool writeFlag;

	int mode;
	/*
	1 Brightness
	2 Saturation
	3 Hightlight
	4 Shadow 
	5 Whitebalance
	6 Contrast
	*/
	int useBrush; 
	MyImage maskImage;

	char* imageFilename;
	char* resultFilename;

	MyImage originImage;
	MyImage resultImage;
	std::vector<MyImage> historyImages; 
	ImageProcess ip;
	
	Manager(const Manager& m);
	Manager& operator=(const Manager& m);
};
