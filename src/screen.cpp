#include "screen.h"


Screen::Screen(int width_, int height_) : width(width_), height(height_)  {} 

menuScreen:: menuScreen(): pathColorCode("../media/asciiCode_"){};


void menuScreen:: draw() {
	// Button* star =  new Button(pathColorCode+Store[8],{0,0},WHITE,GREEN);
	// star->draw();
	// Button* button = new Button(pathColorCode+Store[0],{36,5},WHITE,GREEN);
	// button->draw(); 
	// Button* frame = new Button(pathColorCode+Store[7],{45,12},WHITE,GREEN);
	// frame->draw();
	
	// Button* buttons[6];
	// for(int i=0; i< 6;i++){
	// 	buttons[i] =  new Button(pathColorCode+Store[i+1],{60,SHORT(i*4+14)},BLACK,GREEN);
	// 	buttons[i]->draw();
	// }
	// COORD n1, n2;
	// DynamicEntity *rocket = new DynamicEntity({5,10},{10,20});
    DynamicEntity *rocket = new DynamicEntity("rocket.txt", {5, 10}, {6, 11}, string(1, char(219)), false);
	rocket->draw();
}
