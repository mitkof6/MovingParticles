#ifndef CAMERA3RD_H_
#define CAMERA3RD_H_

#include "Renderable.h"
#include "Math/Vectors.h"

#include "GL/glut.h"

class Camera3rd : public Renderable{
public:
	Camera3rd(){};
	Camera3rd(float offsetX, float offsetY, float offsetZ);
	~Camera3rd(void);

	void lock(Vector3 &pos);
	void setOffset(float offsetX, float offsetY, float offsetZ);

	void draw();
	void update();

private:
	Vector3 camPos, camView, camUp;
	Vector3 *targetPos;
	float xOffset, yOffset, zOffset;

};

#endif

