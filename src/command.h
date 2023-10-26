#pragma once 
// #include "screen.h"
class Screen;
class GameScreen;
class Command {
    public:
        virtual void excute(Screen *&mainScreen) = 0;
    protected:
        void changeScreen(Screen *&mainScreen, Screen *nxtScreen);
};

class EnterGameCommand : public Command {
    public:
        void excute(Screen *&mainScreen);
};