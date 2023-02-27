#include "Cat.h"

Cat::Cat(int x, int y, std::string name) {
	this->coordinates_x = x;
	this->coordinates_y = y;
	this->name = name;
	health = 400;
	dead = false;
}

void Cat::help_me_doctor(Player* player) {
	if (player->health <= 45) {
		this->coordinates_x = player->coordinates_x;
		this->coordinates_y = player->coordinates_y;
	}
}

void Cat::help_from_doctor(Player* player, bool* help_active, actions previous_action) {
	if (player->health >= 85) {
		this->coordinates_x = 11;
		this->coordinates_y = 6;
		*help_active = false;
	}

	if (this->coordinates_x == player->coordinates_x && this->coordinates_y == player->coordinates_y) {
		player->health += 1;
	}
	else if (this->coordinates_x - 1 == player->coordinates_x && this->coordinates_y == player->coordinates_y) {
		player->health += 1;
	}
	else if (this->coordinates_x + 1 == player->coordinates_x && this->coordinates_y == player->coordinates_y) {
		player->health += 1;
	}
	else if (this->coordinates_x == player->coordinates_x && this->coordinates_y - 1 == player->coordinates_y) {
		player->health += 1;
	}
	else if (this->coordinates_x == player->coordinates_x && this->coordinates_y + 1 == player->coordinates_y) {
		player->health += 1;
	}
	else if (this->coordinates_x - 1 == player->coordinates_x && this->coordinates_y - 1 == player->coordinates_y) {
		player->health += 1;
	}
	else if (this->coordinates_x + 1 == player->coordinates_x && this->coordinates_y + 1 == player->coordinates_y) {
		player->health += 1;
	}
	else if (this->coordinates_x + 1 == player->coordinates_x && this->coordinates_y - 1 == player->coordinates_y) {
		player->health += 1;
	}
	else if (this->coordinates_x - 1 == player->coordinates_x && this->coordinates_y + 1 == player->coordinates_y) {
		player->health += 1;
	}

	if (*help_active) {
		switch (previous_action)
		{
		case LEFT:
			this->coordinates_x = player->coordinates_x + 1;
			this->coordinates_y = player->coordinates_y;
			break;
		case RIGHT:
			this->coordinates_x = player->coordinates_x - 1;
			this->coordinates_y = player->coordinates_y;
			break;
		case DOWN:
			this->coordinates_x = player->coordinates_x;
			this->coordinates_y = player->coordinates_y - 1;
			break;
		case UP:
			this->coordinates_x = player->coordinates_x;
			this->coordinates_y = player->coordinates_y + 1;
			break;
		}
	}
}
