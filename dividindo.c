#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>

int main() {
    FILE *saida = fopen("testando.txt","w");

    uint32_t rowsA = 735;

    for (uint32_t core = 0; core < 4; core++) {
        for (uint32_t i= core * rowsA/4; i < (core+1)*rowsA/4; i++) {
            fprintf(saida,"%d %f\n",i,i);
        }
        fprintf(saida,"\n");
    }

    return 0;
}