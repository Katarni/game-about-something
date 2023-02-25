﻿#include "SceneOne.h"
#include "Player.h"
#include <iostream>
#include <conio.h>
#include "Doors.h"
#include "Walls.h"
#include "Creature.h"

using namespace std;

// размеры карты
int win_width = 90;
int win_height = 25;

Player player_one(win_width / 2, win_height / 2, 100, 2); // создание игрока

// список действий
enum actions { STOP, LEFT, RIGHT, DOWN, UP, SHOT, HIT };
actions action = STOP;
actions previous_action;

bool game_end = false;

Arrow list_of_arrows[] = {
	Arrow(), Arrow(), Arrow(),
	Arrow(), Arrow(), Arrow(),
	Arrow(), Arrow(), Arrow(),
	Arrow(), Arrow(), Arrow(),
	Arrow(), Arrow(), Arrow()
};

Doors list_of_doors[] = { 
	Doors(13, 10), 
	Doors(14, 10), 
	Doors(15, 10) 
};

Walls list_of_walls[] = {
	Walls(10, 5), Walls(11, 5), Walls(12, 5),
	Walls(13, 5), Walls(14, 5), Walls(15, 5),
	Walls(16, 5), Walls(17, 5), Walls(18, 5),
	Walls(10, 6), Walls(10, 7), Walls(10, 8),
	Walls(10, 9), Walls(18, 6), Walls(18, 7),
	Walls(18, 8), Walls(18, 9), Walls(11, 9),
	Walls(12, 9), Walls(16, 9), Walls(17, 9),
	Walls(12, 10), Walls(16, 10)
};

Creature list_of_creatures[] = {
	Creature(70, 15, 10),
	Creature(55, 5, 10),
	Creature(30, 20, 10)
};

// удар
void hit() {
	int creature_x = 0;
	int creature_y = 0;

	switch (previous_action){
	case LEFT:
		creature_x = player_one.coordinates_x - 1;
		creature_y = player_one.coordinates_y;
		break;
	case RIGHT:
		creature_x = player_one.coordinates_x + 1;
		creature_y = player_one.coordinates_y;
		break;
	case DOWN:
		creature_x = player_one.coordinates_x;
		creature_y = player_one.coordinates_y + 1;
		break;
	case UP:
		creature_x = player_one.coordinates_x;
		creature_y = player_one.coordinates_y - 1;
		break;
	}

	for (int i = 0; i < sizeof(list_of_doors); i++) {
		if (list_of_doors[i].x == creature_x && list_of_doors[i].y == creature_y) {
			list_of_doors[i].health -= player_one.damage;
		}
	}
}

void shot() {
	int direction = 0;
	switch (previous_action) 
	{
	case LEFT:
		direction = -1;
		break;
	case RIGHT:
		direction = 2;
		break;
	case DOWN:
		direction = -2;
		break;
	case UP:
		direction = 1;
		break;
	}

	for (int i = 0; i < sizeof(list_of_arrows); i++) {
		if (!list_of_arrows[i].shot) {
			list_of_arrows[i].shot = true;
			list_of_arrows[i].set_direction(direction);
			list_of_arrows[i].x = player_one.coordinates_x;
			list_of_arrows[i].y = player_one.coordinates_y;
			return;
		}
	}
}

// передвижение игрока
void player_move() {
	switch (action) {
	case LEFT:
		player_one.coordinates_x--;
		action = STOP;
		previous_action = LEFT;
		break;
	case RIGHT:
		player_one.coordinates_x++;
		previous_action = RIGHT;
		action = STOP;
		break;
	case DOWN:
		player_one.coordinates_y++;
		previous_action = DOWN;
		action = STOP;
		break;
	case UP:
		player_one.coordinates_y--;
		previous_action = UP;
		action = STOP;
		break;
	case SHOT:
		shot();
		action = STOP;
		break;
	case HIT:
		hit();
		action = STOP;
		break;
	}
}

// полет стрел
void arrows_move(Arrow* arrow) {
	switch (arrow->direction) {
	case LEFT:
		arrow->x += 1; // здесь все правильно, иначе не работает
		break;
	case RIGHT:
		arrow->y -= 1; // здесь все правильно, иначе не работает
		break;
	case UP:
		arrow->x -= 1; // здесь не работает
		break;
	case DOWN:
		arrow->y += 1; // здесь все правильно, иначе не работает
		break;
	}
}

// проверка на попадание стрел
void arrow_hit_target(Arrow* arrow) /* Здесь что - то не так, отображение ломается, смотреть коментарий вконце */ {

	// координаты предпологаемой цели 
	int target_x;
	int target_y;
	
	switch (arrow->direction) {
	case LEFT:
		target_x = arrow->x - 1;
		break;
	case RIGHT:
		target_x = arrow->x + 1;
		break;
	case UP:
		target_y = arrow->y - 1;
		break;
	case DOWN:
		target_y = arrow->y + 1;
		break;
	}
	
	// проверки на соответсвие
	for (int i = 0; i < sizeof(list_of_doors); i++) {
		if (list_of_doors[i].x == arrow->x && list_of_doors[i].y == arrow->y && !list_of_doors[i].broken) {
			arrow->x = -100;
			arrow->y = -100;
			arrow->shot = false;
			list_of_doors[i].health -= arrow->damage;
			return;
		}
	}
	
	for (int i = 0; i < sizeof(list_of_walls); i++) {
		if (list_of_walls[i].x == arrow->x && list_of_walls[i].y == arrow->y) {
			arrow->x = -100;
			arrow->y = -100;
			arrow->shot = false;
			return;
		}
	}
	
	if (arrow->x < 1 || arrow->y < 0 || arrow->x > win_width - 1 || arrow->y > win_height - 1) {
		arrow->x = -100;
		arrow->y = -100;
		arrow->shot = false;
		return;
	}
}

