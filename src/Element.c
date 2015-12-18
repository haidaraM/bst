#include <stdio.h>
#include "Element.h"


void afficher_element(const Element e) {
    printf("%d ", e);
}

int compare_element(const Element e1, const Element e2) {
    return e1 - e2;
}

char *get_element_in_char(const Element e)
{
    static char result[10];
    sprintf(result,"%d",e);
    return result;
}
