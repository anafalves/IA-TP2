#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "defaults.h"
// Estrutura para armazenar parametros
struct info
{
    int     popsize;
    // Probabilidade de muta��o
    float   pm;
    // Probabilidade de recombina��o
    float   pr;
    // Tamanho do torneio para sele��o do pai da pr�xima gera��o
    int     tsize;	
    // N de genes = nVertices
    int     numGenes;
    // N�mero de gera��es
    int     numGenerations;
    //Numero de relaçóoes = nArestas
    int     numRelacoes; //narestas
};

// Individuo (solu��o)
typedef struct individual chrom, *pchrom;

struct individual
{
    // Solu��o (objetos ) //MAX_RELACOES
    int     p[MAX_OBJ];
    // Valor da qualidade da solu��o
    float   fitness;
    // 1 se for uma solu��o v�lida e 0 se n�o for
    int     valido;
};

void tournament(pchrom pop, struct info d, pchrom parents);

//void tournament_geral(pchrom pop, struct info d, pchrom);

void genetic_operators(pchrom parents, struct info d, pchrom);

void crossover(pchrom parents, struct info d, pchrom);

void mutation(pchrom offspring, struct info d);

void mutacao_por_troca(pchrom offspring, struct info d);

void recombinacao_dois_pontos_corte(pchrom parents, struct info d, pchrom offspring);
#endif	// ALGORITMO_H