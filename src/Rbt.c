/**
 * @file Rbt.c
 */
#include "Rbt.h"
#include <stdlib.h>
#include <stdio.h>

static void recursive_free(RBNode *rbNode);

static int recursive_search_element(const RBNode *rbNode, const Element element);

static void write_node_in_file(const RBNode *rbNode, FILE *file);

static void recursive_write_digraph(const RBNode *noeud, FILE *file);

static RBNode *recursive_insertion(RBNode **pNoeud, RBNode *fatherNode, const Element element);

RBNode *right_rotation(RBTree * rbTree, RBNode *root);

RBNode *left_rotation(RBTree * rbTree,RBNode *root);

static void rotate_rbtree(RBTree *rbTree, RBNode *node);

void initialize_rbtree(RBTree *rbTree)
{
    rbTree->root = NULL;
    rbTree->nb_elements = 0;
}

void free_rbtree(RBTree *rbTree)
{
    recursive_free(rbTree->root);
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

RBNode* insert_element_in_rbtree(RBTree *rbTree, const Element element)
{

    RBNode *inserted_node = recursive_insertion(&(rbTree->root), NULL, element);
    if (inserted_node != NULL)
    {
        rbTree->nb_elements++;
        rotate_rbtree(rbTree, inserted_node);
    }

    return inserted_node;
}

static void rbtree_insert_case1(RBTree *tree, RBNode *node);

static void rbtree_insert_case2(RBTree *tree, RBNode *node);

static void rbtree_insert_case3(RBTree *tree, RBNode *node);

static void rbtree_insert_case4(RBTree *tree, RBNode *node);

static void rbtree_insert_case5(RBTree *tree, RBNode *node);


void rotate_rbtree(RBTree *rbTree, RBNode *node)
{
    rbtree_insert_case1(rbTree, node);
}

/* Insert case 1: If the new node is at the root of the tree, it must
 * be recolored black, as the root is always black. */
void rbtree_insert_case1(RBTree *tree, RBNode *node)
{
    if(node->father == NULL){

        /* the root is always black */
        node->color = BLACK;
    } else {
        /* not root */
        rbtree_insert_case2(tree,node);
    }
}



/* Insert case 2: If the parent of the new node is red, this
 * conflicts with the red-black tree conditions, as both children
 * of every red node are black. */
void rbtree_insert_case2(RBTree *tree, RBNode *node)
{
    /* Note that if this function is being called, we already know
	 * the node has a parent, as it is not the root node. */
    if(node->father->color == RED){
        rbtree_insert_case3(tree,node);
    }
}

/* Insert case 3: If the parent and uncle are both red, repaint them
 * both black and repaint the grandparent red.  */

void rbtree_insert_case3(RBTree *tree, RBNode *node)
{
    RBNode * grand_father, *uncle;

    /* Note that the node must have a grandparent, as the parent
	 * is red, and the root node is always black. */

    grand_father = node->father->father;
    uncle = get_brother_node(node->father);

    if(uncle != NULL && uncle->color == RED){
        node->father->color = BLACK;
        uncle->color = BLACK;
        grand_father->color = RED;

        rbtree_insert_case1(tree,grand_father);
    } else {
        rbtree_insert_case4(tree,node);
    }
}


/* Case 4: If the parent is red, but the uncle is black, we need to do
 * some rotations to keep the tree balanced and complying with the tree
 * conditions.  If the node is on the opposite side relative to its parent
 * as the parent is relative to its grandparent, rotate around the
 * parent.  Either way, we will continue to case 5.
 *
 * eg.
 *
 *         B                              B
 *        / \                            / \
 *       R   B          ->     node ->  R   B
 *        \                            /
 *         R  <- node                 R
 *
 */
void rbtree_insert_case4(RBTree *tree, RBNode *node)
{
    RBNode *next_node;
    NodeSide rbNodeSide;

    rbNodeSide = get_node_side(node);

    if(rbNodeSide != get_node_side(node->father)){

        next_node = node->father;

        /* Rotate around the parent in the opposite direction
		 * to side. */
        if(rbNodeSide == LEFT_SIDE) {
            right_rotation(tree,node->father);
        } else {
            left_rotation(tree,node->father);
        }
    } else {
        next_node = node;
    }

    rbtree_insert_case5(tree,next_node);
}

/* Case 5: The node is on the same side relative to its parent as the
 * parent is relative to its grandparent.  The node and its parent are
 * red, but the uncle is black.
 *
 * Now, rotate at the grandparent and recolor the parent and grandparent
 * to black and red respectively.
 *
 *               G/B                 P/B
 *              /   \               /   \
 *           P/R     U/B    ->   N/R     G/R
 *          /   \                       /   \
 *       N/R      ?                   ?      U/B
 *
 */

void rbtree_insert_case5(RBTree *tree, RBNode *node)
{
    RBNode * father, *grand_father;
    NodeSide rbNodeSide;

    father = node->father;
    grand_father = father->father;

    rbNodeSide = get_node_side(node);

    father->color = BLACK;
    grand_father->color = RED;

    if(rbNodeSide == LEFT_SIDE){
        grand_father = right_rotation(tree,grand_father);
    } else {
        grand_father = left_rotation(tree,grand_father);
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
    if(rbTree->root->color == RED){
        fprintf(digraph_file, "[fillcolor=red]");
    } else {
        fprintf(digraph_file, "[fillcolor=black]");
    }
    recursive_write_digraph(rbTree->root, digraph_file);
    fprintf(digraph_file, "}\n");
    fclose(digraph_file);
}


RBNode *create_node(const Element element)
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

RBNode *right_rotation(RBTree* rbTree,RBNode *root)
{
    RBNode *new_root;
    new_root = root->left_child;

    /* update the father to point to the new child*/
    if (root->father != NULL)
    {
        if (get_node_side(root) == RIGHT_SIDE)
        {
            root->father->right_child = new_root;
        } else
        {
            root->father->left_child = new_root;
        }
    } else {
        rbTree->root = new_root;
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
RBNode *left_rotation(RBTree *rbTree, RBNode *root)
{
    RBNode *new_root;
    new_root = root->right_child;


    /* update the father to point to the new child*/
    if (root->father != NULL)
    {
        if (get_node_side(root) == RIGHT_SIDE)
        {
            root->father->right_child = new_root;
        } else
        {
            root->father->left_child = new_root;
        }
    } else {
        rbTree->root = new_root;
    }

    /* the new father of new_root is the father of the old root*/
    new_root->father = root->father;
    root->right_child = new_root->left_child;
    if (new_root->left_child != NULL)
    {
        new_root->left_child->father = root;
    }
    /* the old root father become the new root*/
    root->father = new_root;
    new_root->left_child = root;
    return new_root;
}



NodeSide get_node_side(const RBNode *node)
{
    if (node->father != NULL)
    {
        if (node->father->right_child == node)
            return RIGHT_SIDE;
        else return LEFT_SIDE;
    } else return NO_SIDE;
}

RBNode *get_brother_node(const RBNode *node)
{
    NodeSide is_right = get_node_side(node);
    switch (is_right)
    {
        case RIGHT_SIDE: /* node is the right child so we return the left child*/
            return node->father->left_child;
        case LEFT_SIDE: /* node is the left child so we return the right child*/
            return node->father->right_child;
        default: /* the node has no brother*/
            return NULL;
    }

    return NULL;
}

int compute_height(const RBNode * rbNode)
{
    if (rbNode == NULL)
        return 0;
    else return 1 + MAX(compute_height(rbNode->right_child), compute_height(rbNode->left_child));
}

int get_rbtree_height(const  RBTree * rbTree)
{
    return compute_height(rbTree->root);
}

unsigned long get_nb_elements_in_rbtree(const RBTree *rbTree)
{
    return rbTree->nb_elements;
}
