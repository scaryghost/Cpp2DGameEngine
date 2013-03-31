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
    HitBox(double xPos, double yPos);

    bool collide(HitBox const *box) const;
    bool inside(double x, double y) const;
    double getRadius() const;

    void addBoundaryPoint(double xOffset, double yOffset);

    virtual void rotate(double radians);
protected:
    vector<pair<double, double> > boundaryOffsets;
};

}   //namespace core
}   //namespace cpp2dgameengine
}   //namespace etsai

#endif
