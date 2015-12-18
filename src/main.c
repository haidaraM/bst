#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Collection.h"
#include "Ascii.h"

/* Max value of random number */
#define valMax 1000




int main(int argc, char const *ar[]) {

    Collection a;
    initialize_collection(&a);

    int i;

    srand((unsigned) time(NULL));
    for (i = 0; i < 10; ++i) {
        int valeur = rand() % (valMax + 1);
        insert_element_in_collection(&a, valeur);
    }

    show_collection_in_ascii(&a);

     const char fichier[] = "arbre.gv";
    char commande[256];
    create_dot_file_for_collection(&a, fichier);
    sprintf(commande, "dot -Tsvg %s > %s.svg && eog %s.svg 2>/dev/null", fichier, fichier, fichier);
    system(commande);



    testament_collection(&a);

    return 0;
}


