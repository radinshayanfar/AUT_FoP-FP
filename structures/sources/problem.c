/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include "../headers/problem.h"

void Problem_print_problem(struct Problem p) {

    printf("%s", p.text);
    printf("[1] %s", p.choice1.text);
    printf("[2] %s", p.choice2.text);
    printf("[Q]uit/[L]eaderboard\n");

}