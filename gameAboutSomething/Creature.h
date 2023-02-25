#pragma once
struct Creature {
	Creature(int x, int y, int health);

	int x;
	int y;
	int health;
	bool dead;
};

