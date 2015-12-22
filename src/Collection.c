/**
 * @file Collection.c
*/
#include <stdlib.h>
#include "Collection.h"
#include "Avl.h"

void initialize_collection(Collection *collection)
{

#ifdef AVL
    collection->racine = (Avl *) malloc(sizeof(Avl));
    initialize_avl(collection->racine);
#endif

}


void free_collection(Collection *collection)
{
#ifdef AVL
    free_avl((Avl *) collection->racine);
    free(collection->racine);
#endif
}

void insert_element_in_collection(Collection *pos, const Element val)
{
#ifdef AVL
    insert_element_in_avl(pos->racine, val);
#endif
}


int search_element_in_collection(const Collection *collection, const Element element)
{
#ifdef AVL
    return search_element_in_avl((Avl *) collection->racine, element);
#endif
}

void create_dot_file_for_collection(const Collection *collection, const char *fileName)
{
#ifdef AVL
    create_dot_file_for_avl((Avl *) collection->racine, fileName);
#endif

}
