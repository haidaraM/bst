#include <assert.h>
#include <stdlib.h>
#include "Rbt.h"


RBNode *left_rotation(RBTree * rbTree,RBNode *root);
RBNode *right_rotation(RBTree * rbTree,RBNode *root);
RBNode *create_node_rbtree(const Element element);
/**
       1                      1
      / \                    / \
     /   \                  /   \
    0     2(pivot)         0     3
           \      =>            / \
            \                  /   \
             3                2     4
              \
               \
                4
 */
void test_left_rotation()
{
    Element element1 = create_element_int(1);
    RBNode *root = create_node_rbtree(element1);

    Element element0 = create_element_int(0);

    root->left_child = create_node_rbtree(element0);
    root->left_child->father = root;

    Element element2 = create_element_int(2);
    RBNode *rightNode = create_node_rbtree(element2);
    root->right_child = rightNode;
    rightNode->father = root;

    Element element3 = create_element_int(3);
    rightNode->right_child = create_node_rbtree(element3);
    rightNode->right_child->father = rightNode;


    Element element4 = create_element_int(4);
    rightNode->right_child->right_child = create_node_rbtree(element4);
    rightNode->right_child->right_child->father = rightNode->right_child;

    RBNode *new_right_child = left_rotation(NULL, rightNode);
    rightNode = NULL;

    assert(new_right_child->data == element3);
    assert(new_right_child->father == root);
    assert(root->right_child == new_right_child);

    assert(new_right_child->left_child->data == element2);
    assert(new_right_child->left_child->father == new_right_child);

    assert(new_right_child->right_child->data == element4);
    assert(new_right_child->right_child->father == new_right_child);



    free(new_right_child->right_child);
    free(new_right_child->left_child);
    free(root->left_child);
    free(root->right_child);
    free(root);
    free(element0);
    free(element1);
    free(element2);
    free(element3);
    free(element4);
}

/**
       1                       1
      / \                     /  \
     /   \                   /    \
    0     3 (pivot)  =>     0      2
         / \                        \
        /   \                        \
       2     4                        3
                                       \
                                        \
                                         4
 */
void test_right_rotation()
{
    Element element1 = create_element_int(1);
    RBNode *root = create_node_rbtree(element1);

    Element element0 = create_element_int(0);

    root->left_child = create_node_rbtree(element0);
    root->left_child->father = root;

    Element  element3 = create_element_int(3);

    RBNode *rightNode = create_node_rbtree(element3);
    root->right_child = rightNode;
    rightNode->father = root;

    Element element4 = create_element_int(4);
    rightNode->right_child = create_node_rbtree(element4);
    rightNode->right_child->father = rightNode;

    Element element2 = create_element_int(2);
    rightNode->left_child = create_node_rbtree(element2);
    rightNode->left_child->father = rightNode;

    RBNode *new_right_child = right_rotation(NULL, rightNode);
    rightNode = NULL;

    assert(new_right_child->data == element2);
    assert(new_right_child->father == root);
    assert(root->right_child == new_right_child);

    assert(new_right_child->left_child == NULL);

    assert(new_right_child->right_child->data == element3);
    assert(new_right_child->right_child->left_child == NULL);
    assert(new_right_child->right_child->father == new_right_child);

    assert(new_right_child->right_child->right_child->data == element4);
    assert(new_right_child->right_child->right_child->father == new_right_child->right_child);

    free(new_right_child->right_child->right_child);
    free(new_right_child->right_child);
    free(root->left_child);
    free(root->right_child);
    free(root);
    free_element_int(element0);
    free_element_int(element1);
    free_element_int(element2);
    free_element_int(element3);
    free_element_int(element4);
}

void test_get_height()
{
    RBTree rbTree;
    TypePackage typePackage = get_int_typePackage();
    initialize_rbtree(&rbTree, &typePackage);
    assert(get_rbtree_height(&rbTree) == 0);

    insert_element_in_rbtree(&rbTree,create_element_int(50));
    assert(get_rbtree_height(&rbTree) == 1);

    insert_element_in_rbtree(&rbTree,create_element_int(-1));
    assert(get_rbtree_height(&rbTree) == 2);

    insert_element_in_rbtree(&rbTree,create_element_int(10));
    assert(get_rbtree_height(&rbTree) == 2);

    insert_element_in_rbtree(&rbTree,create_element_int(20));
    assert(get_rbtree_height(&rbTree) == 3);

    free_rbtree(&rbTree);

}

void test_get_nb_elements()

{
    RBTree rbTree;
    TypePackage typePackage = get_int_typePackage();
    initialize_rbtree(&rbTree, &typePackage);
    assert(get_nb_elements_in_rbtree(&rbTree) == 0);

    insert_element_in_rbtree(&rbTree,create_element_int(14));
    assert(get_nb_elements_in_rbtree(&rbTree) == 1);

    Element element14 = create_element_int(14);
    insert_element_in_rbtree(&rbTree,element14);
    assert(get_nb_elements_in_rbtree(&rbTree) == 1);

    free_rbtree(&rbTree);
    free(element14);
}

int main(int argc, char const *ar[])
{
    test_left_rotation();
    test_right_rotation();
    test_get_height();
    test_get_nb_elements();
    return 0;
}