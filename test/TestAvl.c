#include "Avl.h"
#include <assert.h>


void test_initialize()
{
    Avl avl;
    initialize_avl(&avl);
    assert(avl.root == NULL);
}

void test_get_height()
{
    Avl avl;
    initialize_avl(&avl);
    insert_element_in_avl(&avl,1);
    insert_element_in_avl(&avl,2);
    insert_element_in_avl(&avl,3);
    assert(get_avl_height(&avl) == 2);

    insert_element_in_avl(&avl,10);
    assert(get_avl_height(&avl) == 3);
    insert_element_in_avl(&avl,11);
    assert(get_avl_height(&avl) == 3);

}

int main(int argc, char const *ar[])
{
    test_initialize();
    test_get_height();
    return 0;
}



