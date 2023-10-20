#include "screen.h"


Screen::Screen(int width_, int height_) : width(width_), height(height_)  {} 

menuScreen:: menuScreen(): pathColorCode("../media/asciiCode_"){};


void menuScreen:: draw() {
	Button* star =  new Button(pathColorCode+Store[8],{0,0},WHITE,GREEN);
	star->draw();
	Button* button = new Button(pathColorCode+Store[0],{36,5},WHITE,GREEN);
	button->draw(); 
	Button* frame = new Button(pathColorCode+Store[7],{45,12},WHITE,GREEN);
	frame->draw();
    appConsole.setFullscreenBackgroundColor(BG_BLUE);
	int choices = 0;
	Button* choose;
	Button* clearChoose;
	DynamicEntity *rocket = new DynamicEntity("rocket.txt", {1,8}, {8, 16}, string(1, char(219)), false);
	rocket->draw();
	int idx ; 
	while(true){
		Button* buttons[6];
		for(int i=0; i< 6;i++){
			if(choices != i ) {
				clearChoose = new Button(pathColorCode+Store[10],{50,SHORT(i*4+13)},WHITE,GREEN);
				clearChoose->draw();
				buttons[i] =  new Button(pathColorCode+Store[i+1],{60,SHORT(i*4+14)},WHITE,GREEN);
				buttons[i]->draw();
				Sleep(12);
			}
			else 				idx = i;
		}
		if(choices==idx){
			choose = new Button(pathColorCode+Store[9],{50,SHORT(idx*4+13)},WHITE,GREEN);
			choose->draw();
			buttons[idx] =  new Button(pathColorCode+Store[idx+1],{60,SHORT(idx*4+14)},WHITE,GREEN);
			buttons[idx]->draw();
			Sleep(12);
		}
		for (int i = 0; i < 6; i++) {
	    delete buttons[i];
		}	
		int c = getch();
		if(c=='s'){
			choices++;
			if(choices == 6) choices = 0; 
		}
		if(c=='w'){
			choices--;
			if(choices == -1) choices = 5; 	
		}

	}

}
