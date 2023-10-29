#pragma once
// #include "screen.h"
class Screen;
class GameScreen;
class Hero;

class Command
{
public:
    virtual void execute(Screen *&mainScreen) {}
    virtual void execute(Hero *hero) {}

protected:
    void changeScreen(Screen *&mainScreen, Screen *nxtScreen);
};

class EnterGameCommand : public Command
{
public:
    void execute(Screen *&mainScreen) override;
    void execute(Hero *hero) override {};
};

class MoveUpCommand : public Command
{
public:
    void execute(Screen *&mainScreen) override {};

    void execute(Hero *hero) override;
};

class MoveDownCommand : public Command
{
public:
    void execute(Screen *&mainScreen) override {};
    void execute(Hero *hero) override;
};

class MoveLeftCommand : public Command
{
public:
    void execute(Screen *&mainScreen) override {};

    void execute(Hero *hero) override;
};

class MoveRightCommand : public Command
{
public:
    void execute(Screen *&mainScreen) override {};

    void execute(Hero *hero) override;
};