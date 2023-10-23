#include "screen.h"


Screen::Screen(int width_, int height_) : width(width_), height(height_), firstScreen(true)  {} 

MenuScreen::MenuScreen() {
    rocket = new DynamicEntity("rocket.txt", {1, 10}, {8, 15}, string(1, char(219)), false);
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
        firstScreen = false;
    }
	Button *buttons[6];
    for (int i = 0; i < 6; i++) 
        buttons[i] = new Button(buttonName[i], {50, SHORT(i * 4 + 13)}, WHITE, GREEN);
    if (kbhit()) {
        int c = getch();
        if (c == 80) (chooseButton += 1) %= 6;
    }
    buttons[chooseButton]->toggleHighlight();
    for (int i = 0; i < 6; i++)
        buttons[i]->draw();
    for (int i = 0; i < 6; i++)
        delete buttons[i];
    rocket->draw();
    // if (rocket->getPos().X == 1) rocket->teleport({9, 10});
    // else rocket->teleport({1, 10});
    rocketMove++;
    rocket->up(1);
    if (rocketMove == 5) {
        rocketMove = 0;
        rocket->teleport({1, 10});
    }
}

GameScreen::GameScreen()
{
	frame = new Entity("redFrame.txt", {1, 1} , {0,0});
	enemy = new DynamicEntity("enemy1.txt", {5,5}, {0,0});

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
		frame->draw();
		//Import "Level" - i cannot load level.txt although it's still correct
		importImage.drawASCII("score.txt", {146, 5});
    	importImage.drawASCII("score.txt", {146, 15});
		firstScreen = false;
	}
    enemy->draw();
    // Move the enemy to the right
    enemy->right(1);
    enemyMove++;
    // Check if it's time to reset the enemy's position
    if (enemyMove == 20)
    {
		enemyMove = 0;
        // Reset the enemy's position to the left
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