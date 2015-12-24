/**
 * @file Avl.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "Avl.h"
#include "Utils.h"


/* intern functions */
static int compute_height(const Node *noeud);

static void recursive_insertion(Node **pNoeud, const Element element);

static Node *right_rotation(Node *root);

static Node *left_rotation(Node *root);

static Node *create_node(const Element element);

static void rotate_avl(Avl *avl);

static void recursive_free(Node *noeud);

static void recursive_rotation(Node **noeud);

static void recursive_write_digraph(const Node *noeud, FILE *file);

static void write_node_in_file(const Node *noeud, FILE *file);

/* **************************************************** */




void initialize_avl(Avl *a)
{
    a->root = NULL;
}

void free_avl(Avl *a)
{
    recursive_free(a->root);
}

void insert_element_in_avl(Avl *a, const Element element)
{
    recursive_insertion(&(a->root), element);
    rotate_avl(a);
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

int recursive_search_element(Node *noeud, const Element element)
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


static void write_node_in_file(const Node *noeud, FILE *file)
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
static Node *create_node(const Element element)
{
    Node *n = malloc(sizeof(Node));
    n->data = element;
    n->right_child = NULL;
    n->left_child = NULL;
    return n;
}


static void recursive_write_digraph(const Node *noeud, FILE *file)
{
    if (noeud != NULL)
    {
        write_node_in_file(noeud, file);
        recursive_write_digraph(noeud->left_child, file);
        recursive_write_digraph(noeud->right_child, file);
    }
}


static void recursive_free(Node *noeud)
{
    if (noeud != NULL)
    {
        recursive_free(noeud->right_child);
        recursive_free(noeud->left_child);
        free(noeud);
    }
}


static void recursive_insertion(Node **pNoeud, const Element element)
{
    if (*pNoeud == NULL)
    {
        *pNoeud = create_node(element);
    } else
    {
        if (compare_element(element, (*pNoeud)->data) > 0)
        { /* element > data => on va à droite*/

            recursive_insertion(&((*pNoeud)->right_child), element);

        } else if (compare_element(element, (*pNoeud)->data) < 0)
        { /*element < data => on va à gauche*/
            recursive_insertion(&((*pNoeud)->left_child), element);
        }
    }
}

static void recursive_rotation(Node **noeud)
{

    if (*noeud != NULL)
    {

        int hauteurGauche = compute_height((*noeud)->left_child);
        int hauteurDroit = compute_height((*noeud)->right_child);


        if (hauteurGauche - hauteurDroit > 1)
        { /* déséquilibré vers la gauche => rotation vers la droite*/
            if (hauteurGauche - hauteurDroit == 2)
            {
                if ((*noeud)->left_child->right_child != NULL)
                {
                    (*noeud)->left_child = left_rotation((*noeud)->left_child);
                }
            }
            *noeud = right_rotation(*noeud);
        } else if (hauteurDroit - hauteurGauche > 1)
        { /* déséquilibré vers la droite => rotation vers la gauche*/
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


/**
 * Fonction de rotation droite
 */
static Node *right_rotation(Node *racine)
{
    Node *nouvelleRacine;
    nouvelleRacine = racine->left_child;
    racine->left_child = nouvelleRacine->right_child;
    nouvelleRacine->right_child = racine;
    return nouvelleRacine;

}

/*Fonction de rotation gauche*/
static Node *left_rotation(Node *racine)
{
    Node *nouvelleRacine;
    nouvelleRacine = racine->right_child;
    racine->right_child = nouvelleRacine->left_child;
    nouvelleRacine->left_child = racine;
    return nouvelleRacine;
}


static int compute_height(const Node *noeud)
{
    if (noeud == NULL)
        return 0;
    else return 1 + MAX(compute_height(noeud->right_child), compute_height(noeud->left_child));
}