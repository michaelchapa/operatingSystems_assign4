#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double *pUnsortedM, *pSortedM;

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "USAGE: %s <integer>\n", argv[0]);
        exit(1);
    }

    int iArraySize = atoi(argv[1]);
    pUnsortedM = malloc(sizeof(double) * iArraySize);
    pSortedM = malloc(sizeof(double) * iArraySize);
    
    generateRandom(iArraySize);

    free(pUnsortedM);
    free(pSortedM);

    return 0;
}

// Populates pUnsortedM with (n) random elements
void generateRandom(int iArraySize){
    srand(time(0)); // Use current time to seed random()
    int i;

    for(i = 0; i < iArraySize; i++){
        pUnsortedM[i] = (double) (rand() % 1000) + 1;
    }
}
