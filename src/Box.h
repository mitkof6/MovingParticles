#ifndef BOX_H_
#define BOX_H_

#include "Renderable.h"

/**
 * Represents the bounding box
 */
class Box : public Renderable{

public:
	/**
	 * @param (red, green, blue, size)
	 */
	Box(float r, float g, float b, float s);
	~Box(void);

	void draw();
	void update(){};

	float getSize();
private:
	float size;
	float red, green, blue;
};

#endif
