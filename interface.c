#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void MSG_MENU(){
    system("cls");
    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. CRIAR E ADICIONAR FUNCIONARIO;");
    printf("\n\t2. BUSCA SEQUENCIAL;");
    printf("\n\t3. KEYSORTING COM BUSCA BINARIA;");
    printf("\n\t4. SELECAO POR SUBSTITUICAO;");
    printf("\n\t5. SELECAO NATURAL;");
    printf("\n\t6. HASH;");
    printf("\n\t7. SAIR.");
    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}

void MSG_MENU6(){
    system("cls");
    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. CRIAR TABELA HASH;");
    printf("\n\t2. BUSCA EM HASH;");
    printf("\n\t3. IMPRIMIR TABELA HASH;");
    printf("\n\t4. SAIR.");
    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}

void MENU6(){
    int opcao=0,i,busc;
    Hash *tab;
    tab = (Hash *)malloc(100*sizeof(Hash));
    int tamanho = 100;
    inicializa(tab,tamanho);
    FILE *arq = fopen("pessoas.dat","rb");
    TCelula *celula;
    celula = (TCelula *)malloc(sizeof(TCelula));
    celula->info.cod=0;
    celula->info.pos=0;
    celula->prox=NULL;
    TFunc *func;
    do{
        MSG_MENU6();
        printf("\n\nDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                for(i = 0;i < tamanho; i++){
                    celula->info.pos=ftell(arq);
                    func = le(arq);
                    celula->info.cod = func->cod;
                    insere(tab,tamanho,celula);
                }
                system("PAUSE");
                break;
            case 2:
                printf("\nDIGITE O CODIGO DO FUNCIONARIO: ");
                fflush(stdin);
                scanf("%d", &busc);
                printf("qualquer coisa");
                printf("%d",busca(tab,tamanho,busc));
                fseek(arq,busca(tab,tamanho,busc),SEEK_SET);
                print_func(le(arq));
                system("PAUSE");
                break;
            case 3:
                imprime(tab,100);
                system("PAUSE");
                break;
            case 4:
                system("cls");
                printf("\n\n\t >>>>>> MSG: Saindo do programa... <<<<<<\n\n");
                fclose(arq);
                system("PAUSE");
                break;
            default:
                printf("\n\n\t >>>>>> ERROR: Digite uma opcao valida!!! <<<<<<\n\n\n");
                system("PAUSE");
            }

        }
    while(opcao!=4);

}

void MENU(){
    int codigo=0;
    int opcao=0;
    do
    {
        FILE *arq = fopen("pessoas.dat","a+b");
        FILE *arq2 = fopen("pessoas.dat","rb");
        TFunc* func;
        MSG_MENU();
        printf("\n\nDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                func = cria_funcionario();
                print_func(func);
                salva(func,arq);
                system("PAUSE");
                break;
            case 2:
                printf("Escolha o codigo do funcionario para busca: \n");
                fflush(stdin);
                scanf("%d", &codigo);
                busca_seq(arq,codigo);
                system("PAUSE");
                break;
            case 3:
                printf("Escolha o codigo do funcionario para busca: \n");
                fflush(stdin);
                scanf("%d", &codigo);
                keysorting(arq,codigo);
                printf("\n");
                system("PAUSE");
                break;
            case 4:
                selecao_sub(arq2,6);
                printf("\nPARTICOES CRIADAS COM SUCESSO");
                printf("\n");
                system("PAUSE");
                break;
            case 5:
                selecao_nat(arq2,6);
                printf("\nPARTICOES CRIADAS COM SUCESSO");
                printf("\n");
                system("PAUSE");
                break;
            case 6:
                MENU6();
            case 7:
                system("cls");
                printf("\n\n\t >>>>>> MSG: Saindo do programa... <<<<<<\n\n");
                fclose(arq);
                fclose(arq2);
                system("PAUSE");
                break;
            default:
                printf("\n\n\t >>>>>> ERROR: Digite uma opcao valida!!! <<<<<<\n\n\n");
                system("PAUSE");
            }
    }
    while(opcao != 7);
}

