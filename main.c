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

    char yn_choice, kkp_junk;
    do {
        printf("Do you want to see leaderboard? ([Y]es/[N]o): ");
        scanf("%c%c", &yn_choice, &kkp_junk);
        yn_choice = toupper(yn_choice);
        if (yn_choice == 'Y') {
            print_leaderboard();
        }
    } while ((yn_choice != 'Y') && (yn_choice != 'N'));

}

void game_start(struct User *user, struct Problem_Node **list) {

    enum State state = restore_from_file(list, user);

    if (state == NOT_SAVED) {
        get_user_name(user);
        read_problems(list);
        printf("Hello %s!\n", user->name);
        return;
    }

    char yn_choice, kkp_junk;
    do {
        printf("Do you want to load previously saved game? ([Y]es/[N]o): ");
        scanf("%c%c", &yn_choice, &kkp_junk);
        yn_choice = toupper(yn_choice);
        if (yn_choice == 'N') {
            get_user_name(user);
            read_problems(list);
            printf("Hello %s!\n", user->name);
            return;
        }
    } while ((yn_choice != 'Y') && (yn_choice != 'N'));
    if (state == LOST) {
        read_problems(list);
    }

    printf("Hello %s!\n", user->name);
}

void game_end(struct Problem_Node *list, struct User user, enum State state) {

    if (state == LOST) {
        save_to_leaderboard(user);
        printf("------- GAME OVER! -------\n");
    }
    char yn_choice, kkp_junk;
    do {
        printf("Do you want to save game? ([Y]es/[N]o) ");
        scanf("%c%c", &yn_choice, &kkp_junk);
        yn_choice = toupper(yn_choice);
        if (yn_choice == 'Y') {
            save_to_file(list, user, state);
        }
    } while ((yn_choice != 'Y') && (yn_choice != 'N'));

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
        if (toupper(choice) == 'Q') {
            game_end(*list, *user, IN_GAME);
        }
    } while ((choice != '1') && (choice != '2') && (toupper(choice) != 'Q'));

}

void printlist(struct Problem_Node *list) {

    struct Problem_Node *current = list;
    while (current != NULL) {
        printf("%d ", current->problem.num);
        current = current->next;
    }
    printf("\n");

}

int main() {

    srand(time(NULL));

    struct Problem_Node *problems_list = NULL;
    struct User user = User_User("");

    game_start(&user, &problems_list);
    while(true) {
        printf("People: %d, Court: %d, Treasury: %d\n", user.user_params.people, user.user_params.court, user.user_params.treasury);
        show_problem(&problems_list, &user);
        if (is_lost(user.user_params)) {
            game_end(problems_list, user, LOST);
        }
    }

    return 0;
}