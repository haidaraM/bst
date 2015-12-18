#ifndef _AVL
#define _AVL
#include "Element.h"


/**
 * @struct Node
 * @brief One node of the tree
 */
typedef struct Node {

    struct Node *leftChild; /**< fils gauche du noeud */
    struct Node *rightChild; /**< fils droit du noeud */
    Element data; /**< information contenue dans le noeud */
} Node;

/**
 * @struct Avl
 * @brief Represent an AVL tree. It can be useful if we want some metadata.
 *
 */
typedef struct {
    Node *root; /**<  root */
} Avl;

/**
 * @brief Initialize an AVL
 * @param avl to initialize
 */
void initialize_avl(Avl *avl);

/**
 * @brief AVL testament
 * @param avl
 */
void testament_avl(Avl *avl);

/**
 * @brief Search an element in the tree
 * @param avl
 * @param element element you are looking for
 * @return 1 if element is present
 *         0 otherwise
 */
int search_element_in_Avl(const Avl *avl, Element element);

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
void insert_element_in_Avl(Avl *avl, Element element);

/**
 * @brief Create a file in dot format for the given AVL
 * @fn void creerFichierDigraphArn(const Avl *avl, const char *fileName)
 * @param avl
 * @param filename
 */
void create_dot_file_for_avl(const Avl *avl, const char *fileName);

#endif
