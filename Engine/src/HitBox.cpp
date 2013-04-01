#include "Cpp2DGameEngine/Engine/HitBox.h"

#include <cmath>

#define ROTATE(rotOffset) \
    for(auto &boundaryOffset: boundaryOffsets) { \
        float xNew, yNew; \
        xNew= boundaryOffset.first * cos(rotOffset) - boundaryOffset.second * sin(rotOffset); \
        yNew= boundaryOffset.first * sin(rotOffset) + boundaryOffset.second * cos(rotOffset); \
        boundaryOffset= make_pair(xNew, yNew); \
    }

namespace etsai {
namespace cpp2dgameengine {
namespace engine {

using std::make_pair;

HitBox::HitBox(float xPos, float yPos) : Object(xPos, yPos, 0) {
}

bool HitBox::collide(HitBox const *box) const {
    bool collided= false;
    auto checkInside= [&collided](HitBox const *left, HitBox const *right) -> void {
        for(auto it= right->boundaryOffsets.begin(); !collided && it != right->boundaryOffsets.end(); it++) {
            collided= left->inside(it->first + right->xPos, it->second + right->yPos);
        }
        collided|= left->inside(right->xPos, right->yPos);
    };

    checkInside(this, box);
    checkInside(box, this);

    return collided;
}

bool HitBox::inside(float x, float y) const {
    size_t i, j= boundaryOffsets.size() - 1;
    bool oddNodes= false;

    for(i= 0; i < boundaryOffsets.size(); i++) {
        float xi, xj, yi, yj;

        xi= boundaryOffsets[i].first + xPos;
        xj= boundaryOffsets[j].first + xPos;
        yi= boundaryOffsets[i].second + yPos;
        yj= boundaryOffsets[j].second + yPos;
        if (((yi < y && yj >= y) || (yj < y && yi >= y)) && (xi <= x || xj <= x)) {
            oddNodes^= (xi + (y - yi) / (yj - yi) * (xj - xi) < x);
        }
        j= i;
    }
    return oddNodes;
}

float HitBox::getRadius() const {
    float maxDistSq, distSq;
    for(auto &boundary: boundaryOffsets) {
        distSq= pow(boundary.first, 2) + pow(boundary.second, 2);
        if (distSq > maxDistSq) {
            maxDistSq= distSq;
        }
    }

    return sqrt(maxDistSq);
}

void HitBox::addBoundaryPoint(float xOffset, float yOffset) {
    boundaryOffsets.push_back(make_pair(xOffset, yOffset));
}

void HitBox::setRotation(float newRotation) {
    float deltaRot= newRotation - rotation;

    Object::setRotation(newRotation);
    ROTATE(deltaRot);
}

void HitBox::rotate(float offset) {
    Object::rotate(offset);
    ROTATE(offset);
}


}
}
}
