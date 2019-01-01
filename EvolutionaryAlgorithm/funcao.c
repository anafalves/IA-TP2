#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include "defaults.h"

// Calcula a qualidade de uma soluï¿½ï¿½o
// Parï¿½metros de entrada: soluï¿½ï¿½o (sol), numero de relaÃ§Ãµes/arestas (numRelacoes),
// matriz com dados do problema (mat) e numero de objectos (v)
// Parï¿½metros de saï¿½da: qualidade da soluï¿½ï¿½o 
float eval_individual_penalizado1(int sol[], struct info d, int mat[MAX_OBJ][MAX_OBJ], int *v) {
    int i, j;
    int conta_zero_sol = 0;
    int invalida = 0;
    int vert = d.numGenes;

    for (i = 0; i < vert; i++)
        if (sol[i] == 0)
            for (j = 0; j < vert; j++)
                // se a solucao for invalida, isto Ã©, se existirem ligacoes entre as pessoas
                if (sol[j] == 0 && mat[i][j] == 1)
                    invalida++;

    for (int j = 0; j < vert; j++)
        if (sol[j] == 0)
            conta_zero_sol++;


    if (invalida > 0)
        *v = 0;

    else
        *v = 1;

    //penalizacao = conta_zero_total - n.invalidas * n.vertices
    return conta_zero_sol - invalida*vert;
}

//penalização cega
float eval_individual_penalizado2(int sol[], struct info d, int mat[MAX_OBJ][MAX_OBJ], int *v) {
    int i, j;
    int conta_zero_sol = 0;
    int invalida = 0;
    int vert = d.numGenes;

    for (i = 0; i < vert; i++)
        if (sol[i] == 0)
            for (j = 0; j < vert; j++)
                // se a solucao for invalida, isto Ã©, se existirem ligacoes entre as pessoas
                if (sol[j] == 0 && mat[i][j] == 1)
                    invalida++;

    for (int j = 0; j < vert; j++)
        if (sol[j] == 0)
            conta_zero_sol++;

    return conta_zero_sol + invalida * 0.58; //retorna custo, total
}

// FunÃ§Ã£o para reparar a soluÃ§Ã£o
// Parametros: solucao, matriz de adjacencias(binaria), numero de vertices
// Coloca a zero os vÃ©rtices que nÃ£o estiverem ligados por uma aresta (invÃ¡lidos)
//float eval_individual_reparado1(int sol[], struct info d,int mat[MAX_OBJ][MAX_OBJ], int *v) {
void eval_individual_reparado1(int sol[], struct info d,int mat[MAX_OBJ][MAX_OBJ]) {
    float moeda; // variÃ¡vel auxiliar
    int i, j;
    int flag = 0;

    //percorre sol[] posicao a posicao
    do {
        flag = 0;
        for (i = 0; i < d.numGenes; i++) {
            for (j = 0; j < d.numGenes; j++) {
                //se nao for o mesmo vertice
                if (i != j) {
                    if (sol[i] == 1 && sol[j] == 1) {
                        if (mat[i][j] != 1) {
                            moeda = rand_01();
                            if (moeda <= 0.5){
                                sol[i] = 0;
                               // *v = 0;
                            }
                            else {
                                sol[j] = 1;
                                //*v = 1;
                            }
                            flag = 1;
                            break;
                            //Comecar de novo
                        }
                    }
                }
            }
        }
    } while (flag == 1);
    
    
  // TODO: ONDE ESTÁ O RETURN!?!?!?!? Como é que conseguiste pôr isto a compilar?
  //return fitness value.
}


//alterar parametros nesta função! **usar:
// - eval_individual_penalizado1(int sol[], struct info d, int *mat)
// - eval_individual_penalizado2(int sol[], struct info d, int *mat)
// - eval_individual_reparado1(int sol[], struct info d, int *mat); 
// - eval_individual_reparado2(int sol[], struct info d, int *mat);
// Avaliacao da populaï¿½ï¿½o
// Parï¿½metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Parï¿½metros de saï¿½da: Preenche pop com os valores de fitness e de validade para cada soluï¿½ï¿½o

void evaluate(pchrom pop, struct info d, int mat[MAX_OBJ][MAX_OBJ]) {
    int i;

    for (i = 0; i < d.popsize; i++)
       //   pop[i].fitness = eval_individual_penalizado1(pop[i].p, d, mat, &pop[i].valido);	
           eval_individual_reparado1(pop[i].p, d, mat);
}

void gera_vizinho(int sol[], int solViz[], int mat[MAX_OBJ][MAX_OBJ], int nGenes) {
    int i, menorCustoIn, maiorCustoOut, p1, p2;

    // Copia a solução para a solução vizinha
    for (i = 0; i < nGenes; i++)
        solViz[i] = sol[i];
    if (rand_01() < PROBGERAVIZ) {
        // escolhe um objeto aleatoriamente
        i = random_l_h(0, nGenes - 1);
        //gera vizinho de forma aleatoria
        for (i = 0; i < nGenes; i++) {
            solViz[i] = round(rand_01());
            if (sol[i] == solViz[i]) {
                solViz[i] = round(rand_01());
            }
        }
    } else {
        menorCustoIn = MAX_OBJ;
        maiorCustoOut = 0;

    }
}

void trepa_colinas(pchrom pop, struct info d, int mat[MAX_OBJ][MAX_OBJ]) {
    int i, j;
    chrom vizinho;

    for (i = 0; i < d.popsize; i++) {
        for (j = 0; j < GENERATIONS_TC; j++) {
            gera_vizinho(pop[i].p, vizinho.p, mat, d.numGenes);
            vizinho.fitness = eval_individual_penalizado2(vizinho.p, d, mat, &vizinho.valido);
            if (vizinho.fitness >= pop[i].fitness)
                pop[i] = vizinho;
        }
    }
}
