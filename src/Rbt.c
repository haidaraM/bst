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
        /* TODO : rotation*/
    }
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
        { /* element > info => on va à droite*/

            recursive_insertion(&((*pNoeud)->right_child), *pNoeud, element);

        } else if (compare_element(element, (*pNoeud)->data) < 0)
        { /*element < info => on va à gauche*/
            recursive_insertion(&((*pNoeud)->left_child), *pNoeud, element);
        }
    }
}

void remove_element_from_rbtree(RBTree *rbTree, const Element element)
{

}
