#include "screen.h"

 
void debug() {
    ofstream fout("debug.txt");
    fout << "debug" << endl;
    fout.close();
}

Screen::Screen(HandlerInput *handlerInput_, string music_) 
    : handlerInputMainScreen(handlerInput_), firstScreen(true), music(music_)  {
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - 13) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y);
	hero = new Hero("phoenix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {11, 5}, 0);
	}

Screen::~Screen() {
    debug();
    delete handlerInputMainScreen;
    delete hero;
}

void Screen::setAgain() {
    firstScreen = true;
}

void Screen::playMusic() {
    sound.play(music);
}

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
    for (int i = 0; i < 6; i++)
        buttonList.addButton(new Button(buttonName[i], {SHORT(80 - buttonName[i].length() * 2), SHORT(i * 4 + 14)}, WHITE, GREEN));
};

MenuScreen::~MenuScreen()
{
    delete rocket;
}

void MenuScreen::draw()
{
    if (firstScreen)
    {
        // const char* path = "../media/music1.wav";
        // PlaySound(path, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP  );
        appConsole.setFullscreenBackgroundColor(BG_BLUE);
        importImage.drawASCII("star.txt", {0, 0});
        importImage.drawASCII("crossingroad.txt", {36, 5});
        Entity *jupiter = new Entity("jupiter.txt", {20, 22}, {12, 11});
        Entity *sartun = new Entity("sartun.txt", {148, 7}, {21, 20});
        Entity *venus = new Entity("venus.txt", {128, 31}, {23, 15});
        importImage.drawASCII("frame.txt", {45, 12});
        jupiter->draw();
        sartun->draw();
        venus->draw();
        firstScreen = false;
        // return;
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

IntroGameScreen::IntroGameScreen() : Screen(new HandlerIntroGameInput(textInput), "intro.wav"), enterGame(false), lastFrame(false) {
    welcome = new Entity("welcome.txt", {10, 0}, {205, 50});
} 

IntroGameScreen::~IntroGameScreen() {
    delete welcome;
    delete[] textInputEntity; 
}

string IntroGameScreen::getName() {
    return name;
}

string IntroGameScreen::getTime() {
    time_t now = time(NULL);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", gmtime(&now));
    return buffer;
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
        importImage.drawCustomImage("from sai gon", {SHORT(appConsole.getWindowSize().X / 2 - 90), 5}, false);  
        importImage.drawCustomImage(getTime(), {SHORT(appConsole.getWindowSize().X / 2 - 90), 15}, false);  
        importImage.drawCustomImage("welcome " + name, {SHORT(appConsole.getWindowSize().X / 2 + 10), 5}, false);
        importImage.drawCustomImage("have a nice day ", {SHORT(appConsole.getWindowSize().X / 2 + 10), 15}, false);
        listPlayer.addPlayer(Player(name, "0", "0"));
        mainPlayer = listPlayer.getPlayer(3);
    
        Sleep(2700);
        appConsole.setFullscreenBackgroundColor(BG_CYAN);   
        string s = "journey to the star with me";
        for(int i = 0; i<s.length();i++) {
            importImage.drawCustomImage(string(1,s[i]), {SHORT(appConsole.getWindowSize().X / 2 - 85 + 6*i), 25}, false);    
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

void GameScreen::buildFrame()
{
    this->frame = new Entity("gameFrame.txt", {SHORT((appConsole.getWindowSize().X - 43) / 2), 0}, {168, 43});
}
void GameScreen::buildFinishline()
{
    this->finish_line = new Entity("finish_line.txt", {0, 4}, {211, 5});
}
void GameScreen::buildEnemy()
{
    this->enemy = new Enemy *[numberEnemy];
    int random = rand() % (appConsole.getWindowSize().X / 2 - 15);
    SHORT posY;
    for (int i = 0; i < 3; ++i){
        posY = 8;
        this->enemy[i] = new Enemy("smallufo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {11, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 25);
    for (int i = 0; i < 3; ++i){
        posY = 13;
        // this->enemy[i + 3] = new Enemy("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {13, 5});
        this->enemy[i + 3] = new Enemy("coolUfo.txt", {SHORT(30 + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {14, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 30);
    for (int i = 0; i < 3; ++i){
        posY = 23;
        this->enemy[i + 6] = new Enemy("bigUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 10 * (i - 1)), posY}, {20, 5});
    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 9);
    for (int i = 0; i < 3; ++i){
        posY = 28;
        // this->enemy[i + 9] = new Enemy("smallufo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 14 * (i - 1)), posY}, {11, 5});
        this->enemy[i + 9] = new Enemy("smallufo.txt", {SHORT(70 + (hero->getHeroWidth() + 40) * i + 14 * (i - 1)), posY}, {11, 5});

    }
    random = rand() % (appConsole.getWindowSize().X / 2 - 18);
    for (int i = 0; i < 3; ++i){
        posY = 38;
        this->enemy[i + 12] = new Enemy("coolUfo.txt", {SHORT(random + (hero->getHeroWidth() + 40) * i + 13 * (i - 1)), posY}, {13, 5});
    }
}
void GameScreen::buildHero()
{
    SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - 13) / 2;
    SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y);
   	hero = nullptr;
	hero = new Hero(nameHero[typeHero], {spawnHero_COORDX, spawnHero_COORDY}, {11, 5}, 0);  
	if(idPlayer != 5) {
		hero->setHeroLevel(stoi(listPlayer.getPlayer(idPlayer)->getLevel()));  
        hero->setHeroScore(stoi(listPlayer.getPlayer(idPlayer)->getScore()));
		idPlayer = 5;				
	}	
}

void GameScreen::buildTrafficlight()
{
    trafficlight = new TrafficLight *[numberTrafficLight];
    for(int i = 0; i < numberTrafficLight; ++i)
    {
        if (i == 1 || i == 3)
            trafficlight[i] = new TrafficLight("traffic.txt", {SHORT(0), this->enemy[i*3]->getPos().Y}, {5, 5}, new GreenState());
        else
            trafficlight[i] = new TrafficLight("traffic.txt", {SHORT(appConsole.getWindowSize().X), this->enemy[i*3]->getPos().Y}, {5, 5}, new GreenState());
    }
}

GameScreen::GameScreen() : Screen(new HandlerGameInput(hero), "game.wav")
{
    // const char* path = "../media/music2.wav";
    // PlaySound(path, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP  );      
    this->buildFrame();
    this->buildFinishline();
    this->buildHero();
    this->buildEnemy();
    this->buildTrafficlight();
}

GameScreen::~GameScreen()
{
    delete frame;
    for (int i = 0; i < numberEnemy; ++i)
        delete enemy[i];
    delete[] enemy;
    for(int i = 0; i < numberTrafficLight; ++i)
        delete trafficlight[i];
    delete[] trafficlight;
    delete finish_line;
}

void GameScreen::manageEnemy()
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

void GameScreen::manageHero()
{
    for (int i = 0; i < numberEnemy; ++i)
    {
        if (hero->isCollision(enemy[i]))
        {
            hero->setHeroScore(0);
            hero->resetDynamicEntity();
            hero->draw();
            hero->changeExist();
        }
    }

    if (hero->AtEdge(7))
    {
        hero->updateHeroExp();
        hero->resetDynamicEntity();
        hero->draw();
        firstScreen = true;
    }
}

void GameScreen::draw()
{
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        finish_line->draw();
        level = to_string(hero->getHeroLevel());
        score = to_string(hero->getHeroScore());
        importImage.drawCustomImage(level, {SHORT(appConsole.getWindowSize().X - 20), 0}, true);
        importImage.drawCustomImage(score, {70, 0}, true);
        importImage.drawCustomImage(level, {SHORT(appConsole.getWindowSize().X - 20), 0}, true);
        importImage.drawCustomImage(score, {70, 0}, true);
        firstScreen = false;    
    }
    for (int i = 0; i < numberEnemy; ++i)
    {
        enemy[i]->setSpeed(hero->getHeroLevel());
    }
    hero->draw();
    manageTrafficLight();
    manageEnemy();
    manageHero();
}

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
        buttonList.clear();
        for (int i = 0; i < 4; i++)
        {
            buttonList.addButton(new Button("#" + listPlayer.getPlayer(i)->getName(), {SHORT(42 + i * 40), SHORT(15)}, WHITE, RED));
            importImage.drawCustomImage("#" + listPlayer.getPlayer(i)->getLevel(), {SHORT(42 + i * 40), SHORT(25)});
            importImage.drawCustomImage("#" + listPlayer.getPlayer(i)->getScore(), {SHORT(42 + i * 40), SHORT(35)});
        }
        importImage.drawImage("LoadGameSaved.txt", {49, 2});
        firstScreen = false;
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
    moon = new DynamicEntity("moon.txt", {SHORT(45), SHORT(2)}, {SHORT(20), SHORT(16)});
    star = new DynamicEntity("Star.txt", {SHORT(189), SHORT(5)}, {SHORT(16), SHORT(16)});
    medal[2] = new Entity("copper.txt", {170, 28}, {11, 11});
    medal[1] = new Entity("silver.txt", {65, 26}, {11, 11});
    medal[0] = new Entity("gold.txt", {115, 13}, {11, 11});
    crown  = new Entity("crown.txt", {115, 1}, {11, 11});
    congratulate[0] = new DynamicEntity("congratulation1.txt", {85, 2 }, {12, 8});
    congratulate[1] = new DynamicEntity("congratulation2.txt", {85, 2}, {12, 8});

}

LeaderBoardScreen::~LeaderBoardScreen()
{
    delete frame;
    delete star;
    delete moon;
    delete crown;
    for (int i = 0; i < 3; i++)
        delete medal[i];
    for (int i = 0; i < 2; i++)
        delete congratulate[i];
}


void LeaderBoardScreen::draw() {
    vector <Player> playerRanking = listPlayer.getPlayers();
    sort(playerRanking.begin(), playerRanking.end());
    if (firstScreen)
    {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        frame->draw();
        moon->draw();
        star->draw();
        Sleep(500);
        for (int i = 2; i >= 0; i--)
        {
            importImage.drawCustomImage(playerRanking[i].getName(), posName[i], false);
            appConsole.SetBackgroundColor(BG_RED);
            importImage.drawCustomImage(playerRanking[i].getScore(), posScore[i], false);
            medal[i]->draw();
            appConsole.SetBackgroundColor(BG_CYAN);
            Sleep(500);
        }
        crown->draw();
        firstScreen = false;
    }

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            congratulate[i]->teleport({SHORT(85 + 60 * j), 2});
            congratulate[i]->draw();
        }
    for (int i = 0; i < 2; i++) 
        for (int j = 0; j < 2; j++) {
            congratulate[i]->teleport({SHORT(75 + 80 * j), 2});
            congratulate[i]->draw();
        }	 
}

PauseGameScreen::PauseGameScreen() : Screen(new HandlerPauseScreenInput(), "game.wav") {
    frame = new Entity("blueESC.txt", {SHORT(appConsole.getWindowSize().X / 2 - 40), 30}, {80, 40});
    COORD posExit = frame->getPos();
    posExit.X += 14;
    posExit.Y += 29;
    COORD posResume = frame->getPos();
    posResume.X += 20;
    posResume.Y += 14;
    buttonList.addButton(new Button("Resume", posResume, BLACK, GREEN));
    buttonList.addButton(new Button("saveandexit", posExit, BLACK, GREEN));
}

PauseGameScreen::~PauseGameScreen() {
    delete frame;
}

void PauseGameScreen::draw() {
    if (firstScreen) {
        frame->draw();
        firstScreen = false;
    }
    buttonList.draw();
}

OverScreen::OverScreen() : Screen(new HandlerOverScreenInput(), "outro.wav") {
	overFrame = new Entity("GameOver.txt",{40,50},{200,43}); 
	hero1 = new Entity("phoenix.txt",{110,36},{11,5}); 
	hero2 = new Entity("dragon.txt",{110,36},{11,5}); 
	die = new DynamicEntity("coolUfo.txt",{80,36},{11,5});
}

OverScreen::~OverScreen() {
	delete die;
	delete overFrame;
	delete hero1;
	delete hero2;
}

void OverScreen::draw() {
    if (firstScreen) {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
		overFrame->draw();
        die->draw();
		if(typeHero == 0) hero1->draw();
		else hero2->draw();
		hero1 = nullptr;
		hero2 = nullptr;		 
		while(count < 10){
			die->right(3);
			die->draw();
			count++;
		}
		die = nullptr;
		die = new DynamicEntity("boom.txt",{111,36},{11,5});
		count = 0;
		die ->draw(); 
        importImage.drawCustomImage("enter to replay", {60, 45});		
		firstScreen = false;			        
    }
    for (int i = 0; i < 6; i++) importImage.drawImage("redSkull.txt", arr[i]);	
    for (int i = 0; i < 6; i++) importImage.drawImage("blackSkull.txt", arr[i]);		
}

SettingScreen::SettingScreen() : Screen(new HandlerSettingInput(hero)){
	settingFrame = new Entity("frameSetting.txt",{0,0},{200,50});
    nv1 = new Entity(nameHero[0],{65,20},{11,5});
    nv2 = new Entity(nameHero[1],{125,20},{11,5});
    for (int i = 0; i < 2; i++)    buttonList.addButton(new Button(buttonName[i], {SHORT(45 + i * 60), SHORT(15)}, WHITE, RED));  
    for(int i = 2; i < 4; i++)
        buttonList.addButton(new Button(buttonName[i], {SHORT(65 + (i-2) * 65), SHORT(34)}, WHITE, RED));        	
};

SettingScreen::~SettingScreen() {
	delete settingFrame;
	delete nv1, nv2;
}

void SettingScreen::draw()
{
    if (firstScreen) {
        appConsole.setFullscreenBackgroundColor(BG_CYAN);
        settingFrame->draw();
		importImage.drawImage("settingTitle.txt", {55, 0});
		importImage.drawImage("bar.txt", {72, 34});		
        firstScreen = false;
        nv1->draw();
        nv2->draw();    
    }
    valueVolume = sound.getVolume() / 25;
    if (valueVolume < 5 && valueVolume > -1)
	for(int i = 1; i < 5; i++){
		if(i <= valueVolume)	importImage.drawImage("figure.txt", {SHORT(73+ (i-1)*14), 35});  
		else  importImage.drawImage("figureClear.txt", {SHORT(73 + (i-1)*14), 35}); 	
	} 
    else valueVolume = 0;
    buttonList.draw();
    importImage.drawImage("tick.txt", {SHORT(69 + typeHero * 60), SHORT(26)});	
    importImage.drawImage("clearTick.txt", {SHORT(69 + (1-typeHero) * 60), SHORT(26)});	
}
