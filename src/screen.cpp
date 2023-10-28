#include "screen.h"

Screen::Screen(HandlerInput *handlerInput_, int width_, int height_) : handlerInputMainScreen(handlerInput_), width(width_), height(height_), firstScreen(true) {}

Command *Screen::handleInput()
{
    return handlerInputMainScreen->handlerInput(buttonList);
}

MenuScreen::MenuScreen() : Screen(new HandlerMenuInput())
{
    rocket = new DynamicEntity("rocket.txt", {1, 25}, {8, 15});
    rocketMove = 0;
};

MenuScreen::~MenuScreen()
{
    delete rocket;
    delete handlerInputMainScreen;
}

void MenuScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
        importImage.drawASCII("star.txt", {0, 0});
        importImage.drawASCII("crossingroad.txt", {36, 5});
        importImage.drawASCII("frame.txt", {45, 12});
        Entity *jupiter = new Entity("jupiter.txt", {20, 22}, {12, 11});
        Entity *sartun = new Entity("sartun.txt", {170, 7}, {21, 20});
        Entity *venus = new Entity("venus.txt", {140, 31}, {23, 15});
        jupiter->draw();
        sartun->draw();
        venus->draw();
        for (int i = 0; i < 6; i++)
            buttonList.addButton(new Button(buttonName[i], {SHORT(80 - buttonName[i].length() * 2), SHORT(i * 4 + 13)}, WHITE, GREEN));
        firstScreen = false;
    }
    buttonList.draw();
    rocket->draw();
    rocketMove++;
    rocket->up(1);
    if (rocketMove == 20)
    {
        rocketMove = 0;
        rocket->teleport({1, 25});
    }
}

GameScreen::GameScreen() : Screen(new HandlerGameInput())
{
    SHORT frameWidth = 168;  // Width of the "frame" entity
    SHORT frameHeight = 42;  // Height of the "frame" entity
    SHORT frameX = (appConsole.getWindowSize().X - frameWidth) / 2;
    // SHORT frameX = 0;  
    SHORT frameY = 0;  // Positioned at the top edge


    frame = new Entity("gameFrame.txt", {frameX, frameY}, {frameWidth, frameHeight});

    //The size of phoenix must be in range of desktop console
    SHORT heroWidth = 11;
    SHORT heroHeight = 3;
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - heroWidth) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y - heroHeight);
    basic = new DynamicEntity("phonix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {heroWidth, heroHeight});
    enemy = new DynamicEntity *[numberEnemy];
    for (int i = 0; i < numberEnemy; ++i)
    {
        int r = rand() % 150;
        enemy[i] = new DynamicEntity("coolUfo.txt", {SHORT(20), SHORT(i * 5 + 3)}, {11, 5});
    }
}

GameScreen::~GameScreen()
{
    delete frame;
    for (int i = 0; i < numberEnemy; ++i)
    {
        delete enemy[i];
        enemy[i] = nullptr;
    }
    delete enemy;
    delete basic;

    frame = nullptr;
    enemy = nullptr;
    basic = nullptr;
}

void GameScreen::spawnEnemy(DynamicEntity *entity, double speed)
{
    entity->draw();
    entity->right(speed);
}

void GameScreen::resetEnemyAtEdge(DynamicEntity *enemy, SHORT posEdge, int index)
{
    if (enemy->getPos().X >= SHORT(posEdge))
    {
        SHORT row = index / (numberEnemy / 3);
        SHORT yPos = 7 + row * 15;
        enemy->teleport({-1, yPos});
    }
}

void GameScreen::draw()
{

    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        basic->draw();
        firstScreen = false;
    }
    for (int i = 0; i < numberEnemy; i++)
    {
        enemy[i]->draw();
    }

    // const int step = numberEnemy / 3;

    // for (int i = 0; i < numberEnemy; i += step)
    // {
    //     spawnEnemy(enemy[i]);
    // }

    // if (isAllDraw)
    // {
    //     for (int j = 0; j < step - 1; ++j)
    //     {
    //         for (int i = 1; i < numberEnemy; i += step)
    //         {
    //             spawnEnemy(enemy[i + j]);
    //         }
    //     }
    // }

    // else
    // {
    //     for (int j = 0; j < step - 1; ++j)
    //     {
    //         for (int i = 1; i < numberEnemy; i += step)
    //         {
    //             if (enemy[i + j - 1]->getPos().X >= SHORT(70))
    //             {

    //                 spawnEnemy(enemy[i + j]);
    //             }
    //             if (i + j == numberEnemy - 1)
    //                 isAllDraw = true;
    //         }
    //     }
    // }

    // for(int i = 0; i < numberEnemy / 3; ++i)
    // {

    // }

    // for (int i = 0; i < numberEnemy; ++i)
    // {
    //     resetEnemyAtEdge(enemy[i], 134, i);
    // }
}

LoadGameScreen::LoadGameScreen() : Screen(new HandlerLoadInput())
{
}

LoadGameScreen::~LoadGameScreen()
{
}

void LoadGameScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_BLUE);


        // importImage.drawImage("LoadGameSaved.txt", {53, 2});
        // for (int i = 0; i < 4; i++) {
        //     buttonList.addButton(new Button("credit", {SHORT(80 - 6 * 2), SHORT(i * 4 + 13)}, WHITE, BLACK));
        // }



        // for (int i = 0 ; i < 4; i++) {
        //     if (i < 2) {
        //         buttonList.addButton(new Button("credit", {SHORT(12 + 84 * i), SHORT(14)}, WHITE, BLACK));
        //     }
        //     else {
        //         buttonList.addButton(new Button("credit", {SHORT(12 + 84 * (i - 2)), SHORT(14 + 14)}, WHITE, BLACK));
        //     }
        // }

        // buttonList.draw();  



        // firstScreen = false;
        // Entity *title = new Entity("LoadGameSaved.txt", {53, 2}, {63, 5});
        // title->draw();
        // for (int i = 0 ; i < 4; i++) {
        //     if (i < 2) {
        //         importImage.drawCustomImage("tien", {SHORT(32 + 84 * i), SHORT(14)});
        //     }
        //     else {
        //         importImage.drawCustomImage("bang", {SHORT(32 + 84 * (i - 2)), SHORT(14 + 14)});
        //     }
        // }



    }

}
