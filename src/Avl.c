/**
 * @file Avl.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "Avl.h"
#include "Utils.h"


/* intern functions */
static int compute_height(const AVLNode *noeud);

static AVLNode *recursive_insertion(AVLNode **pNoeud, const Element element);

static AVLNode *right_rotation(AVLNode *root);

static AVLNode *left_rotation(AVLNode *root);

static AVLNode *create_node(const Element element);

static void rotate_avl(Avl *avl);

static void recursive_free(AVLNode *noeud);

static void recursive_rotation(AVLNode **noeud);

static void recursive_write_digraph(const AVLNode *noeud, FILE *file);

static void write_node_in_file(const AVLNode *noeud, FILE *file);

/* **************************************************** */




void initialize_avl(Avl *a)
{
    a->root = NULL;
    a->nb_elements = 0;
}

void free_avl(Avl *a)
{
    recursive_free(a->root);
}

AVLNode *insert_element_in_avl(Avl *a, const Element element)
{
    AVLNode *inserted_node = recursive_insertion(&(a->root), element);
    if (inserted_node != NULL)
    {
        a->nb_elements++;
        rotate_avl(a);
    }
    return inserted_node;
}


int get_avl_height(const Avl *avl)
{
    return compute_height(avl->root);
}

void create_dot_file_for_avl(const Avl *avl, const char *fileName)
{
    FILE *fichierDigraph;
    fichierDigraph = fopen(fileName, "w");

    fprintf(fichierDigraph, "strict digraph AVL {\n");
    recursive_write_digraph(avl->root, fichierDigraph);
    fprintf(fichierDigraph, "}\n");
    fclose(fichierDigraph);
}

int recursive_search_element(const AVLNode *noeud, const Element element)
{
    if (noeud == NULL)
    {
        return 0;
    } else
    {
        if (compare_element(element, noeud->data) > 0)
        {
            return recursive_search_element(noeud->right_child, element);
        } else if (compare_element(element, noeud->data) < 0)
        {
            return recursive_search_element(noeud->left_child, element);
        } else
            return 1;
    }

}

int search_element_in_avl(const Avl *avl, const Element element)
{
    return recursive_search_element(avl->root, element);
}


static void write_node_in_file(const AVLNode *noeud, FILE *file)
{

    static int idnumer = 0;
    print_element(noeud->data, file);
    fprintf(file, "->");
    fprintf(file, "{");
    if (noeud->left_child != NULL || noeud->right_child != NULL)
    {

        if (noeud->left_child != NULL)
        {
            print_element(noeud->left_child->data, file);
        }
        else
        {
            fprintf(file, "id%d [shape=point]", idnumer++);
        }

        fprintf(file, " ");

        if (noeud->right_child != NULL)
        {
            print_element(noeud->right_child->data, file);
        }
        else
        {
            fprintf(file, "id%d [shape=point]", idnumer++);
        }
    }

    fprintf(file, "};\n");
}

/**
 * @brief create a node with element as data
 */
static AVLNode *create_node(const Element element)
{
    AVLNode *n = malloc(sizeof(AVLNode));
    n->data = element;
    n->right_child = NULL;
    n->left_child = NULL;
    return n;
}


static void recursive_write_digraph(const AVLNode *noeud, FILE *file)
{
    if (noeud != NULL)
    {
        write_node_in_file(noeud, file);
        recursive_write_digraph(noeud->left_child, file);
        recursive_write_digraph(noeud->right_child, file);
    }
}


static void recursive_free(AVLNode *noeud)
{
    if (noeud != NULL)
    {
        recursive_free(noeud->right_child);
        recursive_free(noeud->left_child);
        free(noeud);
    }
}


AVLNode *recursive_insertion(AVLNode **pNoeud, const Element element)
{
    if (*pNoeud == NULL)
    {
        *pNoeud = create_node(element);
        return *pNoeud;
    } else
    {
        if (compare_element(element, (*pNoeud)->data) > 0)
        { /* element > data => we go right*/

            return recursive_insertion(&((*pNoeud)->right_child), element);

        } else if (compare_element(element, (*pNoeud)->data) < 0)
        { /* element < data => we go left*/
            return recursive_insertion(&((*pNoeud)->left_child), element);
        }
    }

    return NULL;
}

static void recursive_rotation(AVLNode **noeud)
{

    if (*noeud != NULL)
    {

        int hauteurGauche = compute_height((*noeud)->left_child);
        int hauteurDroit = compute_height((*noeud)->right_child);


        if (hauteurGauche - hauteurDroit > 1)
        { /* unbalanced left => right rotation*/
            if (hauteurGauche - hauteurDroit == 2)
            {
                if ((*noeud)->left_child->right_child != NULL)
                {
                    (*noeud)->left_child = left_rotation((*noeud)->left_child);
                }
            }
            *noeud = right_rotation(*noeud);
        } else if (hauteurDroit - hauteurGauche > 1)
        { /*unbalanced right => left rotation*/
            if (hauteurDroit - hauteurGauche == 2)
            {
                if ((*noeud)->right_child->left_child != NULL)
                {
                    (*noeud)->right_child = right_rotation((*noeud)->right_child);
                }
            }
            *noeud = left_rotation(*noeud);
        }

        recursive_rotation(&(*noeud)->right_child);
        recursive_rotation(&(*noeud)->left_child);

    }
}

static void rotate_avl(Avl *avl)
{
    recursive_rotation(&avl->root);
}


static AVLNode *right_rotation(AVLNode *root)
{
    AVLNode *new_root;
    new_root = root->left_child;
    root->left_child = new_root->right_child;
    new_root->right_child = root;
    return new_root;

}


static AVLNode *left_rotation(AVLNode *root)
{
    AVLNode *new_root;
    new_root = root->right_child;
    root->right_child = new_root->left_child;
    new_root->left_child = root;
    return new_root;
}


static int compute_height(const AVLNode *noeud)
{
    if (noeud == NULL)
        return 0;
    else return 1 + MAX(compute_height(noeud->right_child), compute_height(noeud->left_child));
}

void remove_element_from_avl(Avl *avl, const Element element)
{

}

unsigned long get_nb_elements_in_avl(const Avl *avl)
{
    return avl->nb_elements;
}
