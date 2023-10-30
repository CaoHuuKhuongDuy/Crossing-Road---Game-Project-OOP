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
    void draw() override;

private:
    Entity *frame;
    Entity ** score;
    Entity ** level;
    DynamicEntity **enemy;
    Command *command;
    Hero *hero;
    const int numberEnemy = 15;
    long int LONGINTscore = 0;
    int INTlevel = int(floor(LONGINTscore / 1000)) + 1;
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
