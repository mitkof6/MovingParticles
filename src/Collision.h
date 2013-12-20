#ifndef COLLISION_H_
#define COLLISION_H_

#include "Particle.h"
#include "Wall.h"

class Collision{
public:
	Collision(void);
	~Collision(void);

	bool checkForWallCollision(Vector3 &massCenter, const Vector3 &pos, float r, Wall &w);
	bool checkForSpheresCollision(Vector3 &massCenter, const Vector3 &p, float r1, const Vector3 &q, float r2);
};

#endif
