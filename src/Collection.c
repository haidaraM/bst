/**
 * @file Collection.c
*/
#include <stdlib.h>
#include "Collection.h"
#include "Avl.h"
#include "Rbt.h"

void initialize_collection(Collection *collection,TypePackage *typePackage)
{

#ifdef AVL
    collection->root = (Avl *) malloc(sizeof(Avl));
    initialize_avl((Avl*)collection->root,typePackage);
#elif RBT
    collection->root = (RBTree *) malloc(sizeof(RBTree));
    initialize_rbtree((RBTree *) collection->root,typePackage);
#endif
}


void free_collection(Collection *collection)
{
#ifdef AVL
    free_avl((Avl *) collection->root);
    free(collection->root);
#elif RBT
    free_rbtree((RBTree *) collection->root);
    free(collection->root);
#endif
}

void insert_element_in_collection(Collection *pos, const Element val)
{
#ifdef AVL
    insert_element_in_avl((Avl*)pos->root, val);
#elif RBT
    insert_element_in_rbtree((RBTree *) pos->root, val);
#endif
}


int search_element_in_collection(const Collection *collection, const Element element)
{
#ifdef AVL
    return search_element_in_avl((Avl *) collection->root, element);

#elif RBT
    return search_element_in_rbtree((RBTree *) collection->root, element);
#endif
}

void create_dot_file_for_collection(const Collection *collection, const char *fileName)
{
#ifdef AVL
    create_dot_file_for_avl((Avl *) collection->root, fileName);
#elif RBT
    create_dot_file_for_rbtree((RBTree *) collection->root, fileName);
#endif

}

void remove_element_from_collection(Collection *collection, const Element element)
{
#ifdef AVL
#elif RBT
#endif
}
