/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include "choice.h"

#ifndef PROBLEM_H
#define PROBLEM_H

struct Problem {
    char text[200];
    struct Choice choice1, choice2;
    int num;
};

void Problem_print_problem(struct Problem p);

#endif