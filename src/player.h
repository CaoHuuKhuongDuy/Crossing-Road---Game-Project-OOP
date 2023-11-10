#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Player {
public:
    Player(){}
    Player(string name, string level, string score);
    string getName() const;
    void setName(const std::string& newName);

    string getScore() const;
    void setScore(const std::string& newScore);

    string getLevel() const;
    void setLevel(const std::string& newLevel);
private:
    string name;
    string score;
    string level;
};

class ListPlayer {
    public:
        ListPlayer();
        void addPlayer (Player p);
        vector<Player> getPlayers();
    private:
        vector<Player> players;
};