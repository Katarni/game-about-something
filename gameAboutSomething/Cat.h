#pragma once
#include <string>
#include "Player.h"

class Cat {
public:
	Cat(int x, int y, std::string name);

	void help_me_doctor(Player* player);

	void help_from_doctor(Player* player, bool* help_active, actions previous_action);

	std::string name;
	int coordinates_x;
	int coordinates_y;
	int health;
	bool dead;
};

