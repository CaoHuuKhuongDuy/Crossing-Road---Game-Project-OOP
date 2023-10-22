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
        int numFrame;
    private:
        int width, height;
};

class menuScreen: public Screen {
    public:	
        menuScreen();
    	void draw() override;
    private:
    	string pathColorCode;
     	string Store[6] = {"newgame","loadgame","leaderboard","setting","credit","exit"};   	
};

class gameScreen : public Screen
{
    public:
        gameScreen();
        void draw() override;

    private:
        string pathColorCode;
        string pathAsciiCode;

        string content[10] = {"star","level","score", "redFrame"};
};
