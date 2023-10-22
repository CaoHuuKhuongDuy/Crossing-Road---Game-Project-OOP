#include "screen.h"


Screen::Screen(int width_, int height_) : width(width_), height(height_), firstScreen(true)  {} 

menuScreen::menuScreen() {
    rocket = new DynamicEntity("rocket.txt", {1, 10}, {8, 15}, string(1, char(219)), false);
    rocketMove = 0;
};

menuScreen::~menuScreen() {
    delete rocket;
}


void menuScreen::draw() {
    if (firstScreen) {
        importImage.drawASCII("star.txt", {0, 0});
        importImage.drawASCII("crossingroad.txt", {36, 5});
        importImage.drawASCII("frame.txt", {45, 12});
	    Entity *jupiter = new Entity("jupiter.txt", {20,22}, {12,11});
	    Entity *sartun = new Entity("sartun.txt", {170,7}, {21, 20});
	    Entity *venus = new Entity("venus.txt", {140,31}, {23, 15});
        jupiter->draw();
        sartun->draw();
        venus->draw();
        firstScreen = false;
    }
	Button *buttons[6];
    for (int i = 0; i < 6; i++) 
        buttons[i] = new Button(buttonName[i], {50, SHORT(i * 4 + 13)}, WHITE, GREEN);
    if (kbhit()) {
        int c = getch();
        if (c == 32) (chooseButton += 1) %= 6;
    }
    buttons[chooseButton]->toggleHighlight();
    for (int i = 0; i < 6; i++)
        buttons[i]->draw();
    for (int i = 0; i < 6; i++)
        delete buttons[i];
    rocket->draw();
    rocketMove++;
    rocket->up(1);
    if (rocketMove == 9) {
        rocketMove = 0;
        rocket->teleport({1, 10});
    }

    
        // Button* button = new Button("", {36,5}, WHITE, GREEN);
	// star->draw();
    
	// button->draw(); 

	// Button* frame = new Button(pathColorCode+Store[7],{45,12},WHITE,GREEN);
	// frame->draw();
	// int choices = 0;
	// Button* choose;
	// Button* clearChoose;
	// int idx ;
	// int move = 8;

	// while (true)
	// {
	// 	for (int i = 0; i < 6; i++)
	// 	{
	// 		if (choices != i)
	// 		{
	// 			clearChoose = new Button(pathColorCode + Store[10], {50, SHORT(i * 4 + 13)}, WHITE, GREEN);
	// 			clearChoose->draw();
	// 			buttons[i] = new Button(pathColorCode + Store[i + 1], {60, SHORT(i * 4 + 14)}, WHITE, GREEN);
	// 			buttons[i]->draw();
	// 		}
	// 		else
	// 		{
	// 			idx = i;
	// 		}
	// 	}
	// 	if(choices==idx){
	// 		choose = new Button(pathColorCode+Store[9],{50,SHORT(idx*4+13)},WHITE,GREEN);
	// 		choose->draw();
	// 		buttons[idx] =  new Button(pathColorCode+Store[idx+1],{60,SHORT(idx*4+14)},WHITE,GREEN);
	// 		buttons[idx]->draw();
	// 	}


	// 	for (int i = 0; i < 6; i++) {
	//     delete buttons[i];
	// 	}	
		
	// 	if(kbhit()){
	// 	int c = getch();
	// 	  if (c == 's') choices++;
	// 	  if (c == 'w') choices--;
    //       (choices += 6) %= 6;
	// 	}
	// 	else {
	// 		// jupiter->draw();
	// 		// sartun->draw();
	// 		// venus->draw();
	// 		rocket->draw();
    //  		//rocket->up(1);
    //  		move --;
    //     	if(move==0) {
    //     		move = 8;
    //     		// rocket->down(8);	
	// 		}
	// 	}
	// }
}




void gameScreen::draw()
{
	Button* star =  new Button(pathAsciiCode+content[0],{0,0},WHITE,GREEN);
	star->draw();

	Entity* redFrame = new Entity(content[3] + ".txt", {1,1}, {40,40});
	redFrame->draw();

	Button* level = new Button(pathAsciiCode+"level", {142,5}, WHITE, GREEN);
	level->draw();

	Button* score = new Button(pathAsciiCode+"score", {142,15}, WHITE, GREEN);
	score->draw();


}