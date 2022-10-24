#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

//Implementacao do hash em memoria principal

void inicializa(Hash *tab, int m) {
    int i;
    for (i = 0; i < m; i++) {
        tab[i] = NULL;
    }
}

int hash(int cod, int tam) {
    return cod % tam;
}

void busca(Hash *tab, int m, int cod){
    int h = hash(cod,m);
    FILE *arq = fopen("pessoas.dat","r+b");
    TCelula *c = tab[h];
    if(tab[h]==NULL){
        printf("\n\nCODIGO DE FUNCIONARIO NAO ENCONTRADO!\n\n");
    }
    else{
        while(c!=NULL){
            if(c->cod==cod){
                fseek(arq,c->pos,SEEK_SET);
                print_func(le(arq));
                break;
            }
            c = c->prox;
        }
        if(c==NULL){
            printf("\n\nCODIGO DE FUNCIONARIO NAO ENCONTRADO!\n\n");
        }
    }
    fclose(arq);
}

TCelula *aloca(int cod, long int pos){
    TCelula *novo = (TCelula *)malloc(sizeof(TCelula));
    novo->cod = cod;
    novo->pos = pos;
    novo->prox = NULL;
    return novo;
}

void insere_aux(TCelula *celula, int cod, long int pos){
    if(celula->prox == NULL){
        celula->prox = aloca(cod,pos);
    }
    else{
        insere_aux(celula->prox,cod,pos);
    }
}

void insere(Hash *tab, int m, int cod, long int pos) {
    int h = hash(cod, m);
    if(tab[h] == NULL){
        tab[h] = aloca(cod,pos);
    }
    else{
        insere_aux(tab[h],cod,pos);
    }
}

void imprime(Hash tab[], int m) {
    int i;
    for (i = 0; i < m; i++) {
        printf("\n%d: ", i);
        if (tab[i]!=NULL) {
            printf("\n");
            while (tab[i]!=NULL) {
                FILE *arquivo = fopen("pessoas.dat","rb");
                fseek(arquivo,tab[i]->pos,SEEK_SET);
                print_func(le(arquivo));printf("\n");
                tab[i] = tab[i]->prox;
            }
        }
        else{
            printf("NULL\n");
        }
    }

}
