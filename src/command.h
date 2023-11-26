#pragma once
#include <vector>
#include <string>
#include "staticVariable.h"

using namespace std;

class Screen;
// class GameScreen;
class Hero;

class Command {
    public:
        virtual void execute() = 0;
        virtual void setAddChar(char c) {};
        virtual bool clearText() { return false;}
        virtual void setIdButtonChoosen(int idButtonChoosen_) {};
    protected:
        void pushScreen(Screen *nxtScreen, int numBack = 1);
        void popScreen();
        int changeHero = 0;
};

class EnterBackScreenCommand : public Command {
    public:
        void execute() override;
};


class EnterMenuCommand : public Command {
    public:
        void execute() override;
};

class EnterIntroGameCommand : public Command {
    public:
        void execute() override;
};

class EnterGameCommand : public Command {
    public:
        EnterGameCommand(int numBack_ = 1);
        void execute() override;
    private:
        int numBack;
};

class EnterLoadGameCommand : public Command {
    public:
        void execute() override;
};

class EnterCreditCommand : public Command {
    public:
        void execute() override;
};

class EnterLeaderCommand : public Command {
    public:
        void execute() override;
};

class EnterSettingCommand : public Command {
    public:
        void execute() override;
};

class EnterPauseScreenCommand : public Command {
    public:
        void execute() override;
};

class EnterOverScreenCommand : public Command {
    public:
        void execute() override;
};

class ExitCommand : public Command {
    public:
        void execute() override;
};

class LoadSavedGameCommand : public Command {
    public:
        void execute() override;
        void setIdButtonChoosen(int idButtonChoosen_);
    private:
        int idButtonChoosen;
};

class InputTextCommand : public Command {
    public:
        InputTextCommand(string &textInput_);
        void setAddChar(char c) override;
        bool clearText() override;
        void execute() override;
    private:
        char addChar;
        int limChar;
        string &textInput;
};

class ResumeGameCommand : public Command {
    public:
        void execute() override;
};

class MoveEntityCommand : public Command {
    public:
        MoveEntityCommand(Hero *&hero_);
        virtual void execute() = 0;
    protected:
        Hero *&hero;
};

class MoveUpCommand : public MoveEntityCommand {
    public:
        MoveUpCommand(Hero *&hero_);
        void execute() override;
};

class MoveDownCommand : public MoveEntityCommand {
    public:
        MoveDownCommand(Hero *&hero_);
        void execute() override;
};

class MoveLeftCommand : public MoveEntityCommand {
    public:
        MoveLeftCommand(Hero *&hero_);
        void execute() override;
};

class MoveRightCommand : public MoveEntityCommand {
    public:
        MoveRightCommand(Hero *&hero_);
        void execute() override;
};

class ExistHeroCommand: public MoveEntityCommand {
    public:
        ExistHeroCommand(Hero *&hero_);
        bool checkExistHero();
        void execute() override;        
};

class SaveHeroCommand : public MoveEntityCommand {
    public:
        SaveHeroCommand(Hero*& hero_);
        void execute() override;
};

class ChangeHeroSkinCommand : public MoveEntityCommand {
    public:
        ChangeHeroSkinCommand(Hero*& hero_);
        void execute() override;
};
    

class CreateHero_1 : public Command {
    public:
    	CreateHero_1(Hero*& hero_);
        void execute() override;
};

class CreateHero_2 : public Command {
    public:
    	CreateHero_2(Hero*& hero_);    	
        void execute() override;
};

class PlusVolume : public Command {
    public:
        void execute() override;
};

class SubVolume : public Command {
    public:
        void execute() override;
};

