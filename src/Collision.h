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

	void handleWallCollision(
		const Vector3 &massCenter, Vector3 &vA, Vector3 &wA, const Matrix3 iInvA, float mA,
		const Vector3 &cp, const Vector3 &cn);
	void handleSphereCollision(
		const Vector3 &massCenterA, Vector3 &vA, Vector3 &wA, const Matrix3 iInvA, float mA,
		const Vector3 &massCenterB, Vector3 &vB, Vector3 &wB, const Matrix3 iInvB, float mB,
		const Vector3 &cp, const Vector3 &cn, float gain);

	void Collision::calculateCollisionPoint(
		const Vector3 &p1, float r1,
		const Vector3 &p2, float r2,
		Vector3 &cp, Vector3 &cn);

private:
	float impulseMagnitude(
		const Vector3 &vA, const Vector3 &wA, const Vector3 &rA, const Matrix3 &iInvA, float mA,
		const Vector3 &vB, const Vector3 &wB, const Vector3 &rB, const Matrix3 &iInvB, float mB,
		const Vector3 &n);

	float impulseMagnitude(
		const Vector3 &vA, const Vector3 &wA, const Vector3 &rA, const Matrix3 &iInvA, float mA,
		const Vector3 &n);
};

#endif
