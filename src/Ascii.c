/**
 * @brief Implementation of the Ascii module
 * @file Ascii.c
*/
#include "Ascii.h"

#include <stdlib.h>
#include <stdio.h>
#include "Ascii.h"
#include <string.h>
#include "Avl.h"
#include "Utils.h"
#include "Rbt.h"
#include "Collection.h"


#define MAX_HEIGHT 1000
#define INFINITY (1<<20)

int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];


/*adjust gap between left and right nodes*/
const int gap = 4;

/*used for printing next node in the same level,*/
/*this is the x coordinate of the next char printed */
int print_next;


typedef struct Asciinode
{
    struct Asciinode *left, *right;

    /*length of the edge from this node to its children*/
    int edge_length;

    int height;

    int lablen;

    /* -1=I am left, 0=I am root, 1=right */
    int parent_dir;

    /* max supported unit32 in dec, 20 digits max*/
    char label[21];
} Asciinode;


/**
 * @brief The following function fills in the lprofile array for the given tree.
It assumes that the center of the label of the root of this tree
is located at a position (x,y).  It assumes that the edge_length
fields have been computed for this tree.
 */
static void compute_lprofile(Asciinode *node, int x, int y)
{
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->left != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

static void compute_rprofile(Asciinode *node, int x, int y)
{
    int i, notleft;
    if (node == NULL) return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->right != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

/**
 * @brief This function prints the given level of the given tree, assuming
that the node has the given x cordinate.
 */
static void print_level(Asciinode *node, int x, int level)
{
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    if (level == 0)
    {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++)
        {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->lablen;
    }
    else if (node->edge_length >= level)
    {
        if (node->left != NULL)
        {
            for (i = 0; i < (x - print_next - (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != NULL)
        {
            for (i = 0; i < (x - print_next + (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else
    {
        print_level(node->left, x - node->edge_length - 1, level - node->edge_length - 1);
        print_level(node->right, x + node->edge_length + 1, level - node->edge_length - 1);
    }
}

/**
 * @brief This function fills in the edge_length and height fields of the specified tree
 */
static void compute_edge_lengths(Asciinode *node)
{
    int h, hmin, i, delta;
    if (node == NULL) return;
    compute_edge_lengths(node->left);
    compute_edge_lengths(node->right);

    /* first fill in the edge_length of node */
    if (node->right == NULL && node->left == NULL)
    {
        node->edge_length = 0;
    }
    else
    {
        if (node->left != NULL)
        {
            for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
            {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->left, 0, 0);
            hmin = node->left->height;
        }
        else
        {
            hmin = 0;
        }
        if (node->right != NULL)
        {
            for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
            {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->right, 0, 0);
            hmin = MIN(node->right->height, hmin);
        }
        else
        {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++)
        {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        /*If the node has two children of height 1, then we allow the two leaves to be within 1, instead of 2*/
        if (((node->left != NULL && node->left->height == 1) ||
             (node->right != NULL && node->right->height == 1)) && delta > 4)
        {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    /* now fill in the height of node*/
    h = 1;
    if (node->left != NULL)
    {
        h = MAX(node->left->height + node->edge_length + 1, h);
    }
    if (node->right != NULL)
    {
        h = MAX(node->right->height + node->edge_length + 1, h);
    }
    node->height = h;
}

static Asciinode *build_ascii_tree_recursive_avl(Node *t)
{
    Asciinode *asciinode;

    if (t == NULL) return NULL;

    asciinode = malloc(sizeof(Asciinode));
    asciinode->left = build_ascii_tree_recursive_avl(t->leftChild);
    asciinode->right = build_ascii_tree_recursive_avl(t->rightChild);

    if (asciinode->left != NULL)
    {
        asciinode->left->parent_dir = -1;
    }

    if (asciinode->right != NULL)
    {
        asciinode->right->parent_dir = 1;
    }

    write_element_in_char_array(t->data, asciinode->label);
    asciinode->lablen = strlen(asciinode->label);

    return asciinode;
}

static Asciinode *build_ascii_tree_recursive_rbtree(RBNode *t)
{
    Asciinode *asciinode;

    if (t == NULL) return NULL;

    asciinode = malloc(sizeof(Asciinode));
    asciinode->left = build_ascii_tree_recursive_rbtree(t->leftChild);
    asciinode->right = build_ascii_tree_recursive_rbtree(t->rightChild);

    if (asciinode->left != NULL)
    {
        asciinode->left->parent_dir = -1;
    }

    if (asciinode->right != NULL)
    {
        asciinode->right->parent_dir = 1;
    }

    write_element_in_char_array(t->data, asciinode->label);
    asciinode->lablen = strlen(asciinode->label);

    return asciinode;
}


/**
 * @brief Copy the tree into the ascii node structre
 */
static Asciinode *build_ascii_tree(Collection *t)
{
    Asciinode *node;
    if (t == NULL) return NULL;
#ifdef AVL
    Avl *avl = (Avl *) t->racine;
    node = build_ascii_tree_recursive(avl->root);

#elif RBT
    RBTree * rbTree = (RBTree *) t->racine;
    node = build_ascii_tree_recursive_rbtree(rbTree->root);
#endif
    node->parent_dir = 0;

    return node;
}

/**
 * @brief Free all the nodes of the given tree
 */
static void free_ascii_tree(Asciinode *node)
{
    if (node == NULL) return;
    free_ascii_tree(node->left);
    free_ascii_tree(node->right);
    free(node);
}


void show_collection_in_ascii(Collection *t)
{
    Asciinode *proot;
    int xmin, i;
    if (t == NULL) return;
    proot = build_ascii_tree(t);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++)
    {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT)
    {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}