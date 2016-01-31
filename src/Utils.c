/**
 * @brief Implementation of utils functions
 * @file Utils.c
*/
#include <stdlib.h>
#include "Utils.h"

int MIN(int x, int y)
{
    return x < y ? x : y;
}


int MAX(int x, int y)
{
    return x < y ? y : x;
}

int get_random_between(int inf, int sup)
{
    return rand() %(sup - inf) + inf;
}
