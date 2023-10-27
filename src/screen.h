#pragma once 

#include "staticVariable.h"
#include "entity.h"
#include "button.h"
#include "handlerInput.h"
#include <iostream>

using namespace stValue;
using namespace std;

class Screen {
    public:
        Screen(HandlerInput *handlerInput_, int width = FIX_WIDTH, int height = FIX_HEIGHT);
        virtual void draw() = 0;
        Command *handleInput();
    protected:
        HandlerInput *handlerInputMainScreen;
        ButtonList buttonList;
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
        DynamicEntity *rocket;
        int rocketMove;
};

class GameScreen : public Screen
{
    public:
        GameScreen();
        ~GameScreen();

        
        void spawnEnemy(DynamicEntity*, double speed = 1);
        void resetEnemyAtEdge(DynamicEntity* entity, SHORT posEdge, int index);
        void draw() override;

    private:
        Entity* frame;
        Entity* edge1, *edge2;
        DynamicEntity** enemy;
        DynamicEntity* basic; 
        DynamicEntity* phonix;

        //Number of enemy will be updated when the level changes
        int numberEnemy = 9;
        bool isAllDraw = false;
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
