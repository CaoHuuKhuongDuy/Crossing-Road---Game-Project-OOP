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

class menuScreen: public Screen {
    public:	
        menuScreen();
        ~menuScreen();
    	void draw() override;
    private:
     	string buttonName[6] = {"newgame","loadgame","leaderboard","setting","credit","exit"};   	
        int chooseButton = 0;
        DynamicEntity *rocket;
        int rocketMove;
};
