#pragma once

#include "staticVariable.h"
#include "entity.h"
#include "button.h"
#include "player.h"
#include "handlerInput.h"
#include <iostream>
#include <algorithm>

using namespace stValue;
using namespace std;

#include <string>


class Screen
{
public:
    Screen(HandlerInput *handlerInput_);
    virtual void draw() = 0;
    virtual Command *handleInput();
    void setAgain();
protected:
    HandlerInput *handlerInputMainScreen;
    ButtonList buttonList;
    bool firstScreen;
    bool firstGame = true;
    string path = "../media/LoadGame/loadGame.txt";
    Player player;
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
    DynamicEntity **meteor;
    int rocketMove;
};


class IntroGameScreen : public Screen {
    public:
        IntroGameScreen();
        ~IntroGameScreen();

        Command *handleInput();
        void draw() override;

        string getName();
    private:
        Entity *welcome;
        string name = "";
        Entity *textInputEntity;
        string textInput;
        bool enterGame;
        bool lastFrame;
        ListPlayer players;
};

class GameScreen : public Screen
{
public:
    GameScreen();
    ~GameScreen();


    void buildFrame();
    void buildFinishline();
    void buildEnemy();
    void buildHero();
    void buildTrafficlight();
    
    void manageTrafficLight();
    void manageEnemy();
    void manageHero();
    
    void draw() override;

private:
    Entity *frame;
    Entity *finish_line;
    Enemy **enemy;
    Hero *hero;
    TrafficLight** trafficlight;
    string level;
    string score;
    const int numberTrafficLight = 5;
    const int numberEnemy = 15;
};      

class OverGameScreen : public Screen {
    public:
        OverGameScreen();
    private:
        Entity *overgameframe, *overframe;
        DynamicEntity *bus;
        Entity *die;	    

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

class CreditScreen : public Screen 
{
public:	
	CreditScreen();
	~CreditScreen();
	void draw() override;
private: 
   DynamicEntity *text[17]; 
   Entity* frame;
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
   			"logic game"
   };	
};
class LeaderBoardScreen : public Screen
{
public:
    LeaderBoardScreen();
    ~LeaderBoardScreen();
    void swap(Player &a, Player &b);
    void draw() override;
private:    
    Entity *frame;
    Entity *title;
    DynamicEntity* moon, * star; 
};


class PauseGameScreen : public Screen {
    public:
        PauseGameScreen();
        ~PauseGameScreen();
        void draw() override;
    private:
        Entity *frame;
};