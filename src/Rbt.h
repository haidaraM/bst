/**
 * @file Rbt.h
 */
#ifndef RBT_H
#define RBT_H

#include "Element.h"

/**
 * @enum Color
 * @brief Enum to specify the node color
 */
typedef enum
{
    RED, BLACK
} Color;

/**
 * @struct RBNode
 * @brief Represent a node in RB Tree
 */
typedef struct RBNode
{
    struct RBNode *leftChild;    /**< Left child of the node */
    struct RBNode *rightChild;    /**< Right child of the node */
    struct RBNode *father;    /**< The father of the node */
    Element data;    /**< Data contained in the node */
    Color color; /**< Node color */
} RBNode;

/**
 * @struct RBTree
 * @brief Reb black tree
 */
typedef struct RBTree
{
    RBNode *root; /**< Root node */
} RBTree;


void initialize_rbtree(RBTree *rbTree);

void free_rbtree(RBTree *rbTree);

void insert_element_in_rbtree(RBTree *rbTree, const Element element);


int search_element_in_rbtree(const RBTree *rbTree, const Element element);


void create_dot_file_for_rbtree(const RBTree *rbTree, const char *fileName);


#endif
