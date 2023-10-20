#include "staticVariable.h"

using namespace stValue;
// enum class EntityType { Hero, Boss, TreeBoss, BusBoss, CarBoss, Rocket };

class Entity {
    public:
        Entity(COORD pos1, COORD pos2);
        virtual void draw() = 0;
    protected:
        // EntityType type;
        COORD startPos, endPos;
};

class Hero : public Entity {
    public:
    
};

class Rocket : public Entity {
    public:
        Rocket(COORD pos1, COORD pos2);
        void draw();
};

class Jupiter : public Entity
{
    public:
        Jupiter(COORD pos1, COORD pos2);
        void draw();
};

class Sartun : public Entity
{
    public:
        Sartun(COORD pos1, COORD pos2);
        void draw();
};


class Venus : public Entity
{
    public:
        Venus(COORD pos1, COORD pos2);
        void draw();
};