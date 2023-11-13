#include "screen.h"

Screen::Screen(HandlerInput *handlerInput_) : handlerInputMainScreen(handlerInput_), firstScreen(true) {}



Command *Screen::handleInput() {
    return handlerInputMainScreen->handlerInput(buttonList);
}


MenuScreen::MenuScreen() : Screen(new HandlerMenuInput())
{
    rocket = new DynamicEntity("rocket.txt", {1, 25}, {8, 15});
    meteor = new DynamicEntity*[7];
    meteor[0] = new DynamicEntity("slight.txt", {27,1}, {4, 4});
    meteor[1] = new DynamicEntity("slight.txt", {175,15}, {4, 4});
    meteor[2] = new DynamicEntity("slight.txt", {135,24}, {4, 4});
    meteor[3] = new DynamicEntity("slight.txt", {40,24}, {4, 4});
    meteor[4] = new DynamicEntity("slight.txt", {143,10}, {4, 4});
    meteor[5] = new DynamicEntity("slight.txt", {22,15}, {4, 4});
    meteor[6] = new DynamicEntity("slight.txt", {143,2}, {4, 4});	
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
    for(int i=0; i<7;i++){
         meteor[i]->draw();  
     	meteor[i]->slip(1);      	
    }
    rocketMove++;
    rocket->up(1);
    if (rocketMove == 20)
    {
        rocketMove = 0;
        rocket->teleport({1, 25});
        meteor[0]->teleport({27, 1});
        meteor[1]->teleport({175, 15});
        meteor[2]->teleport({135, 24});   
        meteor[3]->teleport({40, 24});        
        meteor[4]->teleport({143, 10});        
        meteor[5]->teleport({22, 15});        
        meteor[6]->teleport({143, 2});  		     
    }
}

