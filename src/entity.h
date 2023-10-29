#include "staticVariable.h"

using namespace stValue;
// enum class EntityType { Hero, Boss, TreeBoss, BusBoss, CarBoss, Rocket };

class Entity
{
public:
    Entity(string entityName_, COORD pos1, COORD size_);
    void draw();
    COORD getPos();
    COORD getEndPos();

protected:
    // EntityType type;
    COORD remainStartPos, remainEndPos;
    void removeRemainFrame();
    void verify();
    COORD startPos, size;
    string entityName;
};

class DynamicEntity : public Entity
{
public:
    DynamicEntity(string entityName_, COORD pos1, COORD size_);
    void up(int step);
    void down(int step);
    void left(int step);
    void right(int step);
    void teleport(COORD pos);

protected:
    void caculateRemainFrame(COORD oldPos);
};


class Hero : public DynamicEntity
{
public:
    Hero(string entityName_, COORD pos1, COORD size_, long int score_, int level_);
    bool checkCollision(DynamicEntity* enemy);
    SHORT getHeroWidth();
    SHORT getHeroHeight();
    int getHeroLevel();
    long int getHeroScore();
    void setHeroLevel(const int&);
    void setHeroScore(const long int&);
    void updateHeroExp();
private:
    SHORT heroWidth = 13;
    SHORT heroHeight = 5;
    int level;
    long int score;
};
