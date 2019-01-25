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
#include "structures/headers/state.h"
#include "includes/headers/leaderboard.h"
#include "includes/headers/list.h"
#include "includes/headers/file.h"

#include "includes/debug.h"

// ====================================== //

int get_random_problem(struct Problem_Node *list) {

    int problem_list_len = list_count(list);

    int random = rand() % problem_list_len;
    
    return random;
    
}

void get_user_name(struct User *user) {

    char name[100];
    printf("Please enter your name: ");
    fgets(name, 100 - 1, stdin);
    name[strcspn(name, "\n")] = '\0';
    *user = User_User(name);

}

bool is_lost(struct Parameters param) {

    if ((param.people == 0) || (param.court == 0) || (param.treasury == 0)) {
        return true;
    }
    if (Parameters_get_average(param) < 10) {
        return true;
    }

    return false;

}
void show_leaderboard() {

    char yn_choice, kkp_junk[100];
    do {
        printf("Do you want to see leaderboard? ([Y]es/[N]o): ");
        scanf("%c", &yn_choice);
        fgets(kkp_junk, 100 - 1, stdin);
        yn_choice = toupper(yn_choice);
        if (yn_choice == 'Y') {
            print_leaderboard();
        }
    } while ((yn_choice != 'Y') && (yn_choice != 'N'));

}

void game_start(struct User *user, struct Problem_Node **list, int *last_problem_index) {

    enum State state = restore_from_file(list, user, last_problem_index);

    if (state == DUMP) {
        printf("Welcome back %s!\n", user->name);
        return;
    }

    if (state == NOT_SAVED) {
        get_user_name(user);
        read_problems(list);
        printf("Hello %s!\n", user->name);
        return;
    }

    char yn_choice, kkp_junk[100];
    do {
        printf("Do you want to load previously saved game? ([Y]es/[N]o): ");
        scanf("%c", &yn_choice);
        fgets(kkp_junk, 100 - 1, stdin);
        yn_choice = toupper(yn_choice);
        if (yn_choice == 'N') {
            get_user_name(user);
            read_problems(list);
            *last_problem_index = -1;
            printf("Hello %s!\n", user->name);
            return;
        }
    } while ((yn_choice != 'Y') && (yn_choice != 'N'));
    if (state == LOST) {
        read_problems(list);
    }

    printf("Hello %s!\n", user->name);
}

void game_end(struct Problem_Node *list, struct User user, enum State state, int last_problem_index) {

    if (state == LOST) {
        save_to_leaderboard(user);
        printf("------- GAME OVER! -------\n");
    }
    char yn_choice, kkp_junk[100];
    do {
        printf("Do you want to save game? ([Y]es/[N]o) ");
        scanf("%c", &yn_choice);
        fgets(kkp_junk, 100 - 1, stdin);
        yn_choice = toupper(yn_choice);
        if (yn_choice == 'Y') {
            save_to_file(list, user, state, last_problem_index);
        }
    } while ((yn_choice != 'Y') && (yn_choice != 'N'));

    remove("saves/dump.sgf");

    show_leaderboard();
    printf("Bye %s!\n", user.name);
    exit(0);

}

void use_problem(int index, struct Problem_Node **list, struct User *user, int choice) {

    struct Problem_Node *node = get_at_index(index, *list);

    if (choice == 1) {
        Parameters_change_people(&(user->user_params), node->problem.choice1.effect.people);
        Parameters_change_court(&(user->user_params), node->problem.choice1.effect.court);
        Parameters_change_treasury(&(user->user_params), node->problem.choice1.effect.treasury);
    } else {
        Parameters_change_people(&(user->user_params), node->problem.choice2.effect.people);
        Parameters_change_court(&(user->user_params), node->problem.choice2.effect.court);
        Parameters_change_treasury(&(user->user_params), node->problem.choice2.effect.treasury);
    }

    if (--(node->problem.num) == 0) {
        delete_at_index(list, index);
    }

    if (*list == NULL) {
        read_problems(list);
    }

}

void show_problem(struct Problem_Node **list, struct User *user, int *optional_index) {

    int pr_index;
    if ( *optional_index != -1) {
        pr_index = *optional_index;
        *optional_index = -1;
    } else {
        pr_index = get_random_problem(*list);
    }

    if (is_lost(user->user_params)) {
        save_to_file(*list, *user, DUMP, pr_index);
        game_end(*list, *user, LOST, pr_index);
    }

    struct Problem_Node *problem = get_at_index(pr_index, *list);

    Problem_print_problem(problem->problem);

    save_to_file(*list, *user, DUMP, pr_index);

    char choice, kkp_junk[100];
    do {
        scanf("%c", &choice);
        fgets(kkp_junk, 100 - 1, stdin);
        if ((choice == '1') || (choice == '2')) {
            use_problem(pr_index, list, user, choice - '0');
        }
        if (toupper(choice) == 'Q') {
            game_end(*list, *user, IN_GAME, pr_index);
        }
        if (toupper(choice) == 'L') {
            print_leaderboard();
            Problem_print_problem(problem->problem);
        }
    } while ((choice != '1') && (choice != '2') && (toupper(choice) != 'Q'));

}

int main() {

    srand(time(NULL));

    struct Problem_Node *problems_list = NULL;
    struct User user = User_User("");

    int last_problem_index = -1;
    game_start(&user, &problems_list, &last_problem_index);
    while(true) {
        Parameters_print_all_params(user.user_params);
        show_problem(&problems_list, &user, &last_problem_index);
    }

    return 0;
}