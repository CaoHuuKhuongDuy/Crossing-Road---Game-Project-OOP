#include "command.h"
#include "screen.h"
#include "screenStack.h"



void Command::pushScreen(Screen *nxtScreen, int numBack) {
    listScreen.push(nxtScreen, numBack);
}

void Command::popScreen() {
    listScreen.pop();
}

void EnterBackScreenCommand::execute() {
    popScreen();
}

void EnterMenuCommand::execute() {
    pushScreen(new MenuScreen());
}

void EnterIntroGameCommand::execute() {
    pushScreen(new IntroGameScreen(), 2);
}

EnterGameCommand::EnterGameCommand(int numBack_) : numBack(numBack_) {}

void EnterGameCommand::execute() {
    pushScreen(new GameScreen(), numBack);
}

void EnterLoadGameCommand::execute() {
    pushScreen(new LoadGameScreen());
}

void EnterCreditCommand::execute() {
    pushScreen(new CreditScreen());
}

void EnterLeaderCommand::execute() {
    pushScreen(new LeaderBoardScreen());
}

void EnterSettingCommand:: execute(){
    pushScreen(new SettingScreen());	
}

void EnterPauseScreenCommand::execute() {
    pushScreen(new PauseGameScreen(), 2);
}

void EnterOverScreenCommand::execute() {
    pushScreen(new OverScreen());
}

void ExitCommand::execute() {
    appConsole.closeConsole();

}

void LoadSavedGameCommand::execute() {
    mainPlayer = listPlayer.getPlayer(idButtonChoosen);
    pushScreen(new GameScreen());
}

void LoadSavedGameCommand::setIdButtonChoosen(int idButtonChoosen_) {
    idButtonChoosen = idButtonChoosen_;
}

InputTextCommand::InputTextCommand(string &textInput_) : textInput(textInput_), limChar(6), addChar('*') {}

void InputTextCommand::setAddChar(char c) {
    addChar = c;
}

bool InputTextCommand::clearText() {
    if (!textInput.size()) return false;
    while (textInput.size()) textInput.pop_back();
    return true;
}

void InputTextCommand::execute() {
    if (addChar == '*') return;
    if (addChar == '@') {
        if (textInput.size()) textInput.pop_back();
        return;
    }
    if (textInput.size() < limChar) textInput += addChar;
}

void ResumeGameCommand::execute() {
    listScreen.setNumback(1);
    popScreen();
}

MoveEntityCommand::MoveEntityCommand(Hero *&hero_) : hero(hero_) {}

MoveUpCommand::MoveUpCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}

void MoveUpCommand::execute()
{
    hero->up(5);
}

MoveDownCommand::MoveDownCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}


void MoveDownCommand::execute()
{
    hero->down(5);
}

MoveLeftCommand::MoveLeftCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}


void MoveLeftCommand::execute()
{
    hero->left(5);
}

MoveRightCommand::MoveRightCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}

void MoveRightCommand::execute()
{
    hero->right(5);
}

ExistHeroCommand::ExistHeroCommand(Hero*& hero_):  MoveEntityCommand(hero_) {}

bool ExistHeroCommand:: checkExistHero(){
	if(!hero->getExist()) {
	hero->changeExist();	
	return 0;		
	}
	return 1;
}

void ExistHeroCommand:: execute(){

}


SaveHeroCommand::SaveHeroCommand(Hero*& hero_) : MoveEntityCommand(hero_) {}

void SaveHeroCommand::execute() {
    mainPlayer->setLevel(to_string(hero->getHeroLevel()));
    mainPlayer->setScore(to_string(hero->getHeroScore()));
    listPlayer.savePlayers();
}

ChangeHeroSkinCommand::ChangeHeroSkinCommand(Hero*& hero_) : MoveEntityCommand(hero_){}

void ChangeHeroSkinCommand::execute()
{
    if(typeHero) {
    	if(hero->getSkin() == 0) hero->setEntityname("dragonSkin.txt");
    	else hero->setEntityname("dragon.txt");
	}
	else{
    	if(hero->getSkin() == 0) hero->setEntityname("phonixSkin.txt");
    	else hero->setEntityname("phoenix.txt");		
	} 
	hero->SetSkin(!hero->getSkin());
}

    
CreateHero_1::CreateHero_1(Hero*& hero_){
	
}

void CreateHero_1:: execute(){
    typeHero = 0;
}

CreateHero_2::CreateHero_2(Hero*& hero_){
	
}

void CreateHero_2:: execute(){
	typeHero = 1;
}

void PlusVolume:: execute(){
	sound.setVolume(sound.getVolume() + 25);
}

void SubVolume:: execute(){
	sound.setVolume(sound.getVolume() - 25);
}
