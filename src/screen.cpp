#include "screen.h"


Screen::Screen(int width_, int height_) : width(width_), height(height_), firstScreen(true)  {} 

MenuScreen::MenuScreen() {
    rocket = new DynamicEntity("rocket.txt", {1, 25}, {8, 15});
    rocketMove = 0;
};

MenuScreen::~MenuScreen() {
    delete rocket;
}


void MenuScreen::draw() {
    if (firstScreen) {
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
        importImage.drawASCII("star.txt", {0, 0});
        importImage.drawASCII("crossingroad.txt", {36, 5});
        importImage.drawASCII("frame.txt", {45, 12});
	    Entity *jupiter = new Entity("jupiter.txt", {20,22}, {12,11});
	    Entity *sartun = new Entity("sartun.txt", {170,7}, {21, 20});
	    Entity *venus = new Entity("venus.txt", {140,31}, {23, 15});
        jupiter->draw();
        sartun->draw();
        venus->draw();
        for (int i = 0; i < 6; i++) 
            listButton.addButton(new Button(buttonName[i], {62, SHORT(i * 4 + 13)}, WHITE, GREEN));
        firstScreen = false;
    }
    listButton.draw();
    if (kbhit()) {
        int c = _getch();
        if (c == 32) listButton.changeIdButtonChoosen(listButton.getIdButtonChoosen() + 1);
    }

    rocket->draw();
    rocketMove++;
    rocket->up(1);
    if (rocketMove == 20) {
        rocketMove = 0;
        rocket->teleport({1, 25});
    }
}

GameScreen::GameScreen()
{
	frame = new Entity("redFrame.txt", {1, 1} , {209, 48});
	enemy = new DynamicEntity("enemy1.txt", {5,5}, {6, 6});

};

GameScreen::~GameScreen()
{
	delete frame;
	delete enemy;
}

void GameScreen::draw()
{
	if (firstScreen)
	{
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
		frame->draw();
		importImage.drawASCII("score.txt", {146, 5});
    	importImage.drawASCII("level.txt", {146, 15});
		firstScreen = false;
	}
    enemy->draw();
    enemy->right(1);
    enemyMove++;
    if (enemyMove == 20) {
		enemyMove = 0;
        enemy->teleport({5, 5});
    }

}
	
	// Button* star =  new Button(content[0],{0,0},WHITE,GREEN);
	// star->draw();

	// Entity* redFrame = new Entity(frame + ".txt", {1,1}, {40,40});
	// redFrame->draw();

	// Button* level = new Button("level", {142,5}, WHITE, GREEN);
	// level->draw();

	// Button* score = new Button("score", {142,15}, WHITE, GREEN);
	// score->draw();