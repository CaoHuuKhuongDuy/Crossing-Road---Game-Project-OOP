#include "Player.h"

Player::Player(string name, string level, string score) : name(name), level(level), score(score) {}

string Player::getName() const {
    return name;
}

void Player::setName(const string& newName) {
    name = newName;
}

string Player::getScore() const {
    return score;
}

void Player::setScore(const string& newScore) {
    score = newScore;
}

string Player::getLevel() const {
    return level;
}

void Player::setLevel(const string& newLevel) {
    level = newLevel;
}

ListPlayer::ListPlayer() {}

void ListPlayer::init() {
    ifstream file;
    file.open("../media/LoadGame/loadGame.txt");
    string name, level, score;
    while (file >> name >> level >> score) {
        Player p(name, level, score);
        players.push_back(p);
    }
    file.close();
}

Player* ListPlayer::getPlayer(int index) {
    return &players[index];
}

void ListPlayer::addPlayer(Player p) {
    players.push_back(p);
    players.erase(players.begin());
    savePlayers();
}

void ListPlayer::savePlayers() {
    ofstream fout;
    fout.open("../media/LoadGame/loadGame.txt");
    for (Player &player: players) {
        fout << player.getName() << " " << player.getLevel() << " " << player.getScore() << endl;
    }
    fout.close();
}

vector<Player> ListPlayer::getPlayers() {
    return players;
}
