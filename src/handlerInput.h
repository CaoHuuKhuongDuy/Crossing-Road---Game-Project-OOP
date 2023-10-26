#pragma once 
#include <conio.h>
#include "command.h"
#include "button.h"

class HandlerInput {
    public:
        virtual Command *handlerInput(ButtonList &buttonList) = 0;
    protected:
        int getUserInput();        
};

class HandlerMenuInput : public HandlerInput {
    public:
        HandlerMenuInput();
        ~HandlerMenuInput();
        Command *handlerInput(ButtonList &buttonList);
    private:
        Command *enterGame;
};

class HandlerGameInput : public HandlerInput {
    public:
        HandlerGameInput();
        ~HandlerGameInput();
        Command *handlerInput(ButtonList &buttonList);
};

class HandlerLoadInput : public HandlerInput {
    public:
        Command *handlerInput(ButtonList &buttonList);
};



