#ifndef TYPEPACKAGE_H
#define TYPEPACKAGE_H

#include "Element.h"

/**
 * @brief This struct encapsulates all the operations to do in the Element
 */
typedef struct TypePackage
{

    int (*compare_element)(const Element element, const Element element2);

    void (*print_element)(const Element element, FILE *stream);

    void (*write_element_in_char_array)(const Element element, char *output);

    void (*free_element)(Element element);

} TypePackage;


TypePackage get_int_typePackage();

#endif
