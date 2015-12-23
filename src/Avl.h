/**
 * @brief This module is the implementation of AVL tree
 * @file Avl.h
*/
#ifndef AVL_H
#define AVL_H

#include "Element.h"


/**
 * @brief Tree node
 * @struct Node
 *
 */
typedef struct Node
{

    struct Node *leftChild;    /**< Right child of the node */
    struct Node *rightChild;    /**< Left child of the node */
    Element data; /**< Data contained in the node */
} Node;

/**
 * @struct Avl
 * @brief AVL tree.
 *
 */
typedef struct
{
    Node *root; /**<  The root node of the tree */
} Avl;

/**
 * @brief Initialize an AVL
 * @param avl to initialize
 */
void initialize_avl(Avl *avl);

/**
 * @brief AVL free
 * @param avl to free
 */
void free_avl(Avl *avl);

/**
 * @brief Search an element in the tree
 * @param avl tree in which you want to perform the search
 * @param element element you are looking for
 * @return 1 if element is present
 *         0 otherwise
 */
int search_element_in_avl(const Avl *avl, const Element element);

/**
 * @brief Get the height of the tree
 * @param avl AVL you want the height
 * @return tree height
 */
int get_avl_height(const Avl *avl);

/**
 * @brief Insert an element in the tree
 * @param avl avl in which you wan to insert
 * @param element element to insert
 */
void insert_element_in_avl(Avl *avl, const Element element);

/**
 * @brief Create a file in dot format for the given AVL
 * @fn void creerFichierDigraphArn(const Avl *avl, const char *fileName)
 * @param avl
 * @param filename
 */
void create_dot_file_for_avl(const Avl *avl, const char *fileName);

#endif
