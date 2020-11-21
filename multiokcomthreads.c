#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>

#define N 4


// Implementação com as matrizes em uma linha

uint32_t matrixNumber, rowsA, columnsA, rowsB, columnsB, matrixCounter=0;
// float **matrixA, **matrixB;
float *matrixA, *matrixB;
float *resultMatrix;

int step_i = 0;

// void matrixProduct(double *resultMatrix, float **matrixA, float **matrixB, uint32_t rowsA, uint32_t rowsB, uint32_t columnsA, uint32_t columnsB){
void matrixProduct(FILE* output){
	float sum = 0;
    int core = step_i++;
	for (uint32_t i=0; i < rowsA; i++) {
    // for (int i= core * rowsA/4; i < (core+1)*rowsA/4; i++) {
        // sum = 0;
        printf(" ");
        for (uint32_t j=0; j < columnsB; j++) {
            sum = 0;
            // resultMatrix[(i*columnsB) + j] = 0;
            for (uint32_t k=0; k < rowsB ; k++) {
                sum += matrixA[(i*rowsB)+k] * matrixB[(columnsB*k)+j];
                // sum = sum + matrixA[i][k] * matrixB[k][j];
            }
            /**
             matrixA[i][k] * matrixB[k][j] 
                
            */

            resultMatrix[(i*columnsB)+j] = sum;
            // if (resultMatrix[i][j] >= 0) fprintf(output," ");
            // if (abs(resultMatrix[i][j]) < 10) fprintf(output," ");
            // if (abs(resultMatrix[i][j]) < 100) fprintf(output," ",output);
            // fprintf(output,"%0.2f ",resultMatrix[i][j]);

            // if (resultMatrix[i][j] >= 0) printf(" ");
            // if (abs(resultMatrix[i][j]) < 10) printf(" ");
            // if (abs(resultMatrix[i][j]) < 100) printf(" ");
            // printf("%0.2f ",resultMatrix[i][j]);
            if (resultMatrix[(i*columnsB)+j] >= 0) printf(" ");
            if (abs(resultMatrix[(i*columnsB)+j]) < 10) printf(" ");
            if (abs(resultMatrix[(i*columnsB)+j]) < 100) printf(" ");
            printf("%0.2f ",resultMatrix[(i*columnsB)+j]);

            // if (sum >= 0) printf(" ");
            // printf("%0.2f ",sum);


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
	// FILE *file = fopen("pthread.input","r");
	FILE *file = fopen("servidorpthread.input","r");
    FILE *output = fopen("saida.output","w");

	if(file==NULL){
		printf("Vazio\n");
		exit(0);
	}
	fscanf(file,"%s",buffer);
	matrixNumber = atoi(buffer);
  
    
	while(!feof(file)) {
		fscanf(file,"%s",buffer);
		rowsA = atoi(buffer);
		fscanf(file,"%s",buffer);
		columnsA = atoi(buffer);
		
        // matrixA = malloc(rowsA * sizeof(float*));
        
        matrixA = malloc(rowsA*columnsA*sizeof(float));

		// for (int i=0; i < rowsA; i++) {
		// 	matrixA[i] = malloc(columnsA* sizeof(float));
		// 	for (int j=0; j < columnsA; j++) {
        // 		fscanf(file,"%s",buffer);
        //         // printf("%s ",buffer);
		// 		matrixA[i][j] = atof(buffer);
        //         // if (matrixA[i][j] >= 0) printf(" ");
		// 		// printf("%0.2f ",matrixA[i][j]);
		// 	}
		// 	// printf("\n");
		// }

        for (int i=0; i < rowsA; i++) {
			for (int j=0; j < columnsA; j++) {
        		fscanf(file,"%s",buffer);
				matrixA[(i*columnsA)+j] = atof(buffer);
			}
		}
		// printf("\n");

		fscanf(file,"%s",buffer);
		rowsB = atoi(buffer);
		fscanf(file,"%s",buffer);
		columnsB = atoi(buffer);
		matrixB = malloc(rowsB * columnsB * sizeof(float));
		// matrixB = malloc(rowsB * sizeof(float*));
		// for (int i=0; i < rowsB; i++) {
		// 	matrixB[i] = malloc(columnsB * sizeof(float));
		// 	for (int j=0; j < columnsB; j++) {
        // 		fscanf(file,"%s",buffer);
        //         // printf("%s ",buffer);
		// 		matrixB[i][j] = atof(buffer);
        //         // if (matrixB[i][j] >= 0) printf(" ");
		// 		// printf("%0.2f ",matrixB[i][j]);
		// 	}
		// 	// printf("\n");
		// }

        for (int i=0; i < rowsB; i++) {
			for (int j=0; j < columnsB; j++) {
        		fscanf(file,"%s",buffer);
				matrixB[(i*columnsB)+j] = atof(buffer);
			}
		}


		// printf("\n");
		resultMatrix = malloc(rowsA*columnsB*sizeof(float*));
        // for (int m=0; m < (rowsA); m++) {
        //     resultMatrix[m] = malloc((columnsB)*sizeof(float));
        // }
		
        // printf("M%d\n",matrixCounter);
		// if(matrixCounter == 0) matrixProduct(resultMatrix,matrixA,matrixB,rowsA,rowsB,columnsA,columnsB);
		matrixProduct(output);

		matrixCounter++;

		// printf("Matrix counter: %d",matrixCounter);
        if(matrixCounter == matrixNumber) break;
		printf("\n");
        // //printf("%s\n",buffer);
        
        
	}

	// for (int i = 0; i < N; i++) { 
    //     int* p; 
    //     pthread_create(&threads[i], NULL, matrixProduct, output); 
    // } 
  
    // // joining and waiting for all threads to complete 
    // for (int i = 0; i < N; i++)  
    //     pthread_join(threads[i], NULL);  


    // for (int i = 0 ; i < rowsA; i++)
    //     for (int j=0 ; i < columnsB; j++) {
    //         if (resultMatrix[i][j] >= 0) printf(" ");
    //         if (abs(resultMatrix[i][j]) < 10) printf(" ");
    //         if (abs(resultMatrix[i][j]) < 100) printf(" ");
    //         printf("%0.2f ",resultMatrix[i][j]);

    //     }   
  
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

	fclose(file);
	return 0;
}