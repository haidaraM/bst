/**
 * @file Rbt.c
 */
#include "Rbt.h"
#include <stdlib.h>
#include <stdio.h>

static RBNode *create_node(const Element element);

static void recursive_free(RBNode *rbNode);

static int recursive_search_element(const RBNode *rbNode, const Element element);

static void write_node_in_file(const RBNode *rbNode, FILE *file);

static void recursive_write_digraph(const RBNode *noeud, FILE *file);

static void recursive_insertion(RBNode **pNoeud, RBNode *fatherNode, const Element element);

static RBNode *right_rotation(RBNode *root);

static RBNode *left_rotation(RBNode *root);

static void rotate_rbtree(RBTree *tree);

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
        recursive_insertion(&(rbTree->root), rbTree->root->father, element);
        rotate_rbtree(rbTree);
    }
}

static void rotate_rbtree(RBTree *tree)
{

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
    const char black_color[] =" [fillcolor=black]";
    const char red_color[]=" [fillcolor=red]";

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

static void recursive_insertion(RBNode **pNoeud, RBNode *fatherNode, const Element element)
{
    if (*pNoeud == NULL)
    {
        *pNoeud = create_node(element);
        (*pNoeud)->father = fatherNode;
    } else
    {
        if (compare_element(element, (*pNoeud)->data) > 0)
        { /* element > data => we go right*/

            recursive_insertion(&((*pNoeud)->right_child), *pNoeud, element);

        } else if (compare_element(element, (*pNoeud)->data) < 0)
        { /* element < data => we go left*/
            recursive_insertion(&((*pNoeud)->left_child), *pNoeud, element);
        }
    }
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

    /* the new father of new_root is the father of the old root*/
    new_root->father = root->father;
    root->left_child = new_root->right_child;
    if(new_root->right_child != NULL)
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
    RBNode root_father,*root, root_left_child,root_right_child,root_left_child_left,root_left_child_right;
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

    root_right_child.data= 12;
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


    root=right_rotation(root);

}

