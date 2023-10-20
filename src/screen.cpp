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
	Rocket* rocket = new Rocket({5,10},{10,20});
	rocket->draw();
	Jupiter* jupiter = new Jupiter({22,12}, {0,0});
	jupiter->draw();
	Sartun* sartun = new Sartun({136,30}, {0,0});
	sartun->draw();

	Venus* venus = new Venus({160,12}, {0,0});
	venus->draw();
	Button* buttons[6];
	int choices = 0;
	Button* choose;
	Button* clearChoose;
	int idx ; 
	while(true){
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
