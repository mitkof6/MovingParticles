#ifndef SPRINGCONTAINER_H_
#define SPRINGCONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "DoubleSpring.h"
#include "Sphere.h"
#include "Wall.h"

using namespace std;

class SpringContainer : public AbstractContainer{
public:
	vector<DoubleSpring> doubleSprings;

	SpringContainer();
	~SpringContainer(void);

	void add(DoubleSpring ds);

	void draw();
	void update();

	void enable3rdPerson(){};
	void changeTargert(){};

private:
	void findWallCollisions();
	void checkWall(Sphere &p);

	void findSphereCollisions();
	void checkSpheres(Sphere &p, Sphere &q);
};

#endif
