#include "Vec2D.hpp"
#include "Utils.hpp"
#include <cassert>
#include <cmath>

std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec){
    std::cout << "X: " << vec.mX << ", Y: " << vec.mY << std::endl;
    return consoleOut;
}

Vec2D operator*(float scale, const Vec2D& vec){
  return vec * scale;
}

bool Vec2D::operator==(const Vec2D& vec) const{
  return IsEqual(mX, vec.mX) && IsEqual(mY, vec.mY);
}

bool Vec2D::operator!=(const Vec2D& vec) const{
  return !(*this == vec);;
}

Vec2D Vec2D::operator-() const{
  return Vec2D(-mX, -mY);
}

Vec2D Vec2D::operator*(float scale) const{
  return Vec2D(scale * mX, scale * mY);
}

Vec2D Vec2D::operator/(float scale) const{
  assert(fabsf(scale) > EPSILON);
  return Vec2D(mX / scale, mY/ scale);
}

Vec2D& Vec2D::operator*=(float scale){
  *this = *this * scale;
  return *this;
}

Vec2D& Vec2D::operator/=(float scale){
  assert(fabsf(scale) > EPSILON);
  *this = *this / scale;
  return *this;
}
