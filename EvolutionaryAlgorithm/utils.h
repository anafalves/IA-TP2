#ifndef UTILS_H
#define UTILS_H

#include "defaults.h"

void imprime_matriz(int mat[][MAX_OBJ], int vert) ;

int* init_dados(char *nome, int *n, int *lig);

struct info init_data(char *nomeficheiro, int mat[][MAX_OBJ]);

pchrom init_pop(struct info);

void print_pop(pchrom, struct info);

chrom get_best(pchrom, struct info, chrom);

void write_best(chrom, struct info);

void init_rand();

int random_l_h(int, int);

float rand_01();

int flip();

void grava_testes_ficheiro(char *nome_fich_original, char *nome_fich_guarda,
        int nGenes, int nRelacoes, float mbf_global, int runs,
        double dif, float prob_mut, float prob_rep, int pop_size, int n_geracoes);

#endif	// UTILS_H