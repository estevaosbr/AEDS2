#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "selecao.h"

typedef struct Info{
    int cod;
    long int pos;
}TInfo;

typedef struct TCelula{
    TInfo info;
    struct TCelula *prox;
}TCelula;

typedef TCelula *Hash; //Hash é um vetor que será alocado dinamicamente

void inicializa(Hash *tab, int m);
int hash(int cod, int tam);
void libera(Hash *tab, int m);
int busca(Hash *tab, int m, int cod);
void insere_aux(TCelula *atual, TCelula *prox);
void insere(Hash *tab, int m, TCelula *x);
void imprime(Hash *tab, int m);

