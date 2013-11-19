#ifndef OCTREE_H_
#define OCTREE_H_

#include <vector>

#include "Vector3D.h"
#include "Particle.h"
#include "Constants.h"

using namespace std;

class Octree{

public:
	Octree(Vector3D c1, Vector3D c2, int d);
	~Octree(void);

	void add(Particle &p);
	//void findWallColitions(vector<
private:
	Octree *children[2][2][2];
	
	bool hasChildren;
	Vector3D corner1, corner2, center;
	int depth;
	int numParticles;

	vector<Particle> particles;

	void fileParticle(Particle &p, Vector3D pos, bool add);
	void destroyChildren();
	void collectParticles(vector<Particle> &ps);
	void createChildren();
	void remove(Particle p, Vector3D pos);
};


#endif