void draw() {
	system("cls");

	for (int i = 0; i < win_width; i++) /* вывод верхней границы */ {
		cout << "_";
	}
	cout << endl;

	for (int i = 0; i < win_height; i++) {
		for (int j = 0; j < win_width + 1; j++) {
			if (j == 0 || j == win_width) /* вывод боковых границ */ {
				cout << "|";
			}

			else if (i == player_one.coordinates_y && j == player_one.coordinates_x) /* печать игрока */ {
				cout << "Y";
			}

			else {
				bool printed = false;

				// рисуем стены
				for (int k = 0; k < sizeof(list_of_walls); k++) {
					if (i == list_of_walls[k].y && j == list_of_walls[k].x) {
						cout << "#";
						printed = true;
					}
				}

				// рисуем двери
				if (!printed) {
					for (int k = 0; k < sizeof(list_of_doors); k++) {
						if (i == list_of_doors[k].y && j == list_of_doors[k].x) {
							if (list_of_doors[k].broken) {
								cout << "~";
								printed = true;
							}
							else if (!list_of_doors[k].broken) {
								cout << "*";
								printed = true;
							}
						}
					}
				}

				// рисуем существ
				if (!printed) {
					for (int k = 0; k < sizeof(list_of_creatures); k++) {
						if (j == list_of_creatures[k].x && list_of_creatures[k].y == i) {
							if (!list_of_creatures[k].dead) {
								cout << "M";
								printed = true;
							}
						}
					}
				}

				// рисуем стрелы
				if (!printed) {
					for (int k = 0; k < sizeof(list_of_arrows); k++) /* и здесь тоже отображение валится, смотреть кометрарий в конце */ {
						if (i == list_of_arrows[k].y && j == list_of_arrows[k].x && list_of_arrows[k].shot) {
							cout << "o";
							printed = true;
						}
					}
				}

				if (!printed) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < win_width; i++) /* вывод нижней границы*/ {
		cout << "_";
	}
	cout << endl;
}

void input() {
	// считывание нажатий клавиш
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			action = LEFT;
			break;
		case 'w':
			action = UP;
			break;
		case 'd':
			action = RIGHT;
			break;
		case 's':
			action = DOWN;
			break;
		case 13:
			action = HIT;
			break;
		case 8:
			action = SHOT;
			break;
		}
	}
}

void mechanics() {
	if (player_one.health <= 0) {
		game_end = true;
	}

	for (int i = 0; i < sizeof(list_of_doors); i++) {
		if (list_of_doors[i].health <= 0) {
			list_of_doors[i].broken = true;
		}
	}

	player_move();

	// проверка на границы карты
	if (player_one.coordinates_x < 1) {
		player_one.coordinates_x = 1;
	}
	if (player_one.coordinates_y < 0) {
		player_one.coordinates_y = 0;
	}
	if (player_one.coordinates_x > win_width - 1) {
		player_one.coordinates_x = win_width - 1;
	}
	if (player_one.coordinates_y > win_height - 1) {
		player_one.coordinates_y = win_height - 1;
	}

	// проверка на стены зданий
	for (int i = 0; i < 23; i++) {
		if (list_of_walls[i].x == player_one.coordinates_x && list_of_walls[i].y == player_one.coordinates_y) {
			switch (previous_action)
			{
			case LEFT:
				player_one.coordinates_x++;
				break;
			case RIGHT:
				player_one.coordinates_x--;
				break;
			case DOWN:
				player_one.coordinates_y--;
				break;
			case UP:
				player_one.coordinates_y++;
				break;
			}
		}
	}

	// проверка на двери
	for (int i = 0; i < sizeof(list_of_doors); i++) {
		if (list_of_doors[i].x == player_one.coordinates_x && list_of_doors[i].y == player_one.coordinates_y) {
			if (!list_of_doors[i].broken) /* дверь не сломана */ {
				switch (previous_action)
				{
				case LEFT:
					player_one.coordinates_x++;
					break;
				case RIGHT:
					player_one.coordinates_x--;
					break;
				case DOWN:
					player_one.coordinates_y--;
					break;
				case UP:
					player_one.coordinates_y++;
					break;
				}
			}
		}
	}
	
	for (int i = 0; i < sizeof(list_of_arrows); i++) {
		if (list_of_arrows[i].shot) {
			arrow_hit_target(&list_of_arrows[i]);
		}
	}

	for (int i = 0; i < sizeof(list_of_arrows); i++) {
		if (list_of_arrows[i].shot) {
			arrows_move(&list_of_arrows[i]);
		}
	}
}

bool main_scene() {
	while (!game_end) {
		draw();
		input();
		mechanics();
	}
	if (player_one.health > 0) {
		return true;
	}
	return false;
}

/*
	Ошибочки:
		* метод arrow_hit_target() ломает отображение стен и еще чего-то
		* в методе drow() печать снарядов иногда печатает символы '~' вместо 'o'
		* объекты типа Creatures выводятся методом drow(), как двери, при смерти объекта он меняет облик на сломанную дверь,
			при этом свойства объекта, такие как размер здоровья не соответствует объекту Creatures 
		* стрелы нехотят летать вверх
*/