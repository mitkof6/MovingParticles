#include "Box.h"
#include "GL/glut.h"

Box::Box(float r, float g, float b, float s){

	red = r;
	green = g;
	blue = b;

	size = s;
}


Box::~Box(void){

}

void Box::draw(){

	glPushMatrix();

		glColor3f(red, green, blue);
		glutWireCube(size);

	glPopMatrix();

}

float Box::getSize(){
   return size;
}
