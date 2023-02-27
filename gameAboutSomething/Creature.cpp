#include "Creature.h"

Creature::Creature(int x, int y) {
	this->x = x;
	this->y = y;
	health = 15;
	dead = false;
}
