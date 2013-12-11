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
	ParticleContainer();
	~ParticleContainer(void);

	void add(Particle p);

	void draw();
	void update();

	void enable3rdPerson();
	void changeTargert();
	   

private:
	vector<Particle> particles;

	void findWallCollisions();
	bool checkForCollision(Particle &p, Wall &w);

	void findParticleParticleCollisions();
	bool checkForCollision(Particle &p, Particle &q);

};


#endif
