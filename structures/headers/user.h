/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include <string.h>
#include "parameters.h"

#include "../../includes/debug.h"

#ifndef USER_H
#define USER_H

struct User {
    char name[100];
    struct Parameters user_params;
};

struct User User_User(char name[]);

#endif