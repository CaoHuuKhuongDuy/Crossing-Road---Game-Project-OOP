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
};

class HandlerGameInput : public HandlerInput
{
public:
    HandlerGameInput();
    ~HandlerGameInput();
    Command *handlerInput(ButtonList &buttonList) override {return nullptr;}
    Command *handlerInput() override;

private:
    Command *buttonUP;
    Command *buttonDOWN;
    Command *buttonLEFT;
    Command *buttonRIGHT;
    // Command *buttonPAUSE;
    // Command *buttonSAVE;
    // Command *buttonLOAD;
};

class HandlerLoadInput : public HandlerInput
{
public:
    Command *handlerInput(ButtonList &buttonList);
};
