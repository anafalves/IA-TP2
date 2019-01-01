#ifndef FUNCAO_H
#define FUNCAO_H
#include "defaults.h"

float eval_individual_penalizado1(int sol[], struct info d, int mat[MAX_OBJ][MAX_OBJ], int *v);
float eval_individual_penalizado2(int sol[], struct info d,int mat[MAX_OBJ][MAX_OBJ], int *v);
//float eval_individual_reparado1(int sol[], struct info d,int mat[MAX_OBJ][MAX_OBJ], int *v) ;
void eval_individual_reparado1(int sol[], struct info d,int mat[MAX_OBJ][MAX_OBJ]) ;
void evaluate(pchrom pop, struct info d, int mat[MAX_OBJ][MAX_OBJ]);
void gera_vizinho(int sol[], int solViz[], int mat[MAX_OBJ][MAX_OBJ], int nGenes);
//void trepa_colinas(pchrom pop, struct info d, int mat[MAX_OBJ][MAX_OBJ]);


//void evaluate(pchrom pop, struct info, int *mat);

void trepa_colinas(pchrom pop, struct info d, int mat[MAX_OBJ][MAX_OBJ]);
#endif	// FUNCAO_H