IntroGameScreen::IntroGameScreen() : Screen(new HandlerIntroGameInput(textInput)), enterGame(false), lastFrame(false) {
    welcome = new Entity("welcome.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {150, 50});
} 

IntroGameScreen::~IntroGameScreen() {
    delete welcome;
    delete[] textInputEntity; 
}

string IntroGameScreen::getName() {
    return name;
}

Command *IntroGameScreen::handleInput() {
    if (lastFrame) handlerInputMainScreen->setFixUserInput(1); // Enter Gane
    return handlerInputMainScreen->handlerInput(buttonList);
}

void IntroGameScreen::draw() {
    if (firstScreen) {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        importImage.drawCustomImage("enter name  ", {SHORT(appConsole.getWindowSize().X / 2), 20}, false);
        firstScreen = false;
    } 
    if (textInput.size() == 1 && textInput[0] == '/') {
        welcome->draw();
        importImage.drawCustomImage("welcome " + name, {SHORT(appConsole.getWindowSize().X / 2 + 30), 18}, false);
        importImage.drawCustomImage("have a nice day ", {SHORT(appConsole.getWindowSize().X / 2 + 30), 28}, false);
        listPlayer.addPlayer(Player(name, "0", "0"));
        mainPlayer = listPlayer.getPlayer(3);
    
        Sleep(2000);
        appConsole.setFullscreenBackgroundColor(BG_CYAN);   
        string s = "journey to the stars with me";
        for(int i = 0; i<s.length();i++) {
            importImage.drawCustomImage(string(1,s[i]), {SHORT(appConsole.getWindowSize().X / 2 - 85 + 6*i), 28}, false);    
		    Sleep(70);  	
		}
	    Sleep(1000);  
        lastFrame = true;
        return;
    }  
    textInputEntity = new Entity[6];
    for (int i = 0; i < 6; i++) {
        string fileName = string(1, (i < textInput.size() ? textInput[i] : '@')) + ".txt";
        textInputEntity[i] = Entity(fileName , {SHORT(108 + 12 * i), 31}, {5, 5});
        textInputEntity[i].draw();
    }
    name = textInput;
}


void GameScreen::allocateEnemy()
{
    int random = rand() % (appConsole.getWindowSize().X / 2 - 15);
    SHORT posY;
    for (int i = 0; i < 3; ++i){
        posY = 8;
        enemy[i] = new Enemy("smallufo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 3; ++i){
        posY = 13;
        enemy[i + 3] = new Enemy("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 30);
    for (int i = 0; i < 3; ++i){
        posY = 23;
        enemy[i + 6] = new Enemy("bigUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 10 * (i - 1)), posY}, {20, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 9);
    for (int i = 0; i < 3; ++i){
        posY = 28;
        enemy[i + 9] = new Enemy("smallufo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 14 * (i - 1)), posY}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 18);
    for (int i = 0; i < 3; ++i){
        posY = 38;
        enemy[i + 12] = new Enemy("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {13, 5});
    }

}

void GameScreen::allocateTrafficLight()
{
    trafficlight = new TrafficLight *[numberTrafficLight];
    for(int i = 0; i < numberTrafficLight; ++i)
        trafficlight[i] = new TrafficLight("traffic.txt", {SHORT(appConsole.getWindowSize().X), this->enemy[i*3]->getPos().Y}, {5, 5}, new GreenState());
}

GameScreen::GameScreen() : Screen(new HandlerGameInput(this->hero))
{
    frame = new Entity("gameFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
    // overgameframe = new Entity("GameOver.txt", {SHORT((appConsole.getWindowSize().X - 30) / 2), 0}, {150, 50});
    finish_line = new Entity("finish_line.txt", {0, 4}, {211, 5});
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - 13) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y);
    hero = new Hero("phoenix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {11, 5}, stoi(mainPlayer->getScore()));
    enemy = new Enemy *[numberEnemy];
    allocateEnemy();
    allocateTrafficLight();
}

GameScreen::~GameScreen()
{
    delete frame; frame = nullptr;
    for (int i = 0; i < numberEnemy; ++i)
    {
        delete[] enemy[i];
        enemy[i] = nullptr;
    }
    delete[] enemy;
    for(int i = 0; i < numberTrafficLight; ++i)
        delete[] trafficlight[i];
    delete[] trafficlight;
    delete finish_line;
    delete hero;
}

void GameScreen::manageEnemies()
{
    for (int i = 0; i < numberEnemy; ++i)
        enemy[i]->update(trafficlight[(int(floor(i/3)))]);
}

void GameScreen::manageTrafficLight()
{
    for(int i = 0; i < numberTrafficLight; ++i)
    {
        trafficlight[i]->draw();    
        trafficlight[i]->update();
    }
}

void GameScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        finish_line->draw();
        firstScreen = false;
        string STRINGlevel = to_string(hero->getHeroLevel());
        string STRINGscore = to_string(hero->getHeroScore());
        importImage.drawCustomImage(STRINGlevel, {SHORT(appConsole.getWindowSize().X - 20), 0}, true);
        importImage.drawCustomImage(STRINGscore, {70, 0}, true);
        importImage.drawCustomImage(STRINGlevel, {SHORT(appConsole.getWindowSize().X - 20), 0}, true);
        importImage.drawCustomImage(STRINGscore, {70, 0}, true);
    }
    for (int i = 0; i < numberEnemy; ++i)
    {
        enemy[i]->setSpeed(hero->getHeroLevel());
    }
    hero->draw();
    manageTrafficLight();
    manageEnemies();
    for (int i = 0; i < numberEnemy; ++i)
    {
        if (hero->isCollision(enemy[i]) || hero->isAtEdge(7))
        {
            if (hero->isAtEdge(7)){
                hero->updateHeroExp();      
	            hero->resetDynamicEntity();
	            hero->draw();        
                firstScreen = true;	      	
			}
            else {
                hero->updateHeroExp(0);
                hero->resetDynamicEntity();
                hero->draw();
                firstScreen = true;
                return;
            }
        }
    }
}

// OverGameScreen::OverGameScreen() : Screen() {
//     overgameframe = new Entity("GameOver.txt", {SHORT((appConsole.getWindowSize().X - 30) / 2), 0}, {150, 50});
// }


LoadGameScreen::LoadGameScreen() : Screen(new HandlerLoadInput()){};

LoadGameScreen::~LoadGameScreen() {}

void LoadGameScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
        importImage.drawCustomImage("name ", {0, 15});
        importImage.drawCustomImage("level", {0, 25});
        importImage.drawCustomImage("score", {0, 35});
        for (int i = 0; i < 4; i++)
        {
            buttonList.addButton(new Button("#" + listPlayer.getPlayer(i)->getName(), {SHORT(42 + i * 40), SHORT(15)}, WHITE, RED));
            importImage.drawCustomImage("#" + listPlayer.getPlayer(i)->getLevel(), {SHORT(42 + i * 40), SHORT(25)});
            importImage.drawCustomImage("#" + listPlayer.getPlayer(i)->getScore(), {SHORT(42 + i * 40), SHORT(35)});
        }
        firstScreen = false;
        importImage.drawImage("LoadGameSaved.txt", {49, 2});
    }
    buttonList.draw();
}

CreditScreen::CreditScreen() : Screen(new HandlerCreditInput())
{
    frame = new Entity("creditFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
    for (int i = 0; i < 17; i++)
        text[i] = new DynamicEntity[textCredit[i].length()];
}

CreditScreen::~CreditScreen()
{
    for (int i = 0; i < 17; ++i)
        delete[] text[i];
}

void CreditScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        if (idx == 0)
        {
            for (int i = 0; i < textCredit[idx].length(); i++)
            {
                string substring = textCredit[idx].substr(i, 1);
                text[idx][i] = DynamicEntity(substring + ".txt", {SHORT(80 + i * 6 - textCredit[idx].length() * 4), 43}, {SHORT(6), 5});
            }
        }
        else
        {
            for (int i = 0; i < textCredit[idx].length(); i++)
            {
                string substring = textCredit[idx].substr(i, 1);
                text[idx][i] = DynamicEntity(substring + ".txt", {SHORT(80 + i * 6 - textCredit[idx].length() * 2), 16}, {SHORT(6), 5});
                for (int j = 0; j < textCredit[idx + 1].length(); j++)
                {
                    string substring = textCredit[idx + 1].substr(j, 1);
                    text[idx + 1][j] = DynamicEntity(substring + ".txt", {SHORT(80 + j * 6 - textCredit[idx + 1].length() * 2), 24}, {SHORT(6), 5});
                }
                for (int j = 0; j < textCredit[idx + 2].length(); j++)
                {
                    string substring = textCredit[idx + 2].substr(j, 1);
                    text[idx + 2][j] = DynamicEntity(substring + ".txt", {SHORT(80 + j * 6 - textCredit[idx + 2].length() * 2), 32}, {SHORT(6), 5});
                }
                for (int j = 0; j < textCredit[idx + 3].length(); j++)
                {
                    string substring = textCredit[idx + 3].substr(j, 1);
                    text[idx + 3][j] = DynamicEntity(substring + ".txt", {SHORT(80 + j * 6 - textCredit[idx + 3].length() * 2), 40}, {SHORT(6), 5});
                }
            }
        }
        firstScreen = false;
    }
    if (idx == 0)
    {
        for (int i = 0; i < textCredit[idx].length(); i++)
            text[idx][i].draw();
        for (int i = 0; i < textCredit[idx].length(); i++)
            text[idx][i].up(1);
        if (count == 27)
        {
            for (int i = 0; i < textCredit[idx].length(); i++)
                text[idx][i].resetDynamicEntity();
            idx++;
            if (idx > 17)
                idx = 0;
            firstScreen = true;
            count = 0;
        }
    }
    else
    {
        for (int i = idx; i <= idx + 3; i++)
            for (int j = 0; j < textCredit[i].length(); j++) {
                text[i][j].draw();
                text[i][j].up(1);
            }
        if (count == 15)
        {
            for (int i = 0; i < textCredit[idx].length(); i++)
                text[idx][i].resetDynamicEntity();
            idx = idx + 4;
            if (idx > 16)
                idx = 0;
            firstScreen = true;
            count = 0;
        }
    }

    count++;
}

LeaderBoardScreen::LeaderBoardScreen() : Screen(new HandlerLeaderBoardInput())
{
    frame = new Entity("leaderFrame.txt", {30, 0}, {168, 43});
    title = new Entity("rank.txt", {SHORT((appConsole.getWindowSize().X - 50) / 2), 1}, {25, 6});
    moon = new DynamicEntity("moon.txt", {SHORT(6), SHORT(6)}, {SHORT(16), SHORT(16)});
    star = new DynamicEntity("Star.txt", {SHORT(170), SHORT(38)}, {SHORT(16), SHORT(16)});
}

LeaderBoardScreen::~LeaderBoardScreen()
{
    delete frame;
    delete star;
    delete moon;
    delete title;
}

void LeaderBoardScreen::swap(Player &a, Player &b)
{
    Player temp = a;
    a = b;
    b = temp;
}

void LeaderBoardScreen::draw()
{
    vector <Player> data = listPlayer.getPlayers();
    sort(data.begin(), data.end());
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        title->draw();
        importImage.drawCustomImage("name", {70, 10}, false);
        importImage.drawCustomImage("score", {110, 10}, false);
        for (int i = 2; i >= 0; i--)
        {
            importImage.drawCustomImage(data[i].getName(), {70, SHORT(18 + i * 7)}, false);
            importImage.drawCustomImage(data[i].getScore(), {110, SHORT(18 + i * 7)}, false);
        }
        moon->draw();
        star->draw();
        firstScreen = false;
    }
}