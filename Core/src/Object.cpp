#include "Cpp2DGameEngine/Core/Object.h"

namespace etsai {
namespace cpp2dgameengine {
namespace core {

using std::get;
using std::make_pair;
using std::make_tuple;

Object::Object(double xPos, double yPos, double velocity, double rotation) :
    xPos(xPos), yPos(yPos), velocity(velocity), rotation(rotation), tickObject(true) {
}

double Object::getXPos() const {
    return xPos;
}

double Object::getYPos() const {
    return yPos;
}

double Object::getVelocity() const {
    return velocity;
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
