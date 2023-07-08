#include "Vec2D.hpp"
#include "Utils.hpp"

std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec){
    std::cout << "X: " << vec.mX << ", Y: " << vec.mY << std::endl;
    return consoleOut;
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
