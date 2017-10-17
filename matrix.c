#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <assert.h>
#include "matrix.h"



void init_matrix(matrix** ptr, int size) {

	*ptr = malloc(sizeof(matrix));
	(*ptr) -> indexLines = malloc(size * sizeof(lineHead)); 
	(*ptr) -> size = size;
	(*ptr) -> nbElements = 0; //Matrix is empty

	for (int k = 0; k < size; k++) { //Every line is initialized.

		((*ptr) -> indexLines[k]).first = NULL; 
		((*ptr) -> indexLines[k]).nbLinks = 0; //Every line is empty.
	}

}

void delete_matrix(matrix** ptr) {

	node *nptr, *tmp2;

	for (int i= 0; i < (*ptr) -> size; i++){

		nptr=((*ptr) -> indexLines[i]).first;

		while (nptr != NULL) {

			tmp2 = nptr;
			nptr = nptr -> next;
			free(tmp2);
			
		}
	}
	free((*ptr) -> indexLines);
	free(*ptr);

}


void insert_link(matrix *ptr, int i, int j) { 

	node *nptr;
	node *tmp = (ptr->indexLines[i]).first; 

	if (tmp==NULL || tmp->column > j) { //Line is empty
		nptr = malloc(sizeof(node)); //Node to insert
		nptr -> column = j;
		((ptr -> indexLines[i]).first) = nptr;
		nptr -> next = tmp;
		(ptr -> indexLines[i]).nbLinks++;
		(ptr -> nbElements)++;

	}

	else {

		node *cursor = tmp->next;
		while (cursor != NULL && (cursor -> column <= j)) { 
			tmp = cursor;
			cursor = cursor -> next;
		}

        if (tmp -> column < j ) { //Link is added either between two links or at the end
        	nptr = malloc(sizeof(node));
    		nptr -> column=j; 
			nptr -> next=cursor;
			tmp -> next=nptr;
			(ptr -> indexLines[i]).nbLinks++;
			(ptr -> nbElements)++;

		}

		else { 
			//This link already exists
		}

	}


}


void multiply_vector_matrix_G(matrix M, long double* vector, int nb_multiplications, long double alpha) {

	long double *result = malloc(M.size * sizeof(long double)) ; //Contains result of the multiplication at each iteration

	for (int i = 0; i < M.size; i++) {
		result[i] = 0;
	}

	long double beta; 
	node *cursor;

	for (int k=0; k < nb_multiplications; k++) { //vector is multiplied nb_multiplications times by the Google matrix

		beta=0;

		for (int i=0; i < M.size; i++ ) {
	
			beta = beta + vector[i] *  (1 - alpha) / (long double) M.size;

			if ((M.indexLines[i]).first == NULL) { //Line is empty

				beta = beta + vector[i] * alpha / (long double) M.size; 

			}

			else { //Line contains some elements

				cursor = (M.indexLines[i]).first;
				while (cursor != NULL) { 

					result[cursor->column] = result[cursor->column] + vector[i] / (long double) (M.indexLines[i]).nbLinks;
					cursor = cursor -> next;
				
				}

			}

		}
		for (int i = 0; i < M.size; i++) {

			vector[i] = alpha * result[i] + beta;
			result[i] = 0;
		}
	}

	free(result); 

}


