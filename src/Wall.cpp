#include "Wall.h"


Wall::Wall(int dir){
	direction = dir;
}


Wall::~Wall(void){

}

Vector3D Wall::getWallDirection() {
	switch (direction) {
		case WALL_LEFT:
			return Vector3D(-1, 0, 0);
		case WALL_RIGHT:
			return Vector3D(1, 0, 0);
		case WALL_FAR:
			return Vector3D(0, 0, -1);
		case WALL_NEAR:
			return Vector3D(0, 0, 1);
		case WALL_TOP:
			return Vector3D(0, 1, 0);
		case WALL_BOTTOM:
			return Vector3D(0, -1, 0);
		default:
			return Vector3D(0, 0, 0);
	}
}
