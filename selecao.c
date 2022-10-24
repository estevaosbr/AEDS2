#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "selecao.h"

void selecao_sub_aux(FILE *arq, char* nome, TVet* vetor, int m){
    FILE *arq2 = fopen(nome, "a+b");
    int x=1;
    while(x!=0){
        int j, menor;

        for(j=0;j<m;j++){
            if(vetor[j].congelado==0){
                menor=j;
                break;
            }
            else{
                menor=-1;
            }
        }

        //marca o primeiro registro não congelado como o menor

        for(j=0;j<m;j++){
            if(vetor[j].congelado==0){
                if (vetor[j].func->cod<vetor[menor].func->cod){
                menor = j;
                }
            }
        }

        //procura entre os registros nao congelados qual o menor

        if(menor >= 0){
            salva(vetor[menor].func,arq2);      //salva na particao
            int aux = vetor[menor].func->cod;
            vetor[menor].func = le(arq);        //le o proximo registro
            if(vetor[menor].func->cod < aux){   //se for menor que o guardado, congela esse
                vetor[menor].congelado = 1;
            }
        }


        int f;
        for(f=0;f<m;f++){
            if(vetor[f].congelado==0){
                x=1;
                break;
            }
            else{
                x=0;
            }
        }

        //ve se tem algum descongelado, se tiver, continua ate todos estarem congelados

    }

    int k;
    for (k=0;k<m;k++){
        vetor[k].congelado = 0;
    }

    //descongela
    fclose(arq2);
}

void selecao_sub(FILE *arq, int m){
    int i=0;
    TVet* vetor = (TVet *) malloc(m * sizeof(TVet));
    while (!feof(arq)&&i<m){
        vetor[i].func = (TFunc *) malloc(sizeof(TFunc));
        vetor[i].func = le(arq);
        vetor[i].congelado = 0;
        i++;
    }

    i = 1;
    while (!feof(arq)){
        char* id = "pS";
        char arq2[10];
        snprintf (arq2, 10, "%s%d%s", id, i,".dat");
        selecao_sub_aux(arq,arq2,vetor,m);
        i++;
    }
}

void selecao_nat_aux(FILE *arq, char* nome, TVet* vetor, int m,FILE *reservatorio){
    FILE *arq1 = fopen(nome, "a+b");
    int res=6;
    while(res!=0){
        int j, menor=0;
        for(j=1;j<m;j++){
            if (vetor[j].func->cod<vetor[menor].func->cod){     //procura o menor valor
            menor = j;
            }
        }

        salva(vetor[menor].func,arq1);          //salva na particao
        int aux = vetor[menor].func->cod;
        vetor[menor].func = le(arq);
        if(vetor[menor].func->cod < aux){
            salva(vetor[menor].func,reservatorio);    //se o proximo registro for menor que o guardado, ele vai para reservatorio
            vetor[menor].func = le(arq);
            res = res - 1;
        }
    }

    fclose(arq1);
}

void selecao_nat(FILE *arq, int m){
    int i=0;
    TVet* vetor = (TVet *) malloc(m * sizeof(TVet));
    while (!feof(arq)&&i<m){
        vetor[i].func = (TFunc *) malloc(sizeof(TFunc));
        vetor[i].func = le(arq);
        vetor[i].congelado = 0;
        i++;
    }

    i = 1;
    while (!feof(arq)){
        FILE *reservatorio = fopen("reservatorio.dat","a+b");
        char* id = "pN";
        char arq2[10];
        snprintf (arq2, 10, "%s%d%s", id, i,".dat");
        selecao_nat_aux(arq,arq2,vetor,m,reservatorio);
        remove("reservatorio.dat");
        i++;
    }
}

void imprime_part(char* nome){
    FILE *arq = fopen(nome,"rb");
    printf("%s: \n",nome);
    while(1){
        TFunc *func = le(arq);
        if(feof(arq)){
            break;
        }
        //print_func(func);
        printf("\n%d",func->cod);
        //printf("\n\n");
    }
    fclose(arq);
}

void imprime_partSN(int tipo){
    int i;
    for(i =1;i<10;i++){
        if(tipo==1){
            char* id = "pN";
            char arq2[10];
            snprintf (arq2, 10, "%s%d%s", id, i,".dat");
            imprime_part(arq2);
            printf("\n\n\n");
        }
        if(tipo==2){
            char* id = "pS";
            char arq2[10];
            snprintf (arq2, 10, "%s%d%s", id, i,".dat");
            imprime_part(arq2);
            printf("\n\n\n");
        }
        printf("passei");
    }
}
