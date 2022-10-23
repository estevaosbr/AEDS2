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

void libera(Hash *tab, int m) {
    int i;
    for (i = 0; i < m; i++) {
        if (tab[i]) {
            free(tab[i]);
        }
    }
}

int busca(Hash *tab, int m, int cod) {
    int pos = hash(cod, m);
    if(tab[pos] == NULL){
        return -1;
    }
    TCelula *p = tab[pos];
    printf("%ld",tab[pos]->info.pos);
    while((p != NULL && p->info.cod!= cod)){
        p = p->prox;
    }
    return p->info.pos;
}

void insere_aux(TCelula *atual, TCelula *prox){
    if(atual->prox == NULL){
        atual->prox=prox;
    }
    else{
        insere_aux(atual->prox,prox);
    }
}

void insere(Hash *tab, int m, TCelula *x) {
    int h = hash(x->info.cod, m);
    if(tab[h] == NULL){
        tab[h] = x;
    }
    else{
        insere_aux(tab[h],x);
    }
}

void imprime(Hash tab[], int m) {
    int i;
    for (i = 0; i < m; i++) {
        printf("\n%d: ", i);
        if (tab[i]!=NULL) {
            printf("\n");
            while (tab[i]!=NULL) {
                printf("\n\n %ld \n\n",tab[i]->info.pos);
                FILE *arquivo = fopen("pessoas.dat","rb");
                fseek(arquivo,tab[i]->info.pos,SEEK_SET);
                //print_func(le(arquivo));
                tab[i] = tab[i]->prox;
            }
        }
        else{
            printf("NULL\n");
        }
    }

}
