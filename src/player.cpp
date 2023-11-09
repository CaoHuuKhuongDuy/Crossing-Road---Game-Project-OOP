#include "Player.h"

Player::Player(string name, string level, string score) : name(name), level(level), score(score) {}
ListPlayer::ListPlayer() {}

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

void ListPlayer::addPlayer(Player p) {
    players.push_back(p);
}

vector<Player> ListPlayer::getPlayers() {
    return players;
}
