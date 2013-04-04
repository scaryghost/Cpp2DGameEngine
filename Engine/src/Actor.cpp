#include "Cpp2DGameEngine/Engine/Actor.h"
#include "Cpp2DGameEngine/Core/Consts.h"

#include <cmath>

namespace etsai {
namespace cpp2dgameengine {
namespace engine {

using std::atan2;
using std::cos;
using std::pow;
using std::sin;

unordered_set<Actor*> Actor::createdActors;

Actor::Actor(float xPos, float yPos) : Object(xPos, yPos, 0), timeAccum(0), hitbox(NULL) {
    createdActors.insert(this);
}

Actor::~Actor() {
    createdActors.erase(this);
}

unordered_set<Actor*> Actor::radiusActors() const {
    return radiusActors(hitbox->getRadius());
}

unordered_set<Actor*> Actor::radiusActors(float radius) const {
    unordered_set<Actor*> nearbyActors;
    float radiusSq(pow(radius, 2));

    for(auto actor: createdActors) {
        if (actor != this) {
            float xDelta(actor->objPos.vx - objPos.vx), yDelta(actor->objPos.vy - objPos.vy);
            float actorRadius(actor->hitbox->getRadius());
            float angle= atan2(yDelta, xDelta);

            float xEdge= actor->objPos.vx - actorRadius * cos(angle), yEdge= actor->objPos.vy - actorRadius * sin(angle);
            if (pow(xEdge - objPos.vx, 2) + pow(yEdge - objPos.vy, 2) <= radiusSq) {
                nearbyActors.insert(actor);
            }
        }
    }
    return nearbyActors;
}

void Actor::setPosition(float newXPos, float newYPos) {
    Object::setPosition(newXPos, newYPos);
    hitbox->setPosition(newXPos, newYPos);
}

void Actor::translate(float xOffset, float yOffset) {
    Object::translate(xOffset, yOffset);
    hitbox->translate(xOffset, yOffset);
}

void Actor::setRotation(float newRotation) {
    Object::setRotation(newRotation);
    hitbox->setRotation(newRotation);
}

void Actor::rotate(float offset) {
    Object::rotate(offset);
    hitbox->rotate(offset);
}

bool Actor::tick(float delta) {
    Object::tick(delta);

    timeAccum+= delta;
    Vector2D accel= calcAcceleration(timeAccum);
    velocity+= accel;
    translate(velocity.vx * delta, velocity.vy * delta);

    for(auto actor: radiusActors()) {
        if (this != actor && this->hitbox->collide(actor->hitbox)) {
            this->touch(actor);
            actor->touch(this);
        }
    }
    return true;
}

}
}
}
