#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Funcionario{
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
}TFunc;

typedef struct{
    long int pos;
    int key;
}TKey;

TFunc *cria_funcionario();
void print_func(TFunc *func);
void salva(TFunc *func, FILE *out);
TFunc *le(FILE *in);
int tamanho_arquivo(FILE *arq);
void busca_seq(FILE *arq, int codigo);
int busca_bin(TKey vetor[], int inicio, int fim, int item);
void keysorting(FILE *arq, int codigo);
