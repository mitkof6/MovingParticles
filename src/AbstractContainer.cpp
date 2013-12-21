#include "AbstractContainer.h"


AbstractContainer::AbstractContainer(){
	wallCollisions.setName("Wall");
	ballCollisions.setName("Ball");

	camera = Camera3rd(OFFSET_X, OFFSET_Y, OFFSET_Z);
	thirdPerson = false;
	target = 0;
}

AbstractContainer::AbstractContainer(bool cm){
	collisionMode = cm;
	wallCollisions.setName("Wall");
	ballCollisions.setName("Ball");

	camera = Camera3rd(OFFSET_X, OFFSET_Y, OFFSET_Z);
	thirdPerson = false;
	target = 0;
}


AbstractContainer::~AbstractContainer(void){

}

void AbstractContainer::saveWallCollisions(){
	wallCollisions.saveToMat(WALL_COLLISION_PATH);
}

void AbstractContainer::saveBallCollisions(){
	ballCollisions.saveToMat(BALL_COLLISION_PATH);
}

void AbstractContainer::drawWallCollisions(){
	wallCollisions.draw();
}

void AbstractContainer::drawBallCollisions(){
	ballCollisions.draw();
}

void AbstractContainer::changeCollisionMode(){
	collisionMode = !collisionMode;
}

void AbstractContainer::clearCollisions(){
	wallCollisions.clear();
	ballCollisions.clear();
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
	return wallCollisions;
}

CollisionCounter &AbstractContainer::getBallCollisionCounter(){
	return ballCollisions;
}


