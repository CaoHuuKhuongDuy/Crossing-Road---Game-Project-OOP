#pragma once
#include <conio.h>
#include "command.h"
#include "button.h"

class HandlerInput
{
public:
    virtual Command *handlerInput(ButtonList &buttonList) = 0;
    void setFixUserInput(int fixUserInput);
protected:
    int getUserInput();
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
};

class HandlerLoadInput : public HandlerInput
{
    public:
        Command *handlerInput(ButtonList &buttonList);
};
