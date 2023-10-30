#pragma once 
class Screen;
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