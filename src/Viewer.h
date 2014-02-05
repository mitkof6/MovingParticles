#ifndef VIEWER_H_
#define VIEWER_H_

#include <vector>

#include "Renderable.h"
#include "AbstractContainer.h"
#include "Math/Vectors.h"
#include "Camera.h"
#include "Constants.h"


using namespace std;

/**
 * Object oriented implementation of gl rendering.
 * Object container, camera and events handling
 */
class Viewer {
public:
	/**
	 * Used for dispatching functions
	 */
	static Viewer *instance;

	/**
	 * Constructor
	 *
	 * @param (main)
	 */
	Viewer(int argc, char** argv);
	~Viewer();

	/**
	 * Adds an renderable object in the drawable container
	 *
	 * @param (renderable object)
	 */
	void addToDraw(Renderable *r);

	/**
	 * Adds a system container
	 *
	 * @param (abstract container)
	 */
	void addContainer(AbstractContainer *c);

	/**
	 * Begin main loop
	 */
	void start();
private:
	/**
	 * Renderable objects
	 */
	vector<Renderable *> drawable;

	/**
	 * Container (system)
	 */
	vector<AbstractContainer *> container;
	int containerIndex;

	/**
	 * Camera and 3rd person flag
	 */
	Camera camera;
	bool thirdPerson;
	
	/**
	 * Mouse tracking
	 */
	int sX, sY, eX, eY;
	bool mousePros;

	/**
	 * String drawing color
	 */
	float stringColor[4];

	/**
	 * Histogram flags
	 */
	bool sphereHistogram, wallHistogram;

	/**
	 * Representation flags
	 */
	bool wired, smooth, color, light;

	/**
	 * Setup
	 */
	void init();

	/**
	 * Rendering function
	 */
	void render();

	/**
	 * Idle function
	 */
	void update();

	void reshape (int w, int h);
	
	/**
	 * Keyboard, mouse listeners
	 */
	void keyboard (unsigned char key, int x, int y);
	void mouseButton(int button, int state, int x, int y);
	void mouseMove(int x, int y);

	void drawString(const char *str, int x, int y,
			float color[4], void *font);

	/**
	 * Info
	 */
	void showInfo();

	/**
	 * For setting callbacks
	 */
	static void setDisplayFunction();
	static void setIdeleFunction();
	static void setReshapeFunction(int w, int h);

	static void setKeybordFunction(unsigned char key, int x, int y);
	static void setMouseFunction(int button, int state, int x, int y);
	static void setMouseMoveFunction(int x, int y);
};

#endif /* VIEWER_H_ */
