#include "Cpp2DGameEngine/Util/ObjectManager.h"

#include <cstdarg>

namespace etsai {
namespace cpp2dgameengine {
namespace util {


ObjectManager::ObjectManager() {
}

void ObjectManager::tickObjects(double delta) {
    for(auto obj: objects) {
        obj->tickObject && obj->tick(delta);
    }
}

void ObjectManager::drawObjects() {
    for(auto obj: objects) {
        obj->draw();
    }
}

void ObjectManager::openLibrary(const string& path) {
    if (dllHandle != NULL) {
        dlclose(dllHandle);
        dllHandle= NULL;
    }
    dlopen(path.c_str(), RTLD_LAZY);
    if (!dllHandle) {
        //throw exception, dlerror
        return;
    }
}

Object* ObjectManager::create(const string& classname, ...) {
    string creatorName("create" + classname);
    ObjectFactory creator;
    if (creators.count(creatorName) != 0) {
        creator= reinterpret_cast<ObjectFactory>(dlsym(dllHandle, creatorName.c_str()));
        if (!creator) {
            //throw exception, dlerror
            return NULL;
        }
        creators[creatorName]= creator;
    }
    
    va_list args;
    va_start(args, classname);
    Object *newObject= creators[creatorName](args);
    objects.insert(newObject);
    va_end(args);
    return newObject;
}

}   //namespace util
}   //namespace cpp2dgameengine
}   //namespace etsai
