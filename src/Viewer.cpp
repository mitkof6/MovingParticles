#include "Viewer.h"
#include "GL/glut.h"

Viewer *Viewer::instance = NULL;

Viewer::Viewer(int argc, char** argv) {

	instance = this;

	camera = Camera(
		Vector3(CAM_POS_X, CAM_POS_Y ,CAM_POS_Z),
		Vector3(CAM_VIEW_X, CAM_VIEW_Y, CAM_VIEW_Z),
		Vector3(CAM_UP_X, CAM_UP_Y, CAM_UP_Z));


	mousePros = false;

	ballHistogram = wallHistogram = false;

	thirdPerson = false;

	stringColor[0] = .5;
	stringColor[1] = .5;
	stringColor[2] = .5;
	stringColor[3] = 1.0;

	wired = WIRED;
	smooth = SMOOTH;
	color = COLOR;
	light = LIGHT;

	container = 0;

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
	delete container;
	delete instance;
}

void Viewer::addToDraw(Renderable *r){
	drawable.push_back(r);	
}

void Viewer::setContainer(AbstractContainer *c){
	container = c;
}

void Viewer::start(){
	glutMainLoop();
}

void Viewer::init(){

	//shader
	if(smooth){
		glShadeModel (GL_SMOOTH);
	}else{
		glShadeModel(GL_FLAT);
	}

	//z-buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// color
	if(color){
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE || GL_SPECULAR);
	}
	
  
	//light source
	if(light){
		GLfloat light_position[] = {L_POS_X, L_POS_Y, L_POS_Z, L_POS_W};
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		GLfloat ambient[] = {.1, .1, .1, 1.0};
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

		GLfloat diffuse[] = {.3, .3, .3, 1.0};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

		GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	
	if(wired){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	GLfloat ratio = (GLfloat) WINDOW_WIDTH/(GLfloat) WINDOW_HEIGHT;
	gluPerspective(40.0, ratio, 1.0f, 200.0f);
	glMatrixMode (GL_MODELVIEW);
}

void Viewer::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	//showInfo();

	if(wallHistogram){
		//histogram
		glTranslatef(-4, -5, -15);
		container->drawBallCollisions();
	}else if(ballHistogram){
		//histogram
		glTranslatef(-4, -5, -15);
		container->drawWallCollisions();
	}else{
		//camera
		if(!thirdPerson){
			camera.draw();
		}

		//particles
		if(container != 0)
			container->draw();

		//other objects
		for(unsigned i = 0;i<drawable.size();i++){
			drawable.at(i)->draw();
		}
	}	

	glutSwapBuffers();
}

void Viewer::update(){

	if(container != 0)
		container->update();

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
	case 'q':
		camera.rotateY(CAMERA_ROTATE_SPEED);
		break;
	case 'e':
		camera.rotateY(-CAMERA_ROTATE_SPEED);
		break;
	case '1': //show
		//container->saveWallCollisions();
		wallHistogram = !wallHistogram;
		break;
	case '2': //store ball collisions
		//container->saveBallCollisions();
		ballHistogram = !ballHistogram;
		break;
	case '3': //clear collisions
		container->clearCollisions();
		break;
	case '4': //change collisions mode
		container->changeCollisionMode(); 
		break;
	case '5': //3rd person camera enabled
		container->enable3rdPerson();
		thirdPerson = !thirdPerson;
		break;
	case '6': //3rd person camera change target
		container->changeTargert();
		break;
	case '7': //wird
		wired = !wired;
		if(wired){
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}else{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		break;
	case '8': //smoth
		smooth = !smooth;
		if(smooth){
			glShadeModel (GL_SMOOTH);
		}else{
			glShadeModel(GL_FLAT);
		}
		break;
	case '9': //color
		color = !color;
		if(color){
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE || GL_SPECULAR);
		}else{
			glDisable(GL_COLOR_MATERIAL);
		}
		break;
	case '0': //light
		light = !light;
		if(light){
			glEnable(GL_LIGHTING);
		}else{
			glDisable(GL_LIGHTING);
		}
		
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

		if(abs(difX)>abs(difY)){
			camera.rotateY(-difX*CAMERA_ROTATE_SPEED);
		}else{
			camera.rotateX(-difY*CAMERA_ROTATE_SPEED);
		}
		
		glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

		just_warped = true;
		
	}
	
}

void Viewer::drawString(const char *str, int x, int y, float color[4], void *font){
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

void Viewer::showInfo(){
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
    glLoadIdentity();                   // reset projection matrix
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT); // set to orthogonal projection

    float color[4] = {1, 1, 1, 0.5};

	drawString("Key 1: Wall Histogram", 0, WINDOW_HEIGHT-TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Key 2: Ball Histogram", 0, WINDOW_HEIGHT-2*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Key 3: Clear Data", 0, WINDOW_HEIGHT-3*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Key 4: Collision Mode", 0, WINDOW_HEIGHT-4*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Key 5: 3rd Person", 0, WINDOW_HEIGHT-5*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Key 6: Switch Target", 0, WINDOW_HEIGHT-6*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);

	drawString("Key 7: Solid/Wired", 0, WINDOW_HEIGHT-8*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Key 8: Smooth/Flat", 0, WINDOW_HEIGHT-9*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Key 9: Color/Material", 0, WINDOW_HEIGHT-10*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Key 0: Light on/off", 0, WINDOW_HEIGHT-11*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);

	drawString("Movements: w, s, a, d", 0, 0, color, GLUT_BITMAP_HELVETICA_12);
	drawString("Camera rotation: mouse",  0, TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);

	drawString(container->getCameraMode()==true? "3rd Person Camera" : "Normal Camera",
				0, 6*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
	drawString(container->getCollisionMode()==true? "Collision: real mode" : "Collision: false mode",
				0, 5*TEXT_HEIGHT, color, GLUT_BITMAP_HELVETICA_12);
    

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
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

