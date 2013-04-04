#include "Cpp2DGameEngine/Core/Object.h"

namespace etsai {
namespace cpp2dgameengine {
namespace core {

using std::get;
using std::make_tuple;

unordered_set<Object*> Object::createdObjects;

void Object::tickObjects(float delta) {
    for(auto obj: createdObjects) {
        obj->tickObject && obj->tick(delta);
    }
}

void Object::drawObjects() {
    for(auto obj: createdObjects) {
        obj->draw();
    }
}

Object::Object(float xPos, float yPos, float rotation) :
    objPos(xPos, yPos), rotation(rotation), tickObject(true) {
    createdObjects.insert(this);
}

Object::~Object() {
    createdObjects.erase(this);
}

Vector2D Object::getPosition() const {
    return objPos;
}

float Object::getRotation() const {
    return rotation;
}

void Object::addTimer(float period, const string& name, TimerFunc callback) {
    auto info= make_tuple(period, 0, callback);
    timers.insert(make_pair(name, info));
}

void Object::removeTimer(const string& name) {
    timers.erase(name);
}

void Object::disableTick() {
    tickObject= false;
}

void Object::enableTick() {
    tickObject= true;
}    

void Object::setPosition(float newXPos, float newYPos) {
    objPos.vx= newXPos;
    objPos.vy= newYPos;
}

void Object::setRotation(float newRotation) {
    rotation= newRotation;
}

void Object::translate(float xOffset, float yOffset) {
    objPos.vx+= xOffset;
    objPos.vy+= yOffset;
}

void Object::rotate(float offset) {
    rotation+= offset;
}

bool Object::tick(float delta) {
    for(auto timer: timers) {
        get<1>(timer.second)+= delta;
        if (get<1>(timer.second) >= get<0>(timer.second)) {
            get<2>(timer.second)();
            get<1>(timer.second)-= get<0>(timer.second);
        }
    }
    return true;
}

}
}
}
