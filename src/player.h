#include "staticVariable.h"

class Player {
public:
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
        void addPlayer (string name);
    private:
        vector<Player> players;
};