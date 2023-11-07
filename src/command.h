#pragma once
#include <vector>
#include <string>

using namespace std;

class Screen;
// class GameScreen;
class Hero;

class Command {
    public:
        virtual void execute() = 0;
        virtual void setAddChar(char c) {};
        virtual void clearText() {};
    protected:
        static void changeScreen(Screen *&mainScreen, Screen *nxtScreen);
};

class EnterIntroGameCommand : public Command {
    public:
        void execute() override;
};

class EnterGameCommand : public Command {
    public:
        void execute() override;
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

class InputTextCommand : public Command {
    public:
        InputTextCommand(string &textInput_);
        void setAddChar(char c) override;
        void clearText() override;
        void execute() override;
    private:
        char addChar;
        int limChar;
        string &textInput;
};

class AccessEntityCommand : public Command {
    public:
        AccessEntityCommand(Hero *&hero_);
        virtual void execute() = 0;
    protected:
        Hero *&hero;
};

class MoveUpCommand : public AccessEntityCommand {
    public:
        MoveUpCommand(Hero *&hero_);
        void execute() override;
};

class MoveDownCommand : public AccessEntityCommand {
    public:
        MoveDownCommand(Hero *&hero_);
        void execute() override;
};

class MoveLeftCommand : public AccessEntityCommand {
    public:
        MoveLeftCommand(Hero *&hero_);
        void execute() override;
};

class MoveRightCommand : public AccessEntityCommand {
    public:
        MoveRightCommand(Hero *&hero_);
        void execute() override;
};

class SaveGameCommand : public AccessEntityCommand {
    public:
        SaveGameCommand(Hero* &hero_);
        void execute();
};  