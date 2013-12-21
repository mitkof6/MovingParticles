#ifndef SPRINGCONTAINER_H_
#define SPRINGCONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "DoubleSpring.h"
#include "Sphere.h"
#include "Wall.h"

using namespace std;

/**
 * Represents a container of double spring objects and
 * handles collisions
 */
class SpringContainer : public AbstractContainer{
public:
	vector<DoubleSpring> doubleSprings;

	/**
	 * Default constructor
	 */
	SpringContainer();
	~SpringContainer(void);

	/**
	 * Adds a double spring to system
	 *
	 * @param (double spring)
	 */
	void add(DoubleSpring ds);

	/**
	 * Render system
	 */
	void draw();

	/**
	 * Update system
	 */
	void update();

	void enable3rdPerson(){};
	void changeTargert(){};

private:
	/**
	 * Search for wall collisions
	 */
	void findWallCollisions();

	/**
	 * Handles wall collision
	 *
	 * @param (spehre object)
	 */
	void checkWall(Sphere &p);

	/**
	 * Search for sphere-sphere collisions
	 */
	void findSphereCollisions();

	/**
	 * Handles spheres collision
	 *
	 * @param (sphere1, sphere2)
	 */
	void checkSpheres(Sphere &p, Sphere &q);
};

#endif
