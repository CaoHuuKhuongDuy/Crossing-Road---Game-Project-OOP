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

class DynamicEntity : public Entity {
    public: 
        DynamicEntity(string entityName_, COORD pos1, COORD size_);
        void up(int step);
        void down(int step);
        void left(int step);
        void right(int step);
        void teleport(COORD pos);
    private: 
        void caculateRemainFrame(COORD oldPos);
};
