#ifndef SPRINGCONTAINER_H_
#define SPRINGCONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "DoubleSpring.h"
#include "Particle.h"
#include "Wall.h"
#include "Collision.h"

using namespace std;

class SpringContainer : public AbstractContainer{
public:
	SpringContainer();
	~SpringContainer(void);

	void add(DoubleSpring &ds);

	void draw();
	void update();

	void enable3rdPerson(){};
	void changeTargert(){};

private:
	vector<DoubleSpring> doubleSprings;
	Collision collision;

	void findWallCollisions();
	void checkWall(Particle &p);

	void findSphereCollisions();
	void checkSpheres(Particle &p, Particle &q);
};

#endif
