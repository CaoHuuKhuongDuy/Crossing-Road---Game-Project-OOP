#include "screen.h"

Screen::Screen(HandlerInput *handlerInput_, int width_, int height_) : handlerInputMainScreen(handlerInput_), width(width_), height(height_), firstScreen(true) {}

Command *Screen::handleInput()
{
    return handlerInputMainScreen->handlerInput(buttonList);
}

Command *GameScreen::handleInput()
{
    return handlerInputMainScreen->handlerInput();
}

MenuScreen::MenuScreen() : Screen(new HandlerMenuInput())
{
    rocket = new DynamicEntity("rocket.txt", {1, 25}, {8, 15});
    rocketMove = 0;
};

MenuScreen::~MenuScreen()
{
    delete rocket;
    delete handlerInputMainScreen;
}

void MenuScreen::draw()
{
    if (firstScreen)
    {
        // const char *path = "haha.wav";
        // PlaySound(path, NULL, SND_FILENAME | SND_ASYNC );
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
        importImage.drawASCII("star.txt", {0, 0});
        importImage.drawASCII("crossingroad.txt", {36, 5});
        importImage.drawASCII("frame.txt", {45, 12});
        Entity *jupiter = new Entity("jupiter.txt", {20, 22}, {12, 11});
        Entity *sartun = new Entity("sartun.txt", {170, 7}, {21, 20});
        Entity *venus = new Entity("venus.txt", {140, 31}, {23, 15});
        jupiter->draw();
        sartun->draw();
        venus->draw();
        for (int i = 0; i < 6; i++)
            buttonList.addButton(new Button(buttonName[i], {SHORT(80 - buttonName[i].length() * 2), SHORT(i * 4 + 13)}, WHITE, GREEN));
        firstScreen = false;
    }
    buttonList.draw();
    rocket->draw();
    rocketMove++;
    rocket->up(1);
    if (rocketMove == 20)
    {
        rocketMove = 0;
        rocket->teleport({1, 25});
    }
}

void GameScreen::allocateEnemy()
{
    int random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i] = new DynamicEntity("stone.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(3)}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 3] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(8)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 6] = new DynamicEntity("bigUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 10 * (i - 1)), SHORT(18)}, {20, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 9] = new DynamicEntity("stone.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(23)}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 12] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(33)}, {13, 5});
    }
}

GameScreen::GameScreen() : Screen(new HandlerGameInput(this->hero))
{
    frame = new Entity("gameFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - 13) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y);
    hero = new Hero("phoenix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {11, 5}, LONGINTscore, INTlevel);
    string STRINGlevel = to_string(INTlevel);
    string STRINGscore = to_string(LONGINTscore);
    enemy = new DynamicEntity *[numberEnemy];
    allocateEnemy();
}

GameScreen::~GameScreen()
{
    delete frame;
    frame = nullptr;
    delete level;
    level = nullptr;
    delete score;
    score = nullptr;
    delete command;
    command = nullptr;
    for (int i = 0; i < numberEnemy; ++i)
    {
        delete enemy[i];
        enemy[i] = nullptr;
    }
    delete enemy;
    enemy = nullptr;
    delete hero;
    hero = nullptr;
}


void GameScreen::draw()
{
    string STRINGlevel = to_string(hero->getHeroLevel());
    string STRINGscore = to_string(hero->getHeroScore());
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
	    string substring; 
	    level = new Entity *[STRINGlevel.length()];
	    string temp2 =  to_string(LONGINTscore);
	    score = new Entity *[STRINGscore.length()];
    for(int i=0;i<STRINGlevel.length();i++){
    	substring = STRINGlevel.substr(i,1);
    	level[i] = new Entity("number" + substring  + ".txt",{SHORT(appConsole.getWindowSize().X - 15) + i*4,0},{SHORT(3),3});
		}
    for(int i=0;i<STRINGscore.length();i++){
      	substring = STRINGscore.substr(i,1);
        score[i] = new Entity("number" + substring + ".txt",{SHORT(30+i*4),0},{SHORT(3),3});
		}
        firstScreen = false;
    }
    hero->draw();
    for(int i=0;i<STRINGlevel.length();i++){
        level[i]->draw();
    }
    for(int i=0;i<STRINGscore.length();i++){
         score[i]->draw();
        }
    for(int i = 0; i < numberEnemy; ++i)
    {
        enemy[i]->spawnDynamicEntity(hero->getHeroLevel());
        if (enemy[i]->isAtEdge(appConsole.getWindowSize().X - 1))
            enemy[i]->resetDynamicEntity();
    }

    for (int i = 0; i < numberEnemy; ++i)
    {
        if (hero->isCollision(enemy[i]) == true)
        {
            firstScreen = true;
            hero->resetDynamicEntity();
            return;
        }
    }
    
    
    // If player reaches the end lane, then draw whole screen and update player's level and score subsequently.
    if (hero->isAtEdge(6))
    {
        hero->resetDynamicEntity();
        hero->updateHeroExp();
        hero->draw();
        delete []level;
        delete []score;        
        firstScreen = true;
        
    }


}

// LoadGameScreen::LoadGameScreen() : Screen(new HandlerLoadInput())
// {
// }

// LoadGameScreen::~LoadGameScreen()
// {
// }

void LoadGameScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_BLUE);

        // importImage.drawImage("LoadGameSaved.txt", {53, 2});
        // for (int i = 0; i < 4; i++) {
        //     buttonList.addButton(new Button("credit", {SHORT(80 - 6 * 2), SHORT(i * 4 + 13)}, WHITE, BLACK));
        // }

        // for (int i = 0 ; i < 4; i++) {
        //     if (i < 2) {
        //         buttonList.addButton(new Button("credit", {SHORT(12 + 84 * i), SHORT(14)}, WHITE, BLACK));
        //     }
        //     else {
        //         buttonList.addButton(new Button("credit", {SHORT(12 + 84 * (i - 2)), SHORT(14 + 14)}, WHITE, BLACK));
        //     }
        // }

        // buttonList.draw();

        // firstScreen = false;
        // Entity *title = new Entity("LoadGameSaved.txt", {53, 2}, {63, 5});
        // title->draw();
        // for (int i = 0 ; i < 4; i++) {
        //     if (i < 2) {
        //         importImage.drawCustomImage("tien", {SHORT(32 + 84 * i), SHORT(14)});
        //     }
        //     else {
        //         importImage.drawCustomImage("bang", {SHORT(32 + 84 * (i - 2)), SHORT(14 + 14)});
        //     }
        // }
    }
}

