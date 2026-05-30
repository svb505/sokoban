#include "getRandom.h"
#include "vec2.h"
#include <random>
#include <map>

Vec2 getRandomCoordinate(std::map<int,Vec2> allCellules) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> distIdx(0, allCellules.size()-1);

	return allCellules[distIdx(gen)];
}