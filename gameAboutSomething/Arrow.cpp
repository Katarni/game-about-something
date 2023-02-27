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
	default:
		this->direction = UP;
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

void Arrow::arrow_move() {
	switch (this->direction) {
	case LEFT:
		this->x -= 1; // здесь все правильно, иначе не работает
		break;
	case RIGHT:
		this->x += 1; // здесь все правильно, иначе не работает
		break;
	case UP:
		this->y -= 1; // здесь не работает
		break;
	case DOWN:
		this->y += 1; // здесь все правильно, иначе не работает
		break;
	}
}
