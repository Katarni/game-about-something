#include "Creature.h"

Creature::Creature(int x, int y, int health) {
	this->x = x;
	this->y = y;
	this->health = health;
	dead = false;
}
