/**
 * @file Rbt.c
 */
#include "Rbt.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static RBNode *create_node(const Element element);

static void recursive_free(RBNode *rbNode);

static int recursive_search_element(const RBNode *rbNode, const Element element);

static void write_node_in_file(const RBNode *rbNode, FILE *file);

static void recursive_write_digraph(const RBNode *noeud, FILE *file);

static RBNode *recursive_insertion(RBNode **pNoeud, RBNode *fatherNode, const Element element);

static RBNode *right_rotation(RBNode *root);

static RBNode *left_rotation(RBNode *root);

static void rotate_rbtree(RBTree *rbTree, RBNode *node);

void initialize_rbtree(RBTree *rbTree)
{
    rbTree->root = NULL;
}

void free_rbtree(RBTree *rbTree)
{
    recursive_free(rbTree->root);
}


void insert_element_in_rbtree(RBTree *rbTree, const Element element)
{
    if (rbTree->root == NULL)
    {
        rbTree->root = create_node(element);
        rbTree->root->color = BLACK;
    } else
    {
        RBNode *inserted_node = recursive_insertion(&(rbTree->root), rbTree->root->father, element);
        rotate_rbtree(rbTree, inserted_node);
    }
}

static void rotate_rbtree(RBTree *rbTree, RBNode *node)
{
    while (node != rbTree->root && node->father->color == RED)
    {
        if (node->father == node->father->father->left_child)
        {
            RBNode *tmp = node->father->father->right_child;
            if (tmp != NULL && tmp->color == RED)
            {
                node->father->color = BLACK;
                tmp->color = BLACK;
                node->father->father->color = RED;
                node = node->father->father;
            } else
            {
                if (node == node->father->right_child)
                {
                    node = node->father;
                    node = left_rotation(node);
                }

                node->father->color = BLACK;
                node->father->father->color = RED;

                if(node->father->father == rbTree->root){
                    rbTree->root = right_rotation(rbTree->root);
                } else {

                    node->father->father = right_rotation(node->father->father);
                }
            }
        } else
        {
            RBNode *tmp = node->father->father->left_child;
            if (tmp != NULL && tmp->color == RED)
            {
                node->father->color = BLACK;
                tmp->color = BLACK;
                node->father->father->color = RED;
                node = node->father->father;
            } else
            {
                if(node == node->father->left_child){
                    node = node->father;
                    node = right_rotation(node);
                }

                node->father->color = BLACK;
                node->father->father->color = RED;

                if(node->father->father == rbTree->root){
                    rbTree->root = left_rotation(rbTree->root);
                } else {
                    node->father->father = left_rotation(node->father->father);
                }

            }
        }
    }

    rbTree->root->color = BLACK;
}

int search_element_in_rbtree(const RBTree *rbTree, const Element element)
{
    return recursive_search_element(rbTree->root, element);
}

void create_dot_file_for_rbtree(const RBTree *rbTree, const char *fileName)
{
    FILE *digraph_file;
    digraph_file = fopen(fileName, "w");

    fprintf(digraph_file, "strict digraph AVL {\n node [style=filled fontcolor=white] \n");
    print_element(rbTree->root->data, digraph_file);
    fprintf(digraph_file, "[fillcolor=black]");
    recursive_write_digraph(rbTree->root, digraph_file);
    fprintf(digraph_file, "}\n");
    fclose(digraph_file);
}

static RBNode *create_node(const Element element)
{
    RBNode *rbNode = malloc(sizeof(RBNode));
    rbNode->data = element;
    rbNode->color = RED;
    rbNode->father = NULL;
    rbNode->left_child = NULL;
    rbNode->right_child = NULL;

    return rbNode;
}

static void recursive_free(RBNode *rbNode)
{
    if (rbNode != NULL)
    {
        recursive_free(rbNode->left_child);
        recursive_free(rbNode->right_child);
        free(rbNode);
    }
}

static int recursive_search_element(const RBNode *rbNode, const Element element)
{
    if (rbNode == NULL) return 0;
    else if (compare_element(element, rbNode->data) > 0) return recursive_search_element(rbNode->right_child, element);
    else if (compare_element(element, rbNode->data) < 0) return recursive_search_element(rbNode->left_child, element);
    else return 1;
}

static void write_node_in_file(const RBNode *rbNode, FILE *file)
{
    const char black_color[] = " [fillcolor=black]";
    const char red_color[] = " [fillcolor=red]";

    static int idnumer = 0;
    print_element(rbNode->data, file);
    fprintf(file, "->");
    fprintf(file, "{ ");

    if (rbNode->left_child != NULL || rbNode->right_child != NULL)
    {

        if (rbNode->left_child != NULL)
        {
            print_element(rbNode->left_child->data, file);
            if (rbNode->left_child->color == BLACK)
            {
                fprintf(file, black_color);
            } else
            {
                fprintf(file, red_color);
            }
        }
        else
            fprintf(file, "id%d [shape=point]", idnumer++);

        fprintf(file, " ");
        if (rbNode->right_child != NULL)
        {
            print_element(rbNode->right_child->data, file);
            if (rbNode->right_child->color == BLACK)
            {
                fprintf(file, black_color);
            } else
            {
                fprintf(file, red_color);
            }
        }
        else
            fprintf(file, "id%d [shape=point]", idnumer++);
    }

    fprintf(file, "};\n");
}

