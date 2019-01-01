//#define _CRT_SECURE_NO_WARNINGS //gets
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"
#include "defaults.h"

/*_________________________NOTAS IMPORTANTES _________________________________*/

/* vÃ¡rias coisas a alterar para testes:
    - defines, consoante a tabela anexada, em utils.h (variar uma de cada vez, 
  conforme foi feito para o netlogo)
    - funÃ§Ã£o void trepa_colinas(pchrom pop, struct info d, int *mat), em funcao.c, 
  onde indica o tipo de reparacao/penalizacao a realizar, tambem ela variavel 
  conforme o teste
    - utilizar 3 intancias de testes diferentes: 
 * uma com poucos nÃ³s/vÃ©rtices
 * uma com nÃºmero intermÃ©dio de nÃ³s/vÃ©rtices
 * uma com muitos nÃ³s/vÃ©rtices    
 /*___________________________________________________________________________*/
int main(int argc, char **argv) {

    char nome_fich[100];
    struct info EA_param;
    pchrom parents = NULL, pop = NULL;
    chrom best_run, best_ever;
    int gen_atual, r, runs, i, inv, mat[MAX_OBJ][MAX_OBJ] = {0};
    float mbf = 0.0, perc_invalidos = 0.0, mbf_global = 0.0;

    //contagem de tempo, because why not
    time_t start, end;
    double dif;
    /*_________________________________________________________________________*/
    //inicia contagem de tempo
    time(&start);

    // Lï¿½ os argumentos de entrada
    if (argc == 3) {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    } else
        // Se o nï¿½mero de execuï¿½ï¿½es do processo nï¿½o for colocado nos argumentos de entrada, define-o com um valor por defeito
        if (argc == 2) {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    }// Se o nome do ficheiro de informaï¿½ï¿½es nï¿½o for colocado nos argumentos de entrada, pede-o novamente
    else {
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }
    // Se o nï¿½mero de execuï¿½ï¿½es do processo for menor ou igual a 0, termina o programa
    if (runs <= 0)
        return 0;
    // Inicializa a geraï¿½ï¿½o dos nï¿½meros aleatï¿½rios
    init_rand();
    // Preenche a matriz com dados com as pessoas e pessoas conhecidas e a estrutura EA_param que foram definidos no ficheiro de input
    EA_param = init_data(nome_fich, mat);
    //imprime_matriz(mat, EA_param.numGenes);

    // Faz um ciclo com o nï¿½mero de execuï¿½ï¿½es definidas
    for (r = 0; r < runs; r++) {
        //printf("Repeticao %d\n", r + 1);
        // Geraï¿½ï¿½o da populaï¿½ï¿½o inicial	
        // Como ainda nao existe, escolhe-se como melhor soluï¿½ï¿½o a primeira da populaï¿½ï¿½o (poderia ser outra qualquer)
        pop = init_pop(EA_param);

        // Avalia a populaï¿½ï¿½o inicial
        evaluate(pop, EA_param, mat);

        best_run = pop[0];
        // Encontra-se a melhor soluï¿½ï¿½o dentro de toda a populacao
        best_run = get_best(pop, EA_param, best_run);

        // Aplicaï¿½ï¿½o do algoritmo trepa colinas para refinar a populaï¿½ï¿½o inicial 
        // !!!!!!!!!!!so para hibrido!!!!!!!!!!!!!!!!!!
        // trepa_colinas(pop, EA_param, mat);               

        // Reserva espaï¿½o para os pais da populaï¿½ï¿½o seguinte
        parents = malloc(sizeof (chrom) * EA_param.popsize);
        // Caso nï¿½o consiga fazer a alocaï¿½ï¿½o, envia aviso e termina o programa
        if (parents == NULL) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }

        gen_atual = 1;


        // Ciclo de optimizaï¿½ï¿½o
        while (gen_atual <= EA_param.numGenerations) {
            // Torneio binï¿½rio para encontrar os progenitores (ficam armazenados no vector parents)
            tournament(pop, EA_param, parents);
            // Torneio de k elementos, com k >= 2, para encontrar os progenitores (ficam armazenados no vector parents)
            // Exercï¿½cio 4.5
            //            tournament_geral(pop, EA_param, parents);
            // Aplica os operadores genï¿½ticos aos pais (os descendentes ficam armazenados na estrutura pop)
            genetic_operators(parents, EA_param, pop);
            // Avalia a nova populaï¿½ï¿½o (a dos filhos)
            evaluate(pop, EA_param, mat);
            // Aplicaï¿½ï¿½o do algoritmo trepa colinas para refinar a populaï¿½ï¿½o final
            // !!!!HIBRIDO!!!!!!!!!!
            //  trepa_colinas(pop, EA_param, mat);
            // Actualiza a melhor soluï¿½ï¿½o encontrada
            best_run = get_best(pop, EA_param, best_run);
            gen_atual++;
        }

        // Contagem das soluï¿½ï¿½es invï¿½lidas
        for (inv = 0, i = 0; i < EA_param.popsize; i++)
            if (pop[i].valido == 0)
                inv++;
        // Escreve resultados da repetiï¿½ï¿½o que terminou
        //printf("\nRepeticao %d:", r);
        //write_best(best_run, EA_param);

        perc_invalidos += 100 * (float) inv / EA_param.popsize;
        //printf("\nPercentagem Invalidos: %f\n",  perc_invalidos);
        mbf += best_run.fitness;
        if (r == 0 || best_run.fitness > best_ever.fitness) //maximização
            best_ever = best_run;
        // Liberta a memï¿½ria usada
        free(parents);
        free(pop);
    }

    // Escreve resultados globais
    mbf_global = mbf / r;
    printf("\n\nMBF: %f\n", mbf_global);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, EA_param);
    time(&end);
    dif = difftime(end, start);

    //grava em ficheiro
    grava_testes_ficheiro(nome_fich, FICHEIRO_TESTES,
            EA_param.numGenes, EA_param.numRelacoes,
            mbf_global, runs, dif, PM, PR, POPSIZE, NGERACOES);



    return 0;
}