#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 64

int* initiateData(char *nome, int *nPeople, int *nConnections) {
    
    FILE *f;
    char lineBuffer[MAX];
    int *data;
    int auxPerson, auxConnection;
    int tmpSize;

    f = fopen(nome, "r");
    if (f == NULL) {
        perror("Failed: ");
    }
    
    while (fgets (lineBuffer, MAX, f) != NULL) 
    {
        if(lineBuffer[0] == 'p' )
            break;
    }
    
    sscanf(lineBuffer, "p edge %d %d", nPeople, nConnections );
    
    tmpSize = *nPeople;
    
    printf("%d, %d\n", tmpSize, *nConnections);
    
    data = malloc(sizeof(int)*(*nPeople)*(*nPeople));
    if (!data) {
        printf("Erro na alocacao de memoria\n\n");
        exit(1);
    }
    
    data = malloc(sizeof(int) * tmpSize * tmpSize);
    
    while (fgets (lineBuffer, MAX, f) != NULL) 
    {
        sscanf(lineBuffer, "e %d %d", &auxPerson, &auxConnection);
        
        printf("%d, %d\n", auxPerson, auxConnection);
        
        *(data +((auxPerson - 1) * tmpSize) + (auxConnection - 1)) = 1;        
    }
    
    return data;
}

void printData(int *data, int size) {
        
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            printf("%d\t", *(data + (i*size) + j));
        }
        printf("\n");
    }
    
}

void main()
{
    int *data = NULL;
    int nPeople;
    int nConnections;
    data = initiateData("./files/inst_teste.txt", &nPeople, &nConnections);
    
    printData(data, nPeople);
    
}