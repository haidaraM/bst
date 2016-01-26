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

typedef enum {
    LEFT_SIDE,
    RIGHT_SIDE,
    NO_SIDE
} RBNodeSide;

/**
 * @struct RBNode
 * @brief Represent a node in RB Tree
 */
typedef struct RBNode
{
    struct RBNode *left_child;    /**< Left child of the node */
    struct RBNode *right_child;    /**< Right child of the node */
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

void remove_element_from_rbtree(RBTree * rbTree, const Element element);


void create_dot_file_for_rbtree(const RBTree *rbTree, const char *fileName);

/**
 * @brief Check if a node is the right child of its father
 * @return 1 if it's the case, -1 if the node has no father, 0 if the it's the left child
 */
RBNodeSide get_node_side(const RBNode *node);

/**
 * @brief Get the brother node of a node.
 * @return the brother if it's exist, NULL otherwise
 */
RBNode * get_brother_node(const RBNode * node);

void test_left_rotation();

#endif
