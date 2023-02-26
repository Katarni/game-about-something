#pragma once
class Creature {
public:
	Creature(int x, int y, int health);

	int x;
	int y;
	int health;
	bool dead;
};

