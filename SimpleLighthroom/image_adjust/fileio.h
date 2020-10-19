// Haotian Deng
// hdeng@clemson.edu
// Nov 26 2018 Final Project

#include"myimage.h"

class FileIO{
public:
	static FileIO& getInstance();
	bool readFromFileToImage(MyImage& my, char* filename);
	bool writeImageToFile(const MyImage& my, char* filename);

private:
	FileIO(){}
	FileIO(const FileIO& fi);
};

