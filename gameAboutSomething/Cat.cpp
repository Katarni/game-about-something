#include "Cat.h"

Cat::Cat(int x, int y, std::string name) {
	this->x = x;
	this->y = y;
	this->name = name;
	health = 400;
	dead = false;
}
