#pragma once
#include <conio.h>
#include "command.h"
#include "button.h"

class HandlerInput
{
public:
    HandlerInput();
    virtual Command *handlerInput(ButtonList &buttonList) = 0;
    virtual void setFixUserInput(int fixUserInput);
    virtual ~HandlerInput();
protected:
    int getUserInput();
    Command *enterBackScreen;
private:
    int fixUserInput = -1;
};


class HandlerMenuInput : public HandlerInput
{
public:
    HandlerMenuInput();
    ~HandlerMenuInput();
    Command *handlerInput(ButtonList &buttonList) override;

private:
    Command *enterGame;
    Command *enterLoadGame;
    Command *enterCredit;
    Command *enterLeader;
};

class HandlerIntroGameInput : public HandlerInput {
    public:
        HandlerIntroGameInput(string &textInput_);
        ~HandlerIntroGameInput();
        Command *handlerInput(ButtonList &ButtonList) override;
    private:
        Command *enterGame;
        Command *inputChar;
};

class HandlerGameInput : public HandlerInput
{
public:
    HandlerGameInput(Hero *&hero);
    ~HandlerGameInput();
    Command *handlerInput(ButtonList &buttonList) override;

private:
    Command *buttonUP;
    Command *buttonDOWN;
    Command *buttonLEFT;
    Command *buttonRIGHT;
    Command *saveHero;
    Command *enterPauseScreen;
};

class HandlerLoadInput : public HandlerInput
{
    public:
        HandlerLoadInput();
        ~HandlerLoadInput();
        Command *handlerInput(ButtonList &buttonList);
    private:
        Command *loadSavedGame;
};

class HandlerLeaderBoardInput : public HandlerInput
{
    public:
        HandlerLeaderBoardInput();
        ~HandlerLeaderBoardInput();
        Command *handlerInput(ButtonList &buttonList);
};

class HandlerCreditInput : public HandlerInput {
    public:
        HandlerCreditInput();
        ~HandlerCreditInput();
        Command *handlerInput(ButtonList &buttonList);
};

class HandlerPauseScreenInput : public HandlerInput {
    public:
        HandlerPauseScreenInput();
        ~HandlerPauseScreenInput();
        Command *handlerInput(ButtonList &buttonList);
    private:
        Command *resumeGame;
};