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
    bool firstGame = true;
    string path = "../media/LoadGame/loadGame.txt";
    struct playerData {
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

class InputScreen: public Screen
{
  public:
     InputScreen();
     ~InputScreen();
    Command *handleInput() override;
    void draw() override;

  private:    
      Entity *welcome;
      Entity **chac;	
      string name = "";
      string arr[6] = {"@","@","@","@","@","@"};
};

//class OutputScreen: public Screen
//{
//  public:
//     OutputScreen();
//     ~OutputScreen();
//    Command *handleInput() override;
//    void draw() override;
//
//  private:    
//      Entity *frame;
//      Entity *bus;
//	  Entity *hero;		  	
//};


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
    Entity *finish_line;
    DynamicEntity **enemy;
    Hero *hero;
    TrafficLight* trafficlight;
    const int numberEnemy = 15;
    Entity *welcome;
    Entity **chac;	
    string name = "";
    string arr[6] = {"@","@","@","@","@","@"};
    Entity *overgameframe;
    DynamicEntity *bus;
    Entity *die;	    
};

class LoadGameScreen : public Screen
{
public:
    LoadGameScreen();
    ~LoadGameScreen();
    Command *handleInput() override;
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
    Command *handleInput() override;
	void draw() override;
private: 
   DynamicEntity **text[17]; 
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
    Command *handleInput() override;
    void swap(playerData &a, playerData &b);
    void draw() override;
private:    
    Entity *frame;
    Entity *title;
    DynamicEntity* moon, * star; 
   };
