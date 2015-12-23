/**
 * @file Element.h
*/
#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdio.h>

/**< An element in the tree.
 * You can define your own element but you have to redefine the following functions */
typedef int Element;

/**
 * @brief Print the element in the given stream.
 * @param e element to show
 * @param stream the stream in which you wan to print the element. The stream can be stdout or a regular file in file
 * system.
 */
void print_element(const Element e, FILE *stream);


/**
 * @brief Write in the given array the element. The array must be large enough to contain the element in char*
 * @param e element
 */
void write_element_in_char_array(const Element e, char *output);

/**
 * @brief Compare two elements.
 * @param e1 first element
 * @param e2 second element
 * @return Return x such as :
 *  = 0 si e1=e2,
 * x<0 si e1 < e2,
 * x >0 si e1 > e2
 */
int compare_element(const Element e1, const Element e2);


#endif