static void recursive_write_digraph(const RBNode *noeud, FILE *file)
{
    if (noeud != NULL)
    {
        write_node_in_file(noeud, file);
        recursive_write_digraph(noeud->left_child, file);
        recursive_write_digraph(noeud->right_child, file);
    }
}

static RBNode *recursive_insertion(RBNode **pNoeud, RBNode *fatherNode, const Element element)
{
    if (*pNoeud == NULL)
    {
        *pNoeud = create_node(element);
        (*pNoeud)->father = fatherNode;
        return *pNoeud;
    } else
    {
        if (compare_element(element, (*pNoeud)->data) > 0)
        { /* element > data => we go right*/

            return recursive_insertion(&((*pNoeud)->right_child), *pNoeud, element);

        } else if (compare_element(element, (*pNoeud)->data) < 0)
        { /* element < data => we go left*/
            return recursive_insertion(&((*pNoeud)->left_child), *pNoeud, element);
        }
    }

    return NULL;
}

void remove_element_from_rbtree(RBTree *rbTree, const Element element)
{

}


/**
       10               7
      /  \             / \
     /    \           /   \
    7      12   =>   6    10
   / \                   /  \
  /   \                 /    \
 6     8               8     12

 */

RBNode *right_rotation(RBNode *root)
{
    RBNode *new_root;
    new_root = root->left_child;

    /* update the father to point to the new child*/
    if(root->father != NULL){
        if(root->father->right_child == root)
        {
            root->father->right_child = new_root;
        } else {
            root->father->left_child = new_root;
        }
    }

    /* the new father of new_root is the father of the old root*/
    new_root->father = root->father;
    root->left_child = new_root->right_child;
    if (new_root->right_child != NULL)
    {
        new_root->right_child->father = root;
    }

    /* the old root father become the new root*/
    root->father = new_root;
    new_root->right_child = root;
    return new_root;
}


/**
       10               7
      /  \             / \
     /    \           /   \
    7      12   <=   6    10
   / \                   /  \
  /   \                 /    \
 6     8               8     12

 */
RBNode *left_rotation(RBNode *root)
{
    RBNode *new_root;
    new_root = root->right_child;


    /* update the father to point to the new child*/
    if(root->father != NULL){
        if(root->father->right_child == root)
        {
            root->father->right_child = new_root;
        } else {
            root->father->left_child = new_root;
        }
    }

    /* the new father of new_root is the father of the old root*/
    new_root->father = root->father;
    root->right_child = new_root->left_child;
    if(new_root->left_child != NULL)
    {
        new_root->left_child->father = root;
    }
    /* the old root father become the new root*/
    root->father = new_root;
    new_root->left_child = root;
    return new_root;
}


void test_right_rotation()
{
    RBNode root_father, *root, root_left_child, root_right_child, root_left_child_left, root_left_child_right;
    root = malloc(sizeof(RBNode));

    root_left_child_right.data = 8;
    root_left_child_right.right_child = NULL;
    root_left_child_right.left_child = NULL;
    root_left_child_right.father = &root_left_child;

    root_left_child_left.data = 6;
    root_left_child_left.right_child = NULL;
    root_left_child_left.left_child = NULL;
    root_left_child_left.father = &root_left_child;

    root_left_child.data = 7;
    root_left_child.left_child = &root_left_child_left;
    root_left_child.right_child = NULL;
    root_left_child.father = root;

    root_right_child.data = 12;
    root_right_child.left_child = NULL;
    root_right_child.right_child = NULL;
    root_right_child.father = root;


    root->data = 10;
    root->left_child = &root_left_child;
    root->right_child = &root_right_child;
    root->father = &root_father;

    root_father.right_child = root;
    root_father.left_child = NULL;
    root_father.data = 9;
    root_father.father = NULL;


    root = right_rotation(root);

}



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
    RBNode *root = create_node(1);
    root->left_child = create_node(0);
    root->left_child->father = root;

    RBNode *rightNode = create_node(2);
    root->right_child = rightNode;
    rightNode->father = root;

    rightNode->right_child = create_node(3);
    rightNode->right_child->father = rightNode;


    rightNode->right_child->right_child = create_node(4);
    rightNode->right_child->right_child->father = rightNode->right_child;

    rightNode = left_rotation(rightNode);


    assert(rightNode->data == 3);
    assert(rightNode->father == root);
    assert(rightNode->left_child->data == 2);
    assert(rightNode->left_child->father == rightNode);
    assert(root->right_child == rightNode);
    assert(root->right_child->right_child->data == 4);
    assert(root->father == NULL);
    assert(rightNode->right_child->father == rightNode);




    free(rightNode->right_child->right_child);
    free(rightNode->right_child);
    free(rightNode);
    free(root);


}
