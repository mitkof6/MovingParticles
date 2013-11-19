#ifndef GRID_H_
#define GRID_H_

#include "Renderable.h"

class Grid : public Renderable{
public:
	Grid(float r, float g, float b, int s, int Y);
	~Grid(void);

	void draw();
private:
	int size;
	int y;
};

#endif
