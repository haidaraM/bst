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
 * @param e element to show
 */
void afficher_element(const Element e);

/**
 * @brief Return the element in the format you want in the dot file generated
 * @param e element to get in char*
 */
char *get_element_in_char(const Element e);

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
