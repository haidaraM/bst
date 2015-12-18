#ifndef _collection
#define _collection

#include "Element.h"

typedef struct {
    void *racine;
} Collection;


/**
 * @brief Initialize a collection
 */
void initialize_collection(Collection *a);

/**
 * Testament of the collection
 */
void testament_collection(Collection *collection);

/**
 * Insert an element in the collection
 */
void insert_element_in_collection(Collection *pos, Element val);


/**
 * @brief Search in element in the collection
 */
int search_element_in_collection(const Collection *collection, Element element);

/**
 * @brief Create a file in dot format for the given collection
 * @fn void create_dot_file_for_collection(const Avl *avl, const char *fileName)
 * @param collection
 * @param filename
 */
void create_dot_file_for_collection(const Collection *collection, const char *fileName);


#endif









