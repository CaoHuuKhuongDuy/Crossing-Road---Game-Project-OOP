#include "staticVariable.h"

using namespace stValue;

class Entity {
    public:
        Entity(string entityName_, COORD pos1, COORD size_);
        void draw();
        COORD getPos();
        COORD getEndPos();
    protected:
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
    int getSpeed();

protected:
    void caculateRemainFrame(COORD oldPos);
    int speed;
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
