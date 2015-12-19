/**
 * @file Element.h
*/
#ifndef _ELEMENT
#define _ELEMENT

/**< An element in the tree.
 * You can define your own element but you have to redefine the following functions */
typedef int Element;

/**
 * @brief Show the element
 */
void afficher_element(const Element e);

/**
 *
 */
char *get_element_in_char(const Element e);

/**
 * @brief Compare two elements.
 * Return x such as :
 * x = 0 si e1=e2,
 * x<0 si e1 < e2,
 * x >0 si e1 > e2
 */
int compare_element(const Element e1, const Element e2);


#endif
