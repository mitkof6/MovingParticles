#include "CollisionCounter.h"


CollisionCounter::CollisionCounter(void){
	time = counter = 0;
}


CollisionCounter::~CollisionCounter(void){

}

void CollisionCounter::incTime(){
	time++;
}

void CollisionCounter::incCounter(){
	counter++;
}

void CollisionCounter::registerEvent(){
	timeSeq.push_back(time);
	counterSeq.push_back(counter);
}

void CollisionCounter::saveToMat(string path){
	FILE *file;

    if (!(file = fopen(path.c_str(), "w")))
		return;

	for(unsigned i = 0;i<timeSeq.size();i++){
		fprintf(file, "%d %d\n", timeSeq[i], counterSeq[i]);
	}

	fclose(file);
}
