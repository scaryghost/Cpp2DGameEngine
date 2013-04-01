#include "Cpp2DGameEngine/Core/Object.h"

namespace etsai {
namespace cpp2dgameengine {
namespace core {

using std::get;
using std::make_pair;
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
    xPos(xPos), yPos(yPos), rotation(rotation), tickObject(true) {
    createdObjects.insert(this);
}

Object::~Object() {
    createdObjects.erase(this);
}

float Object::getXPos() const {
    return xPos;
}

float Object::getYPos() const {
    return yPos;
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

void Object::translate(float xOffset, float yOffset) {
    xPos+= xOffset;
    yPos+= yOffset;
}

void Object::rotate(float angle) {
    rotation+= angle;
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
