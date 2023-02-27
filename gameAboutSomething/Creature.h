#pragma once
#include "Player.h"
class Creature {
public:
	Creature(int x, int y);

	void creatures_move(Player* player);

	void creatures_hit(Player* player, bool* hit_active);

	int x;
	int y;
	int health;
	bool dead;
};

