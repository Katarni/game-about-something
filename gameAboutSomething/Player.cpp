#include "Player.h"

Player::Player() {
	this->coordinates_x = 0;
	this->coordinates_y = 0;
	this->health = 100;
	this->damage = 2;
}

Player::Player(int coordinates_x, int coordinates_y, int health, int damage) {
	this->coordinates_x = coordinates_x;
	this->coordinates_y = coordinates_y;
	this->health = health;
	this->damage = damage;
}