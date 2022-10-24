#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "selecao.h"

typedef struct TCelula{
    int cod;
    long int pos;
    struct TCelula *prox;
}TCelula;

typedef TCelula *Hash; //Hash é um vetor que será alocado dinamicamente

void inicializa(Hash *tab, int m);
int hash(int cod, int tam);
void busca(Hash *tab, int m, int cod);
TCelula *aloca(int cod, long int pos);
void insere_aux(TCelula *celula, int cod, long int pos);
void insere(Hash *tab, int m, int cod, long int pos);
void imprime(Hash *tab, int m);
