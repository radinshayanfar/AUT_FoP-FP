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
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "structures/headers/user.h"
#include "structures/headers/linked_list.h"
#include "includes/headers/list.h"
#include "includes/headers/file.h"
#include "structures/headers/state.h"
#include "includes/headers/leaderboard.h"

#include "includes/debug.h"

// ====================================== //

struct Problem_Node *get_random_problem(struct Problem_Node *list) {

    int problem_list_len = list_count(list);

    int random = rand() % problem_list_len;
    
    for(int i = 0; i < random; i++) {
        list = list->next;
    }
    return list;
    
}

void printlist(struct Problem_Node *list) {

    struct Problem_Node *current = list;
    while (current != NULL) {
        printf("%s", current->problem.text);
        current = current->next;
    }

}

int main() {

    srand(time(NULL));

    struct User user = User_User("Radin Sh");
    user.user_params.people = 60;
    user.user_params.court = 70;

    // struct Problem_Node *problems_list = NULL;
    // read_problems(&problems_list);
    // printf("%s", get_random_problem(problems_list)->problem.choice1.text);
    // printf("%d\n", list_count(problems_list));
    // save_to_file(problems_list, user, IN_GAME);
    // printf("%d\n", restore_from_file(&problems_list, &user));
    // printf("%d\n", user.user_params.court);
    // printlist(problems_list);
    save_to_leaderboard(user);
    print_leaderboard();

    return 0;
}