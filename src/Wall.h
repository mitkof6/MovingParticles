#ifndef WALL_H_
#define WALL_H_

#include "Math/Vectors.h"
#include "Constants.h"

class Wall{

public:
	Wall(){};
	Wall(int dir);
	~Wall(void);

	int getWall();
	Vector3 getWallDirection();

private:
	
	int direction;
};

#endif

