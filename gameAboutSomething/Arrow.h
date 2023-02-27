#pragma once
struct Arrow {
	Arrow();

	Arrow(int x, int y, int damage, int direction);

	void set_direction(int direction);

	void arrow_move();

	int x;
	int y;
	int damage;
	bool shot;
	enum directions { LEFT, RIGHT, UP, DOWN };
	directions direction;
};

