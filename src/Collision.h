#ifndef COLLISION_H_
#define COLLISION_H_

#include "Wall.h"
#include "Math/Vectors.h"
#include "Math/Matrices.h"

/**
 * Defines basic collision checks, corrections and
 * computations of new velocity, angular velocity
 * after a collision
 */
class Collision{
public:
	Collision(void);
	~Collision(void);

	/**
	 * Checks for wall collision between sphere. If collision exist
	 * correction of sphere mass center is made
	 *
	 * @param (mass center, position of sphere, radius, wall)
	 */
	bool checkForWallCollision(
			Vector3 &massCenter, const Vector3 &pos, float r, Wall &w);

	/**
	* Checks for sphere-sphere collision. If collision exist
	* correction of one of the two spheres' mass center is made
	*
	* @param (mass center, position of sphere 1, radius 1,
	* 		  position of sphere 1, radius 2)
	*/
	bool checkForSpheresCollision(
			Vector3 &massCenter, const Vector3 &p, float r1,
			const Vector3 &q, float r2);

	/**
	 * Handles collision between sphere and wall. Computes new velocity and
	 * angular velocity based on conservation laws (implements impulse)
	 *
	 * @param (mass center, velocity, angular v, inertia inverse, mass,
	 * 			collision point, collision normal from wall to sphere)
	 */
	void handleWallCollision(
		const Vector3 &massCenter, Vector3 &vA, Vector3 &wA, const Matrix3 iInvA, float mA,
		const Vector3 &cp, const Vector3 &cn);

	/**
	* Handles collision between spheres. Computes new velocity and
	* angular velocity based on conservation laws (implements impulse)
	*
	* @param (mass center 1, velocity 1, angular v 1, inertia inverse 1, mass 1,
	* 		  mass center 2, velocity 2, angular v 2, inertia inverse 2, mass 2,
	* 		  collision point, collision normal from sphere2 to sphere1)
	*/
	void handleSphereCollision(
		const Vector3 &massCenterA, Vector3 &vA, Vector3 &wA, const Matrix3 iInvA, float mA,
		const Vector3 &massCenterB, Vector3 &vB, Vector3 &wB, const Matrix3 iInvB, float mB,
		const Vector3 &cp, const Vector3 &cn, float gain);

	/**
	 * Calculates collision point cp = p1 + t(p2-p1), t = r1/(r1+r2)
	 *
	 * @param (position 1, radius 1, possition 2, radius 2,
	 * 		   collision point, collision normal from 2->1)
	 */
	void calculateCollisionPoint(
		const Vector3 &p1, float r1,
		const Vector3 &p2, float r2,
		Vector3 &cp, Vector3 &cn);

private:
	/**
	 * Calculates impulse magnitude based on parameters
	 * between two particles
	 */
	float impulseMagnitude(
		const Vector3 &vA, const Vector3 &wA, const Vector3 &rA, const Matrix3 &iInvA, float mA,
		const Vector3 &vB, const Vector3 &wB, const Vector3 &rB, const Matrix3 &iInvB, float mB,
		const Vector3 &n);

	/**
	* Calculates impulse magnitude based on parameters
	*  between a particle and a wall
	*/
	float impulseMagnitude(
		const Vector3 &vA, const Vector3 &wA, const Vector3 &rA, const Matrix3 &iInvA, float mA,
		const Vector3 &n);
};

#endif
