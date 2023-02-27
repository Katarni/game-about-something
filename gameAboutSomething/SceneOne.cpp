#include "SceneOne.h"
#include "Player.h"
#include <iostream>
#include <conio.h>

using namespace std;

// размеры карты
int win_width = 90;
int win_height = 25;

Player player_one(win_width / 2, win_height / 2, 100, 2); // создание игрока

Cat doctor(11, 6, "Doctor"); // создание котика

// список действий
actions action = STOP;
actions previous_action;

bool game_end = false;
bool help_active = false;
bool hit_active = false;
bool need_help = false;

unsigned free_arrows = 15;

Arrow list_of_arrows[] = {
	Arrow(), Arrow(), Arrow(),
	Arrow(), Arrow(), Arrow(),
	Arrow(), Arrow(), Arrow(),
	Arrow(), Arrow(), Arrow(),
	Arrow(), Arrow(), Arrow()
};

int doors_coordinates_x[] = { 13, 14, 15 };
int doors_coordinates_y[] = { 9, 9, 9 };
int doors_health[] = { 5, 5, 5 };
bool doors_broken[] = { false, false, false };

// меняешь координаты? а циклы поменять не забыл?
int walls_coordinates_x[] = {
	10, 11, 12, 13, 14, 15, 16, 17, 18, 
	10, 10, 10, 10, 
	18, 18, 18, 18, 
	11, 12, 16, 17
};
int walls_coordinates_y[] = { 
	5, 5, 5, 5, 5, 5, 5, 5, 5, 
	6, 7, 8, 9, 
	6, 7, 8, 9, 
	9, 9, 9, 9
};

int fences_coordinates_x[] = {
	8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
	25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
	9, 10, 11, 12, 13, 14, 15, 16, 17, 18
};
int fences_coordinates_y[] = {
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  
	4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
	13, 13, 13, 13, 13, 13, 13, 13, 13, 13
};

Sheeps first_sheep(22, 11);
Sheeps second_sheep(19, 12);

Sheeps list_of_sheeps[] = {
	first_sheep, second_sheep
};

Creature first_creature(70, 15);
Creature second_creature(55, 5);
Creature third_creature(30, 20);

Creature list_of_creatures[] = {
	first_creature, second_creature, third_creature
};

void test() {
	player_one.health = 20;
}

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

	for (int i = 0; i < 3; i++) {
		if (doors_coordinates_x[i] == creature_x && doors_coordinates_y[i] == creature_y) {
			doors_health[i] -= player_one.damage;
		}
	}
}

