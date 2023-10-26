#include "screen.h"

Screen::Screen(int width_, int height_) : width(width_), height(height_), firstScreen(true) {}

Screen::Screen(HandlerInput *handlerInput_, int width_, int height_) : 
    handlerInputMainScreen(handlerInput_), width(width_), height(height_), firstScreen(true)  {} 

Command *Screen::handleInput() {
    return handlerInputMainScreen->handlerInput(buttonList);
}

MenuScreen::MenuScreen() : Screen(new HandlerMenuInput()) {
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
            buttonList.addButton(new Button(buttonName[i], {62, SHORT(i * 4 + 13)}, WHITE, GREEN));
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
    frame = new Entity("redFrame.txt", {1, 2}, {209, 47});
    enemy = new DynamicEntity *[numberEnemy];

    int enemiesPerRow = numberEnemy / 3; // Số lượng enemies trên mỗi hàng

    for (int i = 0; i < numberEnemy; ++i)
    {
        SHORT row = i / enemiesPerRow; // Xác định hàng cho enemy hiện tại

        // Tính toán vị trí Y dựa trên hàng
        SHORT yPos = 7 + row * 15;

        enemy[i] = new DynamicEntity("enemy1.txt", {-1, yPos}, {6, 6});
    }

    edge1 = new Entity("edge.txt", {1, 1}, {0, 0});
    edge2 = new Entity("edge.txt", {140, 1}, {0, 0});
}

GameScreen::~GameScreen()
{
    delete frame;
    for (int i = 0; i < numberEnemy; ++i)
        delete enemy[i];
    delete enemy;
    delete edge1;
    delete edge2;
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
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
        frame->draw();
        importImage.drawASCII("level.txt", {146, 5});
        importImage.drawASCII("score.txt", {146, 15});
        firstScreen = false;
    }
    edge1->draw();
    edge2->draw();

    const int step = numberEnemy / 3;

    for (int i = 0; i < numberEnemy; i += step)
    {
        spawnEnemy(enemy[i]);
    }
    if (!isAllDraw)
    {
        for (int j = 0; j < step - 1; ++j)
        {
            for (int i = 1; i < numberEnemy; i += step)
            {
                if (enemy[i + j - 1]->getPos().X >= SHORT(45))
                {
                    spawnEnemy(enemy[i + j]);
                    if (j == step - 2)
                        isAllDraw = true;
                }
            }
        }
    }
    else
    {
        for (int j = 0; j < step - 1; ++j)
        {
            for (int i = 1; i < numberEnemy; i += step)
            {
                spawnEnemy(enemy[i + j]);
            }
        }
    }

    for (int i = 0; i < numberEnemy; ++i)
    {
        resetEnemyAtEdge(enemy[i], 134, i);
    }
}

LoadGameScreen::LoadGameScreen() : Screen(new HandlerLoadInput()) {
    
}

LoadGameScreen::~LoadGameScreen()
{
}

void LoadGameScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
        importImage.drawASCII("LoadGameSaved.txt", {340, 20});
        firstScreen = false;
    }
    Button *buttons[4];
    for (int i = 0; i < 4; i++)
        buttons[i] = new Button(buttonName[i], {50, SHORT(i * 4 + 13)}, WHITE, GREEN);
    if (kbhit())
    {
        int c = getch();
        if (c == 80)
            (chooseButton += 1) %= 6;
    }
    buttons[chooseButton]->toggleHighlight();
    for (int i = 0; i < 4; i++)
        buttons[i]->draw();
    for (int i = 0; i < 4; i++)
        delete buttons[i];
}
