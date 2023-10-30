#include "screen.h"

Screen::Screen(HandlerInput *handlerInput_, int width_, int height_) : handlerInputMainScreen(handlerInput_), width(width_), height(height_), firstScreen(true) {}

Command *Screen::handleInput()
{
    return handlerInputMainScreen->handlerInput(buttonList);
}

Command *GameScreen::handleInput()
{
    return handlerInputMainScreen->handlerInput();
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
        // const char *path = "haha.wav";
        // PlaySound(path, NULL, SND_FILENAME | SND_ASYNC );
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
        enemy[i] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(3)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 3] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(8)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 6] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(18)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 9] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(23)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 12] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(33)}, {13, 5});
    }
}

GameScreen::GameScreen() : Screen(new HandlerGameInput())
{
    frame = new Entity("gameFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - 13) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y + 10);
    hero = new Hero("phoenix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {13, 5}, LONGINTscore, INTlevel);
    // string STRINGlevel = to_string(INTlevel);
    // string STRINGscore = to_string(LONGINTscore);
    // level = new Entity(to_string(INTlevel) + ".txt");
    // score = new Entity(to_string(LONGINTscore) + ".txt");
    // The size of phoenix must be in range of desktop console
    enemy = new DynamicEntity *[numberEnemy];
    allocateEnemy();
}

GameScreen::~GameScreen()
{
    delete frame;
    frame = nullptr;
    delete level;
    level = nullptr;
    delete score;
    score = nullptr;
    delete command;
    command = nullptr;
    for (int i = 0; i < numberEnemy; ++i)
    {
        delete enemy[i];
        enemy[i] = nullptr;
    }
    delete enemy;
    enemy = nullptr;
    delete hero;
    hero = nullptr;
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

void GameScreen::resetHeroIFAtEdge(Hero *hero, SHORT posEdge_Y)
{
    if (hero->getEndPos().Y <= posEdge_Y)
    {
        firstScreen = true;
        hero->updateHeroExp();
        hero->teleport({hero->getPos().X, SHORT(appConsole.getWindowSize().Y + 10)});
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
        firstScreen = false;
    }
    hero->draw();
    for (int i = 0; i < numberEnemy; i++)
    {
        spawnEnemy(enemy[i], INTlevel);
    }

    for (int i = 0; i < numberEnemy; ++i)
    {
        resetEnemyIFAtEdge(enemy[i], appConsole.getWindowSize().X - 1);
    }

    command = handlerInputMainScreen->handlerInput();

    if (command != nullptr)
    {
        command->execute(hero);
    }
    for (int i = 0; i < numberEnemy; ++i)
    {

        if (hero->checkCollision(enemy[i]) == true)
        {
            firstScreen = true;
            hero->teleport({hero->getPos().X, SHORT(appConsole.getWindowSize().Y + 10)});
        }
    }

    // If player reaches the end lane, then draw whole screen and update player's level and score subsequently.
    resetHeroIFAtEdge(hero, 6);
}

// LoadGameScreen::LoadGameScreen() : Screen(new HandlerLoadInput())
// {
// }

// LoadGameScreen::~LoadGameScreen()
// {
// }

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
