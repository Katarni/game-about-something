#pragma once
#include "Player.h"
#include "Arrow.h"
#include "Sheeps.h"
#include "Creature.h"
#include "Cat.h"

void test();

void hit();

void shot();

void player_move();

void sheeps_move(Sheeps* sheep);

void creatures_move(Creature* cteature);

void arrow_hit_target(Arrow* arrow);

void is_step_free();

void draw();

void input();

void mechanics();

bool main_scene();
