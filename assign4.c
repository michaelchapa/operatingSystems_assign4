#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void generateRandom(int iArraySize);
void selectionSort(int iStart, int iEnd);
void printList(int iStart, int iEnd); // TODO remove from final
void printExecTime(clock_t start, clock_t end);

double *pUnsortedM, *pSortedM;

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "USAGE: %s <integer>\n", argv[0]);
        exit(1);
    }
    
    clock_t startExec, endExec; // stopwatch for execution time
    int iArraySize = atoi(argv[1]);
    pUnsortedM = malloc(sizeof(double) * iArraySize);
    pSortedM = malloc(sizeof(double) * iArraySize);
    
    generateRandom(iArraySize);
    startExec = clock();
    selectionSort(0, iArraySize);
    endExec = clock();
    printExecTime(startExec, endExec);

    free(pUnsortedM);
    free(pSortedM);

    return 0;
}

// Populates pUnsortedM with (n) random elements
void generateRandom(int iArraySize){
    srand(time(0)); // Seed for rand()
    int i;

    for(i = 0; i < iArraySize; i++){
        pUnsortedM[i] = (double) (rand() % 1000) + 1;
    }
}

// Sorts values in array from specified start to end indices
void selectionSort(int iStart, int iEnd){
    int i, j, iMinIndex;
    double dTemp;

    for(i = iStart; i < iEnd; i++){
        iMinIndex = i;
        for(j = i + 1; j < iEnd; j++){
            if(pUnsortedM[j] < pUnsortedM[iMinIndex])
                iMinIndex = j;
        }
        // insert values into the array
        dTemp = pUnsortedM[iMinIndex];
        pUnsortedM[iMinIndex] = pUnsortedM[i];
        pUnsortedM[i] = dTemp;
    }
}

// Prints out all values of the array
void printList(int iStart, int iEnd){
    int i;

    for(i = iStart; i < iEnd; i++)
        printf("%d: %lf\n", i, pUnsortedM[i]);
}

// Prints out execution time of program
void printExecTime(clock_t start, clock_t end){
    double dTime = (double) (end - start) / CLOCKS_PER_SEC;
    dTime = dTime * 1000.0; // Seconds to Milliseconds :P
    printf("Sorting is done in %.1lfms when one thread is used\n", dTime);
}
