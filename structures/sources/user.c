/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include <string.h>
#include "../headers/user.h"
#include "../headers/parameters.h"

struct User User_User(char name[]){
    struct User user;
    strcpy(user.name, name);
    user.user_params = Parameters_Parameters(50, 50, 50);

    return user;
}