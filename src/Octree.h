#ifndef OCTREE_H_
#define OCTREE_H_

#include <vector>

#include "Vector3D.h"
#include "Particle.h"
#include "Constants.h"
#include "Renderable.h"
#include "ParticleWallContainer.h"
#include "ParticlePairContainer.h"

using namespace std;

class Octree : public Renderable{

public:
	//Octree(){};
	Octree(Vector3D c1, Vector3D c2, int d);
	~Octree(void);

	void add(Particle p);

	void draw();
	void update();
private:
	Octree *children[2][2][2];
	
	bool hasChildren;
	Vector3D corner1, corner2, center;
	int depth;
	int numParticles;

	vector<Particle> particles;

	void fileParticle(Particle p, bool add);
	void destroyChildren();
	void collectParticles(vector<Particle> &ps);
	void createChildren();
	void remove(Particle p);
	
	void findWallCollisions(vector<ParticleWallContainer> &container);
	void Octree::checkWall(vector<ParticleWallContainer> &container, Wall w, char coord, int dir);
	void handleWallCollision();

	void findParticleCollisions(vector<ParticlePairContainer> &container);
	void handleParticlePairCollision();
};


#endif