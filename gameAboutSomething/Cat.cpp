#include "Cat.h"

Cat::Cat(int x, int y, std::string name) {
	this->coordinates_x = x;
	this->coordinates_y = y;
	this->name = name;
	health = 400;
	dead = false;
}
