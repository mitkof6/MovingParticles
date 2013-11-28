#ifndef COLLISIONCOUNTER_H_
#define COLLISIONCOUNTER_H_

#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

class CollisionCounter{

public:
	CollisionCounter(void);
	~CollisionCounter(void);

	void incTime();
	void incCounter();
	void registerEvent();

	void saveToMat(string path);

private:
	unsigned long time, counter;
	vector<unsigned long> timeSeq, counterSeq;
};

#endif

