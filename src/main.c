#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Collection.h"
#include "Ascii.h"
#include "Rbt.h"



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
#define valMax 1000



int main(int argc, char const *ar[])
{

    Collection a;
    initialize_collection(&a);

    int i, element;

    srand((unsigned) time(NULL));
    for (i = 0; i < 5; ++i)
    {
        element = rand() % (valMax + 1);
        insert_element_in_collection(&a, element);
    }

    /*show_collection_in_ascii(&a);*/

    const char fichier[] = "arbre.gv";
    char commande[256];
    create_dot_file_for_collection(&a, fichier);
    sprintf(commande, "dot -Tsvg %s > %s.svg && eog %s.svg 2>/dev/null", fichier, fichier, fichier);
    system(commande);


    free_collection(&a);


    return 0;
}


