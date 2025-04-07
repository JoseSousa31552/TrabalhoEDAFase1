#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "Structs.h"
#include "ASSFunco.h"

#pragma warning(disable : 4996)

int main() {
    int opcao;
    antena* lista_antenas = NULL;
    nefasto* lista_nefastos = NULL;
    char nome_ficheiro[100];
    do {
        printf("\nMenu:\n");
        printf("1. Carregar antenas do ficheiro\n");
        printf("2. Mostrar matriz de antenas\n");
        printf("3. Calcular e mostrar efeitos nefastos\n");
        printf("4. Inserir nova antena\n");
        printf("5. Remover antena\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Digite o nome do ficheiro: ");
            scanf("%s", nome_ficheiro);
            lista_antenas = CarregarAntenasDoFicheiro(nome_ficheiro);
            if (lista_antenas != NULL) {
                printf("Antenas carregadas com sucesso!\n");
            }
            else return 1;
            break;

        case 2:
            if (lista_antenas == NULL) {
                printf("Nenhuma antena carregada ainda.\n");
            }
            else {
                mostrarMatrizAntenas(lista_antenas);
            }
            break;

        case 3:
            if (lista_antenas == NULL) {
                printf("Nenhuma antena carregada ainda.\n");
            }
            else {
                
                lista_nefastos = calcularEfeitoNefastoFinal(lista_antenas);
                mostrarMatrizNefastos(lista_antenas, lista_nefastos);
            }
            break;

        case 4: {
            int linha, coluna;
            char frequencia;
            printf("Digite a linha: ");
            scanf("%d", &linha);
            printf("Digite a coluna: ");
            scanf("%d", &coluna);
            printf("Digite a frequencia: ");
            scanf(" %c", &frequencia);

            antena* nova = CriarAntena(coluna, linha, frequencia);
            lista_antenas = insereOrdenado(lista_antenas, nova);
            printf("Antena inserida com sucesso!\n");
            break;
        }

        case 5: {
            int linha, coluna;
            printf("Digite a linha: ");
            scanf("%d", &linha);
            printf("Digite a coluna: ");
            scanf("%d", &coluna);

            if (procurarantena(lista_antenas, linha, coluna) != NULL) {
                
                lista_antenas = removerantena(lista_antenas, linha, coluna);
                printf("Antena removida.\n");
            }
            else{
                printf("A antena nao existe\n");
            }
            break;
        }

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);


    libertarListaAntenas(lista_antenas);
    libertarListaNefasto(lista_nefastos);

    return 0;
}
