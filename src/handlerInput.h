#pragma once
#include <conio.h>
#include "command.h"
#include "button.h"

class HandlerInput
{
public:
    virtual Command *handlerInput(ButtonList &buttonList) = 0;
    virtual Command *handlerInput() = 0;

protected:
    int getUserInput();
};

class HandlerMenuInput : public HandlerInput
{
public:
    HandlerMenuInput();
    ~HandlerMenuInput();
    Command *handlerInput(ButtonList &buttonList) override;
    Command *handlerInput() override {return nullptr;}

private:
    Command *enterGame;
    Command *enterLoadGame;
    Command *enterCredit;
};

class HandlerGameInput : public HandlerInput
{
public:
    HandlerGameInput(Hero *&hero);
    ~HandlerGameInput();
    Command *handlerInput(ButtonList &buttonList) override {return nullptr;}
    Command *handlerInput() override;

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
