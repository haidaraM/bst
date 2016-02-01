#include <assert.h>
#include <stdlib.h>
#include "Rbt.h"


RBNode *left_rotation(RBTree * rbTree,RBNode *root);
RBNode *right_rotation(RBTree * rbTree,RBNode *root);

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
    TypePackage typePackage = get_int_typePackage();
    RBNode *root = create_node(create_element_int(1));
    root->left_child = create_node(0);
    root->left_child->father = root;

    RBNode *rightNode = create_node(create_element_int(2));
    root->right_child = rightNode;
    rightNode->father = root;

    rightNode->right_child = create_node(create_element_int(3));
    rightNode->right_child->father = rightNode;


    rightNode->right_child->right_child = create_node(create_element_int(4));
    rightNode->right_child->right_child->father = rightNode->right_child;

    RBNode *new_right_child = left_rotation(NULL, rightNode);
    rightNode = NULL;

    assert(new_right_child->data == create_element_int(3));
    assert(new_right_child->father == root);
    assert(root->right_child == new_right_child);

    assert(new_right_child->left_child->data == 2);
    assert(new_right_child->left_child->father == new_right_child);

    assert(new_right_child->right_child->data == 4);
    assert(new_right_child->right_child->father == new_right_child);



    free(new_right_child->right_child);
    free(new_right_child->left_child);
    free(root->left_child);
    free(root->right_child);
    free(root);
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
    RBNode *root = create_node(1);
    root->left_child = create_node(0);
    root->left_child->father = root;

    RBNode *rightNode = create_node(3);
    root->right_child = rightNode;
    rightNode->father = root;

    rightNode->right_child = create_node(4);
    rightNode->right_child->father = rightNode;


    rightNode->left_child = create_node(2);
    rightNode->left_child->father = rightNode;

    RBNode *new_right_child = right_rotation(NULL, rightNode);
    rightNode = NULL;

    assert(new_right_child->data == 2);
    assert(new_right_child->father == root);
    assert(root->right_child == new_right_child);

    assert(new_right_child->left_child == NULL);

    assert(new_right_child->right_child->data == 3);
    assert(new_right_child->right_child->left_child == NULL);
    assert(new_right_child->right_child->father == new_right_child);

    assert(new_right_child->right_child->right_child->data == 4);
    assert(new_right_child->right_child->right_child->father == new_right_child->right_child);

    free(new_right_child->right_child->right_child);
    free(new_right_child->right_child);
    free(root->left_child);
    free(root->right_child);
    free(root);
}

void test_get_height()
{
    RBTree rbTree;
    TypePackage typePackage = get_int_typePackage();
    initialize_rbtree(&rbTree, &typePackage);
    assert(get_rbtree_height(&rbTree) == 0);

    insert_element_in_rbtree(&rbTree,50);
    assert(get_rbtree_height(&rbTree) == 1);

    insert_element_in_rbtree(&rbTree,-1);
    assert(get_rbtree_height(&rbTree) == 2);

    insert_element_in_rbtree(&rbTree,10);
    assert(get_rbtree_height(&rbTree) == 2);

    insert_element_in_rbtree(&rbTree,20);
    assert(get_rbtree_height(&rbTree) == 3);

    free_rbtree(&rbTree);

}

void test_get_nb_elements()
{
    RBTree rbTree;
    TypePackage typePackage = get_int_typePackage();
    initialize_rbtree(&rbTree, &typePackage);
    assert(get_nb_elements_in_rbtree(&rbTree) == 0);

    insert_element_in_rbtree(&rbTree,14);
    assert(get_nb_elements_in_rbtree(&rbTree) == 1);

    insert_element_in_rbtree(&rbTree,14);
    assert(get_nb_elements_in_rbtree(&rbTree) == 1);

    free_rbtree(&rbTree);
}

int main(int argc, char const *ar[])
{
    test_left_rotation();
    test_right_rotation();
    test_get_height();
    test_get_nb_elements();
    return 0;
}