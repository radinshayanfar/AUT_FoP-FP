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

#include "../../structures/headers/state.h"
#include "../../structures/headers/linked_list.h"
#include "../../structures/headers/user.h"

#ifndef FILE_H
#define FILE_H

void save_to_file(struct Problem_Node *list, struct User user, enum State state);
enum State restore_from_file(struct Problem_Node **list, struct User *user);
struct Problem file_to_problem(char ch_file_name[]);
void read_problems(struct Problem_Node **list);

#endif