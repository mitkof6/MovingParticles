#ifndef SPHERECONTAINER_H_
#define SPHERECONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "Sphere.h"
#include "Constants.h"
#include "Wall.h"
#include "Math/Vectors.h"

using namespace std;

class SphereContainer : public AbstractContainer{
public:
	vector<Sphere> particles;

	SphereContainer();
	SphereContainer(bool collisionMode);
	~SphereContainer(void);

	void add(Sphere &p);

	void draw();
	void update();

	void enable3rdPerson();
	void changeTargert();
	   

private:
	void findWallCollisions();

	void findSphereCollisions();

};


#endif
