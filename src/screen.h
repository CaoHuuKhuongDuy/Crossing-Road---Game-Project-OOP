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
    private:
        int width, height;
};

class menuScreen: public Screen {
    public:	
        menuScreen();
    	void draw() override;
    private:
    	string pathColorCode;
    	string Store[12] = {"crossingroad","newgame","loadgame","leaderboard","setting","credit","exit","frame","star","rocket","sartun","jupiter"};
    	
};
