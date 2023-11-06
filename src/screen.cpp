#include "screen.h"

Screen::Screen(HandlerInput *handlerInput_) : handlerInputMainScreen(handlerInput_), firstScreen(true), preScreen(nullptr) {}


Screen *Screen::getPreScreen() {
    return preScreen;
}

Command *Screen::handleInput()
{
    return handlerInputMainScreen->handlerInput(buttonList);
}

Command *GameScreen::handleInput()
{
    return handlerInputMainScreen->handlerInput();
}

Command *LeaderBoardScreen::handleInput()
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
        Entity *sartun = new Entity("sartun.txt", {148, 7}, {21, 20});
        Entity *venus = new Entity("venus.txt", {128, 31}, {23, 15});
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
    int random = rand() % (appConsole.getWindowSize().X / 2 - 15);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i] = new DynamicEntity("smallufo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(3+5)}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 3] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(8+5)}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 30);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 6] = new DynamicEntity("bigUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 10 * (i - 1)), SHORT(18+5)}, {20, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 9);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 9] = new DynamicEntity("smallufo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 14 * (i - 1)), SHORT(23+5)}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 18);
    for (int i = 0; i < 4; ++i)
    {
        enemy[i + 12] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), SHORT(33+5)}, {13, 5});
    }
}

GameScreen::GameScreen() : Screen(new HandlerGameInput(this->hero))
{
    frame = new Entity("gameFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
    welcome = new Entity("welcome.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {150, 50});
    finish_line = new Entity("finish_line.txt", {0, 4}, {211, 5});
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - 13) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y);
    hero = new Hero("phoenix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {11, 5}, 0);
    enemy = new DynamicEntity *[numberEnemy];
    allocateEnemy();
}

GameScreen::~GameScreen()
{
    delete frame;
    for (int i = 0; i < numberEnemy; ++i)
        delete enemy[i];
    delete finish_line;   
    delete enemy;
    delete hero;
}


void GameScreen::draw()
{
    string STRINGlevel = to_string(hero->getHeroLevel());
    string STRINGscore = to_string(hero->getHeroScore());
    int count=0;
    if (firstGame) {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);  
        importImage.drawCustomImage("enter name  ",{SHORT(appConsole.getWindowSize().X/2), 20}, false);	
    }
    while(firstGame)
	{
		bool checkEnter = true;
		chac = new Entity *[6]; 
    for (int i = 0; i < 6; ++i)
    {
		chac[i] = new Entity(arr[i]+".txt", {SHORT(108 + 12*i) , 31}, {5, 5});
		chac[i]->draw();    	
	}
	while(checkEnter){
    	if(kbhit()){
    		char c = getch();
    		if(c==8&&count>0){
     		   count--;
     		   arr[count] = "@";
			   name.erase(count, 1);	
			}
    		if(c==13){
    		   firstGame = false;	
    		   delete [] chac;
               appConsole.setFullscreenBackgroundColor(BG_CYAN);    
               welcome->draw();
			   importImage.drawCustomImage("welcome " + name,{SHORT(appConsole.getWindowSize().X/2 + 30), 18}, false);	 
			   importImage.drawCustomImage("have a good day ",{SHORT(appConsole.getWindowSize().X/2 +30), 28}, false);	 
			   Sleep(1200);
 		} 
 		if(c >='a'&&c<='z'){
     		name += c; 
    		arr[count] = c;
    		count++;
		 }
       	 checkEnter = false;	
	}
	    if(count == 6){
	    	count = 0;
	    	for (int i = 0; i < 6; ++i) arr[i] = "@";
	    	name = "";
		}		
	}

	
//		firstGame = false;	 	
	}
    
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        finish_line->draw();
        for(int i = 0; i < numberEnemy; ++i)
            enemy[i]->setSpeed(hero->getHeroLevel());
        firstScreen = false;
    }
    hero->draw();
    // return;
    importImage.drawCustomImage(STRINGlevel, {SHORT(appConsole.getWindowSize().X - 20), 0}, true);
    importImage.drawCustomImage(STRINGscore, {70, 0}, true);
    for(int i = 0; i < numberEnemy; ++i)
    {
        enemy[i]->spawnDynamicEntity(enemy[i]->getSpeed());
        if (enemy[i]->isAtEdge(appConsole.getWindowSize().X - 1))
            enemy[i]->resetDynamicEntity();
    }

    for (int i = 0; i < numberEnemy; ++i)
    {
        if (hero->isCollision(enemy[i]) || hero->isAtEdge(7))
        {
            if (hero->isAtEdge(7))
                hero->updateHeroExp();
            else 
                hero->updateHeroExp(0);
            hero->resetDynamicEntity();
            hero->draw();        
            firstScreen = true;
            return;
        }
    }
    
    
    // If player reaches the end lane, then draw whole screen and update player's level and score subsequently.
    // if (hero->isAtEdge(6))
    // {
    //     hero->resetDynamicEntity();
    //     hero->updateHeroExp();
    //     hero->draw();        
    //     firstScreen = true;
        
    // }


}

