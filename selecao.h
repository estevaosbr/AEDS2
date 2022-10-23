#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionario.h"


typedef struct{
    TFunc *func;
    int congelado; //0 - normal \ 1 - congelado
}TVet;

typedef struct{
    char *nome;
    int fim;
}TVFile;

void selecao_sub_aux(FILE *arq, char* nome, TVet* vetor, int m);
void selecao_sub(FILE *arq, int m);
void selecao_nat_aux(FILE *arq, char* nome, TVet* vetor, int m,FILE *reservatorio);
void selecao_nat(FILE *arq, int m);
int menor(TVet* vet, int tam);
int fimarq(FILE *arq);
void intercalacao(FILE *arq, int num_p);
