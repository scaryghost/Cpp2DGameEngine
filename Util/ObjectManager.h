#ifndef ETSAI_CPP2DGAMEENGINE_UTIL_OBJECTMANAGER
#define ETSAI_CPP2DGAMEENGINE_UTIL_OBJECTMANAGER

#include "Cpp2DGameEngine/Core/Object.h"

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <dlfcn.h>

namespace etsai {
namespace cpp2dgameengine {
namespace util {

using core::Object;
using std::string;
using std::unordered_map;
using std::unordered_set;

class ObjectManager {
public:
    ObjectManager();

    void tickObjects(double delta);
    void drawObjects();
    void openLibrary(const string& path);
    Object* create(const string& classname, ...);

private:
    typedef Object* (*ObjectFactory)(...);

    void* dllHandle;
    unordered_map<string, ObjectFactory> creators;
    unordered_set<Object*> objects;
};

}   //namespace util
}   //namespace cpp2dgameengine
}   //namespace etsai

#endif
