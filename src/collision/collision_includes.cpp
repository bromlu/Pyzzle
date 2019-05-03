#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

static bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
	float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

	if(uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
		return true;
	}

	return false;
}
