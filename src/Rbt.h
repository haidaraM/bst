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
 * @enum NodeSide
 * @brief Enum to know the side of the node relative to it's parent
 */
typedef enum {
    LEFT_SIDE,
    RIGHT_SIDE,
    NO_SIDE
} NodeSide;

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
    unsigned long nb_elements; /**< Number of elements in the tree */
} RBTree;

/**
 * @brief Initialize the tree
 * @param rbtree the tree to initialize
 */
void initialize_rbtree(RBTree *rbTree);

/**
 * @brief Free the tree
 * @param rbtree the tree to free
 */
void free_rbtree(RBTree *rbTree);

/**
 * @brief Insert an element in the tree
 * @param rbTree rbTree in which you wan to insert
 * @param element element to insert
 * @return return the inserted node or NULL if there was no node inserted
 */
RBNode * insert_element_in_rbtree(RBTree *rbTree, const Element element);

/**
 * @brief Get the number of elements in the tree
 */
unsigned long get_nb_elements_in_rbtree(const RBTree * rbTree);

/**
 * @brief an element in the tree
 * @param rbtree the tree in which to perform the search
 * @param element element to search
 */
int search_element_in_rbtree(const RBTree *rbTree, const Element element);

/**
 * @brief get the height of the tree
 */
int get_rbtree_height(const  RBTree * rbTree);

/**
 * @brief Remove an element in the tree
 */
void remove_element_from_rbtree(RBTree * rbTree, const Element element);


/**
 * @brief Create a file in dot format for the given RBTree
 * @param rbTree
 * @param filename
 */
void create_dot_file_for_rbtree(const RBTree *rbTree, const char *fileName);

/**
 * @brief Check if a node is the right child of its father
 * @return 1 if it's the case, -1 if the node has no father, 0 if the it's the left child
 */
NodeSide get_node_side(const RBNode *node);

/**
 * @brief Get the brother node of a node.
 * @return the brother if it's exist, NULL otherwise
 */
RBNode * get_brother_node(const RBNode * node);


/**
 * @brief Create a node with element as data
 * @param element
 */
RBNode *create_node(const Element element);


#endif
