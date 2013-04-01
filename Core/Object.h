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
    static void tickObjects(float delta);
    static void drawObjects();

    typedef function<void ()> TimerFunc;

    Object(float xPos, float yPos, float rotation);
    virtual ~Object();

    tuple<float, float> getPosition() const;
    float getRotation() const;

    void addTimer(float period, const string& name, TimerFunc callback);
    void removeTimer(const string& name);
    void disableTick();
    void enableTick();
    
    virtual void setPosition(float newXPos, float newYPos);
    virtual void translate(float xOffset, float yOffset);
    virtual void setRotation(float newRotation);
    virtual void rotate(float offset);

protected:
    float xPos;
    float yPos;
    float rotation;

    virtual bool tick(float delta);
    virtual void draw()= 0;

private:
    bool tickObject;
    typedef tuple<float, float, TimerFunc> TimerInfo;
    unordered_map<string, TimerInfo> timers;

    static unordered_set<Object*> createdObjects;
};

}   //namespace core
}   //namespace cpp2dgameengine
}   //namespace etsai


#endif
