#include "SpringContainer.h"


SpringContainer::SpringContainer() : AbstractContainer(){

}


SpringContainer::~SpringContainer(void){
	
}

void SpringContainer::add(DoubleSpring ds){
	doubleSprings.push_back(ds);
}

void SpringContainer::draw(){
	for(unsigned i = 0;i<doubleSprings.size();i++){
		doubleSprings[i].draw();
	}
}

void SpringContainer::update(){
	for(unsigned i = 0;i<doubleSprings.size();i++){
		doubleSprings[i].update();
	}
}

void SpringContainer::enable3rdPerson(){

}

void SpringContainer::changeTargert(){

}
