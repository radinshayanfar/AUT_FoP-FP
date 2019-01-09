/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include "stdlib.h"
#include "../../structures/headers/linked_list.h"

#include "../debug.h"

#ifndef LIST_H
#define LIST_H

struct Problem_Node * new_node(struct Problem problem);
void delete_at_index(struct Problem_Node **list, int index);
void list_delete_all(struct Problem_Node **list);
struct Problem_Node *get_at_index(int index, struct Problem_Node *list);
int list_count(struct Problem_Node *list);

#endif