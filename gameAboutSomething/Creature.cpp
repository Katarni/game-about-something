#include "Creature.h"
#include <iostream>

Creature::Creature(int x, int y) {
	this->x = x;
	this->y = y;
	health = 15;
	dead = false;
}

void Creature::creatures_move(Player* player) {
	int is_move = rand() % 100;
	if (is_move <= 8) {
		if (this->x >= player->coordinates_x) {
			if (this->y >= player->coordinates_y) {
				if (this->x - player->coordinates_x >= this->y - player->coordinates_y) {
					this->x -= 1;
				}
				else {
					this->y -= 1;
				}
			}
			else {
				if (this->x - player->coordinates_x >= player->coordinates_y - this->y) {
					this->x -= 1;
				}
				else {
					this->y += 1;
				}
			}
		}
		else {
			if (this->y >= player->coordinates_y) {
				if (player->coordinates_x - this->x >= this->y - player->coordinates_y) {
					this->x += 1;
				}
				else {
					this->y -= 1;
				}
			}
			else {
				if (player->coordinates_x - this->x >= player->coordinates_y - this->y) {
					this->x += 1;
				}
				else {
					this->y += 1;
				}
			}
		}
	}
}

void Creature::creatures_hit(Player* player, bool* hit_active) {
	if (this->x == player->coordinates_x && this->y == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else if (this->x - 1 == player->coordinates_x && this->y == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else if (this->x + 1 == player->coordinates_x && this->y == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else if (this->x == player->coordinates_x && this->y - 1 == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else if (this->x == player->coordinates_x && this->y + 1 == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else if (this->x - 1 == player->coordinates_x && this->y - 1 == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else if (this->x + 1 == player->coordinates_x && this->y + 1 == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else if (this->x + 1 == player->coordinates_x && this->y - 1 == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else if (this->x - 1 == player->coordinates_x && this->y + 1 == player->coordinates_y) {
		player->health -= 0.25;
		*hit_active = true;
	}
	else {
		*hit_active = false;
	}
}
