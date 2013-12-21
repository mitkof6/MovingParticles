#ifndef COLLISIONCOUNTER_H_
#define COLLISIONCOUNTER_H_

#include <vector>
#include <stdio.h>
#include <string>

#include "Constants.h"
#include "Renderable.h"
#include "GL/glut.h"

using namespace std;

class CollisionCounter : public Renderable{

public:
	CollisionCounter(void);
	~CollisionCounter(void);

	void incTime();
	void incCounter();
	void registerEvent();
	void clear();

	void draw();
	void update();

	void setName(string n);

	void saveToMat(string path);

	unsigned long getDifference();

	void add(unsigned long count);

private:
	string name;
	unsigned long time, counter;
	short difference;
	vector<unsigned long> timeSeq, counterSeq;

	void drawString(const char *str, int x, int y, float color[4], void *font);
};

#endif

