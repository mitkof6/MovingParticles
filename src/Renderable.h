#ifndef RENDERABLE_H_
#define RENDERABLE_H_

class Renderable{
public:
	Renderable(){};
	Renderable(float r, float g, float b){
		red = r;
		green = g;
		blue = b;
	}
	~Renderable(void){};

	virtual void setColor(float r, float g, float b){
		red = r;
		green = g;
		blue = b;
	}

	virtual void draw() =0;
	virtual void update() =0;
protected:
	float red;
	float green;
	float blue;
};

#endif
