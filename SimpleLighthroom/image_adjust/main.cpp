// Haotian Deng
// hdeng@clemson.edu
// Nov 26 2018 Final Project

#include<OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<iostream>
#include<vector>
#include"manager.h"
#include"resource.h"


Manager manager;
Resource res(640,480,4,new float[640*480*4]);
bool recordMouse = false;

void init(void)
{  
    manager.print();
	manager.run();
	manager.prepare(res.windowWidth,res.windowHeight,res.channels);
	res.displayData = new float[res.windowWidth*res.windowHeight*4];
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	manager.display(res.displayData);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(res.channels ==3)
		glDrawPixels(res.windowWidth,res.windowHeight,GL_RGB, GL_FLOAT, res.displayData);
	else if(res.channels ==4)
		glDrawPixels(res.windowWidth,res.windowHeight,GL_RGBA, GL_FLOAT, res.displayData);
	else if(res.channels ==1){
		glDrawPixels(res.windowWidth,res.windowHeight,GL_LUMINANCE, GL_FLOAT, res.displayData);
	}
	glFlush();
}

	
void handleKey(unsigned char key,int x, int y){
	x=x;//useless, just get rid of the warning
	y=y;//useless, just get rid of the warning
	switch(key){	
		case 'r':
			manager.resetImage();
			manager.display(res.displayData);
			break;
		case 'w':
			if(manager.canWrite()){
				if(manager.save()){
					std::cout << "saved"<< std::endl;
				}
				else{
					std::cout << "save file false" << std::endl;
				}
			}
			else{
				std::cout << "no filename" << std::endl;
			}
			break;

		case 'u':
			manager.undo();
			manager.display(res.displayData);	
			break;
		case 'o':
			manager.displayOriginal(res.displayData);
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
            manager.setUseBrush(0);
			manager.setMode(key);
			std::cout << "mode select " << key<< std::endl;
			break;

		case 'q':
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void SpecialKey(int Key, int x, int y){
	x = x;
	y = y;
	switch(Key){
		case GLUT_KEY_UP:
			manager.adjust(0.05);
			manager.display(res.displayData);	
			break;
		case GLUT_KEY_DOWN:
			manager.adjust(-0.05);
			manager.display(res.displayData);	
			break;
	
	}
	glutPostRedisplay();
}



int main(int argc, char** argv){
	if(!manager.parseArgs(argc, argv)){
		exit(-1);
	}

	init();	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(res.windowWidth,res.windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("adjust");
	glutDisplayFunc(display);

	glutKeyboardFunc(handleKey);
	glutSpecialFunc(SpecialKey);

	glutMainLoop();
	return 0;
}
