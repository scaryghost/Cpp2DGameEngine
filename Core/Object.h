#ifndef ETSAI_CPP2DGAMEENGINE_CORE_OBJECT
#define ETSAI_CPP2DGAMEENGINE_CORE_OBJECT

#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

namespace etsai {
namespace cpp2dgameengine {
namespace core {

using std::function;
using std::string;
using std::tuple;
using std::unordered_map;
using std::unordered_set;

class Object {
public:
    typedef function<void ()> TimerFunc;

    static void tickObjects(double delta);
    static void drawObjects();
    
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

    virtual void tick(double delta)= 0;
    virtual void draw()= 0;

private:
    typedef tuple<double, double, TimerFunc> TimerInfo;
    unordered_map<string, TimerInfo> timers;

    static unordered_set<Object*> objects;
    static unordered_set<Object*> tickableObjects;
};

}   //namespace core
}   //namespace cpp2dgameengine
}   //namespace etsai


#endif
