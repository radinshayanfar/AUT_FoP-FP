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
#include <ctype.h>

#include "structures/headers/user.h"
#include "structures/headers/linked_list.h"
#include "includes/headers/list.h"
#include "includes/headers/file.h"
#include "structures/headers/state.h"
#include "includes/headers/leaderboard.h"

#include "includes/debug.h"

// ====================================== //

int get_random_problem(struct Problem_Node *list) {

    int problem_list_len = list_count(list);

    int random = rand() % problem_list_len;
    
    return random;
    
}

void get_user_name(char name[]) {

    printf("Please enter your name: ");
    fgets(name, 100 - 1, stdin);

}

void game_start(struct User *user, struct Problem_Node **list) {

    enum State state = restore_from_file(list, user);

    if (state == NOT_SAVED) {
        get_user_name(user->name);
        return;
    }

    char yn_choice, kkp_junk;
    do {
        printf("Do you want to load previously saved game ([Y]es/[N]o): ");
        scanf("%c%c", &yn_choice, &kkp_junk);
        yn_choice = toupper(yn_choice);
        if (yn_choice == 'N') {
            get_user_name(user->name);
            read_problems(list);
            return;
        }
    } while ((yn_choice != 'Y') && (yn_choice != 'N'));
    if (state == LOST) {
        read_problems(list);
    }

    printf("Hello %s", user->name);
}

void use_problem(int index, struct Problem_Node **list, struct User *user, int choice) {

    struct Problem_Node *node = get_at_index(index, *list);

    if (choice == 1) {
        user->user_params.people += node->problem.choice1.effect.people;
        user->user_params.court += node->problem.choice1.effect.court;
        user->user_params.treasury += node->problem.choice1.effect.treasury;
    } else {
        user->user_params.people += node->problem.choice2.effect.people;
        user->user_params.court += node->problem.choice2.effect.court;
        user->user_params.treasury += node->problem.choice2.effect.treasury;
    }

    if (--(node->problem.num) == 0) {
        delete_at_index(list, index);
    }

    if (*list == NULL) {
        read_problems(list);
    }

}

void show_problem(struct Problem_Node **list, struct User *user) {

    int pr_index = get_random_problem(*list);
    struct Problem_Node *problem = get_at_index(pr_index, *list);

    printf("%s", problem->problem.text);
    printf("[1] %s", problem->problem.choice1.text);
    printf("[2] %s", problem->problem.choice2.text);

    char choice, kkp_junk;
    do {
        scanf("%c%c", &choice, &kkp_junk);
        if ((choice == '1') || (choice == '2')) {
            use_problem(pr_index, list, user, choice - '0');
        }
    } while ((choice != '1') && (choice != '2'));

}

int main() {

    srand(time(NULL));

    struct Problem_Node *problems_list = NULL;
    struct User user = User_User("");

    game_start(&user, &problems_list);
    show_problem(&problems_list, &user);

    // printf("%s", get_random_problem(problems_list)->problem.choice1.text);
    // printf("%d\n", list_count(problems_list));
    // save_to_file(problems_list, user, LOST);IN_GAME
    // printf("%d\n", restore_from_file(&problems_list, &user));
    // printf("%d\n", user.user_params.court);
    // printlist(problems_list);
    // save_to_leaderboard(user);
    // print_leaderboard();

    return 0;
}