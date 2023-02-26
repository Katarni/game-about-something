#pragma once
#include "Player.h"
#include "Arrow.h"
#include "Sheeps.h"
#include "Cat.h"

void test();

void hit();

void shot();

void player_move();

void help_me_doctor();

void help_from_doctor();

void sheeps_move();

void arrows_move(Arrow* arrow);

void arrow_hit_target(Arrow* arrow);

void is_step_free();

void draw();

void input();

void mechanics();

bool main_scene();
