#include <stdio.h>
#include <stdlib.h>
#include "Avl.h"
#include "Utils.h"


/* intern functions */
static int compute_height(Node *noeud);

static void insertion(Node **pNoeud, Element element);

static Node *right_rotation(Node *root);

static Node *left_rotation(Node *root);

static Node *create_node(Element element);

static void rotate_avl(Avl *avl);

static void recursive_testament(Node *noeud);

static void recursive_rotation(Node **noeud);

static void recursive_write_digraph(const Node *noeud, FILE *file);

static void write_node_in_file(const Node *noeud, FILE *file);

/* **************************************************** */




void initialize_avl(Avl *a) {
    a->root = NULL;
}

void testament_avl(Avl *a) {
    recursive_testament(a->root);
}

void insert_element_in_Avl(Avl *a, Element element) {
    insertion(&(a->root), element);
    rotate_avl(a);
}


int get_avl_height(const Avl *avl) {
    return compute_height(avl->root);
}

void create_dot_file_for_avl(const Avl *avl, const char *fileName) {
    FILE *fichierDigraph;
    fichierDigraph = fopen(fileName, "w");

    fprintf(fichierDigraph, "strict digraph AVL {\n");
    recursive_write_digraph(avl->root, fichierDigraph);
    fprintf(fichierDigraph, "}\n");
    fclose(fichierDigraph);
}

int recursive_search_element(Node *noeud, Element element) {
    if (noeud == NULL) {
        return 0;
    } else {
        if (compare_element(element, noeud->data) > 0) {
            return recursive_search_element(noeud->rightChild, element);
        } else if (compare_element(element, noeud->data) < 0) {
            return recursive_search_element(noeud->leftChild, element);
        } else
            return 1;
    }

}

int search_element_in_Avl(const Avl *avl, Element element) {
    return recursive_search_element(avl->root, element);
}




static int idnumer = 0;

static void write_node_in_file(const Node *noeud, FILE *file) {
    fprintf(file, "%d", noeud->data);
    fprintf(file, "->");
    fprintf(file, "{");
    if (noeud->leftChild != NULL || noeud->rightChild != NULL) {

        if (noeud->leftChild != NULL)
            fprintf(file, "%d", noeud->leftChild->data);
        else
            fprintf(file, "id%d [shape=point]", idnumer++);
        fprintf(file, " ");
        if (noeud->rightChild != NULL)
            fprintf(file, "%d", noeud->rightChild->data);
        else
            fprintf(file, "id%d [shape=point]", idnumer++);
    }


    fprintf(file, "};\n");
}

/**
 * @brief Crée un noeud avec element comme data
 * @fn static Node *create_node(Element element)
 */
static Node *create_node(Element element) {
    Node *n = malloc(sizeof(Node));
    n->data = element;
    n->rightChild = NULL;
    n->leftChild = NULL;

    return n;
}


static void recursive_write_digraph(const Node *noeud, FILE *file) {
    if (noeud != NULL) {
        write_node_in_file(noeud, file);
        recursive_write_digraph(noeud->leftChild, file);
        recursive_write_digraph(noeud->rightChild, file);
    }
}


static void recursive_testament(Node *noeud) {
    if (noeud != NULL) {
        recursive_testament(noeud->rightChild);
        recursive_testament(noeud->leftChild);
        free(noeud);
    }
}

/**
 * Methodé récursive faisant l'insertion dans l'arbre
 */
static void insertion(Node **pNoeud, Element element) {
    if (*pNoeud == NULL) {
        *pNoeud = create_node(element);
    } else {
        if (compare_element(element, (*pNoeud)->data) > 0) { /* element > data => on va à droite*/

            insertion(&((*pNoeud)->rightChild), element);

        } else if (compare_element(element, (*pNoeud)->data) < 0) { /*element < data => on va à gauche*/
            insertion(&((*pNoeud)->leftChild), element);
        }
    }
}

static void recursive_rotation(Node **noeud) {

    if (*noeud != NULL) {

        int hauteurGauche = compute_height((*noeud)->leftChild);
        int hauteurDroit = compute_height((*noeud)->rightChild);


        if (hauteurGauche - hauteurDroit > 1) { /* déséquilibré vers la gauche => rotation vers la droite*/
            if (hauteurGauche - hauteurDroit == 2) {
                if ((*noeud)->leftChild->rightChild != NULL) {
                    (*noeud)->leftChild = left_rotation((*noeud)->leftChild);
                }
            }
            *noeud = right_rotation(*noeud);
        } else if (hauteurDroit - hauteurGauche > 1) { /* déséquilibré vers la droite => rotation vers la gauche*/
            if (hauteurDroit - hauteurGauche == 2) {
                if ((*noeud)->rightChild->leftChild != NULL) {
                    (*noeud)->rightChild = right_rotation((*noeud)->rightChild);
                }
            }
            *noeud = left_rotation(*noeud);
        }

        recursive_rotation(&(*noeud)->rightChild);
        recursive_rotation(&(*noeud)->leftChild);

    }
}

static void rotate_avl(Avl *avl) {
    recursive_rotation(&avl->root);
}


/**
 * Fonction de rotation droite
 */
static Node *right_rotation(Node *racine) {
    Node *nouvelleRacine;
    nouvelleRacine = racine->leftChild;
    racine->leftChild = nouvelleRacine->rightChild;
    nouvelleRacine->rightChild = racine;
    return nouvelleRacine;

}

/*Fonction de rotation gauche*/
static Node *left_rotation(Node *racine) {
    Node *nouvelleRacine;
    nouvelleRacine = racine->rightChild;
    racine->rightChild = nouvelleRacine->leftChild;
    nouvelleRacine->leftChild = racine;
    return nouvelleRacine;
}


static int compute_height(Node *noeud) {
    if (noeud == NULL)
        return 0;
    else return 1 + MAX(compute_height(noeud->rightChild), compute_height(noeud->leftChild));
}