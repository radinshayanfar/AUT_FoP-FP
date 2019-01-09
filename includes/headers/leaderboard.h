/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include "../../structures/headers/user.h"

#define LEADERBOARD_SIZE 10

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

int user_compare(const void *u1, const void *u2);
void save_to_leaderboard(struct User user);
void print_leaderboard();

#endif