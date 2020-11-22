#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>

#define N 4


uint32_t matrixNumber, *rowsA, *columnsA, *rowsB, *columnsB, matrixCounter=0;
float **matrixA, **matrixB, **resultMatrix;
// float *matrixA, *matrixB, *resultMatrix;

int aux = 0;

// void matrixProduct(double *resultMatrix, float **matrixA, float **matrixB, uint32_t rowsA, uint32_t rowsB, uint32_t columnsA, uint32_t columnsB){
void matrixProduct(uint32_t matrixCounter){
	float sum = 0;
    int thread = aux++;
    // printf("%d\n",aux);
	// for (uint32_t i=0; i < rowsA; i++) {
    for (int i= thread * rowsA[matrixCounter]/4; i < (thread+1)*rowsA[matrixCounter]/4; i++) {
        // sum = 0;
        // printf(" ");
        for (uint32_t j=0; j < columnsB[matrixCounter]; j++) {
            sum = 0;
            // resultMatrix[(i*columnsB) + j] = 0;
            for (uint32_t k=0; k < rowsB[matrixCounter] ; k++) {
                sum += matrixA[matrixCounter][(i*rowsB[matrixCounter])+k] * matrixB[matrixCounter][(columnsB[matrixCounter]*k)+j];
                // sum = sum + matrixA[i][k] * matrixB[k][j];
            }
            /**
             matrixA[i][k] * matrixB[k][j] 
                
            */

            // resultMatrix[(i*columnsB)+j] = sum;
            resultMatrix[matrixCounter][(i*columnsB[matrixCounter])+j] = sum;

            // if (resultMatrix[i][j] >= 0) fprintf(output," ");
            // if (abs(resultMatrix[i][j]) < 10) fprintf(output," ");
            // if (abs(resultMatrix[i][j]) < 100) fprintf(output," ",output);
            // fprintf(output,"%0.2f ",resultMatrix[i][j]);

            // if (resultMatrix[i][j] >= 0) printf(" ");
            // if (abs(resultMatrix[i][j]) < 10) printf(" ");
            // if (abs(resultMatrix[i][j]) < 100) printf(" ");
            // printf("%0.2f ",resultMatrix[i][j]);


            // if (resultMatrix[(i*columnsB)+j] >= 0) printf(" ");
            // if (abs(resultMatrix[(i*columnsB)+j]) < 10) printf(" ");
            // if (abs(resultMatrix[(i*columnsB)+j]) < 100) printf(" ");
            // printf("%0.2f ",resultMatrix[(i*columnsB)+j]);

            // if (resultMatrix[matrixCounter][(i*columnsB)+j] >= 0) printf(" ");
            // if (abs(resultMatrix[matrixCounter][(i*columnsB)+j]) < 10) printf(" ");
            // if (abs(resultMatrix[matrixCounter][(i*columnsB)+j]) < 100) printf(" ");
            // printf("%0.2f ",resultMatrix[matrixCounter][(i*columnsB)+j]);
            // if(i == rowsA -1 && j == columnsB - 1) printf("%0.2f ",resultMatrix[matrixCounter][(i*columnsB)+j]);

            // if (sum >= 0) printf(" ");
            // printf("%0.2f ",sum);


        }
        printf("\n");
    }
}



