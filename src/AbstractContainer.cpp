#include "AbstractContainer.h"


AbstractContainer::AbstractContainer(void){ 
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


