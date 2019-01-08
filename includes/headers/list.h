/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include "../../structures/headers/linked_list.h"

#ifndef LIST_H
#define LIST_H

struct Problem_Node * new_node(struct Problem problem);
void delete_at_index(struct Problem_Node **list, int index);
int list_count(struct Problem_Node *list);

#endif