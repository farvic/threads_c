#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


//int main(int nArgs,char* arquivo[]){
char c, buffer[50];

void matrixReader(uint32_t rows, uint32_t columns, FILE *file, float **matrixA) {
	// float *matrixA, *matrixB;
	
	printf("hel");
	while(!feof(file)) {
		fscanf(file,"%s",&buffer);
		rows = atoi(buffer);
		fscanf(file,"%s",&buffer);
		columns = atoi(buffer);
		*matrixA = malloc(rows * columns & sizeof(int));
		for (int i=0; i < rows; i++) {
			for (int j=0; j < columns; j++) {
        		fscanf(file,"%s",&buffer);
				// if(strcmp("-",&buffer[0]) == 0) printf("%c",buffer[0]);
				// printf("%c",buffer[0]);
				(*matrixA)[(i+columns) + j] = atof(buffer);
				printf("%f",(*matrixA)[(i+columns) + j]);
				// if (matrixA[(i+columns) + j] >= 0) printf(" ");
				// printf("%0.2f ",matrixA[(i+columns) + j]);
			}
			// printf("\n");
		}
		// printf("\n");
        // //printf("%s\n",buffer);
		// free(matrixA);
	}
}

int main(){
	uint32_t matrixNumber, rows, columns;
	float *matrixA, *matrixB;

	//FILE * file = fopen (arquivo[1] , " r " ) ;
	FILE *file = fopen("pthread.input","r");

	if(file==NULL){
		printf("Vazio\n");
		exit(0);
	}
	fscanf(file,"%s",&buffer);
	matrixNumber = atoi(buffer);
	// fscanf(file,"%s",&buffer);
	// rows = atoi(buffer);
	// fscanf(file,"%s",&buffer);
	// columns = atoi(buffer);
	// printf("MatrixssNumbers: %d\nRows:%d\nColumns:%d\n",matrixNumber,rows,columns);

	matrixReader(rows, columns, file, &matrixA);
	for (int i=0; i < rows; i++) {
		for (int j=0; j < columns; j++) {
			if (matrixA[(i+columns) + j] >= 0) printf(" ");
			printf("%0.2f ",matrixA[(i+columns) + j]);
		}
		printf("\n");
	}
	printf("\n");
	// while(!feof(file)) {

	// 	fscanf(file,"%s",&buffer);
	// 	rows = atoi(buffer);
	// 	fscanf(file,"%s",&buffer);
	// 	columns = atoi(buffer);
	// 	matrixA = malloc(rows * columns & sizeof(int));
	// 	for (int i=0; i < rows; i++) {
	// 		for (int j=0; j < columns; j++) {
    //     		fscanf(file,"%s",&buffer);
	// 			matrixA[(i+columns) + j] = atof(buffer);
	// 			printf("%0.2f ",matrixA[(i+columns) + j]);
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("\n");
    //     // //printf("%s\n",buffer);
		
	// 	free(matrixA);
	// }

	fclose(file);
	return 0;
}