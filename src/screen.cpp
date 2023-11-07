#include "screen.h"

Screen::Screen(HandlerInput *handlerInput_) : handlerInputMainScreen(handlerInput_), firstScreen(true), preScreen(nullptr) {}


Screen *Screen::getPreScreen() {
    return preScreen;
}


Command *Screen::handleInput() {
    return handlerInputMainScreen->handlerInput(buttonList);
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

IntroGameScreen::IntroGameScreen() : Screen(new HandlerIntroGameInput(textInput)), enterGame(false), lastFrame(false) {
    welcome = new Entity("welcome.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {150, 50});
} 

IntroGameScreen::~IntroGameScreen() {
    delete welcome;
    delete[] textInputEntity; 
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
        Sleep(3000);
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
    for (int i = 0; i < 4; ++i)
    {
        posY = 8;
        enemy[i] = new DynamicEntity("smallufo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 4; ++i)
    {
        posY = 13;
        // trafficlight[1] = new TrafficLight("traffic.txt", {SHORT(appConsole.getWindowSize().X), posY}, {5, 5}, false);
        enemy[i + 3] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {13, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 30);
    for (int i = 0; i < 4; ++i)
    {
        posY = 23;
        // trafficlight[2] = new TrafficLight("traffic.txt", {SHORT(appConsole.getWindowSize().X), posY}, {5, 5}, false);
        enemy[i + 6] = new DynamicEntity("bigUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 10 * (i - 1)), posY}, {20, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 9);
    for (int i = 0; i < 4; ++i)
    {
        posY = 28;
        // trafficlight[3] = new TrafficLight("traffic.txt", {SHORT(appConsole.getWindowSize().X), posY}, {5, 5}, false);
        enemy[i + 9] = new DynamicEntity("smallufo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 14 * (i - 1)), posY}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 18);
    for (int i = 0; i < 4; ++i)
    {
        posY = 38;
        // trafficlight[4] = new TrafficLight("traffic.txt", {SHORT(appConsole.getWindowSize().X), posY}, {5, 5}, false);
        enemy[i + 12] = new DynamicEntity("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {13, 5});
    }
}

void GameScreen::allocateTrafficLight()
{
    trafficlight = new TrafficLight *[numberTrafficLight];
    for(int i = 0; i < this->numberTrafficLight; ++i)
        trafficlight[i] = new TrafficLight("traffic.txt", {SHORT(appConsole.getWindowSize().X), this->enemy[i*3]->getPos().Y}, {5, 5}, false);
    controltrafficlight = new ControlTrafficLight(false);
}

GameScreen::GameScreen() : Screen(new HandlerGameInput(this->hero))
{
    frame = new Entity("gameFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
    // overgameframe = new Entity("GameOver.txt", {SHORT((appConsole.getWindowSize().X - 30) / 2), 0}, {150, 50});
    finish_line = new Entity("finish_line.txt", {0, 4}, {211, 5});
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - 13) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y);
    hero = new Hero("phoenix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {11, 5}, 0);
    enemy = new DynamicEntity *[numberEnemy];
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
    delete controltrafficlight;
}


void GameScreen::manageEnemies()
{
    for (int i = 0; i < numberEnemy; ++i)
    {
        enemy[i]->spawnDynamicEntity(enemy[i]->getSpeed());
        if (enemy[i]->isAtEdge(appConsole.getWindowSize().X - trafficlight[i % 3]->getSize().X - 2))
            enemy[i]->resetDynamicEntity();
    }
}

void GameScreen::manageTrafficLight()
{
    controltrafficlight->updateTrafficLight();
    if (controltrafficlight->isRedOn())
    {
        trafficlight[controltrafficlight->stopRow1]->freezeRowEnemy(enemy, controltrafficlight->stopRow1);
        trafficlight[controltrafficlight->stopRow1]->setLight(controltrafficlight->isRedOn());
        trafficlight[controltrafficlight->stopRow2]->freezeRowEnemy(enemy, controltrafficlight->stopRow2);
        trafficlight[controltrafficlight->stopRow2]->setLight(controltrafficlight->isRedOn());
    }
}

void GameScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        for(int i = 0; i < numberTrafficLight; ++i)
            trafficlight[i]->draw();
        finish_line->draw();
        for (int i = 0; i < numberEnemy; ++i)
            enemy[i]->setSpeed(hero->getHeroLevel());
        firstScreen = false;
        string STRINGlevel = to_string(hero->getHeroLevel());
        string STRINGscore = to_string(hero->getHeroScore());
        importImage.drawCustomImage(STRINGlevel, {SHORT(appConsole.getWindowSize().X - 20), 0}, true);
        importImage.drawCustomImage(STRINGscore, {70, 0}, true);
        importImage.drawCustomImage(STRINGlevel, {SHORT(appConsole.getWindowSize().X - 20), 0}, true);
        importImage.drawCustomImage(STRINGscore, {70, 0}, true);
    }

    hero->draw();
    for (int i = 0; i < numberEnemy; ++i)
    {
        enemy[i]->setSpeed(hero->getHeroLevel());
    }
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
//                appConsole.setFullscreenBackgroundColor(BG_CYAN);                
//				overframe->draw();
//				bus->draw();
//				die->draw();
//				int count = 0;
//				while(!firstScreen){
//				    if(count < 10){
//						bus->right(4);
//     					bus->draw();
//						count++;
//						Sleep(5);
//						if(count == 10)	{
//							die = nullptr ;
//							die = new Entity("boom.txt",{162,25},{11,5}); 
//							die->draw();
//                			importImage.drawCustomImage("enter to replay",{SHORT(appConsole.getWindowSize().X/2), 36}, false);	
//							die = new Entity("phoenix.txt",{162,25},{11,5});  							
//						}			    	
//					}					 					
//					if(kbhit()){
//						char c = getch();
//						if(c == 13) {
//							bus->teleport({120,25});
				            hero->resetDynamicEntity();
				            hero->draw();        
				            firstScreen = true;							
//						} 
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
    ifstream fin(path);
    playerData data[4];
    int i = 0;
    while (!fin.eof())
    {
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
        for (int i = 0; i < 4; i++)
        {
            buttonList.addButton(new Button("#" + data[i].name, {SHORT(42 + i * 32), SHORT(15)}, WHITE, GREEN));
            importImage.drawCustomImage("#" + data[i].level, {SHORT(42 + i * 32), SHORT(25)});
            importImage.drawCustomImage("#" + data[i].score, {SHORT(42 + i * 32), SHORT(35)});
        }

        buttonList.draw();

        firstScreen = false;
        importImage.drawImage("LoadGameSaved.txt", {43, 2});
    }
}

CreditScreen::CreditScreen() : Screen(new HandlerCreditInput())
{
    frame = new Entity("creditFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
    for (int i = 0; i < 17; i++)
        text[i] = new DynamicEntity *[textCredit[i].length()];
}

CreditScreen::~CreditScreen()
{
    for (int i = 0; i < 17; ++i)
    {
        for (int j = 0; j < textCredit[i].size(); j++)
            delete text[i][j];
        delete[] text[i];
    }
    delete[] text;
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
                text[idx][i] = new DynamicEntity(substring + ".txt", {SHORT(80 + i * 6 - textCredit[idx].length() * 4), 43}, {SHORT(6), 5});
            }
        }
        else
        {
            for (int i = 0; i < textCredit[idx].length(); i++)
            {
                string substring = textCredit[idx].substr(i, 1);
                text[idx][i] = new DynamicEntity(substring + ".txt", {SHORT(80 + i * 6 - textCredit[idx].length() * 2), 16}, {SHORT(6), 5});
                for (int i = 0; i < textCredit[idx + 1].length(); i++)
                {
                    string substring = textCredit[idx + 1].substr(i, 1);
                    text[idx + 1][i] = new DynamicEntity(substring + ".txt", {SHORT(80 + i * 6 - textCredit[idx + 1].length() * 2), 24}, {SHORT(6), 5});
                }
                for (int i = 0; i < textCredit[idx + 2].length(); i++)
                {
                    string substring = textCredit[idx + 2].substr(i, 1);
                    text[idx + 2][i] = new DynamicEntity(substring + ".txt", {SHORT(80 + i * 6 - textCredit[idx + 2].length() * 2), 32}, {SHORT(6), 5});
                }
                for (int i = 0; i < textCredit[idx + 3].length(); i++)
                {
                    string substring = textCredit[idx + 3].substr(i, 1);
                    text[idx + 3][i] = new DynamicEntity(substring + ".txt", {SHORT(80 + i * 6 - textCredit[idx + 3].length() * 2), 40}, {SHORT(6), 5});
                }
            }
        }
        firstScreen = false;
    }
    if (idx == 0)
    {
        for (int i = 0; i < textCredit[idx].length(); i++)
            text[idx][i]->draw();
        for (int i = 0; i < textCredit[idx].length(); i++)
            text[idx][i]->up(1);
        if (count == 27)
        {
            for (int i = 0; i < textCredit[idx].length(); i++)
                text[idx][i]->resetDynamicEntity();
            idx++;
            if (idx > 17)
                idx = 0;
            firstScreen = true;
            count = 0;
        }
    }
    else
    {
        for (int i = 0; i < textCredit[idx].length(); i++)
            text[idx][i]->draw();
        for (int i = 0; i < textCredit[idx].length(); i++)
            text[idx][i]->up(1);
        for (int i = 0; i < textCredit[idx + 1].length(); i++)
            text[idx + 1][i]->draw();
        for (int i = 0; i < textCredit[idx + 1].length(); i++)
            text[idx + 1][i]->up(1);
        for (int i = 0; i < textCredit[idx + 2].length(); i++)
            text[idx + 2][i]->up(1);
        for (int i = 0; i < textCredit[idx + 3].length(); i++)
            text[idx + 3][i]->up(1);
        for (int i = 0; i < textCredit[idx + 2].length(); i++)
            text[idx + 2][i]->draw();
        for (int i = 0; i < textCredit[idx + 3].length(); i++)
            text[idx + 3][i]->draw();
        if (count == 15)
        {
            for (int i = 0; i < textCredit[idx].length(); i++)
                text[idx][i]->resetDynamicEntity();
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

void LeaderBoardScreen::swap(playerData &a, playerData &b)
{
    playerData temp = a;
    a = b;
    b = temp;
}

void LeaderBoardScreen::draw()
{
    ifstream fin(path);
    playerData data[4];
    int i = 0;
    while (!fin.eof())
    {
        fin >> data[i].name;
        fin >> data[i].level;
        fin >> data[i].score;
        i++;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (stoi(data[i].score) > stoi(data[j].score))
                swap(data[i], data[j]);
        }
    }
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        title->draw();
        importImage.drawCustomImage("name", {70, 10}, false);
        importImage.drawCustomImage("score", {110, 10}, false);
        for (int i = 2; i >= 0; i--)
        {
            importImage.drawCustomImage(data[i].name, {70, SHORT(18 + i * 7)}, false);
            importImage.drawCustomImage(data[i].score, {110, SHORT(18 + i * 7)}, false);
        }
        moon->draw();
        star->draw();
        firstScreen = false;
    }
}
