// Haotian Deng
// hdeng@clemson.edu
// Nov 26 2018 Final Project

#include"manager.h"
#include"colorwindow.h"

bool Manager::parseArgs(int argc, char** argv){ //process argument
	if(argc < 3)
		return false;
	int fileCount=0;
	char* tmpFilenameList[2];

	for(int i = 1; i!= argc; i++){

		if(fileCount <3){
			tmpFilenameList[fileCount] = argv[i];
			fileCount++;
		}else {
			return false;
		}
	}

	imageFilename= tmpFilenameList[0];
	if(fileCount==2){
		writeFlag= true;
		resultFilename = tmpFilenameList[1];
	}
	return true;
}

void Manager::print(){
	std::cout << "==========================================" << std::endl;
	std::cout << "usage: press number 1-6 to select mode" << std::endl;
	std::cout << "up key to enhance effect" << std::endl;
	std::cout << "down key to reduce effect" << std::endl;	
	std::cout << "==========================================" << std::endl;
	std::cout << "1 adjust brightness  " << std::endl;
	std::cout << "2 adjust saturation " << std::endl;
	std::cout << "3 adjust highlight " << std::endl;
	std::cout << "4 adjust shadow " << std::endl;
	std::cout << "5 adjust whitebalance " << std::endl;
	std::cout << "6 adjust contrast " << std::endl;
  	std::cout << "==========================================" << std::endl;
 
	std::cout << "w write to file " << std::endl;
	std::cout << "o display original image " << std::endl;
	std::cout << "u undo modification " << std::endl;
	std::cout << "==========================================" << std::endl;

}

void Manager::run(){	
	//read image
	if(!FileIO::getInstance().readFromFileToImage(originImage,imageFilename)){
		exit(-1);	
	}
	//initialize the result image
	originImage = originImage.to4ChannelsImage();
	resultImage = originImage;
	historyImages.push_back(MyImage(resultImage));
	float* maskData = new float[resultImage.width* resultImage.height];
	for(int i = 0; i!= resultImage.width* resultImage.height; i++){
		maskData[i] = 0.0;
	}
	//same width and height as the original image
	maskImage = MyImage(resultImage.width, resultImage.height, 1,maskData );
}



bool Manager::save(){
	//save the current result
	if(!FileIO::getInstance().writeImageToFile(resultImage,resultFilename)){
		return false;
	}
	return true;
}



void Manager::resetImage(){
	//reset the image to original Image
	resultImage = originImage;
	historyImages.clear();
	historyImages.push_back(MyImage(resultImage));
}

void Manager::undo(){
	if(historyImages.size()>1){
		historyImages.pop_back();
		if(!historyImages.empty())
			resultImage= historyImages.back();
	}
}

bool Manager::canWrite(){
	//there are output filename
	return writeFlag;
}

void Manager::display(float* des){
	resultImage.displayOutput(des);
}

void Manager::displayOriginal(float* des){
	originImage.displayOutput(des);
}

void Manager::prepare(int& w, int& h, int& c){
	//set weight height channels for displaying
	w = originImage.getWidth();
	h = originImage.getHeight();
	c = originImage.getChannels();
}

void Manager::setMode(int i){
	// ascii '0' is 48
	if(i < '7' && i > '0'){
		mode = i-48;
	}
}

void Manager::setUseBrush(int i){
	useBrush= i;
	if(i == 0){
		for(int i = 0; i!= resultImage.width* resultImage.height; i++){
			maskImage.data[i] = 1;
		}
	}
	else{
		for(int i = 0; i!= resultImage.width* resultImage.height; i++){
			maskImage.data[i] = 0;
		}

	}
}


void Manager::adjust(double value){
	//different function will be called
	switch(mode){
		case 1:
			ip.adjustBrightness(resultImage, maskImage, value);
			break;
		case 2:
			ip.adjustSaturation(resultImage, maskImage, value);
			break;
		case 3:

			ip.adjustHighlight(resultImage,maskImage, value);
			break;
		case 4:
			ip.adjustShadow(resultImage,maskImage, value);
			break;
		case 5:
			ip.adjustWhitebalance(resultImage, maskImage, value);
			break;
		case 6:
			ip.adjustContrast(resultImage, maskImage,value);
			break;
	}

	historyImages.push_back(MyImage(resultImage));

}