void shot() {
	if (free_arrows > 0) {
		int direction = 0;
		switch (previous_action)
		{
		case RIGHT:
			direction = 2;
			break;
		case DOWN:
			direction = -2;
			break;
		case UP:
			direction = 1;
			break;
		case LEFT:
			direction = -1;
			break;
		}

		for (int i = 0; i < sizeof(list_of_arrows); i++) {
			if (!list_of_arrows[i].shot) {
				free_arrows--;
				list_of_arrows[i].shot = true;
				list_of_arrows[i].set_direction(direction);
				list_of_arrows[i].x = player_one.coordinates_x;
				list_of_arrows[i].y = player_one.coordinates_y;
				return;
			}
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
	case HEALTH:
		help_active = true;
		doctor.help_me_doctor(&player_one);
		action = STOP;
		break;
	case TEST:
		test();
		action = STOP;
		break;
	}
}

// овечки тоже ходят, но не всегда
void sheeps_move(Sheeps* sheep) {
	int is_move = rand() % 100;
	if (is_move >= 75) {
		int direction = rand() % 4;

		switch (direction)
		{
		case 0:
			sheep->x += 1;
			break;
		case 1:
			sheep->x -= 1;
			break;
		case 2:
			sheep->y += 1;
			break;
		case 3:
			sheep->y -= 1;
			break;
		}
	}
}

// проверка на попадание стрел
void arrow_hit_target(Arrow* arrow) {

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

	// двери
	for (int i = 0; i < 3; i++) {
		if (doors_coordinates_x[i] == arrow->x && doors_coordinates_y[i] == arrow->y && !doors_broken[i]) {
			arrow->x = -100;
			arrow->y = -100;
			arrow->shot = false;
			doors_health[i] -= arrow->damage;
			return;
		}
	}
	
	// стены
	for (int i = 0; i < 21; i++) {
		if (walls_coordinates_x[i] == arrow->x && walls_coordinates_y[i] == arrow->y) {
			arrow->x = -100;
			arrow->y = -100;
			arrow->shot = false;
			return;
		}
	}

	// заборы
	for (int i = 0; i < 48; i++) {
		if (fences_coordinates_x[i] == arrow->x && fences_coordinates_y[i] == arrow->y) {
			arrow->x = -100;
			arrow->y = -100;
			arrow->shot = false;
			return;
		}
	}

	// существа
	for (int i = 0; i < 3; i++) {
		if (list_of_creatures[i].x == arrow->x && list_of_creatures[i].y == arrow->y && !list_of_creatures[i].dead) {
			arrow->x = -100;
			arrow->y = -100;
			arrow->shot = false;
			list_of_creatures[i].health -= arrow->damage;
			return;
		}
	}
	
	// границы
	if (arrow->x < 1 || arrow->y < 0 || arrow->x > win_width - 1 || arrow->y > win_height - 1) {
		arrow->x = -100;
		arrow->y = -100;
		arrow->shot = false;
		return;
	}
}

void is_step_free() {

	// Игрок

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
	for (int i = 0; i < 21; i++) {
		if (walls_coordinates_x[i] == player_one.coordinates_x && walls_coordinates_y[i] == player_one.coordinates_y) {
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
	for (int i = 0; i < 3; i++) {
		if (doors_coordinates_x[i] == player_one.coordinates_x && doors_coordinates_y[i] == player_one.coordinates_y) {
			if (!doors_broken[i]) /* дверь не сломана */ {
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

	// проверка на забор
	for (int i = 0; i < 48; i++) {
		if (fences_coordinates_x[i] == player_one.coordinates_x && fences_coordinates_y[i] == player_one.coordinates_y) {
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

	// Овечки

	for (int j = 0; j < 2; j++) {
		if (list_of_sheeps[j].x < 1) {
			list_of_sheeps[j].x = 1;
		}
		if (list_of_sheeps[j].y < 0) {
			list_of_sheeps[j].y = 0;
		}
		if (list_of_sheeps[j].x > win_width - 1) {
			list_of_sheeps[j].x = win_width - 1;
		}
		if (list_of_sheeps[j].y > win_height - 1) {
			list_of_sheeps[j].y = win_height - 1;
		}

		// проверка на стены зданий
		for (int i = 0; i < 21; i++) {
			if (walls_coordinates_x[i] == list_of_sheeps[j].x && walls_coordinates_y[i] == list_of_sheeps[j].y) {
				sheeps_move(&list_of_sheeps[j]);
			}
		}

		// проверка на двери
		for (int i = 0; i < 3; i++) {
			if (doors_coordinates_x[i] == list_of_sheeps[j].x && doors_coordinates_y[i] == list_of_sheeps[j].y) {
				if (!doors_broken[i]) /* дверь не сломана */ {
					sheeps_move(&list_of_sheeps[j]);
				}
			}
		}
	}
}

void draw() {
	system("cls");

	cout << fixed;
	cout.precision(2);

	if (need_help) {
		system("color 04");
	}
	else if (hit_active) {
		system("color 0C");
	}
	else if (help_active) {
		system("color 02");
	}
	else {
		system("color 07");
	}

	for (int i = 0; i < win_width; i++) /* вывод верхней границы */ {
		cout << "_";
	}
	cout << endl;

	for (int i = 0; i < win_height; i++) {
		for (int j = 0; j < win_width + 1; j++) {
			if (j == 0 || j == win_width) /* вывод боковых границ */ {
				cout << "|";
				if (j == win_width && i == 1) {
					cout << "     Health: " << player_one.health;
				}
			}

			else if (i == player_one.coordinates_y && j == player_one.coordinates_x) /* печать игрока */ {
				cout << "Y";
			}

			else if (i == doctor.coordinates_y && j == doctor.coordinates_x) /* печать котика */ {
				cout << "@";
			}

			else {
				bool printed = false;

				if (!printed) {
					for (int k = 0; k < 48; k++) /* вывод забора */ {
						if (i == fences_coordinates_y[k] && j == fences_coordinates_x[k]) {
							cout << "\\";
							printed = true;
						}
					}
				}

				// рисуем стены
				if (!printed) {
					for (int k = 0; k < 21; k++) {
						if (i == walls_coordinates_y[k] && j == walls_coordinates_x[k]) {
							cout << "#";
							printed = true;
						}
					}
				}
				
				// рисуем двери
				if (!printed) {
					for (int k = 0; k < 3; k++) {
						if (i == doors_coordinates_y[k] && j == doors_coordinates_x[k]) {
							if (doors_broken[k]) {
								cout << "~";
								printed = true;
							}
							else {
								cout << "\"";
								printed = true;
							}
						}
					}
				}

				// рисуем овечек
				if (!printed) {
					for (int k = 0; k < 2; k++) {
						if (j == list_of_sheeps[k].x && i == list_of_sheeps[k].y && !list_of_sheeps[k].dead) {
							cout << "*";
							printed = true;
						}
					}
				}

				
				// рисуем существ
				if (!printed) {
					for (int k = 0; k < 3; k++) {
						if (j == list_of_creatures[k].x && list_of_creatures[k].y == i) {
							if (!list_of_creatures[k].dead) {
								cout << "!";
								printed = true;
							}
						}
					}
				}

				// рисуем стрелы
				if (!printed) {
					for (int k = 0; k < sizeof(list_of_arrows); k++) {
						if (i == list_of_arrows[k].y && j == list_of_arrows[k].x && list_of_arrows[k].shot) {
							switch (list_of_arrows[k].direction)
							{
							case LEFT:
								cout << ">";
								break;
							case RIGHT:
								cout << "^";
								break;
							case UP:
								cout << "<";
								break;
							case DOWN:
								cout << "v";
								break;
							default:
								cout << " ";
								break;
							}
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
		case 'h':
			action = HEALTH;
			break;
		case 't':
			action = TEST;
			break;
		}
	}
}

void mechanics() {
	if (player_one.health <= 0) {
		game_end = true;
	}

	if (player_one.health <= 25) {
		need_help = true;
	}
	else {
		need_help = false;
	}

	for (int i = 0; i < 3; i++) {
		if (doors_health[i] <= 0) {
			doors_broken[i] = true;
		}
	}

	doctor.help_from_doctor(&player_one, &help_active, previous_action);

	player_move();

	for (int i = 0; i < 3; i++) {
		if (!list_of_creatures[i].dead) {
			list_of_creatures[i].creatures_move(&player_one);
			list_of_creatures[i].creatures_hit(&player_one, &hit_active);
		}
	}

	for (int i = 0; i < 2; i++) {
		if (!list_of_sheeps[i].dead) {
			sheeps_move(&list_of_sheeps[i]);
		}
	}

	is_step_free();
	
	for (int i = 0; i < sizeof(list_of_arrows); i++) {
		if (list_of_arrows[i].shot) {
			arrow_hit_target(&list_of_arrows[i]);
		}
	}

	for (int i = 0; i < sizeof(list_of_arrows); i++) {
		if (list_of_arrows[i].shot) {
			list_of_arrows[i].arrow_move();
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
		* стрелы нехотят летать влево

	Коментарии:
		* во всех преборных циклах указаны значения длины списков константой, а не функцией, потому что иначе некорректно отображаются
	
*/