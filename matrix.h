#ifndef MATRIX_H
#define MATRIX_H
#include <stdbool.h>

typedef struct matrix matrix;
typedef struct node node;
typedef struct lineHead lineHead;


struct node { 
	int column;
	node *next;
};
struct lineHead { 
	int nbLinks;
	node *first;
};

struct matrix {
	int size;
	int nbElements;
	lineHead *indexLines ;
};

void init_matrix(matrix** ptr, int size);
        /* initialize a size * size matrix.
         *
         * Requires :
         *       size > 0;
         * Ensures:
         *       **ptr does not contain links.
         */
void delete_matrix(matrix** ptr);
        /* Deletes the matrix.  Ressources allowed to the matrix are freed.
         *
         * Requires :
         *      ptr != NULL;
         */
void insert_link(matrix *ptr, int i, int j);
        /* Links i to j in matrix ptr.
         *
         * Requires :
         *      ptr != NULL;
         *      M -> size > i >= 0
         *      M -> size > j >=0
         * Ensures :
         *      M.nbElements > 0;
         */

void multiply_vector_matrix_G(matrix M, long double* vector, int nb_multiplications, long double alpha);
        /* Multiply vector nb_multiplications times by a Google matrix parametrized with alpha.
         *
         * Requires :
         *      M has been initialized with init_matrix.
         *		vector != NULL
         *		nb_multiplications > 0
         *		1 >= alpha >= 0
         * Ensures :
         *      vector = vecteur * G^nb_multiplications
         */

#endif
