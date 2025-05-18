#include "STRUCT.H"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Assinaturas.h"

int main() {
    char nomeFicheiro[100];
    printf("Nome do ficheiro a carregar (ex: mapa.txt): ");
    scanf("%s", nomeFicheiro);

    Vertice* lista = CarregarAntenasDoFicheiro(nomeFicheiro);
    if (!lista) {
        printf("Erro ao carregar o ficheiro.\n");
        return 1;
    }

    Graph* grafoCompleto = NULL;
    Graph* grafosPorFrequencia[256] = { NULL };

    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Criar grafo com TODAS as antenas\n");
        printf("2. Criar grafos separados por frequência\n");
        printf("3. Ver grafo completo\n");
        printf("4. Ver grafo por frequência (ex: A)\n");
        printf("5. Testar procura em largura por Frequencia\n");
        printf("6. Testar procura em profundidade por Frequencia\n");
        printf("7. Encontrar todos os caminhos entre duas antenas\n");
        printf("8. Calcula interferencia entre duas antenas.\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao) {
        case 1: {
            printf("Criar grafo com TODAS as antenas...\n");
            grafoCompleto = CriaGraph();
            for (Vertice* v = lista; v != NULL; v = v->next) {
                Vertice* novo = CriarVertice(v->frequencia, v->linha, v->coluna);
                bool res;
                grafoCompleto = InsereVerticeGraph(grafoCompleto, novo, &res);
            }
            ConstruirAdjacenciasTodas(grafoCompleto->InicioGraph);
            printf("Grafo completo criado com sucesso!\n");
            break;
        }

        case 2: {
            printf("Criar grafos por frequencia...\n");
            for (Vertice* v = lista; v != NULL; v = v->next) {
                unsigned char f = v->frequencia;
                if (grafosPorFrequencia[f] == NULL)
                    grafosPorFrequencia[f] = CriaGraph();

                Vertice* novo = CriarVertice(v->frequencia, v->linha, v->coluna);
                bool res;
                grafosPorFrequencia[f] = InsereVerticeGraph(grafosPorFrequencia[f], novo, &res);
            }

            // Construir adjacências para cada grafo por frequência
            for (int i = 0; i < 256; i++) {
                if (grafosPorFrequencia[i]) {
                    ConstruirAdjacencias(grafosPorFrequencia[i]->InicioGraph);
                }
            }
            printf("Grafos por frequencia criados com sucesso!\n");
            break;
        }

        case 3: {
            if (!grafoCompleto) {
                printf("O grafo completo ainda nao foi criado (opção 1).\n");
                break;
            }
            printf("\n--- Grafo Completo ---\n");
            ShowGaphLA(grafoCompleto);
            break;
        }

        case 4: {
            char freq;
            printf("Indique a frequência (ex: A): ");
            scanf(" %c", &freq);
            getchar(); // Limpar o buffer
            if (!grafosPorFrequencia[(unsigned char)freq]) {
                printf("O grafo da frequência '%c' ainda nao foi criado ou nao existe.\n", freq);
                break;
            }
            printf("\n--- Grafo da frequencia '%c' ---\n", freq);
            ShowGaphLA(grafosPorFrequencia[(unsigned char)freq]);
            break;
        }
        case 5: {
            char freq;
            int linhaOrigem, colunaOrigem;
            printf("Indique a frequencia do grafo para busca em largura (ex: A): ");
            scanf(" %c", &freq);
            getchar(); // Limpar o buffer
            if (!grafosPorFrequencia[(unsigned char)freq]) {
                printf("O grafo da frequencia '%c' ainda nao foi criado ou nao existe.\n", freq);
                break;
            }

            printf("Linha da antena de origem: ");
            scanf("%d", &linhaOrigem);
            printf("Coluna da antena de origem: ");
            scanf("%d", &colunaOrigem);

            printf("Procura em Largura na frequencia '%c' a partir de (%d, %d):\n", freq, linhaOrigem, colunaOrigem);
            ResetVertices(grafosPorFrequencia[(unsigned char)freq]->InicioGraph); //resetar os vertices
            if (!BreadthFirstTraversalLA(grafosPorFrequencia[(unsigned char)freq], linhaOrigem, colunaOrigem)) {
                printf("Erro na travessia em largura ou antena de origem inválida.\n");
            }
            break;
        }
        case 6: {
            char freq;
            int linhaOrigem, colunaOrigem;
            printf("Indique a frequência do grafo para busca em profundidade (ex: A): ");
            scanf(" %c", &freq);
            getchar();
            if (!grafosPorFrequencia[(unsigned char)freq]) {
                printf("O grafo da frequência '%c' ainda não foi criado ou não existe.\n", freq);
                break;
            }
            printf("Linha da antena de origem: ");
            scanf("%d", &linhaOrigem);
            printf("Coluna da antena de origem: ");
            scanf("%d", &colunaOrigem);

            printf("\nProcura em Profundidade na frequência '%c' a partir de (%d, %d):\n", freq, linhaOrigem, colunaOrigem);
            ResetVertices(grafosPorFrequencia[(unsigned char)freq]->InicioGraph);
            if (!DepthFirstTraversal(grafosPorFrequencia[(unsigned char)freq], linhaOrigem, colunaOrigem)) {
                printf("Erro na travessia em profundidade ou antena de origem inválida.\n");
            }
            break;
        }
        case 7: {
            if (!grafoCompleto) {
                printf("O grafo completo ainda não foi criado (opção 1).\n");
                break;
            }
            int linhaOrigem, colunaOrigem, linhaDestino, colunaDestino;
            printf("Linha da antena de origem: ");
            scanf("%d", &linhaOrigem);
            printf("Coluna da antena de origem: ");
            scanf("%d", &colunaOrigem);
            printf("Linha da antena de destino: ");
            scanf("%d", &linhaDestino);
            printf("Coluna da antena de destino: ");
            scanf("%d", &colunaDestino);

            printf("\nProcurando todos os caminhos entre (%d, %d) e (%d, %d):\n", linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);
            ProcurarTodosOsCaminhos(grafoCompleto, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);
            break;
        }
        case 8: {
            char f1, f2;
            printf("Indique a primeira frequência (ex: A): ");
            scanf(" %c", &f1);
            printf("Indique a segunda frequência (ex: B): ");
            scanf(" %c", &f2);
            getchar();

            if (!grafosPorFrequencia[(unsigned char)f1] || !grafosPorFrequencia[(unsigned char)f2]) {
                printf("Um ou ambos os grafos das frequências indicadas não foram criados (use opção 2).\n");
                break;
            }

            Vertice* a = grafosPorFrequencia[(unsigned char)f1]->InicioGraph;
            Vertice* b;

            printf("\nIntersecções (pares A-B):\n");
            while (a) {
                b = grafosPorFrequencia[(unsigned char)f2]->InicioGraph;
                while (b) {
                    printf("Antena %c (%d,%d) Antena %c (%d,%d)\n",
                        f1, a->linha, a->coluna, f2, b->linha, b->coluna);
                    b = b->next;
                }
                a = a->next;
            }

            break;
        }

        case 0:
            printf("A sair...\n");
            break;

        default:
            printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    // Libertar memória
    LibertarVertice(lista);
    if (grafoCompleto) {
        LibertarVertice(grafoCompleto->InicioGraph);
        free(grafoCompleto);
    }

    for (int i = 0; i < 256; i++) {
        if (grafosPorFrequencia[i]) {
            LibertarVertice(grafosPorFrequencia[i]->InicioGraph);
            free(grafosPorFrequencia[i]);
        }
    }

    return 0;
}