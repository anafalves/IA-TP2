#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"
#include "defaults.h"

// Leitura dos par�metros e dos dados do problema
// Par�metros de entrada: Nome do ficheiro e matriz a preencher com os vertices de pessoas
// Par�metros de sa�da: Devolve a estrutura com os par�metros
struct info init_data(char *nomeficheiro, int mat[][MAX_OBJ]) {
    struct info d;
    FILE *f;
    int i;
    char str[100];

    f = fopen(nomeficheiro, "r");
    if (!f) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    while (strcmp(str, "edge")) {
        // Lê o numero de iteracoes  
        fscanf(f, "%s", str);
    }

    // Numero de vertices
    fscanf(f, "%d", &d.numGenes);
    // Numero de ligacoes (quantas linhas estao a seguir)
    fscanf(f, "%d", &d.numRelacoes);

    if (!mat) {
        printf("Erro na alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }
    if (d.numGenes > MAX_OBJ) {
        printf("Demasiados nos!\n");
        exit(EXIT_FAILURE);
    }

    int vertice, aresta;
    for (i = 0; i < d.numRelacoes; i++) {
        fscanf(f, " e %d %d", &vertice, &aresta);
        mat[vertice - 1][aresta - 1] = 1;
        mat[aresta - 1][vertice - 1] = 1;
        //printf("[%d]%d %d\n", i, vertice, aresta);
    }

    d.pm = PM;
    d.pr = PR;
    d.popsize = POPSIZE;
    d.numGenerations = NGERACOES;
    d.tsize = TSIZE;

    fclose(f);
    return d;
}

void imprime_matriz(int mat[][MAX_OBJ], int vert) {
    for (int i = 0; i < vert; i++) {
        printf("\n");
        for (int j = 0; j < vert; j++) {
            printf("%d ", mat[i][j]);
        }
    }
}



// Criacao da populacao inicial. O vector e alocado dinamicamente
// Par�metro de entrada: Estrutura com par�metros do problema
// Par�metro de sa�da: Preenche a estrutura da popula��o apenas o vector bin�rio

pchrom init_pop(struct info d) {
    int i, j;
    pchrom indiv;

    indiv = malloc(sizeof (chrom) * d.popsize);
    if (indiv == NULL) {
        printf("Erro na alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < d.popsize; i++) {
        for (j = 0; j < d.numGenes; j++) //nvertices                       
            indiv[i].p[j] = flip(); //p = p[MAX_OBJ];
        indiv[i].fitness = 0.0;
    }
    return indiv;
}

// Actualiza a melhor solu��o encontrada
// Par�metro de entrada: populacao actual (pop), estrutura com par�metros (d)
// e a melhor solucao encontrada at� a gera��oo imediatamente anterior (best)
// Par�metro de sa�da: a melhor solucao encontrada at� a gera��o actual

chrom get_best(pchrom pop, struct info d, chrom best) {
    int i;

    for (i = 0; i < d.popsize; i++) {
        if (best.fitness < pop[i].fitness)
            best = pop[i];
    }
    return best;
}


// Escreve uma solu��o na consola
// Par�metro de entrada: populacao actual (pop) e estrutura com par�metros (d)

void write_best(chrom x, struct info d) {
    int i;

    printf("\nBest individual: %4.1f\n", x.fitness);
    for (i = 0; i < d.numGenes; i++)
        printf("%d", x.p[i]);
    putchar('\n');
}

// Devolve um valor inteiro distribuido uniformemente entre min e max

int random_l_h(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1

float rand_01() {
    return ((float) rand()) / RAND_MAX;
}

// Inicializa��o do gerador de n�meros aleat�rios

void init_rand() {
    srand((unsigned) time(NULL));
}

// Simula o lan�amento de uma moeda, retornando o valor 0 ou 1

int flip() {
    if ((((float) rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}

void grava_testes_ficheiro(char *nome_fich_original, char *nome_fich_guarda,
        int nGenes, int nRelacoes, float mbf_global, int runs, double dif,
        float prob_mut, float prob_rep, int pop_size, int n_geracoes) {

    FILE *f;
    f = fopen(nome_fich_guarda, "a");

    if (f == NULL) {
        printf("Asneira na abertura do ficheiro %s", nome_fich_guarda);
        return;
    }

    fprintf(f, "%s %d %d %.4f %d %.2lf %.2f %.2f %d %d\n", nome_fich_original, nGenes, nRelacoes, mbf_global, runs, dif, prob_mut, prob_rep, pop_size, n_geracoes);
    /*
      grava_testes_ficheiro(nome_fich, FICHEIRO_TESTES,
        EA_param.numGenes, EA_param.numRelacoes,
        mbf_global, runs, best_ever, dif, PM, PR, POPSIZE, NGERACOES)
     */
    fclose(f);
}
