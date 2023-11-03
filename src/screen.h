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
    Screen(HandlerInput *handlerInput_);
    virtual void draw() = 0;
    virtual Command *handleInput();

protected:
    HandlerInput *handlerInputMainScreen;
    ButtonList buttonList;
    bool firstScreen;
    string path = "../media/LoadGame/loadGame.txt";
    struct playerData
    {
        string name;
        string level;
        string score;
    };
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
    DynamicEntity **enemy;
    Hero *hero;
    const int numberEnemy = 15;
    // long int LONGINTscore = 0;
    // int INTlevel = int(floor(LONGINTscore / 1000)) + 1;
};

class LoadGameScreen : public Screen
{
public:
    LoadGameScreen();
    ~LoadGameScreen();
    Command *handleInput() override;
    void draw() override;

private:
    Entity *frame;
    string buttonName[4] = {"player1", "player2", "player3", "player4"};
    int chooseButton = 0;
};

class CreditScreen : public Screen
{
public:
    CreditScreen();
    ~CreditScreen();
    Command *handleInput() override;
    void draw() override;

private:
    DynamicEntity **text[17];
    Entity *frame;
    int count = 0;
    int idx = 0;
    string textCredit[17] = {
        "product by group 6",
        "cao huu khuong duy",
        "debug and clean code",
        "logic game",
        "handle input game",
        "nguyen thanh thai",
        "debug and clean code",
        "logic game",
        "artist",
        "tu chi tien",
        "save and load",
        "tester",
        "artist",
        "ngo hai bang",
        "artist and music",
        "debug and clean code",
        "logic game"};
};
