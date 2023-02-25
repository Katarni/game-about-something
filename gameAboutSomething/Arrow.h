#pragma once
struct Arrow {
	Arrow();

	Arrow(int x, int y, int damage, int direction);

	void set_direction(int direction);

	int x;
	int y;
	int damage;
	bool shot;
	enum directions {LEFT, RIGHT, UP, DOWN, STOP};
	directions direction;
};

