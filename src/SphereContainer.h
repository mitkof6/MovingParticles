#ifndef SPHERECONTAINER_H_
#define SPHERECONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "Sphere.h"
#include "Constants.h"
#include "Wall.h"
#include "Math/Vectors.h"

using namespace std;

/**
 * Sphere container contains spheres and handles
 * collisions.
 */
class SphereContainer : public AbstractContainer{
public:
	vector<Sphere> spheres;

	/**
	 * Default constructor
	 */
	SphereContainer();

	/**
	 * Constructor
	 *
	 * @param (collision mode (real or false))
	 */
	SphereContainer(bool collisionMode);
	~SphereContainer(void);

	/**
	 * Adds a sphere to container
	 */
	void add(Sphere &p);

	/**
	 * Render spheres
	 */
	void draw();

	/**
	 * Updates system
	 */
	void update();

	void enable3rdPerson();
	void changeTargert();
	   

private:
	/**
	 * Checks and handles wall collisions
	 */
	void findWallCollisions();

	/**
	 * Checks and handles spheres collisions
	 */
	void findSphereCollisions();

};


#endif
