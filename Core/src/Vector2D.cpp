#include "Cpp2DGameEngine/Core/Vector2D.h"

#include <cmath>

namespace etsai {
namespace cpp2dgameengine {
namespace core {

using std::endl;

Vector2D::Vector2D() : Vector2D(0, 0) {
}

Vector2D::Vector2D(float vx, float vy) : vx(vx), vy(vy) {
}

Vector2D Vector2D::normalize() const {
    int vSize(size());
    return Vector2D(vx/vSize, vy/vSize);
}

float Vector2D::size() const {
    return sqrt(vx * vx + vy * vy);
}

float Vector2D::dot(const Vector2D& rhs) const {
    return vx * rhs.vx + vy * rhs.vy;
}

float Vector2D::angle(const Vector2D& rhs) const {
    return acos(dot(rhs) / (size() * rhs.size()));
}

void Vector2D::print(ostream& os) const {
    os << "(" << vx << ", " << vy << ")";
}

void Vector2D::println(ostream& os) const {
    print(os);
    os << endl;
}

Vector2D& Vector2D::operator +=(const Vector2D& rhs) {
    vx+= rhs.vx;
    vy+= rhs.vy;
    return *this;
}

Vector2D& Vector2D::operator -=(const Vector2D& rhs) {
    vx-= rhs.vx;
    vy-= rhs.vy;
    return *this;
}

Vector2D& Vector2D::operator *=(float scale) {
    vx*= scale;
    vy*= scale;
    return *this;
}

Vector2D& Vector2D::operator <<=(float angle) {
    float newAngle(atan(vy/vx) + angle);
    float vSize(size());

    vx= vSize * cos(newAngle);
    vy= vSize * sin(newAngle);
    return *this;
}

Vector2D& Vector2D::operator >>=(float angle) {
    float newAngle(atan(vy/vx) - angle);
    float vSize(size());

    vx= vSize * cos(newAngle);
    vy= vSize * sin(newAngle);
    return *this;
}

bool Vector2D::operator ==(const Vector2D& rhs) const {
    return (vx == rhs.vx && vy == rhs.vy);
}

bool Vector2D::operator !=(const Vector2D& rhs) const {
    return (vx != rhs.vx || vy != rhs.vy);
}

Vector2D operator +(const Vector2D& lhs, const Vector2D& rhs) {
    return Vector2D(lhs.vx + rhs.vx, lhs.vy + rhs.vy);
}

Vector2D operator -(const Vector2D& lhs, const Vector2D& rhs) {
    return Vector2D(lhs.vx - rhs.vx, lhs.vy - rhs.vy);
}

Vector2D operator *(const Vector2D& lhs, float scale) {
    return Vector2D(lhs.vx * scale, lhs.vy * scale);
}

Vector2D operator *(float scale, const Vector2D& rhs) {
    return Vector2D(scale * rhs.vx, scale * rhs.vy);
}

Vector2D operator <<(const Vector2D& lhs, float angle) {
    float newAngle(atan(lhs.vy/lhs.vx) + angle);
    float vSize(lhs.size());

    return Vector2D(vSize * cos(newAngle), vSize * sin(newAngle));
}

Vector2D operator >>(const Vector2D& lhs, float angle) {
    float newAngle(atan(lhs.vy/lhs.vx) - angle);
    float vSize(lhs.size());

    return Vector2D(vSize * cos(newAngle), vSize * sin(newAngle));
}

ostream& operator <<(ostream& os, const Vector2D& rhs) {
    rhs.print(os);
    return os;
}

}   //namespace core
}   //namespace cpp2dgameengine
}   //namespace etsai
