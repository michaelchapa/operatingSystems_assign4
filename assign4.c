#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

void generateRandom(int iArraySize);
void *selectionSort(void *params);
void printList(int iStart, int iEnd);
void printExecTime(clock_t start, clock_t end, int bMulti);

typedef struct param {
    int iArraySize;
    int iStart;
    int iEnd;
} param_t;

double *pUnsortedM, *pSortedM;

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "USAGE: %s <integer>\n", argv[0]);
        exit(1);
    }
    
    clock_t startExec, endExec; // stopwatch for execution time
    pthread_t tid;              // For multi-threading
    param_t params, params2;    // Param structure for thread
    int iArraySize = atoi(argv[1]), iMid;
    pUnsortedM = malloc(sizeof(double) * iArraySize);
    pSortedM = malloc(sizeof(double) * iArraySize);
    
    // Single thread execution and metrics
    if(argc != 2){
        fprintf(stderr, "USAGE: %s <integer>\n", argv[0]);
        exit(1);
    }
    
    // Single thread execution and metrics
    generateRandom(iArraySize);
    params = (param_t) {.iArraySize = iArraySize, .iStart = 0, .iEnd = iArraySize};
    startExec = clock();
    selectionSort((void *) &params); // Pass params struct
    endExec = clock();
    printExecTime(startExec, endExec, 0);
    
    // 2 thread execution and metrics
    generateRandom(iArraySize);
    iMid = iArraySize / 2;
    params = (param_t) {.iArraySize = iArraySize, .iStart = 0, .iEnd = iMid};
    params2 = (param_t) {.iArraySize = iArraySize, .iStart = iMid, .iEnd = iArraySize};
    
    startExec = clock();
    selectionSort((void *) &params);
    pthread_create(&tid, NULL, selectionSort, (void *) &params2);
    endExec = clock();
    printExecTime(startExec, endExec, 1);
    
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
void *selectionSort(void *params){
    param_t *pParams = (param_t *)params; // we can use pointer access now!
    int i, j, iMinIndex;
    double dTemp;

    for(i = pParams->iStart; i < pParams->iEnd; i++){
        iMinIndex = i;
        for(j = i + 1; j < pParams->iEnd; j++){
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
void printExecTime(clock_t start, clock_t end, int bMulti){
    double dTime = (double) (end - start) / CLOCKS_PER_SEC;
    dTime = dTime * 1000.0; // Seconds to Milliseconds :P

    if(bMulti)
        printf("Sorting is done in %.1lfms when two threads are used\n", dTime);
    else
        printf("Sorting is done in %.1lfms when one thread is used\n", dTime);
}
