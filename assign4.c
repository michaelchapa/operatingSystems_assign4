#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "USAGE: %s <integer>\n", argv[0]);
        exit(1);
    }

    int iArraySize = atoi(argv[1]);

    printf("%d\n", iArraySize);

    return 0;
}
