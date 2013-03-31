#ifndef ETSAI_CPP2DGAMEENGINE_CORE_ACTOR
#define ETSAI_CPP2DGAMEENGINE_CORE_ACTOR

#include "Cpp2DGameEngine/Core/Object.h"
#include "Cpp2DGameEngine/Core/HitBox.h"

namespace etsai {
namespace cpp2dgameengine {
namespace core {

class Actor : public Object {
public:
    Actor(float xPos, float yPos);
    virtual ~Actor();

    virtual void translate(float xOffset, float yOffset);
    virtual void rotate(float angle);

    virtual void touch(Actor* actor)= 0;
protected:
    HitBox *hitbox;

private:
    static unordered_set<Actor*> createdActors;
};

}
}
}

#endif
