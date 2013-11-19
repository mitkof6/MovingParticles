#ifndef BOX_H_
#define BOX_H_

#include "Renderable.h"

class Box : public Renderable{

public:
	Box(float r, float g, float b,
		float s);
	~Box(void);

	void draw();
	void update(){};

	float getSize();
private:
	float size;
};

#endif