int main(int nArgs,char* arquivo[]){
// int main(){

	// uint32_t matrixNumber, rowsA, columnsA, rowsB, columnsB, matrixCounter=0;
	// float **matrixA, **matrixB;
	// double *resultMatrix;
	

	pthread_t threads[N];

    char buffer[20];

	FILE *file = fopen(arquivo[1],"r");
    FILE *output = fopen(arquivo[2],"w");
	// FILE *file = fopen("pthread.input","r");
	// FILE *file = fopen("servidorpthread.input","r");
    // FILE *output = fopen("saida.output","w");

	if(file==NULL){
		printf("Vazio\n");
		exit(0);
	}
	fscanf(file,"%s",buffer);
	matrixNumber = atoi(buffer);

    matrixA = malloc(matrixNumber * sizeof(float*));
    matrixB = malloc(matrixNumber * sizeof(float*));
    resultMatrix = malloc(matrixNumber * sizeof(float*));

    rowsA = malloc(matrixNumber * sizeof(uint32_t));
    rowsB = malloc(matrixNumber * sizeof(uint32_t));
    columnsA = malloc(matrixNumber * sizeof(uint32_t));
    columnsB = malloc(matrixNumber * sizeof(uint32_t));
    
	while(!feof(file)) {
		fscanf(file,"%s",buffer);
		rowsA[matrixCounter] = atoi(buffer);
		fscanf(file,"%s",buffer);
		columnsA[matrixCounter] = atoi(buffer);
		
        // matrixA = malloc(rowsA * sizeof(float*));
        // matrixA = malloc(rowsA*columnsA*sizeof(float));



        matrixA[matrixCounter] = malloc(rowsA[matrixCounter]*columnsA[matrixCounter]*sizeof(float));



        for (int i=0; i < rowsA[matrixCounter]; i++) {
			for (int j=0; j < columnsA[matrixCounter]; j++) {
        		fscanf(file,"%s",buffer);
				matrixA[matrixCounter][(i*columnsA[matrixCounter])+j] = atof(buffer);
                // matrixA[(i*columnsA)+j] = atof(buffer);
			}
		}
		// printf("\n");

		fscanf(file,"%s",buffer);
		rowsB[matrixCounter] = atoi(buffer);
		fscanf(file,"%s",buffer);
		columnsB[matrixCounter] = atoi(buffer);

        matrixB[matrixCounter] = malloc(rowsB[matrixCounter] * columnsB[matrixCounter] * sizeof(float));

		resultMatrix[matrixCounter] = malloc(rowsA[matrixCounter] * columnsB[matrixCounter] * sizeof(float));
        // resultMatrix= malloc(rowsA * columnsB * sizeof(float));


        for (int i=0; i < rowsB[matrixCounter]; i++) {
			for (int j=0; j < columnsB[matrixCounter]; j++) {
        		fscanf(file,"%s",buffer);
				matrixB[matrixCounter][(i*columnsB[matrixCounter])+j] = atof(buffer);
                // matrixB[(i*columnsB)+j] = atof(buffer);
			}
		}
		
        // printf("M%d\n",matrixCounter);
		// matrixProduct(matrixCounter);

        
        for (uint32_t i = 0; i < N; i++) { 
            int* p;
            if((rowsA[matrixCounter]/4)  ) 
            pthread_create(&threads[i], NULL, matrixProduct, matrixCounter); 
        }
        
        for (int i = 0; i < N; i++)  
            pthread_join(threads[i], NULL);
        aux = 0;  




		matrixCounter++;

        
        

		// printf("Matrix counter: %d",matrixCounter);
        if(matrixCounter == matrixNumber) break;
		printf("\n");
        // //printf("%s\n",buffer);
        
        
	}
    // for (uint32_t contador=0; contador < matrixNumber; contador++) {
    //     matrixProduct(contador);
    //     printf("\n");
    // }
    // matrixProduct(output,0);

	// for (int j=0; j < matrixNumber ; j++){
    //     for (int i = 0; i < N; i++) { 
    //         int* p; 
    //         pthread_create(&threads[i], NULL, matrixProduct, j); 
    //     }
    //     for (int i = 0; i < N; i++)  
    //         pthread_join(threads[i], NULL);  
    // }

    for (uint32_t i = 0; i < matrixNumber; i++) {
        fprintf(output,"M%d\n",i);
        for (uint32_t j = 0; j < rowsA[i]; j++) {
            // fprintf(output," ");
            for (uint32_t k=0; k < columnsB[i]; k++) {
                if (resultMatrix[i][(j*columnsB[i])+k] >= 0) fprintf(output," ");
                if (abs(resultMatrix[i][(j*columnsB[i])+k]) < 10) fprintf(output," ");
                if (abs(resultMatrix[i][(j*columnsB[i])+k]) < 100) fprintf(output," ");
                fprintf(output,"%0.2f",resultMatrix[i][(j*columnsB[i])+k]);
                // if(j == rowsA -1 && k == columnsB - 1) fprintf(output,"%0.2f ",resultMatrix[i][(j*columnsB)+k]);
            }
            fprintf(output,"\n");
        }
        // fprintf(output,"\n");      
        
    }

	free(matrixA);
	free(matrixB);
	free(resultMatrix);
	fclose(file);
	return 0;
}