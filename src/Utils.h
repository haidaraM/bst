/**
 * @brief Contains some functions used across the project
 * @file Utils.h
*/
#ifndef UTILS_H
#define UTILS_H

int MAX(int x, int y);

int MIN(int x, int y);

/**
 * @brief Get a random value between inf and sup
 */
int get_random_between(int inf, int sup);



/**
 * @enum NodeSide
 * @brief Enum to know the side of the node relative to it's parent
 */
typedef enum {
    LEFT_SIDE,
    RIGHT_SIDE,
    NO_SIDE
} NodeSide;


#endif