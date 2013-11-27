/*
 * Viewer.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: Jim Stanev
 */

#include "Viewer.h"

#include "GL\glut.h"


Viewer *Viewer::instance = NULL;

Viewer::Viewer(int argc, char** argv) {

	instance = this;

	camera = Camera(
		Vector3D(CAM_POS_X, CAM_POS_Y ,CAM_POS_Z),
		Vector3D(CAM_VIEW_X, CAM_VIEW_Y, CAM_VIEW_Z),
		Vector3D(CAM_UP_X, CAM_UP_Y, CAM_UP_Z));


	mousePros = false;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);

	glutInitWindowPosition (WINDOW_X_POS, WINDOW_Y_POS);

	glutCreateWindow (WINDOW_NAME);

	init ();

	glutDisplayFunc(setDisplayFunction);
	glutIdleFunc(setIdeleFunction);
	glutReshapeFunc(setReshapeFunction);

	glutKeyboardFunc(setKeybordFunction);

	glutMouseFunc(setMouseFunction);
	glutMotionFunc(setMouseMoveFunction);
	glutPassiveMotionFunc(setMouseMoveFunction);
}

Viewer::~Viewer() {
	for(unsigned i = 0;i<drawable.size();i++){
		delete drawable.at(i);
	}
}

void Viewer::addToDraw(Renderable *r){
	drawable.push_back(r);	
}

void Viewer::start(){
	glutMainLoop();
}

void Viewer::init(){

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0,-50.0,0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	GLfloat ratio = (GLfloat) WINDOW_WIDTH/(GLfloat) WINDOW_HEIGHT;
	gluPerspective(40.0, ratio, 1.0f, 200.0f);
	glMatrixMode (GL_MODELVIEW);
}

void Viewer::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);

	//glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	 //camera
	camera.draw();

	for(unsigned i = 0;i<drawable.size();i++){
		drawable.at(i)->draw();
	}

	glutSwapBuffers();
}

void Viewer::update(){
	for(unsigned i = 0;i<drawable.size();i++){
		drawable[i]->update();
	}

	glutPostRedisplay();
}



void Viewer::reshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	GLfloat ratio = (GLfloat) w/(GLfloat) h;
	gluPerspective(40.0, ratio, 1.0f, 200.0f);
	glMatrixMode (GL_MODELVIEW);
}

void Viewer::keyboard (unsigned char key, int x, int y){
	switch (key) {
	case 'w':
		camera.move(CAMERA_MOVE_SPEED);
		break;
	case 's':
		camera.move(-CAMERA_MOVE_SPEED);
		break;
	case 'd':
		camera.strafe(CAMERA_MOVE_SPEED);
		break;
	case 'a':
		camera.strafe(-CAMERA_MOVE_SPEED);
		break;
	default:
		break;
	}
}

void Viewer::mouseButton(int button, int state, int x, int y){
	if(button==GLUT_LEFT_BUTTON){
		
		if (state == GLUT_DOWN) {
			mousePros = true;
		}else  {
			mousePros = false;
		}
	}
}

void Viewer::mouseMove(int x, int y){
	static bool just_warped = false;
	if(just_warped) {
        just_warped = false;
        return;
    }
	if(mousePros){
		int difX = x-WINDOW_WIDTH/2;
		int difY = y-WINDOW_HEIGHT/2;

		
		//camera.rotateX(difX*0.06);
		
		camera.rotateY(-difX*CAMERA_ROTATE_SPEED);

		//glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

		just_warped = true;
		
	}
	
}

void Viewer::setDisplayFunction(){
	instance->render();
}

void Viewer::setIdeleFunction(){
	instance->update();
}

void Viewer::setReshapeFunction(int w, int h){
	instance->reshape(w, h);
}

void Viewer::setKeybordFunction(unsigned char key, int x, int y){
	instance->keyboard(key, x, y);
}

void Viewer::setMouseFunction(int button, int state, int x, int y){
	instance->mouseButton(button, state, x, y);
}

void Viewer::setMouseMoveFunction(int x, int y){
	instance->mouseMove(x, y);
}

