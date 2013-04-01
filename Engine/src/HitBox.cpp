#include "Cpp2DGameEngine/Engine/HitBox.h"

#include <cmath>

namespace etsai {
namespace cpp2dgameengine {
namespace engine {

using std::make_pair;

HitBox::HitBox(double xPos, double yPos) : Object(xPos, yPos, 0, 0) {
}

bool HitBox::collide(HitBox const *box) const {
    bool collided= false;

    for(auto it= box->boundaryOffsets.begin(); !collided && it != box->boundaryOffsets.end(); it++) {
        collided= inside(it->first + box->xPos, it->second + box->yPos);
    }
    collided|= inside(box->xPos, box->yPos);
    for(auto it= boundaryOffsets.begin(); !collided && it != boundaryOffsets.end(); it++) {
        collided= box->inside(it->first + xPos, it->second + yPos);
    }
    collided|= box->inside(xPos, yPos);
    return collided;
}

bool HitBox::inside(double x, double y) const {
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

double HitBox::getRadius() const {
    double maxDistSq, distSq;
    for(auto &boundary: boundaryOffsets) {
        distSq= pow(boundary.first, 2) + pow(boundary.second, 2);
        if (distSq > maxDistSq) {
            maxDistSq= distSq;
        }
    }

    return sqrt(maxDistSq);
}

void HitBox::addBoundaryPoint(double xOffset, double yOffset) {
    boundaryOffsets.push_back(make_pair(xOffset, yOffset));
}

void HitBox::rotate(double radians) {
    Object::rotate(radians);
    for(auto &offset: boundaryOffsets) {
        double xNew, yNew;
        xNew= offset.first * cos(radians) - offset.second * sin(radians);
        yNew= offset.first * sin(radians) + offset.second * cos(radians);
        offset= make_pair(xNew, yNew);
    }
}


}
}
}
