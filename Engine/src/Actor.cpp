#include "Cpp2DGameEngine/Engine/Actor.h"
#include "Cpp2DGameEngine/Core/Consts.h"

#include <cmath>

namespace etsai {
namespace cpp2dgameengine {
namespace engine {

using core::PI;
using std::atan2;
using std::cos;
using std::pow;
using std::sin;

unordered_set<Actor*> Actor::createdActors;

Actor::Actor(float xPos, float yPos) : Object(xPos, yPos, 0, 0), hitbox(NULL) {
    createdActors.insert(this);
}

Actor::~Actor() {
    createdActors.erase(this);
}

void Actor::checkCollisions() {
    for(auto actor: createdActors) {
        if (this != actor && this->hitbox->collide(actor->hitbox)) {
            this->touch(actor);
        }
    }
}

unordered_set<Actor*> Actor::radiusActors() const {
    return radiusActors(hitbox->getRadius());
}

unordered_set<Actor*> Actor::radiusActors(double radius) const {
    unordered_set<Actor*> nearbyActors;
    double radiusSq(pow(radius, 2));

    for(auto actor: createdActors) {
        if (actor != this) {
            double xDelta(actor->xPos - xPos), yDelta(actor->yPos - yPos);
            double actorRadius(actor->hitbox->getRadius());
            double angle= atan2(yDelta, xDelta);

            double xEdge= actor->xPos - actorRadius * cos(angle), yEdge= actor->yPos - actorRadius * sin(angle);
            if (pow(xEdge - xPos, 2) + pow(yEdge - yPos, 2) <= radiusSq) {
                nearbyActors.insert(actor);
            }
        }
    }
    return nearbyActors;
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
