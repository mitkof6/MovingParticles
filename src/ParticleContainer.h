#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include <vector>

#include "Particle.h"
#include "Constants.h"
#include "Wall.h"
#include "Vector3D.h"
#include "CollisionCounter.h"

using namespace std;


class ParticleContainer : public Renderable{
public:
	ParticleContainer(void);
	~ParticleContainer(void);

	void draw();
	void update();

	void add(Particle p);

	void saveWallCollisions();
	void saveBallCollisions();
	   

private:
	vector<Particle> particles;

	CollisionCounter wallCollisions, ballCollisions;

	void findWallCollisions();
	bool checkForCollision(Particle &p, Wall &w);

	void findParticleParticleCollisions();
	bool checkForCollision(Particle &p, Particle &q);

};


#endif
