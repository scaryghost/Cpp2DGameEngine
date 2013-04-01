#include "Cpp2DGameEngine/Core/Object.h"

namespace etsai {
namespace cpp2dgameengine {
namespace core {

using std::get;
using std::make_pair;
using std::make_tuple;

unordered_set<Object*> Object::createdObjects;

void Object::tickObjects(double delta) {
    for(auto obj: createdObjects) {
        obj->tickObject && obj->tick(delta);
    }
}

void Object::drawObjects() {
    for(auto obj: createdObjects) {
        obj->draw();
    }
}

Object::Object(double xPos, double yPos, double rotation) :
    xPos(xPos), yPos(yPos), rotation(rotation), tickObject(true) {
    createdObjects.insert(this);
}

Object::~Object() {
    createdObjects.erase(this);
}

double Object::getXPos() const {
    return xPos;
}

double Object::getYPos() const {
    return yPos;
}

double Object::getRotation() const {
    return rotation;
}

void Object::addTimer(double period, const string& name, TimerFunc callback) {
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

void Object::translate(double xOffset, double yOffset) {
    xPos+= xOffset;
    yPos+= yOffset;
}

void Object::rotate(double angle) {
    rotation+= angle;
}

bool Object::tick(double delta) {
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
