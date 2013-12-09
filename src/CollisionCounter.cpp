#include "CollisionCounter.h"


CollisionCounter::CollisionCounter(){
	time = counter = 0;
}


CollisionCounter::~CollisionCounter(void){

}

void CollisionCounter::incTime(){
	time++;
}

void CollisionCounter::incCounter(){
	counter++;
}

void CollisionCounter::registerEvent(){
	timeSeq.push_back(time);
	counterSeq.push_back(counter);
}

void CollisionCounter::clear(){
	time = counter = 0;
	timeSeq.clear();
}

void CollisionCounter::setName(string n){
	name = n;
}

void CollisionCounter::saveToMat(string path){
	FILE *file;

    if (!(file = fopen(path.c_str(), "w")))
		return;

	for(unsigned i = 0;i<timeSeq.size();i++){
		fprintf(file, "%d %d\n", timeSeq[i], counterSeq[i]);
	}

	fclose(file);
}


void drawText(const char *str,float size, float r, float g, float b){

	glPushMatrix();
	glScalef(size,size,size);
	
	for (int i=0;i<strlen(str);i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();

}

void CollisionCounter::draw(){
	
	glPushMatrix();

	glPushMatrix();
		glTranslatef(10, 0, 0);
		drawText("Time", 0.002f, 0, .5, .5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 10, 0);
		drawText("Collisions", 0.002f, 0, .5, .5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5, 10, 0);
		drawText(name.c_str(), 0.004f, 0, .5, .5);
	glPopMatrix();
	
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
