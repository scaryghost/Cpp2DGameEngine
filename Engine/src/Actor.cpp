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

unordered_set<Actor*> Actor::radiusActors(double radius) const {
    unordered_set<Actor*> nearbyActors;
    double hitboxRadiusSq(pow(hitbox->getRadius(), 2));

    for(auto actor: createdActors) {
        double actorRadius(actor->hitbox->getRadius());
        double angle= 2 * PI - atan2(actor->yPos - yPos, actor->xPos - xPos);
        double xEdge= actor->xPos + actorRadius * cos(angle), yEdge= actor->yPos + actorRadius * sin(angle);
        if (pow(xEdge - xPos, 2) + pow(yEdge - yPos, 2) <= hitboxRadiusSq) {
            nearbyActors.insert(actor);
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
