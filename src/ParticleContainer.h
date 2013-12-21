#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "Particle.h"
#include "Constants.h"
#include "Wall.h"
#include "Math/Vectors.h"

using namespace std;

class ParticleContainer : public AbstractContainer{
public:
	vector<Particle> particles;

	ParticleContainer();
	ParticleContainer(bool collisionMode);
	~ParticleContainer(void);

	void add(Particle &p);

	void draw();
	void update();

	void enable3rdPerson();
	void changeTargert();
	   

private:
	void findWallCollisions();

	void findSphereCollisions();

};


#endif
