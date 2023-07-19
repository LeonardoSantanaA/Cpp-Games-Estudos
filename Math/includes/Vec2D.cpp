#include "Vec2D.hpp"
#include "Utils.hpp"
#include <cassert>
#include <cmath>

const Vec2D Vec2D::Zero;

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

Vec2D Vec2D::operator+(const Vec2D& vec) const{
  return Vec2D(mX+ vec.mX, mY + vec.mY);
}

Vec2D Vec2D::operator-(const Vec2D& vec) const{
  return Vec2D(mX - vec.mX, mY - vec.mY);
}

Vec2D& Vec2D::operator+=(const Vec2D& vec){
  *this = *this + vec;
  return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& vec){
  *this = *this - vec;
  return *this;
}

float Vec2D::Mag2() const{
  return Dot(*this);
}

float Vec2D::Mag() const{
  return sqrt(Mag2()); 
}

Vec2D Vec2D::GetUnitVec() const{
  float mag = Mag();
  if(mag > EPSILON){
    return *this / mag;
  }
  return Vec2D::Zero;
}

Vec2D& Vec2D::Normalize(){
  float mag = Mag();
  if(mag > EPSILON){
    *this /= mag;
  }
  return *this;
}

float Vec2D::Distance(const Vec2D vec) const{
  return (vec - *this).Mag();
}

float Vec2D::Dot(const Vec2D& vec) const{
  return mX * vec.mX + mY * vec.mY;
}

Vec2D Vec2D::ProjectOnto(const Vec2D& vec2) const{

  Vec2D unitVec2 = vec2.GetUnitVec();

  float dot = Dot(unitVec2);
  
  return unitVec2 * dot;
}

float Vec2D::AngleBetween(const Vec2D& vec2) const{
  return acosf(GetUnitVec().Dot(vec2.GetUnitVec()));
}

Vec2D Vec2D::Reflect(const Vec2D& normal) const{
  return *this - 2 * ProjectOnto(normal);
}
