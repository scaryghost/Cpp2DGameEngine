#include "Cpp2DGameEngine/Engine/Actor.h"

namespace etsai {
namespace cpp2dgameengine {
namespace engine {

unordered_set<Actor*> Actor::createdActors;

Actor::Actor(float xPos, float yPos) : Object(xPos, yPos, 0, 0), hitbox(NULL) {
    createdActors.insert(this);
}

Actor::~Actor() {
    createdActors.erase(this);
}

void Actor::translate(float xOffset, float yOffset) {
    Object::translate(xOffset, yOffset);
    hitbox->translate(xOffset, yOffset);
}

void Actor::rotate(float angle) {
    Object::rotate(angle);
    hitbox->rotate(angle);
}

}
}
}
