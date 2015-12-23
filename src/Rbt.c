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

static void recursive_insertion(RBNode **pNoeud, RBNode * fatherNode, const Element element);


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
        recursive_insertion(&(rbTree->root),rbTree->root->father,element);
        /* TODO : rotation*/
    }
}

int search_element_in_rbtree(const RBTree *rbTree, const Element element)
{
    return recursive_search_element(rbTree->root, element);
}

void create_dot_file_for_rbtree(const RBTree *rbTree, const char *fileName)
{
    FILE *fichierDigraph;
    fichierDigraph = fopen(fileName, "w");

    fprintf(fichierDigraph, "strict digraph AVL {\n node [style=filled fontcolor=white] \n");
    fprintf(fichierDigraph, "%d [fillcolor=black]", rbTree->root->data);
    recursive_write_digraph(rbTree->root, fichierDigraph);
    fprintf(fichierDigraph, "}\n");
    fclose(fichierDigraph);
}

static RBNode *create_node(const Element element)
{
    RBNode *rbNode = malloc(sizeof(RBNode));
    rbNode->data = element;
    rbNode->color = RED;
    rbNode->father = NULL;
    rbNode->leftChild = NULL;
    rbNode->rightChild = NULL;

    return rbNode;
}

static void recursive_free(RBNode *rbNode)
{
    if (rbNode != NULL)
    {
        recursive_free(rbNode->leftChild);
        recursive_free(rbNode->rightChild);
        free(rbNode);
    }
}

static int recursive_search_element(const RBNode *rbNode, const Element element)
{
    if (rbNode == NULL) return 0;
    else if (compare_element(element, rbNode->data) > 0) return recursive_search_element(rbNode->rightChild, element);
    else if (compare_element(element, rbNode->data) < 0) return recursive_search_element(rbNode->leftChild, element);
    else return 1;
}

static void write_node_in_file(const RBNode *rbNode, FILE *file)
{
    static int idnumer = 0;
    print_element(rbNode->data, file);
    fprintf(file, "->");
    fprintf(file, "{ ");
    if (rbNode->leftChild != NULL || rbNode->rightChild != NULL)
    {

        if (rbNode->leftChild != NULL)
        {
            if (rbNode->leftChild->color == BLACK)
            {
                fprintf(file, "%d [fillcolor=black]", rbNode->leftChild->data);
            } else
            {
                fprintf(file, "%d [fillcolor=red]", rbNode->leftChild->data);
            }
        }
        else
            fprintf(file, "id%d [shape=point]", idnumer++);


        fprintf(file, " ");
        if (rbNode->rightChild != NULL)
        {
            if (rbNode->rightChild->color == BLACK)
            {
                fprintf(file, "%d [fillcolor=black]", rbNode->rightChild->data);
            } else
            {
                fprintf(file, "%d [fillcolor=red]", rbNode->rightChild->data);
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
        recursive_write_digraph(noeud->leftChild, file);
        recursive_write_digraph(noeud->rightChild, file);
    }
}

static void recursive_insertion(RBNode **pNoeud, RBNode * fatherNode,const Element element)
{
    if(*pNoeud == NULL)
    {
        *pNoeud = create_node(element);
        (*pNoeud)->father = fatherNode;
    } else
    {
        if (compare_element(element, (*pNoeud)->data) > 0) { /* element > info => on va à droite*/

            recursive_insertion(&((*pNoeud)->rightChild),*pNoeud, element);

        } else if (compare_element(element, (*pNoeud)->data) < 0) { /*element < info => on va à gauche*/
            recursive_insertion(&((*pNoeud)->leftChild),*pNoeud, element);
        }
    }
}