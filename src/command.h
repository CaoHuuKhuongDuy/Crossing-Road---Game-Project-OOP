#pragma once
#include <vector>
class Screen;
// class GameScreen;
class Hero;

class Command
{
public:
    virtual void execute() = 0;

protected:
    void changeScreen(Screen *&mainScreen, Screen *nxtScreen);
};

class EnterGameCommand : public Command
{
public:
    void execute() override;
};

class EnterLoadGameCommand : public Command
{
public:
    void execute() override;
};

class EnterCreditCommand : public Command
{
public:
    void execute() override;
};

class MoveEntityCommand : public Command
{
public:
    MoveEntityCommand(Hero *&hero_);
    virtual void execute() = 0;

protected:
    Hero *&hero;
};

class MoveUpCommand : public MoveEntityCommand
{
public:
    MoveUpCommand(Hero *&hero_);
    void execute() override;
};

class MoveDownCommand : public MoveEntityCommand
{
public:
    MoveDownCommand(Hero *&hero_);
    void execute() override;
};

class MoveLeftCommand : public MoveEntityCommand
{
public:
    MoveLeftCommand(Hero *&hero_);
    void execute() override;
};

class MoveRightCommand : public MoveEntityCommand
{
public:
    MoveRightCommand(Hero *&hero_);
    void execute() override;
};