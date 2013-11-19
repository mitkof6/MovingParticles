#ifndef TEAPOT_H_
#define TEAPOT_H_

#include "Renderable.h"
#include "GL\glut.h"

class TeaPot : public Renderable{

public:
	TeaPot(float r, float g, float b, int s) : Renderable(r, g, b){
		size = s;	
	}
	~TeaPot(void);

	void draw(){
		glPopMatrix();

		glColor3f(red, green, blue);

		glutWireTeapot(size);

		glPopMatrix();
	}
	void update(){};

private:
	int size;
};

#endif