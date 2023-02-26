#pragma once
#include <string>
class Cat {
public:
	Cat(int x, int y, std::string name);

	std::string name;
	int x;
	int y;
	int health;
	bool dead;
};

