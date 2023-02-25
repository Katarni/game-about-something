#include "Arrow.h"

Arrow::Arrow() {
	x = -100;
	y = -100;
	direction = RIGHT;
	shot = false;
	damage = 1;
}

Arrow::Arrow(int x, int y, int damage, int direction) {
	this->x = x; 
	this->y = y;
	this->damage = damage;
	shot = false;
	switch (direction) {
	case 2:
		this->direction = RIGHT;
		break;
	case 1:
		this->direction = UP;
		break;
	case -1:
		this->direction = LEFT;
		break;
	case -2:
		this->direction = DOWN;
		break;
	}
}

void Arrow::set_direction(int direction) {
	switch (direction) {
	case 2:
		this->direction = RIGHT;
		break;
	case 1:
		this->direction = UP;
		break;
	case -1:
		this->direction = LEFT;
		break;
	case -2:
		this->direction = DOWN;
		break;
	}
}
