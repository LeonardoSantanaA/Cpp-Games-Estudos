#include "includes/Vec2D.hpp"

int main( int argc , char **argv ){
  Vec2D aVec(3, 7);
  Vec2D resultVec = 3 * aVec;

  std::cout << resultVec << std::endl;

  return 0;
}

