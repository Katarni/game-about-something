#pragma once

enum actions { STOP, LEFT, RIGHT, DOWN, UP, SHOT, HIT, HEALTH, TEST };

class Player {
public:
	Player();

	Player(int coordinates_x, int coordinates_y, double health, int damage);

	int coordinates_x;
	int coordinates_y;
	double health;
	int damage;
};

