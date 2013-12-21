#ifndef WALL_H_
#define WALL_H_

#include "Math/Vectors.h"
#include "Constants.h"

/**
 * Represents a wall based on defined enumerator
 */
class Wall{

public:
	/**
	 * Default constructor (does nothing)
	 */
	Wall(){};

	/**
	 * Represents a wall based on enumerator
	 *
	 * @param (enumerator index)
	 */
	Wall(int dir);
	~Wall(void);

	/**
	 * Get wall index
	 */
	int getWall();

	/**
	 * Get wall normal direction
	 */
	Vector3 getWallDirection();

private:
	
	int direction;
};

#endif

