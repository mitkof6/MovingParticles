#ifndef VIEWER_H_
#define VIEWER_H_

#include <vector>

#include "Renderable.h"
#include "AbstractContainer.h"
#include "Math/Vectors.h"
#include "Camera.h"
#include "Constants.h"


using namespace std;

class Viewer {
public:
	static Viewer *instance;

	Viewer(int argc, char** argv);
	virtual ~Viewer();

	void addToDraw(Renderable *r);
	void setContainer(AbstractContainer *c);
	void start();
private:
	vector<Renderable *> drawable;

	AbstractContainer *container;

	Camera camera;
	bool thirdPerson;
	
	int sX, sY, eX, eY;
	bool mousePros;

	float stringColor[4];

	bool ballHistogram, wallHistogram;

	void init();

	void render();
	void update();
	void reshape (int w, int h);
	
	void keyboard (unsigned char key, int x, int y);
	void mouseButton(int button, int state, int x, int y);
	void mouseMove(int x, int y);

	void drawString(const char *str, int x, int y, float color[4], void *font);
	void showInfo();

	static void setDisplayFunction();
	static void setIdeleFunction();
	static void setReshapeFunction(int w, int h);

	static void setKeybordFunction(unsigned char key, int x, int y);
	static void setMouseFunction(int button, int state, int x, int y);
	static void setMouseMoveFunction(int x, int y);
};

#endif /* VIEWER_H_ */
