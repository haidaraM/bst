/**
 * @file Element.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "Element.h"


void print_element_int(const Element e, FILE *stream)
{
    if(stream != NULL)
    {
        int *element_int_1 = (int *) e;
        fprintf(stream, "%d", *element_int_1);
    }

}

int compare_element_int(const Element e1, const Element e2)
{
    int *element_int_1 = (int *) e1;
    int *element_int_2 = (int *) e2;

    return *element_int_1 - *element_int_2;
}

void write_element_int_in_char_array(const Element e, char *output)
{
    int *element_int_1 = (int *) e;
    sprintf(output, "%d", *element_int_1);
}

Element create_element_int(int element_int)
{
    int *new_element = (void *) malloc(sizeof(int));
    *new_element = element_int;
    return new_element;
}


void free_element_int(Element element)
{
    free(element);
}
