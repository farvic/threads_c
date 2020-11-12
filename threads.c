#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


//int main(int nArgs,char* arquivo[]){
int main(){
    char c;

	//FILE * file = fopen (arquivo[1] , " r " ) ;
	FILE *file = fopen("pthread.input","r");

	if(file==NULL){
		printf("Vazio\n");
		exit(0);
	}
    while(!feof(file)) {
        fscanf(file,"%c",&c);
        printf("%c",c);
    }
	// while(fscanf(file,"%s")!=EOF){
	// 		//printf("%s ",&code[n]);
	// 		//cmm[n] = code[n];
	// 		//printf("%s",&cmm[n]);
	// }
	fclose(file);
	return 0;
}