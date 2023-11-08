#include "Utils.h"
#include <cmath>
#include <cassert>
#include <random>

bool IsEqual(float x, float y){
  return fabsf(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y){
  return x > y || IsEqual(x, y);
}


bool IsLessThanOrEqual(float x, float y){
  return x < y || IsEqual(x, y);
}

int GetRandomNumber(int n1, int n2){
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_int_distribution<int> uniform_dist(n1, n2);
	return uniform_dist(re);
}

float GetRandomNumberFloat(float n1, float n2) {
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_real_distribution<float> uniform_dist(n1, n2);
	return uniform_dist(re);
}