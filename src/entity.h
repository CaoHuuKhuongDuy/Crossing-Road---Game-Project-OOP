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
    bool isAtEdge(SHORT posEdge_X);
    virtual void resetDynamicEntity();
    void spawnDynamicEntity(double speed = 1);
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
    SHORT getHeroWidth();
    SHORT getHeroHeight();
    void setHeroLevel(const int&);
    void setHeroScore(const long int&);
    void updateHeroExp();
    void resetDynamicEntity();
    bool isAtEdge(SHORT posEdge_Y);
    bool isCollision(DynamicEntity* enemy);
    int getHeroLevel();
    long int getHeroScore();
private:
    SHORT heroWidth = 13;
    SHORT heroHeight = 5;
    int level = 1;
    long int score = 0;
};
