#ifndef ETSAI_CPP2DGAMEENGINE_CORE_ACTOR
#define ETSAI_CPP2DGAMEENGINE_CORE_ACTOR

#include "Cpp2DGameEngine/Core/Object.h"
#include "Cpp2DGameEngine/Engine/HitBox.h"

#include <unordered_set>

namespace etsai {
namespace cpp2dgameengine {
namespace engine {

using core::Object;
using core::Vector2D;
using std::unordered_set;

class Actor : public core::Object {
public:
    Actor(float xPos, float yPos);
    virtual ~Actor();

    unordered_set<Actor*> radiusActors() const;
    unordered_set<Actor*> radiusActors(float radius) const;

    virtual void setPosition(float newXPos, float newYPos);
    virtual void translate(float xOffset, float yOffset);
    virtual void setRotation(float newRotation);
    virtual void rotate(float offset);

protected:
    float timeAccum;
    HitBox *hitbox;
    Vector2D velocity;

    virtual bool tick(float delta);
    virtual void touch(Actor* actor)= 0;
    virtual Vector2D calcAcceleration(float time)= 0;
private:
    static unordered_set<Actor*> createdActors;
};

}
}
}

#endif
