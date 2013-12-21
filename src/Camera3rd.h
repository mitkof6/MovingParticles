#ifndef CAMERA3RD_H_
#define CAMERA3RD_H_

#include "Renderable.h"
#include "Math/Vectors.h"

#include "GL/glut.h"

/**
 * Simple 3rd person camera
 */
class Camera3rd : public Renderable{
public:

	/**
	 * Default constructor (does nothing)
	 */
	Camera3rd(){};

	/**
	 * Constructor
	 *
	 * @param (distance from target x, y, z)
	 */
	Camera3rd(float offsetX, float offsetY, float offsetZ);
	~Camera3rd(void);

	/**
	 * Lock on target
	 *
	 * @param (position of target)
	 */
	void lock(Vector3 &pos);

	/**
	 * Sets new offset
	 */
	void setOffset(float offsetX, float offsetY, float offsetZ);

	/**
	 * Set camera using glut.lookAt
	 */
	void draw();

	/**
	 * Update camera position based on the tractable
	 * particle
	 */
	void update();

private:
	Vector3 camPos, camView, camUp;
	Vector3 *targetPos;
	float xOffset, yOffset, zOffset;

};

#endif

