#pragma once 

#include "staticVariable.h"
#include"entity.h"
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
        int chooseButton = 0;
        DynamicEntity *rocket;
        int rocketMove;
};

class GameScreen : public Screen
{
    public:
        GameScreen();
        void draw() override;

    private:
        string content[10] = {"star","level","score", "redFrame"};
};
