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
#include "../headers/list.h"

struct Problem_Node * new_node(struct Problem problem) {

    struct Problem_Node *new = malloc(sizeof(struct Problem_Node));
    new->problem = problem;
    new->next = NULL;

    return new;

}

void delete_at_index(struct Problem_Node **list, int index) {

    if (index == 0) {
        struct Problem_Node *temp = (*list);
        *list = (*list)->next;
        free(temp);
        return;
    }
    
    struct Problem_Node* current = *list;
    for (int i = 0; i < index - 1; i++, current = current->next) ;

    struct Problem_Node *temp = current->next;
    current->next = current->next->next;
    free(temp);

}

int list_count(struct Problem_Node *list) {
    int i = 0;
    while (list != NULL) {
        i++;
        list = list->next;
    }
    return i;
}