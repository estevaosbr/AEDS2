#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionario.h"

TFunc *cria_funcionario(){
    TFunc *funcionario;
    funcionario = (TFunc *) malloc(sizeof(TFunc));
    printf("\nCodigo: ");
    scanf("%d",&funcionario->cod);
    printf("\nNome: ");
    fflush(stdin);
    gets(funcionario->nome);
    printf("\nCPF ");
    gets(funcionario->cpf);
    printf("\nData de nascimento:");
    gets(funcionario->data_nascimento);
    printf("\nSalario: ");
    scanf("%lf", &funcionario->salario);
    return funcionario;
}

void print_func(TFunc *func){
    printf("\nCodigo: %d", func->cod);
    printf("\nNome: %s", func->nome);
    printf("\nNascimento: %s", func->data_nascimento);
    printf("\nCPF: %s", func->cpf);
    printf("\nSalario: R$%.2lf", func->salario);
}

void salva(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    fwrite(func->nome, sizeof(char),sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char),sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char),sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}

int tamanho_arquivo(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq) / sizeof(TFunc);
    return tam;
}

void busca_seq(FILE *arq, int codigo){

    printf("--------------------------------------------------\n");
    double time_spent = 0.0;
    clock_t begin = clock();
    printf("BUSCANDO O CODIGO %d DE FORMA SEQUENCIAL", codigo);

    int comparacoes = 0;
    fseek(arq,0,SEEK_SET);
    TFunc *func = le(arq);

    while (func != NULL){
        comparacoes++;
        if (func->cod == codigo){
            printf("\nENCONTRADO!");
            print_func(func);
            break;
        }
        func = le(arq);
    }
    if (func == NULL){
        printf("\nNAO ENCONTRADO!");
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nO numero de comparacoes foi: %d",comparacoes);
    printf("\nTempo de execucao foi de %f segundos", time_spent);
    printf("\n--------------------------------------------------");
}

int busca_bin(TKey vetor[], int inicio, int fim, int item){

    int i = (inicio + fim) / 2;

    if (inicio > fim) {
        return -1;
    }
    if (vetor[i].key == item) {
        return i;
    }
    if (vetor[i].key < item) {
        return busca_bin(vetor, i + 1, fim, item);
    } else {
        return busca_bin(vetor, inicio, i - 1, item);
    }
}


void keysorting(FILE *arq, int codigo){

    TKey vetor[tamanho_arquivo(arq)];
    int i = 0;
    fseek(arq,0,SEEK_SET);
    TFunc *func = le(arq);

    while (i < (sizeof(vetor)/sizeof(TKey))){
        vetor[i].key = func->cod;
        vetor[i].pos = ftell(arq);
        func = le(arq);
        i++;
    }

    printf("\nVETOR PARA GUARDAR AS CHAVES E RRNs DOS REGISTROS\n\n");

    double time_spent = 0.0;
    clock_t begin = clock();
    printf("Indices desordenados, em ordem de acordo com a gravacao: \n");
    for (i = 0; i < (sizeof(vetor)/sizeof(TKey)); i++){
        printf("%d ",vetor[i].key);
    }

    printf("\n\nORDENACAO USANDO INSERTIONSORT: \n");
    int k, j;
    TKey aux;
    for (k = 1; k <= (sizeof(vetor)/sizeof(TKey)-1) ; k++){
        aux = vetor[k];
        j = k - 1;
        while (j >= 0 && aux.key < vetor[j].key) {
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao foi de %f segundos\n",time_spent);


    printf("\nOrdenado: \n");
    for (i = 0; i < (sizeof(vetor)/sizeof(TKey)); i++){
        printf("%d ",vetor[i].key);
    }

    printf("\n\n--------------------------------------------------\n");
    printf("BUSCANDO O CODIGO %d DE FORMA BINARIA",codigo);
    int indice;
    double time_spent1 = 0.0;
    clock_t begin1 = clock();
    indice = busca_bin(vetor,0,(sizeof(vetor)/sizeof(TKey)),codigo);
    if (indice != -1){
        printf("\nENCONTRADO!");
    }
    else{
        printf("\nNAO ENCONTRADO!");
        return;
    }

    fseek(arq,vetor[indice].pos-sizeof(TFunc),SEEK_SET);
    print_func(le(arq));

    clock_t end2 = clock();
    time_spent1 += (double)(end2 - begin1) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao foi de %f segundos\n",time_spent1);
}

