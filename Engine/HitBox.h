#ifndef ETSAI_CPP2DGAMEENGINE_CORE_HITBOX
#define ETSAI_CPP2DGAMEENGINE_CORE_HITBOX

#include "Cpp2DGameEngine/Core/Object.h"

#include <vector>

namespace etsai {
namespace cpp2dgameengine {
namespace engine {

using std::pair;
using std::vector;

class HitBox : public core::Object {
public:
    HitBox(float xPos, float yPos);

    bool collide(HitBox const *box) const;
    bool inside(float x, float y) const;
    float getRadius() const;

    void addBoundaryPoint(float xOffset, float yOffset);

    virtual void setRotation(float newRotation);
    virtual void rotate(float offset);

protected:
    vector<pair<float, float> > boundaryOffsets;

    
};

}   //namespace core
}   //namespace cpp2dgameengine
}   //namespace etsai

#endif
