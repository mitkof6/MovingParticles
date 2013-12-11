#ifndef CAMERA_H_
#define CAMERA_H_

#include "Math/Vectors.h"
#include "Renderable.h"

class Camera : Renderable{
public:

	Camera(){};
	Camera(Vector3 poss, Vector3 vieww, Vector3 upp);
	virtual ~Camera();

	void move(float speed);
	void rotateX(float speed);
	void rotateY(float speed);
	void strafe(float speed);

	void draw();
	void update(){};

private:
	Vector3 pos, view, up;
};


#endif /* CAMERA_H_ */
