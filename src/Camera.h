#ifndef CAMERA_H_
#define CAMERA_H_

#include "Math/Vectors.h"
#include "Renderable.h"

/**
 * Simple first person camera
 */
class Camera : public Renderable{
public:

	/**
	 * Default constructor (does nothing)
	 */
	Camera(){};

	/**
	 * Constructor
	 * @param (position, view, up) see opengl lookAt
	 */
	Camera(Vector3 poss, Vector3 vieww, Vector3 upp);
	virtual ~Camera();

	/**
	 * Moves forward/backward camera position
	 *
	 * @param (speed) if >0 forward else backward
	 */
	void move(float speed);

	/**
	* RotateX()
	*
	* @param (speed) if >0 down else up
	*/
	void rotateX(float speed);

	/**
	* RotateY()
	*
	* @param (speed) if >0 left else right
	*/
	void rotateY(float speed);

	/**
	* Moves left/right camera position
	*
	* @param (speed) if >0 left else right
	*/
	void strafe(float speed);

	/**
	 * Set camera using glut.lookAt
	 */
	void draw();

	/**
	 * Does nothing
	 */
	void update(){};

private:
	Vector3 pos, view, up;
};


#endif /* CAMERA_H_ */
