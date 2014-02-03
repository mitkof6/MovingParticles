#include "AbstractContainer.h"

AbstractContainer::AbstractContainer(){
	wallCollisionCounter.setName("Wall");
	sphereCollisionCounter.setName("Particles");

	camera = Camera3rd(OFFSET_X, OFFSET_Y, OFFSET_Z);
	thirdPerson = false;
	target = 0;
}

AbstractContainer::AbstractContainer(bool cm){
	collisionMode = cm;
	wallCollisionCounter.setName("Wall");
	sphereCollisionCounter.setName("Particles");

	camera = Camera3rd(OFFSET_X, OFFSET_Y, OFFSET_Z);
	thirdPerson = false;
	target = 0;
}


AbstractContainer::~AbstractContainer(void){

}

void AbstractContainer::saveWallCollisions(){
	wallCollisionCounter.saveToMat(WALL_COLLISION_PATH);
}

void AbstractContainer::saveBallCollisions(){
	sphereCollisionCounter.saveToMat(BALL_COLLISION_PATH);
}

void AbstractContainer::drawWallCollisions(){
	wallCollisionCounter.draw();
}

void AbstractContainer::drawBallCollisions(){
	sphereCollisionCounter.draw();
}

void AbstractContainer::changeCollisionMode(){
	collisionMode = !collisionMode;
}

void AbstractContainer::clearCollisions(){
	wallCollisionCounter.clear();
	sphereCollisionCounter.clear();
}

bool AbstractContainer::getCameraMode(){
	return thirdPerson;
}

int AbstractContainer::getTargetIndex(){
	return target;
}

bool AbstractContainer::getCollisionMode(){
	return collisionMode;
}

CollisionCounter &AbstractContainer::getWallCollisionCounter(){
	return wallCollisionCounter;
}

CollisionCounter &AbstractContainer::getSphereCollisionCounter(){
	return sphereCollisionCounter;
}


