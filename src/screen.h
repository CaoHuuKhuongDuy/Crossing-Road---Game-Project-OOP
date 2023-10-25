#pragma once 

#include "staticVariable.h"
#include "entity.h"
#include "button.h"
#include <iostream>

using namespace stValue;
using namespace std;

class Screen {
    public:
        Screen(int width = FIX_WIDTH, int height = FIX_HEIGHT);
        virtual void draw() = 0;
    protected:
        bool firstScreen;
        ListButton listButton;
    private:
        int width, height;
};

class MenuScreen: public Screen {
    public:	
        MenuScreen();
        ~MenuScreen();
    	void draw() override;
    private:
     	string buttonName[6] = {"newgame","loadgame","leaderboard","setting","credit","exit"};   	
        DynamicEntity *rocket;
        int rocketMove;
};

class GameScreen : public Screen
{
    public:
        GameScreen();
        ~GameScreen();
        void draw() override;

    private:
        Entity* frame;
        DynamicEntity* enemy;
        int enemyMove = 0;
};

class LoadGameScreen : public Screen{
    public:
        LoadGameScreen();
        ~LoadGameScreen();
        void draw() override;
    private:
        string buttonName[4] = {"player1", "player2", "player3", "player4"};
        int chooseButton = 0;
};