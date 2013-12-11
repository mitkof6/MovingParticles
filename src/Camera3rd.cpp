#include "Camera3rd.h"


Camera3rd::Camera3rd(float offsetX, float offsetY, float offsetZ) {
	camUp = Vector3(0, 1, 0);
	xOffset = offsetX;
	yOffset = offsetY;
	zOffset = offsetZ;
}


Camera3rd::~Camera3rd(void){
	//delete targetPos;
}

void Camera3rd::lock(Vector3 &pos){
	
	targetPos = &pos;
	update();
}

void Camera3rd::setOffset(float offsetX, float offsetY, float offsetZ){
	xOffset = offsetX;
	yOffset = offsetY;
	zOffset = offsetZ;
}

void Camera3rd::draw(){
	
	gluLookAt(
		camPos.x, camPos.y, camPos.z,
		camView.x, camView.y, camView.z,
		camUp.x, camUp.y, camUp.z);
	
}

void Camera3rd::update(){
	//Vector3D n = targetVelocity->normalize();
	//n = (n*-OFFSET+camPos)/10;
	camPos = targetPos->operator+(Vector3(xOffset, yOffset, zOffset));
	camView = *targetPos;
	//camUp = n.cross(Vector3D(0, 1, 0));
}
