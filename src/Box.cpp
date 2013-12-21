#include <iostream>

#include "Box.h"
#include "GL/glut.h"

using namespace std;
Box::Box(float r, float g, float b, float s){

	red = r;
	green = g;
	blue = b;

	size = s;
}


Box::~Box(void){
	
}

void Box::draw(){

	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();

		glColor3f(red, green, blue);

		glLineWidth(2);
		glutWireCube(size);
		glLineWidth(1);

	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopAttrib();

}

float Box::getSize(){
   return size;
}
