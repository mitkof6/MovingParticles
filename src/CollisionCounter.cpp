#include "CollisionCounter.h"


CollisionCounter::CollisionCounter(){
	time = counter = difference = 0;
}


CollisionCounter::~CollisionCounter(void){

}

void CollisionCounter::incTime(){
	time++;
}

void CollisionCounter::incCounter(){
	difference++;
	counter++;
}

void CollisionCounter::registerEvent(){
	timeSeq.push_back(time);
	counterSeq.push_back(counter);
}

void CollisionCounter::clear(){
	time = counter = 0;
	timeSeq.clear();
	counterSeq.clear();
}

void CollisionCounter::setName(string n){
	name = n;
}

void CollisionCounter::saveToMat(string path){
	FILE *file;

    if (!(file = fopen(path.c_str(), "w")))
		return;

	for(unsigned i = 0;i<timeSeq.size();i++){
		fprintf(file, "%lu %lu\n", timeSeq[i], counterSeq[i]);
	}

	fclose(file);
}

/*
void drawText(const char *str,float size, float r, float g, float b){

	glPushMatrix();
	glScalef(size,size,size);
	
	for (unsigned int i=0;i<strlen(str);i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();

}
*/

void CollisionCounter::drawString(const char *str, int x, int y, float color[4], void *font){
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}

void CollisionCounter::draw(){
	
	glPushMatrix();

	float color[] = {0.5,0.5,0.5,1.0};

	drawString("Time", 10, 0, color, GLUT_BITMAP_8_BY_13);
	drawString("Collisions", 0, 10, color, GLUT_BITMAP_8_BY_13);
	drawString(name.c_str(), 5, 10, color, GLUT_BITMAP_8_BY_13);
	
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0, 10);
		glVertex2f(0, 0);
		glVertex2f(10, 0);
	glEnd();

	glColor3f(0, 1, 0);
	
	for(unsigned i = 0;i<timeSeq.size();i++){
		glBegin(GL_LINES);
			glVertex2f(timeSeq[i]*10.0/time, 0);
			glVertex2f(timeSeq[i]*10.0/time, counterSeq[i]*10.0/counter);
		glEnd();
	}
	
	glPopMatrix();
}


void CollisionCounter::update(){

}

unsigned long CollisionCounter::getDifference(){
	short temp = difference;
	difference = 0;
	return temp;
	
}

void CollisionCounter::add(unsigned long count){
	counter += count;		
}
