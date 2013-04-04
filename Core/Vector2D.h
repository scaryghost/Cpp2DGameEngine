#ifndef ETSAI_CPP2DGAMEENGINE_CORE_VECTOR2D
#define ETSAI_CPP2DGAMEENGINE_CORE_VECTOR2D

#include <ostream>

namespace etsai {
namespace cpp2dgameengine {
namespace core {

using std::ostream;

class Vector2D {
public:
    Vector2D();
    Vector2D(float vx, float vy);

    Vector2D normalize() const;
    float size() const;
    float dot(const Vector2D& rhs) const;
    float angle(const Vector2D& rhs) const;
    void print(ostream& os) const;
    void println(ostream& os) const;

    Vector2D& operator +=(const Vector2D& rhs);
    Vector2D& operator -=(const Vector2D& rhs);
    Vector2D& operator *=(float scale);
    Vector2D& operator <<=(float angle);
    Vector2D& operator >>=(float angle);

    bool operator ==(const Vector2D& rhs) const;
    bool operator !=(const Vector2D& rhs) const;

    float vx, vy;
};

Vector2D operator +(const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator -(const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator *(const Vector2D& lhs, float scale);
Vector2D operator *(float scale, const Vector2D& rhs);
Vector2D operator <<(const Vector2D& lhs, float angle);
Vector2D operator >>(const Vector2D& lhs, float angle);

ostream& operator <<(ostream& os, const Vector2D& rhs);

}   //namespace core
}   //namespace cpp2dgameengine
}   //namespace etsai

#endif
