/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/list.h"
#include "../../structures/headers/state.h"
#include "../../structures/headers/linked_list.h"
#include "../../structures/headers/user.h"
#include "../../structures/headers/problem.h"

#include "../debug.h"

#ifndef FILE_H
#define FILE_H

void save_to_file(struct Problem_Node *list, struct User user, enum State state, int last_problem_index);
enum State restore_from_file(struct Problem_Node **list, struct User *user, int *last_problem_index);
struct Problem file_to_problem(char ch_file_name[]);
void read_problems(struct Problem_Node **list);

#endif