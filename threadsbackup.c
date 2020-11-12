#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


//int main(int nArgs,char* arquivo[]){
int main(){
    char c, buffer[50];
	uint32_t matrixNumber, rowsA, columnsA, rowsB, columnsB, matrixCounter;
	float *matrixA, *matrixB, *resultMatrix, sum;

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
    // matrixA = malloc(matrixNumber * sizeof(float));
    resultMatrix = malloc(matrixNumber * sizeof(float));
    
    
	while(!feof(file)) {
		fscanf(file,"%s",&buffer);
		rowsA = atoi(buffer);
		fscanf(file,"%s",&buffer);
		columnsA = atoi(buffer);
		matrixA = malloc(rowsA * columnsA * sizeof(float));
		for (int i=0; i < rowsA; i++) {
			for (int j=0; j < columnsA; j++) {
        		fscanf(file,"%s",&buffer);
                // printf("%s ",buffer);
				matrixA[(i*columnsA) + j] = atof(buffer);
                if (matrixA[(i*columnsA) + j] >= 0) printf(" ");
				printf("%0.2f ",matrixA[(i*columnsA) + j]);
			}
			printf("\n");
		}
		printf("\n");

		fscanf(file,"%s",&buffer);
		rowsB = atoi(buffer);
		fscanf(file,"%s",&buffer);
		columnsB = atoi(buffer);
		matrixB = malloc(rowsB * columnsB * sizeof(float));
		for (int i=0; i < rowsB; i++) {
			for (int j=0; j < columnsB; j++) {
        		fscanf(file,"%s",&buffer);
                // printf("%s ",buffer);
				matrixB[(i*columnsB) + j] = atof(buffer);
                if (matrixB[(i*columnsB) + j] >= 0) printf(" ");
				printf("%0.2f ",matrixB[(i*columnsB) + j]);
			}
			printf("\n");
		}
		printf("\n");
		resultMatrix = malloc(rowsA*columnsB*sizeof(float));
		printf("multiplicacao\n");
		for (int i=0; i < rowsA; i++) {
			// sum = 0;
			for (int j=0; j < columnsB; j++) {
				sum = 0;
				for (int k=0; k < rowsB ; k++) {
					sum += matrixA[(i*columnsA)+k] * matrixB[(rowsB*k)+j];
				}
				/**
				 matrixA[i][k] * matrixB[k][j] 
				 
				*/


				resultMatrix[(i*columnsB) + j] = sum;
                if (resultMatrix[(i*columnsB) + j] >= 0) printf(" ");
				printf("%0.2f ",resultMatrix[(i*columnsB) + j]);
			}
			printf("\n");
		}

		matrixCounter++;


        if(matrixCounter == matrixNumber) break;
		printf("\n");
        // //printf("%s\n",buffer);
        
        
		// free(matrixA);
	}
    // printf("%f",matrixA[3][(3*columns)+2]);
    // free(matrixA);

	fclose(file);
	return 0;
}