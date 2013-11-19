#include "Grid.h"
#include "GL\glut.h"

Grid::Grid(float r, float g, float b, int s, int Y) : Renderable(r, g, b){
	size = s;
	y = Y;
}


Grid::~Grid(void){}

void Grid::draw(){
	glPushMatrix();

	glColor3f(red, green, blue);
	for (int i = -size; i <= size; i += 2) {
		for (int j = -size; j <= size; j += 2) {
			glBegin(GL_QUADS);
				glVertex3f(i, y, j);
                glVertex3f(i, y, j - 1);
                glVertex3f(i - 1, y, j - 1);
                glVertex3f(i - 1, y, j);
			glEnd();
         }
	}

	glPopMatrix();
}
