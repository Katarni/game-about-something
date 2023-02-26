#pragma once
#include <string>
class Cat {
public:
	Cat(int x, int y, std::string name);

	std::string name;
	int coordinates_x;
	int coordinates_y;
	int health;
	bool dead;
};

