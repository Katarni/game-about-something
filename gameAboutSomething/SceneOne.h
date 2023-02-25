#pragma once
#include "Player.h"
#include "Arrow.h"

void hit();

void shot();

void player_move();

void arrows_move(Arrow* arrow);

void arrow_hit_target(Arrow* arrow);

void draw();

void input();

void mechanics();

bool main_scene();