Command *LoadGameScreen::handleInput()
{
    return handlerInputMainScreen->handlerInput();
}

LoadGameScreen::LoadGameScreen() : Screen(new HandlerMenuInput()) {};

LoadGameScreen::~LoadGameScreen() {}

void LoadGameScreen::draw()
{   
    ifstream fin(path);
    playerData data[4];
    int i = 0;
    while (!fin.eof()) {
        fin >> data[i].name;
        fin >> data[i].level;
        fin >> data[i].score;
        i++;
    }

    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
        importImage.drawCustomImage("name", {0, 15});
        importImage.drawCustomImage("level", {0, 25});
        importImage.drawCustomImage("score", {0, 35});
        for (int i = 0 ; i < 4; i++) {
            buttonList.addButton(new Button("#" + data[i].name, {SHORT(42 + i*32), SHORT(15)}, WHITE, GREEN));
            importImage.drawCustomImage("#" + data[i].level, {SHORT(42 + i*32), SHORT(25)});
            importImage.drawCustomImage("#" + data[i].score, {SHORT(42 + i*32), SHORT(35)});
        }

        buttonList.draw();

        firstScreen = false;
        importImage.drawImage("LoadGameSaved.txt", {43, 2});
    }
}

CreditScreen::CreditScreen() : Screen(new HandlerMenuInput())
{
	frame = new Entity("creditFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
	for(int i=0;i<17;i++)	text[i] = new DynamicEntity *[textCredit[i].length()];
}

CreditScreen:: ~ CreditScreen() 
{
    for (int i = 0; i < 11; ++i)
    {
        delete text[i];
        text[i] = nullptr;
    }
    delete[] text;

}

Command *CreditScreen::handleInput() {
    return nullptr;
}

void CreditScreen::draw()
{ 
 	    if (firstScreen)
        {
         appConsole.setFullscreenBackgroundColor(BG_CYAN);
         frame->draw();
         if(idx==0){
            for(int i=0;i<textCredit[idx].length();i++){
           string substring = textCredit[idx] .substr(i,1);
           text[idx][i] = new DynamicEntity(substring + ".txt",{SHORT(80+i*6 - textCredit[idx].length()*4),43},{SHORT(6),5});       	
 		}	
 		}
 		else{
 	      for(int i=0;i<textCredit[idx].length();i++){
           string substring = textCredit[idx] .substr(i,1);
           text[idx][i] = new DynamicEntity(substring + ".txt",{SHORT(80+i*6 - textCredit[idx].length()*2),16},{SHORT(6),5});     
 		  for(int i=0;i<textCredit[idx+1].length();i++){
           string substring = textCredit[idx+1] .substr(i,1);
           text[idx+1][i] = new DynamicEntity(substring + ".txt",{SHORT(80+i*6 - textCredit[idx+1].length()*2),24},{SHORT(6),5});       	  	
 		}
 		for(int i=0;i<textCredit[idx+2].length();i++){
           string substring = textCredit[idx+2] .substr(i,1);
           text[idx+2][i] = new DynamicEntity(substring + ".txt",{SHORT(80+i*6 - textCredit[idx+2].length()*2),32},{SHORT(6),5});       	  	
 		}
 		for(int i=0;i<textCredit[idx+3].length();i++){
           string substring = textCredit[idx+3] .substr(i,1);
           text[idx+3][i] = new DynamicEntity(substring + ".txt",{SHORT(80+i*6 - textCredit[idx+3].length()*2),40},{SHORT(6),5});       	  	
 		}
 	}
 }
 	 firstScreen = false;	
 	}
 	if(idx==0){
 		for(int i=0;i<textCredit[idx].length();i++)   text[idx][i]->draw();
 	    for(int i=0;i<textCredit[idx].length();i++)	text[idx][i]->up(1);
 	    if(count==27){
 		for(int i=0;i<textCredit[idx].length();i++) text[idx][i]->resetDynamicEntity();
 		idx++;
 		if(idx> 17) idx = 0;
 		firstScreen = true;
 		count=0;
 	}
 	}
 	else{
 		for(int i=0;i<textCredit[idx].length();i++)   text[idx][i]->draw();
 	    for(int i=0;i<textCredit[idx].length();i++)	text[idx][i]->up(1);	
 	    for(int i=0;i<textCredit[idx+1].length();i++)   text[idx+1][i]->draw();
 	    for(int i=0;i<textCredit[idx+1].length();i++)	text[idx+1][i]->up(1);
 	    for(int i=0;i<textCredit[idx+2].length();i++)	text[idx+2][i]->up(1);
 	    for(int i=0;i<textCredit[idx+3].length();i++)	text[idx+3][i]->up(1);
 	    for(int i=0;i<textCredit[idx+2].length();i++)   text[idx+2][i]->draw();
 	    for(int i=0;i<textCredit[idx+3].length();i++)   text[idx+3][i]->draw();	    	    
 	    if(count==15){
 		for(int i=0;i<textCredit[idx].length();i++) text[idx][i]->resetDynamicEntity();
 		idx= idx +4;
 		if(idx>16) idx = 0;
 		firstScreen = true;
 		count=0;
 	}
 	}

 	count ++;
	

}

LeaderBoardScreen::LeaderBoardScreen() : Screen(new HandlerMenuInput()) {
    frame = new Entity("leaderFrame.txt", {30, 0}, {168, 43});
    title = new Entity("rank.txt",{SHORT((appConsole.getWindowSize().X-50) / 2),1},{25,6});
    moon =  new DynamicEntity("moon.txt",{SHORT(6),SHORT(6)},{SHORT(16),SHORT(16)});
    star =  new DynamicEntity("Star.txt",{SHORT(170),SHORT(38)},{SHORT(16),SHORT(16)});
};

LeaderBoardScreen::~LeaderBoardScreen() {
	delete frame;
	delete star;
	delete moon;
	delete title;
}

void LeaderBoardScreen:: swap(playerData &a, playerData &b)
{
  playerData temp = a;
  a = b;
  b = temp;
}


void LeaderBoardScreen:: draw(){
    ifstream fin(path);
    playerData data[4];
    int i = 0;
    while (!fin.eof()) {
        fin >> data[i].name;
        fin >> data[i].level;
        fin >> data[i].score;
        i++;
    }
    for(int i = 0;i<4;i++){
    	for(int j=0;j<4;j++){
    		if(stoi(data[i].score)>stoi(data[j].score)) swap(data[i],data[j]);
		}
	}
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        title->draw();
        importImage.drawCustomImage("name", {70, 10},false);
        importImage.drawCustomImage("score", {110, 10},false);
        for(int i = 2;i>=0;i--){
        importImage.drawCustomImage(data[i].name, {70, SHORT(18+i*7)},false);
        importImage.drawCustomImage(data[i].score, {110, SHORT(18+i*7)},false);  
	
		}       
        moon->draw();
        star->draw();
        firstScreen = false;
    }	
}
