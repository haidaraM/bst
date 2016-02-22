#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Collection.h"
#include "Utils.h"
#include "Ascii.h"



/**
 * @file main.c
 *
 * @mainpage
 * This project contains some implementation of some binary search trees in C.
 *
 * Each implementation is separated despite there are some common operations. With this, you can choose an implementation
 * without touch others.
 *
 * @author Mohamed El Mouctar HAIDARA - elmhaidara@gmail.com
 */

/* Max value of random number */


int main(int argc, char const *ar[])
{
    srand((unsigned) time(NULL));

    Collection a;
    TypePackage typePackage = get_int_typePackage();
    initialize_collection(&a,&typePackage);

    int i;

    for (i = 0; i < 50; ++i)
    {
        insert_element_in_collection(&a, create_element_int(get_random_between(-500,1000)));
    }

    /*show_collection_in_ascii(&a);*/

    const char fichier[] = "tree.gv";
    char commande[256];
    create_dot_file_for_collection(&a, fichier);
    sprintf(commande, "dot -Tsvg %s > %s.svg && open %s.svg", fichier, fichier, fichier);
    system(commande);


    free_collection(&a);


    return 0;
}


