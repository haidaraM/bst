/**
 * @file Element.c
*/
#include <stdio.h>
#include "Element.h"


void print_element(const Element e, FILE *stream)
{
    if (stream != NULL)
    {
        fprintf(stream, "%d", e);
    }

}

int compare_element(const Element e1, const Element e2)
{
    return e1 - e2;
}

void write_element_in_char_array(const Element e, char *output)
{
    sprintf(output, "%d", e);

}
