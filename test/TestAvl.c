#include "Avl.h"
#include <assert.h>
#include <Avl.h>


void test_initialize()
{
    Avl avl;
    TypePackage typePackage = get_int_typePackage();
    initialize_avl(&avl,&typePackage);
    assert(avl.root == NULL);
    assert(avl.nb_elements == 0);
}

void test_get_height()
{
    Avl avl;
    TypePackage typePackage = get_int_typePackage();
    initialize_avl(&avl,&typePackage);
    insert_element_in_avl(&avl,create_element_int(1));
    insert_element_in_avl(&avl,create_element_int(2));
    insert_element_in_avl(&avl,create_element_int(3));
    assert(get_avl_height(&avl) == 2);

    insert_element_in_avl(&avl,create_element_int(10));
    assert(get_avl_height(&avl) == 3);
    insert_element_in_avl(&avl,create_element_int(11));
    assert(get_avl_height(&avl) == 3);

    free_avl(&avl);
}

void test_get_nb_elements()
{
    Avl avl;
    TypePackage typePackage = get_int_typePackage();
    initialize_avl(&avl,&typePackage);
    assert(get_nb_elements_in_avl(&avl) == 0);

    insert_element_in_avl(&avl,create_element_int(1));
    assert(get_nb_elements_in_avl(&avl) == 1);

    insert_element_in_avl(&avl,create_element_int(1));
    assert(get_nb_elements_in_avl(&avl) == 1);

    free_avl(&avl);
}

int main(int argc, char const *ar[])
{
    test_initialize();
    test_get_height();
    test_get_nb_elements();
    return 0;
}



