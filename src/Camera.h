#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector3D.h"
#include "Renderable.h"

class Camera : Renderable{
public:
	Vector3D pos, view, up;

	Camera(){};
	Camera(Vector3D poss, Vector3D vieww, Vector3D upp);
	virtual ~Camera();

	void move(float speed);
	void rotateX(float speed);
	void rotateY(float speed);
	void strafe(float speed);

	void draw();
	void update(){};

};


#endif /* CAMERA_H_ */
