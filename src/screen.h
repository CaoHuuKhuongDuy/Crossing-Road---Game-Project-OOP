#pragma once

#include "staticVariable.h"
#include "entity.h"
#include "button.h"
#include "handlerInput.h"
#include <iostream>

using namespace stValue;
using namespace std;

class Screen
{
public:
    Screen(HandlerInput *handlerInput_, int width = FIX_WIDTH, int height = FIX_HEIGHT);
    virtual void draw() = 0;
    virtual Command *handleInput();

protected:
    HandlerInput *handlerInputMainScreen;
    ButtonList buttonList;
    bool firstScreen;

private:
    int width, height;
};

class MenuScreen : public Screen
{
public:
    MenuScreen();
    ~MenuScreen();
    void draw() override;

private:
    string buttonName[6] = {"newgame", "loadgame", "leaderboard", "setting", "credit", "exit"};
    DynamicEntity *rocket;
    int rocketMove;
};

class GameScreen : public Screen
{
public:
    GameScreen();
    ~GameScreen();

    Command *handleInput() override;

    void allocateEnemy();
    void spawnEnemy(DynamicEntity *, double speed = 1);
    void resetEnemyIFAtEdge(DynamicEntity *entity, SHORT posEdge_X);
    void resetHeroIFAtEdge(DynamicEntity *entity, SHORT posEdge_Y);
    void draw() override;

private:
    Entity *frame;
    Entity *score;
    Entity *level;
    DynamicEntity **enemy;
    Command *command;
    Hero *phoenix;
    SHORT heroWidth = 13;
    SHORT heroHeight = 5;
    const int numberEnemy = 15;
    int INTlevel = 1;
    long int LONGINTscore = 0;
};

class LoadGameScreen : public Screen
{
public:
    LoadGameScreen();
    ~LoadGameScreen();
    void draw() override;

private:
    string buttonName[4] = {"player1", "player2", "player3", "player4"};
    int chooseButton = 0;
};
