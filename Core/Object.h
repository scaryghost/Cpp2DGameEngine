#ifndef ETSAI_CPP2DGAMEENGINE_CORE_OBJECT
#define ETSAI_CPP2DGAMEENGINE_CORE_OBJECT

#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>

namespace etsai {
namespace cpp2dgameengine {

namespace util{
class ObjectManager;
}   //namespace util

namespace core {

using std::function;
using std::string;
using std::tuple;
using std::unordered_map;


class Object {
public:
    typedef function<void ()> TimerFunc;

    Object(double xPos, double yPos, double velocity, double rotation);

    double getXPos() const;
    double getYPos() const;
    double getVelocity() const;
    double getRotation() const;

    void addTimer(double period, const string& name, TimerFunc callback);
    void removeTimer(const string& name);
    void disableTick();
    void enableTick();
    
    virtual void translate(double xOffset, double yOffset);
    virtual void rotate(double angle);

protected:
    double xPos;
    double yPos;
    double velocity;
    double rotation;

    virtual bool tick(double delta);
    virtual void draw()= 0;

private:
    bool tickObject;
    typedef tuple<double, double, TimerFunc> TimerInfo;
    unordered_map<string, TimerInfo> timers;

    friend class util::ObjectManager;
};

}   //namespace core
}   //namespace cpp2dgameengine
}   //namespace etsai


#endif