// CreditScreen::CreditScreen() : Screen(new HandlerGameInput())
// {
// 	frame = new Entity("creditFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
// 	for(int i=0;i<17;i++)	text[i] = new DynamicEntity *[textCredit[i].length()];
// }

// CreditScreen:: ~ CreditScreen() 
// {
//     for (int i = 0; i < 11; ++i)
//     {
//         delete text[i];
//         text[i] = nullptr;
//     }
//     delete[] text;

// }

// void CreditScreen::draw()
// { 
// 	    if (firstScreen)
//     {
//         appConsole.setFullscreenBackgroundColor(BG_BLACK);
//         frame->draw();
//         if(idx==0){
//            for(int i=0;i<textCredit[idx].length();i++){
//           string substring = textCredit[idx] .substr(i,1);
//           text[idx][i] = new DynamicEntity(substring + ".txt",{80+i*6 - textCredit[idx].length()*4,43},{SHORT(6),5});       	
// 		}	
// 		}
// 		else{
// 	      for(int i=0;i<textCredit[idx].length();i++){
//           string substring = textCredit[idx] .substr(i,1);
//           text[idx][i] = new DynamicEntity(substring + ".txt",{80+i*6 - textCredit[idx].length()*2,16},{SHORT(6),5});     
// 		  for(int i=0;i<textCredit[idx+1].length();i++){
//           string substring = textCredit[idx+1] .substr(i,1);
//           text[idx+1][i] = new DynamicEntity(substring + ".txt",{80+i*6 - textCredit[idx+1].length()*2,24},{SHORT(6),5});       	  	
// 		}
// 		for(int i=0;i<textCredit[idx+2].length();i++){
//           string substring = textCredit[idx+2] .substr(i,1);
//           text[idx+2][i] = new DynamicEntity(substring + ".txt",{80+i*6 - textCredit[idx+2].length()*2,32},{SHORT(6),5});       	  	
// 		}
// 		for(int i=0;i<textCredit[idx+3].length();i++){
//           string substring = textCredit[idx+3] .substr(i,1);
//           text[idx+3][i] = new DynamicEntity(substring + ".txt",{80+i*6 - textCredit[idx+3].length()*2,40},{SHORT(6),5});       	  	
// 		}
// 	}
// }
// 	 firstScreen = false;	
// 	}
// 	if(idx==0){
// 		for(int i=0;i<textCredit[idx].length();i++)   text[idx][i]->draw();
// 	    for(int i=0;i<textCredit[idx].length();i++)	text[idx][i]->up(1);
// 	    if(count==27){
// 		for(int i=0;i<textCredit[idx].length();i++) text[idx][i]->resetDynamicEntity();
// 		idx++;
// 		if(idx> 17) idx = 0;
// 		firstScreen = true;
// 		count=0;
// 	}
// 	}
// 	else{
// 		for(int i=0;i<textCredit[idx].length();i++)   text[idx][i]->draw();
// 	    for(int i=0;i<textCredit[idx].length();i++)	text[idx][i]->up(1);	
// 	    for(int i=0;i<textCredit[idx+1].length();i++)   text[idx+1][i]->draw();
// 	    for(int i=0;i<textCredit[idx+1].length();i++)	text[idx+1][i]->up(1);
// 	    for(int i=0;i<textCredit[idx+2].length();i++)	text[idx+2][i]->up(1);
// 	    for(int i=0;i<textCredit[idx+3].length();i++)	text[idx+3][i]->up(1);
// 	    for(int i=0;i<textCredit[idx+2].length();i++)   text[idx+2][i]->draw();
// 	    for(int i=0;i<textCredit[idx+3].length();i++)   text[idx+3][i]->draw();	    	    
// 	    if(count==15){
// 		for(int i=0;i<textCredit[idx].length();i++) text[idx][i]->resetDynamicEntity();
// 		idx= idx +4;
// 		if(idx>16) idx = 0;
// 		firstScreen = true;
// 		count=0;
// 	}
// 	}

// 	count ++;
	

// }
