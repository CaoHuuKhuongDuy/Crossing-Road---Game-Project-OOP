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

void GameScreen::allocateEnemy()
{
    int random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i] = new DynamicEntity("coolUfo.txt", {SHORT(random + (heroWidth + 40) * i + 13 * (i - 1)), SHORT(heroHeight + 5)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 3] = new DynamicEntity("coolUfo.txt", {SHORT(random + (heroWidth + 40) * i + 13 * (i - 1)), SHORT(heroHeight + 5 + 5 + 2-1)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 6] = new DynamicEntity("coolUfo.txt", {SHORT(random + (heroWidth + 40) * i + 13 * (i - 1)), SHORT(heroHeight + 5 + 5 + 5 + 2 - 1)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 9] = new DynamicEntity("coolUfo.txt", {SHORT(random + (heroWidth + 40) * i + 13 * (i - 1)), SHORT((heroHeight + 3) * 2 + 5 + 5 + 3 + 5 + 5 - 1)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 12] = new DynamicEntity("coolUfo.txt", {SHORT(random + (heroWidth + 40) * i + 13 * (i - 1)), SHORT((heroHeight + 3) * 2 + 5 + 5 + 3 + 5 + 5 + 5 - 1)}, {13, 5});
    }
}

GameScreen::GameScreen() : Screen(new HandlerGameInput())
{
    frame = new Entity("gameFrame.txt", {SHORT((appConsole.getWindowSize().X - 42) / 2), 0}, {190, 42});
    // string STRINGlevel = to_string(INTlevel);
    // string STRINGscore = to_string(LONGINTscore);
    // level = new Entity(to_string(INTlevel) + ".txt");
    // score = new Entity(to_string(LONGINTscore) + ".txt");

    // The size of phoenix must be in range of desktop console
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - heroWidth) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y - heroHeight);
    phoenix = new DynamicEntity("phoenix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {heroWidth, heroHeight});
    enemy = new DynamicEntity *[numberEnemy];
    allocateEnemy();

}

GameScreen::~GameScreen()
{
    delete frame; frame = nullptr;
    delete level; level = nullptr;
    delete score; score = nullptr;
    
    for (int i = 0; i < numberEnemy; ++i)
    {
        delete enemy[i]; enemy[i] = nullptr;
    }
    delete enemy;  enemy = nullptr;
    delete phoenix; phoenix = nullptr;
}

void GameScreen::spawnEnemy(DynamicEntity *entity, double speed)
{
    entity->draw();
    entity->right(speed);
}

void GameScreen::resetEnemyIFAtEdge(DynamicEntity *enemy, SHORT posEdge_X)
{
    if (enemy->getEndPos().X >= SHORT(posEdge_X))
    {
        SHORT temp = enemy->getPos().Y;
        enemy->teleport({0, temp});
    }
}

void GameScreen::resetHeroIFAtEdge(DynamicEntity* hero, SHORT posEdge_Y)
{
    if (hero->getEndPos().Y < posEdge_Y)
    {
        firstScreen = true;
        LONGINTscore += 100;
        INTlevel = LONGINTscore / 1000 + 1;
    }
}


void GameScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        // level->draw();
        // score->draw();
        phoenix->draw();
        firstScreen = false;
    }
    for (int i = 0; i < numberEnemy; i++)
    {
        spawnEnemy(enemy[i], INTlevel);
    }

    for (int i = 0; i < numberEnemy; ++i)
    {
        resetEnemyIFAtEdge(enemy[i], appConsole.getWindowSize().X - 1);
    }

    

    //If player reaches the end lane, then draw whole screen and update player's level and score subsequently.
    resetHeroIFAtEdge(phoenix, 5);


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
