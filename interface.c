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
    printf("\n\t5. IMPRIMIR PARTICOES;");
    printf("\n\t7. HASH;");
    printf("\n\t8. SAIR.");
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
    int opcao=0,i,busc=0;
    Hash *tab;
    tab = (Hash *)malloc(100*sizeof(Hash));
    int tamanho = 100;
    inicializa(tab,tamanho);
    FILE *arq = fopen("pessoas.dat","rb");
    TFunc *func;
    do{
        MSG_MENU6();
        printf("\n\nDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                for(i = 0;i < tamanho; i++){
                    func = le(arq);
                    insere(tab,tamanho,func->cod,(ftell(arq)-sizeof(TFunc)));
                }
                system("PAUSE");
                break;
            case 2:
                printf("\n\nDigite um codigo para busca: ");
                fflush(stdin);
                scanf("%d", &busc);
                busca(tab,tamanho,busc);
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
    int codigo=0,codigo1=0;
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
                printf("1 - NATURAL / 2 - SUBSTITUICAO: \n");
                fflush(stdin);
                scanf("%d", &codigo1);
                imprime_partSN(codigo1);
                system("PAUSE");
                break;
            case 7:
                MENU6();
            case 8:
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
    while(opcao != 8);
}
