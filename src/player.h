#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

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

    bool operator<(const Player& p) const {
        return stoi(score) > stoi(p.score);
    }

private:
    string name;
    string score;
    string level;
};

class ListPlayer {
    public:
        ListPlayer();
        void init();
        void addPlayer (Player p);
        void savePlayers();
        Player* getPlayer(int index);
        vector<Player> getPlayers();
    private:
        vector<Player> players;
};