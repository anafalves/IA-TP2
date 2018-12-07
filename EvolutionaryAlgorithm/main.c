#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 64

#define FILE_NAME_DIR  "./files/c-fat200-1.clq"

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
        
    data = malloc(sizeof(int)*(*nPeople)*(*nPeople));
    if (!data) {
        printf("Erro na alocacao de memoria\n\n");
        exit(1);
    }
    
    data = calloc(tmpSize * tmpSize, sizeof(int));
    
    fgets (lineBuffer, MAX, f);
    
    while (fgets (lineBuffer, MAX, f) != NULL) 
    {
        sscanf(lineBuffer, "e %d %d", &auxPerson, &auxConnection);
                
        *(data +((auxPerson - 1) * tmpSize) + (auxConnection - 1)) = 1;        
    }
    
    
    
    return data;
}

void printData(int *data, int size) {
        
    printf("\t");
    for(int i=0; i<size; i++) {
        printf("P%d\t", i+1);
    }
    printf("\n");
    
    for(int i=0; i<size; i++) {
        printf("P%d --> \t", i+1);        
        for(int j=0; j<size; j++) {
            printf("%d\t", *(data + (i*size) + j));
        }
        printf("\n");
    }
    
}

void main(int argc, char *argv[])
{
/*
     if (argc != 2){
         printf("File not found\nClosing program...\n");
         exit(1);
     }
*/
                 
    int* data = NULL;
    int nPeople;
    int nConnections;
    
    data = initiateData(FILE_NAME_DIR, &nPeople, &nConnections);
    
    printData(data, nPeople);
    
}