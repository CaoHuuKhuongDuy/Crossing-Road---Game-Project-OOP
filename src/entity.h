#include "staticVariable.h"

using namespace stValue;
// enum class EntityType { Hero, Boss, TreeBoss, BusBoss, CarBoss, Rocket };

class Entity {
    public:
        Entity(string entityName_, COORD pos1, COORD size_, string defaultValue_ = " ", bool colorBG_ = true);
        void draw();
        COORD remainStartPos, remainEndPos;
    protected:
        // EntityType type;
        void verify();
        COORD startPos, size;
        string entityName;
        bool colorBG;
        string defaultValue;
};

class DynamicEntity : public Entity {
    public: 
        DynamicEntity(string entityName_, COORD pos1, COORD size_, string defaultValue_ = " ", bool colorBG_ = true);
        void up(int step);
        void down(int step);
        void left(int step);
        void right(int step);
        void teleport(COORD pos);
    protected: 
        void caculateRemainFrame(COORD oldPos);
};