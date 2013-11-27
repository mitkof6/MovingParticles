#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include <vector>
#include <iostream>

#include "Particle.h"
#include "ParticlePair.h"
#include "Constants.h"
#include "Wall.h"
#include "Vector3D.h"

using namespace std;


class ParticleContainer : public Renderable{
public:
	ParticleContainer(void);
	~ParticleContainer(void);

	void draw();
	void update();

	void add(Particle p);
	   

private:
	vector<Particle> particles;
	vector<ParticlePair> collisionPairs;

	void findWallCollisions();
	bool checkForCollision(Particle &p, Wall &w);

	void findParticleParticleCollisions();
	bool checkForCollision(Particle &p, Particle &q);

	void resolveRepaitedCollisions();

};


#endif
