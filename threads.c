#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>

#define N 4

uint32_t matrixNumber, rowsA, columnsA, rowsB, columnsB, matrixCounter=0;
float **matrixA, **matrixB;
double *resultMatrix;

int step_i = 0;

// void matrixProduct(double *resultMatrix, float **matrixA, float **matrixB, uint32_t rowsA, uint32_t rowsB, uint32_t columnsA, uint32_t columnsB){
void matrixProduct(void* arg){
	double sum = 0;
	int core = step_i++;
	for (int i= core * rowsA/4; i < (core+1)*rowsA/4; i++) {
			// sum = 0;
			for (int j=0; j < columnsB; j++) {
				sum = 0;
				// resultMatrix[(i*columnsB) + j] = 0;
				for (int k=0; k < rowsB ; k++) {
					// sum += matrixA[(i*columnsA)+k] * matrixB[(rowsB*k)+j];
					sum = sum + matrixA[i][k] * matrixB[k][j];
				}
				/**
				 matrixA[i][k] * matrixB[k][j] 
				 
				*/

				// resultMatrix[(i*columnsB) + j] = sum;
                // if (resultMatrix[(i*columnsB) + j] >= 0) printf(" ");
				// printf("%0.2f ",resultMatrix[(i*columnsB) + j]);

                if (sum >= 0) printf(" ");
				printf("%0.2f ",sum);


			}
			printf("\n");
		}
}



//int main(int nArgs,char* arquivo[]){
int main(){

	// uint32_t matrixNumber, rowsA, columnsA, rowsB, columnsB, matrixCounter=0;
	// float **matrixA, **matrixB;
	// double *resultMatrix;
	

	pthread_t threads[N];

    char buffer[20];

	//FILE * file = fopen (arquivo[1] , " r " );
	FILE *file = fopen("pthread.input","r");
	// FILE *file = fopen("servidorpthread.input","r");

	if(file==NULL){
		printf("Vazio\n");
		exit(0);
	}
	fscanf(file,"%s",buffer);
	matrixNumber = atoi(buffer);
	// fscanf(file,"%s",buffer);
	// rows = atoi(buffer);
	// fscanf(file,"%s",buffer);
	// columns = atoi(buffer);
	// printf("MatrixssNumbers: %d\nRows:%d\nColumns:%d\n",matrixNumber,rows,columns);
    // matrixA = malloc(matrixNumber * sizeof(float));
    // resultMatrix = malloc(matrixNumber * sizeof(float));
    
    
	while(!feof(file)) {
		fscanf(file,"%s",buffer);
		rowsA = atoi(buffer);
		fscanf(file,"%s",buffer);
		columnsA = atoi(buffer);
		matrixA = malloc(1000 * sizeof(float));
		for (int i=0; i < rowsA; i++) {
			matrixA[i] = malloc(1000 * sizeof(float));
			for (int j=0; j < columnsA; j++) {
        		fscanf(file,"%s",buffer);
                // printf("%s ",buffer);
				matrixA[i][j] = atof(buffer);
                // if (matrixA[i][j] >= 0) printf(" ");
				// printf("%0.2f ",matrixA[i][j]);
			}
			// printf("\n");
		}
		// printf("\n");

		fscanf(file,"%s",buffer);
		rowsB = atoi(buffer);
		fscanf(file,"%s",buffer);
		columnsB = atoi(buffer);
		// matrixB = malloc(rowsB * columnsB * sizeof(float));
		matrixB = malloc(1000 * sizeof(float));
		for (int i=0; i < rowsB; i++) {
			matrixB[i] = malloc(1000 * sizeof(float));
			for (int j=0; j < columnsB; j++) {
        		fscanf(file,"%s",buffer);
                // printf("%s ",buffer);
				matrixB[i][j] = atof(buffer);
                // if (matrixB[i][j] >= 0) printf(" ");
				// printf("%0.2f ",matrixB[i][j]);
			}
			// printf("\n");
		}
		// printf("\n");
		printf("M%d",matrixCounter);
		resultMatrix = malloc(rowsA*columnsB*sizeof(double));
		// printf("Multiplicacao %d \n",matrixCounter);
		
		// if(matrixCounter == 0) matrixProduct(resultMatrix,matrixA,matrixB,rowsA,rowsB,columnsA,columnsB);
		// matrixProduct();

		matrixCounter++;


        if(matrixCounter == matrixNumber) break;
		// printf("\n");
        // //printf("%s\n",buffer);
        
        
	}

	for (int i = 0; i < N; i++) { 
        int* p; 
        pthread_create(&threads[i], NULL, matrixProduct, (void*)(p)); 
    } 
  
    // joining and waiting for all threads to complete 
    for (int i = 0; i < N; i++)  
        pthread_join(threads[i], NULL);     
  
    // Displaying the result matrix 
    // cout << endl 
    //      << "Multiplication of A and B" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matC[i][j] << " ";         
    //     cout << endl; 
    // } 


	free(matrixA);
	free(matrixB);
	free(resultMatrix);
    // printf("%f",matrixA[3][(3*columns)+2]);
    // free(matrixA);

	fclose(file);
	return 0;
}