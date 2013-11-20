#ifndef WALL_H_
#define WALL_H_

#include "Vector3D.h"
#include "Constants.h"

class Wall{

public:
	Wall(){};
	Wall(int dir);
	~Wall(void);

	Vector3D getWallDirection();

private:
	
	int direction;
};

#endif

