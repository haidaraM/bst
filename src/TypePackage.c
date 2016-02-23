#include "TypePackage.h"

TypePackage get_int_typePackage()
{
    TypePackage result = {compare_element_int, print_element_int, write_element_int_in_char_array, free_element_int};
    return result;
}
