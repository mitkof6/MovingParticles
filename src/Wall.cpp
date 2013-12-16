#include "Wall.h"


Wall::Wall(int dir){
	direction = dir;
}


Wall::~Wall(void){

}

int Wall::getWall(){
	return direction;
}

Vector3 Wall::getWallDirection() {
	switch (direction) {
		case WALL_LEFT:
			return Vector3(-1, 0, 0);
		case WALL_RIGHT:
			return Vector3(1, 0, 0);
		case WALL_FAR:
			return Vector3(0, 0, -1);
		case WALL_NEAR:
			return Vector3(0, 0, 1);
		case WALL_TOP:
			return Vector3(0, 1, 0);
		case WALL_BOTTOM:
			return Vector3(0, -1, 0);
		default:
			//return Vector3(1, 1, 1);//TODO
			break;
	}
}
