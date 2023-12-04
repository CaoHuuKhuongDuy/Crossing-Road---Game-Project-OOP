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
    Screen(HandlerInput *handlerInput_, string music_ = "background.wav");
    virtual ~Screen();
    virtual void draw() = 0;
    virtual Command *handleInput();
    void playMusic();
    void setAgain();

protected:
    string music;
    HandlerInput *handlerInputMainScreen;
    ButtonList buttonList;
    bool firstScreen;
    bool firstGame = true;
    string path = "../media/LoadGame/loadGame.txt";
    string nameHero[2] = {"phoenix.txt", "dragon.txt"};
    Player player; 
    Hero *hero;
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
    COORD idx[12] = {{28, 1},{196, 15},{151, 24},{40, 24},{159, 10},{22, 15},{159, 2},{165, 16},{51, 11},{50, 26},{50, 0},{203, 27}};
};


class IntroGameScreen : public Screen {
    public:
        IntroGameScreen();
        ~IntroGameScreen();

        Command *handleInput();
        void draw() override;

        string getName();
        string getTime();
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
class LeaderBoardScreen : public Screen{
public:
    LeaderBoardScreen();
    ~LeaderBoardScreen();
    void draw() override;
private:    
    Entity *frame;
    DynamicEntity* moon, * star, *congratulate[2];  
    Entity *gold, *silver, *copper, *crown;
    COORD posName[3] = {{90, 12}, {42, 25}, {147, 27}};
    COORD posScore[3] = {{90, 49}, {45, 49}, {150, 49}};
    Entity* medal[3];

};

class PauseGameScreen : public Screen {
    public:
        PauseGameScreen();
        ~PauseGameScreen();
        void draw() override;
    private:
        Entity *frame;
};


class OverScreen : public Screen {
    public:
        OverScreen();
        ~OverScreen();
        void draw() override;
    private: 
    	Entity* overFrame,* hero1, *hero2;
    	DynamicEntity* die;
    	int count = 0;
    	COORD arr[6] = {{32, 25},{24, 38},{44, 15},{162, 28},{170, 38},{177, 14}};
};

class SettingScreen : public Screen {
    public:
        SettingScreen();
        ~SettingScreen();
        void draw() override;
    private: 
    	Entity *settingFrame, * nv1, * nv2;
        string buttonName[4] = {"frameChoose", "frameChoose", "sub", "plus"};
        string nameHero[2] = {"phoenix.txt", "dragon.txt"}; 
    	int chooseButton = 0;
        int valueVolume = 4; 

};
