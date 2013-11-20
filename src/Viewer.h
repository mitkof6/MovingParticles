/*
 * Viewer.h
 *
 *  Created on: Oct 22, 2013
 *      Author: Jim Stanev
 */

#ifndef VIEWER_H_
#define VIEWER_H_

#include <vector>

#include "Renderable.h"
#include "Vector3D.h"
#include "Camera.h"
#include "Constants.h"


using namespace std;

class Viewer {
public:
	static Viewer *instance;

	Viewer(int argc, char** argv);
	virtual ~Viewer();

	void addToDraw(Renderable *r);
	void start();
private:
	vector<Renderable *> drawable;

	Camera camera;

	int sX, sY, eX, eY;
	bool mousePros;

	void init();

	void render();
	void update();
	void reshape (int w, int h);
	
	void keyboard (unsigned char key, int x, int y);
	void mouseButton(int button, int state, int x, int y);
	void mouseMove(int x, int y);

	static void setDisplayFunction();
	static void setIdeleFunction();
	static void setReshapeFunction(int w, int h);

	static void setKeybordFunction(unsigned char key, int x, int y);
	static void setMouseFunction(int button, int state, int x, int y);
	static void setMouseMoveFunction(int x, int y);
};

#endif /* VIEWER_H_ */
