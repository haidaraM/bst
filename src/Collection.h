/**
 * @brief This module represents a collection of elements
 * @file Collection.h
*/
#ifndef COLLECTION_H
#define COLLECTION_H

#include "Element.h"
#include "TypePackage.h"

/**
 * @struct Collection
 * @brief Represent a collection of element
 */
typedef struct
{
    void *root; /**< Pointer on the concrete implementation of collection : AVL or ... */
} Collection;


/**
 * @brief Initialize a collection
 * @param collection collection to initialize
 */
void initialize_collection(Collection *collection, TypePackage * typePackage);

/**
 * @brief Testament of the collection
 * @param collection collection to free
 */
void free_collection(Collection *collection);

/**
 * @brief Insert an element in the collection
 * @param collection collection in which you want to insert
 * @param element element to insert
 * @return A pointer on the inserted node
 */
void * insert_element_in_collection(Collection *collection, const Element element);


/**
 * @brief Remove element in the collection
 * @param collection
 * @param element element to remove
 */
void remove_element_from_collection(Collection * collection, const Element element);


/**
 * @brief Search in element in the collection
 * @param collection collection in which you want to perfom the search
 * @param element element you are looking for
 * @return 1 if element is present
 *         0 otherwise
 */
int search_element_in_collection(const Collection *collection, const Element element);

/**
 * @brief Get the collection size
 * @param collection
 * @return the number of elements in the collection
 */
unsigned long get_nb_elements_in_collection(const Collection * collection);

/**
 * @brief Create a file in dot format for the given collection
 * @param collection
 * @param filename
 */
void create_dot_file_for_collection(const Collection *collection, const char *fileName);


#endif









