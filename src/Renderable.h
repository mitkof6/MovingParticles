#ifndef RENDERABLE_H_
#define RENDERABLE_H_

class Renderable{
public:
	Renderable(){};

	~Renderable(void){};

	virtual void draw() =0;
	virtual void update() =0;

};

#endif
