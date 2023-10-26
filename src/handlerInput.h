#pragma once 
#include <conio.h>
#include "command.h"
#include "button.h"

class HandlerInput {
    public:
        virtual Command *handlerInput(Screen *&mainScreen, ButtonList &buttonList) = 0;
    protected:
        int getUserInput();        
        void changeScreen(Screen *&mainScreen, Screen *nxtScreen);
};

class HandlerMenuInput : public HandlerInput {
    public:
        HandlerMenuInput();
        Command *handlerInput(Screen *&mainScreen, ButtonList &buttonList);
    private:
        Command *enterGame;
};

