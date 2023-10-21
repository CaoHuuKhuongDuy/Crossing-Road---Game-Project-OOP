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
	int choices = 0;
	Button* choose;
	Button* clearChoose;
	DynamicEntity *rocket = new DynamicEntity("rocket.txt", {1,10}, {8, 18}, string(1, char(219)), false);
	Entity *jupiter = new Entity("Jupiter.txt", {20,22}, {0,0});
	Entity *sartun = new Entity("Sartun.txt", {170,7}, {0,0});
	Entity *venus = new Entity("Venus.txt", {140,31}, {0,0});
	int idx ;
	int move = 8;

	Button *buttons[6];
	while (true)
	{
		for (int i = 0; i < 6; i++)
		{
			if (choices != i)
			{
				clearChoose = new Button(pathColorCode + Store[10], {50, SHORT(i * 4 + 13)}, WHITE, GREEN);
				clearChoose->draw();
				buttons[i] = new Button(pathColorCode + Store[i + 1], {60, SHORT(i * 4 + 14)}, WHITE, GREEN);
				buttons[i]->draw();
			}
			else
			{
				idx = i;
			}
		}
		if(choices==idx){
			choose = new Button(pathColorCode+Store[9],{50,SHORT(idx*4+13)},WHITE,GREEN);
			choose->draw();
			buttons[idx] =  new Button(pathColorCode+Store[idx+1],{60,SHORT(idx*4+14)},WHITE,GREEN);
			buttons[idx]->draw();
		}


		for (int i = 0; i < 6; i++) {
	    delete buttons[i];
		}	
		
		if(kbhit()){
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
		else {
			jupiter->draw();
			sartun->draw();
			venus->draw();
			rocket->draw();
     		rocket->up(1);
     		move --;
        	if(move==0) {
        		move = 8;
        		rocket->down(8);	
			}
		}
	}
}
