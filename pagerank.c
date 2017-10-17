#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "matrix.h"
#include "string_functions.h"




int main (int argc, char *argv[]) {

	//Initialize default values
	long double alpha = 0.85; 
	int nb_multiplications = 150;
	char *file_name;

	if (argc == 2) { //No arguments given
		file_name = argv[1];

	}

	else if (argc == 4) { //One argument is given

		if (argv[1][0] != '-') { //Syntax error
			return -1;
		}

		if (argv[1][1] == 'A' && real_only(argv[2])) { //Alpha is given
			sscanf(argv[2], "%Lf", &alpha);				
		}

		else if (argv[1][1] == 'I' && integer_only(argv[2]))  { //Number of iterations is given
			sscanf(argv[2], "%i", &nb_multiplications);			
		}

		else {
			return -1;			
		} 

		file_name = argv[3]; 

	}
	else if (argc == 6) { // Both arguments are given

		if (argv[1][0] != '-' || argv[3][0] != '-') { //Syntax error
			return -1;
		}

		if ((argv[1][1] == 'A' && real_only(argv[2]) ) && (argv[3][1] == 'I' && integer_only(argv[4]))) { 
			sscanf(argv[4], "%i", &nb_multiplications);
			sscanf(argv[2], "%Lf", &alpha);
		}

		else if ((argv[3][1] == 'A' && real_only(argv[4])) && (argv[1][1] == 'I' && integer_only(argv[2]))) { 
			sscanf(argv[2], "%i", &nb_multiplications);
			sscanf(argv[4], "%Lf", &alpha);
		}

		else { //Syntax error
			return -1;			
		} 

		file_name = argv[5];


	}

	else { //Syntax error
		printf("./pagerank -I [number of iterations] -A [alpha] network_file.net\n");
		return -1;		
	}

	printf("nb_multiplications=%i alpha=%Lf file_name=%s\n", nb_multiplications, alpha, file_name);
	


	FILE *network_file = fopen(file_name, "r");
	int nb_pages;
	int nb_read;
	int nb_links=0;
	matrix *M;

	if (network_file == NULL) { 
			printf("Erreur: Impossible d'ouvrir le fichier");
		}

	else {

		if (fscanf(network_file, "%i%n\n", &nb_pages,&nb_read) == EOF){
			printf("Erreur: Le network_file est vide");
			return -1;
		} ;

		init_matrix(&M, nb_pages);

		int source_page;
		int target_page;		

		while(fscanf(network_file, "%i %i%n\n", &source_page, &target_page, &nb_read) != EOF ) {
			assert(source_page >= 0 && source_page < nb_pages); 
			assert(target_page >= 0 && target_page < nb_pages); 
			nb_links++; 
			insert_link(M, source_page, target_page);

		}
	}
	fclose(network_file);

	printf("nb_pages=%i nb_links=%i\n", nb_pages,nb_links);

	printf("Number of elements in the matrix=%i\n", M -> nbElements);

	long double *vector_pi = malloc(nb_pages * sizeof(long double)); //vector_pi which contains weights

	for (int j=0; j<nb_pages; j++) { //Init of vector_pi

		vector_pi[j]= 1 / (long double) nb_pages;;
	}

	multiply_vector_matrix_G(*M, vector_pi, nb_multiplications, alpha); //vector_pi is multiplied by matrix G nb_multiplications times
	delete_matrix(&M);

	int file_name_length = 0; //If file_name="exemple.net" then file_name_length=7

	while (file_name[file_name_length] != '.'){

		file_name_length++;
	}

	char* weights_file_name = malloc((file_name_length + 2) * sizeof(char)); //If file_name="exemple.net" then weights_file_name="exemple.p"
	char* pagerank_file_name = malloc((file_name_length + 4) * sizeof(char));	//If file_name="exemple.net" then file_name="exemple.ord"


 	for (int i=0; i <= file_name_length; i++) {
 		weights_file_name[i] = file_name[i];
  		pagerank_file_name[i] = file_name[i];		
 	}

 	weights_file_name[file_name_length+1] = 'p';
  	weights_file_name[file_name_length+2] = '\0';
 	pagerank_file_name[file_name_length+1] = 'o';
  	pagerank_file_name[file_name_length+2] = 'r';
   	pagerank_file_name[file_name_length+3] = 'd';
   	pagerank_file_name[file_name_length+4] = '\0';

   	printf("weights_file_name= %s\n", weights_file_name);
   	printf("pagerank_file_name= %s\n", pagerank_file_name);
 	
	FILE *weights_file = fopen(weights_file_name, "w+");
	FILE *pagerank_file = fopen(pagerank_file_name, "w+");

    free(weights_file_name);
    free(pagerank_file_name);

	int max_index;
	long double max_value;

    if (weights_file  !=  NULL && pagerank_file != NULL) {

    	fprintf(weights_file, "%i %1.15Lf %i\n", nb_pages, alpha, nb_multiplications);
      	fprintf(pagerank_file, "%i\n", nb_pages);

    	for (int i=0; i < nb_pages; i++) { //Selection sort

    		max_index = 0;
    		max_value = vector_pi[0];

    		for (int j=0; j < nb_pages; j++) {

    			if (vector_pi[j] > max_value) {
    				max_index = j;
    				max_value = vector_pi[j];
    			}

    		}
    		vector_pi[max_index] = -1;
    		fprintf(weights_file, "%1.15Lf\n", max_value);
       		fprintf(pagerank_file, "%i\n", max_index);
    	}
    }

    else {
    	printf("Error: Unable to write output files"); //weights_file  ==  NULL || pagerank_file == NULL
    }

    fclose(pagerank_file);
    fclose(weights_file);

    printf("Success: Output files written\n");

    free(vector_pi);

	return EXIT_SUCCESS;
	
}

