/*****************************************************************//**
 * \file  FUNCOES.c
 * \brief
 *
 * \author José
 * \date  Maio 2025
 *********************************************************************/
#pragma once
#include "STRUCT.H"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>


#pragma warning(disable : 4996)
int MAX_COLUNAS = 0;
int MAX_LINHAS = 0;


#pragma region VERTICE
/*====================================================================
* Vertice
* =====================================================================
*/
/**
 * .CriarVertice
 *
 * \param frequencia
 * \param linha
 * \param coluna
 * \return
 */
Vertice* CriarVertice(char frequencia, int linha, int coluna) {
    Vertice* aux;
    aux = (Vertice*)malloc(sizeof(Vertice));
    if (aux != NULL) {
        aux->coluna = coluna;
        aux->linha = linha;
        aux->frequencia = frequencia;
        aux->visitado = false;
        aux->next = NULL;
        aux->adnext = NULL;
    }
    return aux;
}

/**
 * .Carregar antenas do ficheiro txt
 *
 * \param nome_ficheiro
 * \return
 */
Vertice* CarregarAntenasDoFicheiro(const char* nome_ficheiro) {
    FILE* fp = fopen(nome_ficheiro, "r");
    if (fp == NULL) {
        return NULL;
    }

    Vertice* lista = NULL;
    Vertice* ultima = NULL;
    char linha[256];
    int l = 0;
    MAX_COLUNAS = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        int comp = strlen(linha);

        if (comp > 0 && (linha[comp - 1] == '\n' || linha[comp - 1] == '\r')) {
            linha[comp - 1] = '\0';
            comp--;
        }

        if (comp > MAX_COLUNAS) {
            MAX_COLUNAS = comp;
        }

        for (int c = 0; c < comp; c++) {
            char fre = linha[c];
            if (fre != '.') {
                Vertice* ant = CriarVertice(fre, l, c);
                if (lista == NULL) {
                    lista = ant;
                }
                else {
                    ultima->next = ant;
                }
                ultima = ant;
            }
        }
        l++;
    }
    MAX_LINHAS = l;
    fclose(fp);
    return lista;
}

/**
 * .Verifica se o vertice existe
 *
 * \param inicio
 * \param id
 * \return
 */
bool ExisteVertice(Vertice* inicio, int l, int c) {
    if (inicio == NULL) return false;
    Vertice* aux = inicio;
    while (aux) {
        if (aux->linha == l && aux->coluna == c) return true;
        aux = aux->next;
    }
    return false;
}

/**
 * .Procura o vertice
 *
 * \param h
 * \param l
 * \param c
 * \return
 */
Vertice* ProcurarVertice(Vertice* h, int l, int c) {
    Vertice* aux = h;
    while (aux != NULL) {
        if (aux->linha == l && aux->coluna == c) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

/**
 * . Insere o vertice na lista ligada de forma ordenada
 *
 * \param inicio
 * \param novo
 * \param res
 * \return
 */
Vertice* InsereOrdenado(Vertice* inicio, Vertice* novo, bool* res) {
    *res = false;

    if (novo == NULL) {
        return inicio;
    }

    if (ExisteVertice(inicio, novo->linha, novo->coluna)) {
        free(novo);
        return inicio;
    }

    if (inicio == NULL) {
        inicio = novo;
        *res = true;
        return inicio;
    }

    if ((novo->linha < inicio->linha) || (novo->linha == inicio->linha && novo->coluna < inicio->coluna)) {
        novo->next = inicio;
        inicio = novo;
        *res = true;
        return inicio;
    }

    Vertice* atual = inicio;
    Vertice* anterior = atual;

    while ((atual->linha < novo->linha || (atual->linha == novo->linha && atual->coluna < novo->coluna)) && atual->next != NULL) {
        anterior = atual;
        atual = atual->next;
    }

    if ((atual->linha == novo->linha && atual->coluna > novo->coluna)) {
        novo->next = atual;
        anterior->next = novo;
        *res = true;
        return inicio;
    }

    if (atual->linha < novo->linha || (atual->linha == novo->linha && atual->coluna < novo->coluna)) {
        atual->next = novo;
        *res = true;
        return inicio;
    }
    *res = true;
    return inicio;
}


/**
 * .Apaga a adjacencia
 *
 * \param AdjacenciaApag
 */
void ApagaADJ(ADJ* AdjacenciaApag) {
    free(AdjacenciaApag);
}


/**
 * .Apaga adjacencia na Lista de Adjacencias
 *
 * \param ListAdj
 * \param l
 * \param c
 * \param res
 * \return
 */
ADJ* ElimiminaAdj(ADJ* ListAdj, int l, int c, bool* res) {
    if (res) *res = false;
    if (ListAdj == NULL) return NULL;

    ADJ* aux = ListAdj;
    ADJ* ant = NULL;
    while (aux && (aux->l != l || aux->c != c)) {
        ant = aux;
        aux = aux->prox;
    }
    if (!aux) {
        return ListAdj;
    }

    if (ant == NULL) {
        ListAdj = aux->prox;
    }
    else {
        ant->prox = aux->prox;
    }
    ApagaADJ(aux);
    if (res) *res = true;
    return ListAdj;
}


/**
 * @brief  Apaga todas as adjacências de uma LA
 * @param  listAdj
 * @param  res
**/
ADJ* ElimiminaAllAdj(ADJ* listAdj, bool* res) {
    if (res) *res = false;
    if (listAdj == NULL) return NULL;

    ADJ* aux = listAdj;
    while (aux) {
        ADJ* proximo = aux->prox;
        ApagaADJ(aux);
        aux = proximo;
    }
    if (res) *res = true;
    return NULL;
}

/**
 * .Remove vertice que esteja em outras adjacencias
 *
 * \param lista
 * \param linha
 * \param coluna
 * \param res
 * \return
 */
Vertice* RemoverAdjacenciasParaVertice(Vertice* lista, int linha, int coluna, bool* res) {
    if (res) *res = true;
    Vertice* aux = lista;
    while (aux) {
        aux->adnext = ElimiminaAdj(aux->adnext, linha, coluna, res);
        aux = aux->next;
    }
    return lista;
}

/**
 * .Remover Vertice
 *
 * \param h
 * \param linha
 * \param coluna
 * \return
 */
Vertice* RemoverVertice(Vertice* h, int linha, int coluna, bool* res) {
    if (res) *res = false;
    if (h == NULL) return NULL;
    if (!ExisteVertice(h, linha, coluna)) return h;

    bool adjRemovidas = true;
    h = RemoverAdjacenciasParaVertice(h, linha, coluna, &adjRemovidas);

    if (h->linha == linha && h->coluna == coluna) {
        Vertice* aux = h;
        h = h->next;
        aux->adnext = ElimiminaAllAdj(aux->adnext, res);
        free(aux);
        if (res) *res = true;
        return h;
    }

    Vertice* aux = h;
    Vertice* auxAnt = NULL;

    while (aux && (aux->linha != linha || aux->coluna != coluna)) {
        auxAnt = aux;
        aux = aux->next;
    }

    if (aux) {
        auxAnt->next = aux->next;
        aux->adnext = ElimiminaAllAdj(aux->adnext, res);
        free(aux);
        if (res) *res = true;
    }

    return h;
}

/**
 * .
 * Função para libertar a memoria da lista de vértices
 * \param lista
 */
Vertice* LibertarVertice(Vertice* lista) {
    Vertice* atual = lista;
    while (atual != NULL) {
        Vertice* proximo = atual->next;
        atual->adnext = ElimiminaAllAdj(atual->adnext, NULL);
        free(atual);
        atual = proximo;
    }
    return NULL;
}

void ShowGraph(Vertice* graph) {
    Vertice* atual = graph;
    while (atual != NULL) {
        printf("Antena em (%d, %d) - Frequencia: %c\n", atual->linha, atual->coluna, atual->frequencia);
        ADJ* atulADJ = atual->adnext;
        while (atulADJ != NULL) {
            printf("\t\tAdjacente em (%d, %d) - Frequencia: %c\n", atulADJ->l, atulADJ->c, atulADJ->freque);
            atulADJ = atulADJ->prox;
        }
        atual = atual->next;
    }
}
#pragma endregion

#pragma region ADJ
/*====================================================================
* ADJACENCIA
* =====================================================================
*/

/**
 * .Criar Adjacencia
 *
 * \param frequencia
 * \param linha
 * \param coluna
 * \return
 */
ADJ* CriaAdj(char frequencia, int linha, int coluna) {
    ADJ* aux;
    aux = (ADJ*)malloc(sizeof(ADJ));
    if (aux == NULL) return NULL;
    aux->c = coluna;
    aux->l = linha;
    aux->freque = frequencia;
    aux->prox = NULL;
    return aux;
}

/**
 * .Inser na lista da adjacencia, evita duplicados pela linha e coluna
 *
 * \param ListaAdja
 * \param l
 * \param c
 * \param frequencia
 * \return
 */
ADJ* InsereAdj(ADJ* ListaAdja, int l, int c, char frequencia) {
    ADJ* ver = ListaAdja;
    while (ver != NULL) {
        if (ver->l == l && ver->c == c) {
            return ListaAdja;
        }
        ver = ver->prox;
    }

    ADJ* NewAdj;
    if ((NewAdj = CriaAdj(frequencia, l, c)) == NULL) {
        return ListaAdja;
    }

    if (ListaAdja == NULL) {
        ListaAdja = NewAdj;
    }
    else {
        ADJ* aux = ListaAdja;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = NewAdj;
    }
    return ListaAdja;
}

/**
 * .Configura a adjacencia de cada vertice, colocando apenas frequencias iguais.
 *
 * \param lista
 */
bool ConstruirAdjacencias(Vertice* lista) {
    if (lista == NULL) return false;

    for (Vertice* v1 = lista; v1 != NULL; v1 = v1->next) {
        for (Vertice* v2 = lista; v2 != NULL; v2 = v2->next) {
            if (v1 != v2 && v1->frequencia == v2->frequencia) {
                v1->adnext = InsereAdj(v1->adnext, v2->linha, v2->coluna, v2->frequencia);
            }
        }
    }
    return true;
}

/**
 * .Configura a adjacencia de cada vertice, grafo total.
 *
 * \param lista
 */
bool ConstruirAdjacenciasTodas(Vertice* lista) {
    if (lista == NULL) return false;

    for (Vertice* v1 = lista; v1 != NULL; v1 = v1->next) {
        for (Vertice* v2 = lista; v2 != NULL; v2 = v2->next) {
            if (v1 != v2) { 
                v1->adnext = InsereAdj(v1->adnext, v2->linha, v2->coluna, v2->frequencia);
            }
        }
    }
    return true;
}




#pragma endregion

#pragma region GRAFO
/*====================================================================
* Grafo
* =====================================================================
*/

/**
 * .Cria o Grafo
 *
 * \return
 */
Graph* CriaGraph() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    if (g != NULL) {
        g->InicioGraph = NULL;
        g->NumeroVertices = 0;
    }
    return g;
}

/**
 * .Inser o vertice no grafo
 *
 * \param h
 * \param novo
 * \param res
 * \return
 */
Graph* InsereVerticeGraph(Graph* h, Vertice* novo, bool* res) {
    *res = false;
    if (h == NULL || novo == NULL) return NULL;

    if (ExisteVertice(h->InicioGraph, novo->linha, novo->coluna)) {
        free(novo);
        return h;
    }

    h->InicioGraph = InsereOrdenado(h->InicioGraph, novo, res);
    if (*res == true) h->NumeroVertices++;
    return h;
}

/**
 * .Inser a adjacencia no grafo
 *
 * \param h
 * \param lOrigem
 * \param cOrigem
 * \param lDestino
 * \param cDestino
 * \param res
 * \return
 */
Graph* InsereAdjGraph(Graph* h, int lOrigem, int cOrigem, int lDestino, int cDestino, bool* res) {
    *res = false;
    if (h == NULL) return NULL;

    Vertice* origem = ProcurarVertice(h->InicioGraph, lOrigem, cOrigem);
    Vertice* destino = ProcurarVertice(h->InicioGraph, lDestino, cDestino);
    if (origem == NULL || destino == NULL) return h;

    origem->adnext = InsereAdj(origem->adnext, destino->linha, destino->coluna, destino->frequencia);
    *res = true;
    return h;
}

/**
 * .Apaga adjacencia entre dois vertices
 *
 * \param g
 * \param linhaOrigem
 * \param colunaOrigem
 * \param linhaDestino
 * \param colunaDestino
 * \param res
 * \return
 */
Graph* EliminaAdjGraph(Graph* g, int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, bool* res) {
    *res = false;
    if (g == NULL) return NULL;

    Vertice* verticeOrigem = ProcurarVertice(g->InicioGraph, linhaOrigem, colunaOrigem);
    if (verticeOrigem == NULL) return g;

    verticeOrigem->adnext = ElimiminaAdj(verticeOrigem->adnext, linhaDestino, colunaDestino, res);

    return g;
}

/**
 * .Procura determinado vertice num grafo. Devolve o vertice, caso exista
 *
 * \param g
 * \param linha
 * \param coluna
 * \return
 */
Vertice* OndeEstaVerticeGraph(Graph* g, int linha, int coluna) {
    if (g == NULL) return NULL;
    return (ProcurarVertice(g->InicioGraph, linha, coluna));
}

/**
 * .Verifica se determinado vertice existe num grafo
 *
 * \param g
 * \param linha
 * \param coluna
 * \return
 */
bool ExisteVerticeGraph(Graph* g, int linha, int coluna) {
    if (g == NULL) return false;
    return (ExisteVertice(g->InicioGraph, linha, coluna));
}

/**
  * @brief  Apaga vertice de um grafo
  * @param  g         -
  * @param  codVertice -
  * @param  res       -
  * @retval         -
  * @date  29.04.2024
**/
Graph* EliminaVerticeGraph(Graph* g, int linha, int coluna, bool* res) {
    *res = false;
    if (g == NULL) return NULL;

    g->InicioGraph = RemoverVertice(g->InicioGraph, linha, coluna, res);
    if (*res == true) {
        g->NumeroVertices--;
    }
    return g;
}

/**
 * .Apresenta grafo
 *
 * \param g
 */
void ShowGaphLA(Graph* g) {
    ShowGraph(g->InicioGraph);
}

#pragma endregion

#pragma region LARGURA QUEUE


/**
 * .Mete na queue
 *
 * \param fila
 * \param fim
 * \param valor
 * \return
 */
bool InserirQueue(int fila[], int* fim, int valor) {
    if (*fim >= MAX) return false;  // Verifica se a fila está cheia
    fila[(*fim)++] = valor;         // Insere o valor no final da fila
    return true;
}

/**
 * .Remove da queue
 *
 * \param fila
 * \param inicio
 * \return
 */
int RemoverQueue(int fila[], int* inicio) {
    return fila[(*inicio)++];        // Remove o valor do início da fila
}

/**
 * .Verifica se a fila está vazia
 *
 * \param fim
 * \param inicio
 * \return
 */
bool VaziaQueue(int fim, int inicio) {
    return fim == inicio;          
}

/**
 * .Mostra a antena alcançada
 *
 * \param v
 */
void ApanhaVertice(Vertice* v) {
    printf("Antena alcançada: (%d, %d)\n", v->linha, v->coluna);
}

/**
 * .Procura em largura
 *
 * \param g
 * \param linhan
 * \param colunan
 * \return
 */
bool BreadthFirstTraversalLA(Graph* g, int linhan, int colunan) {
    if (g == NULL) return false;

    int Lqueue[MAX];  // fila de linhas
    int Cqueue[MAX];  // fila de colunas
    int rear = 0, front = 0;

    Vertice* lstVertices = g->InicioGraph;

    Vertice* origem = ProcurarVertice(lstVertices, linhan, colunan);
    if (origem == NULL) return false;

    origem->visitado = true;

    if (!InserirQueue(Lqueue, &rear, linhan)) return false;
    if (!InserirQueue(Cqueue, &rear, colunan)) return false;

    while (!VaziaQueue(rear, front)) {
        int linhaAtual = RemoverQueue(Lqueue, &front);
        int colunaAtual = RemoverQueue(Cqueue, &front);

        Vertice* atual = ProcurarVertice(lstVertices, linhaAtual, colunaAtual);
        if (atual == NULL) return false;

        ApanhaVertice(atual);

        ADJ* adj = atual->adnext;
        while (adj) {
            Vertice* vizinho = ProcurarVertice(lstVertices, adj->l, adj->c);
            if (vizinho && !vizinho->visitado) {
                vizinho->visitado = true;
                if (!InserirQueue(Lqueue, &rear, adj->l)) return false;
                if (!InserirQueue(Cqueue, &rear, adj->c)) return false;
            }
            adj = adj->prox;
        }
    }

    return true;
}

/**
 * .Reseta o campo visitado dos vertices
 *
 * \param inicio
 * \return
 */
Vertice* ResetVertices(Vertice* inicio) {
    Vertice* aux = inicio;
    while (aux) {
        aux->visitado = false;
        aux = aux->next;
    }
    return inicio;
}

#pragma endregion

#pragma region PROFUNDIDADE STACK
/*====================================================================
* PROFUNDIDADE STACK
* =====================================================================
*/




/**
 * .Vê se a stack esta vazia
 * 
 * \param top
 * \return 
 */
bool isStackEmpty(int top) {
    return (top == -1);
}


/**
 * .Insere um valor no topo da pilha (stack)
 * 
 * \param stack
 * \param top
 * \param valor
 * \return 
 */
bool push(int stack[], int* top, int valor) {
    if (*top >= MAX - 1) return false;  // overflow
    stack[++(*top)] = valor;
    return true;
}


/**
 * .Remove e retorna o valor do topo da pilha (stack)
 * 
 * \param stack
 * \param top
 * \return 
 */
int pop(int stack[], int* top) {
    if (*top == -1) return -1; // stack vazia
    return stack[(*top)--];
}


/**
 * .Obtém o primeiro vértice adjacente não visitado a um vértice específico
 * 
 * \param lstVertices
 * \param linha
 * \param coluna
 * \return 
 */
Vertice* GetAdjNaoVisitado(Vertice* lstVertices, int linha, int coluna) {
    Vertice* v = ProcurarVertice(lstVertices, linha, coluna);
    if (!v) return NULL;

    ADJ* adj = v->adnext;
    while (adj) {
        Vertice* viz = ProcurarVertice(lstVertices, adj->l, adj->c);
        if (viz && !viz->visitado) {
            return viz;
        }
        adj = adj->prox;
    }
    return NULL;
}


/**
 * .Realiza uma travessia em profundidade (DFS) no grafo a partir de um vértice inicial
 * 
 * \param g
 * \param linOrigem
 * \param colOrigem
 * \return 
 */
bool DepthFirstTraversal(Graph* g, int linOrigem, int colOrigem) {
    if (g == NULL) return false;

    int topL = -1, topC = -1;
    int Lstack[MAX];
    int Cstack[MAX];

    Vertice* lstVertices = g->InicioGraph;
    Vertice* origem = ProcurarVertice(lstVertices, linOrigem, colOrigem);
    if (!origem) return false;
    if (origem->visitado) return true;

    origem->visitado = true;
    ApanhaVertice(origem);

    push(Lstack, &topL, linOrigem);
    push(Cstack, &topC, colOrigem);

    while (!isStackEmpty(topL)) {
        int linhaAtual = Lstack[topL];
        int colunaAtual = Cstack[topC];

        Vertice* adjNaoVisitado = GetAdjNaoVisitado(lstVertices, linhaAtual, colunaAtual);

        if (adjNaoVisitado == NULL) {
            pop(Lstack, &topL);
            pop(Cstack, &topC);
        }
        else {
            adjNaoVisitado->visitado = true;
            ApanhaVertice(adjNaoVisitado);

            push(Lstack, &topL, adjNaoVisitado->linha);
            push(Cstack, &topC, adjNaoVisitado->coluna);
        }
    }
    return true;
}


/**
 * .Imprime o caminho percorrido entre dois vértices
 * 
 * \param linhas
 * \param colunas
 * \param tamanho
 */
void ImprimirCaminho(int* linhas, int* colunas, int tamanho) {
    printf("Caminho encontrado:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("(%d, %d)", linhas[i], colunas[i]);
        if (i < tamanho - 1)
            printf(" -> ");
    }
    printf("\n");
}


/**
 * .Realiza uma busca em profundidade (DFS) para encontrar todos os caminhos entre dois vértices
 * 
 * \param g
 * \param atual
 * \param destino
 * \param caminhoLinhas
 * \param caminhoColunas
 * \param profundidade
 * \return 
 */
bool  MostrarTodosCaminhosDFS(Graph* g, Vertice* atual, Vertice* destino, int* caminhoLinhas, int* caminhoColunas, int profundidade) {
    if (!atual || !destino) return false;

    atual->visitado = true;
    caminhoLinhas[profundidade] = atual->linha;
    caminhoColunas[profundidade] = atual->coluna;
    profundidade++;

    if (atual == destino) {
        ImprimirCaminho(caminhoLinhas, caminhoColunas, profundidade);
    }
    else {
        ADJ* adj = atual->adnext;
        while (adj) {
            Vertice* vizinho = ProcurarVertice(g->InicioGraph, adj->l, adj->c);
            if (vizinho && !vizinho->visitado) {
                MostrarTodosCaminhosDFS(g, vizinho, destino, caminhoLinhas, caminhoColunas, profundidade);
            }
            adj = adj->prox;
        }
    }

    atual->visitado = false; // backtrack
    return true;
}


/**
 * .Procura todos os caminhos entre dois vértices em um grafo
 * 
 * \param g
 * \param linOrigem
 * \param colOrigem
 * \param linDestino
 * \param colDestino
 * \return 
 */
bool ProcurarTodosOsCaminhos(Graph* g, int linOrigem, int colOrigem, int linDestino, int colDestino) {
    Vertice* origem = ProcurarVertice(g->InicioGraph, linOrigem, colOrigem);
    Vertice* destino = ProcurarVertice(g->InicioGraph, linDestino, colDestino);
    if (!origem || !destino) {
        return false;
    }

    int caminhoLinhas[MAX];
    int caminhoColunas[MAX];

    
    Vertice* aux = g->InicioGraph;
    while (aux) {
        aux->visitado = false;
        aux = aux->next;
    }

    MostrarTodosCaminhosDFS(g, origem, destino, &caminhoLinhas, &caminhoColunas, 0);
    return true;
}

#pragma endregion


/**
 * .Calcula interferencia entre duas antenas.
 * 
 * \param grafo
 * \param freqA
 * \param freqB
 */
void CalcularInterferenciasAB(Graph* grafo, char freqA, char freqB) {
    printf("=== INTERFERÊNCIAS ENTRE FREQUÊNCIAS %c e %c ===\n", freqA, freqB);

    Vertice* atualA = grafo->InicioGraph;
    while (atualA != NULL) {
        if (atualA->frequencia == freqA) {
            Vertice* atualB = grafo->InicioGraph;
            while (atualB != NULL) {
                if (atualB->frequencia == freqB) {
                    if (atualA == atualB) {
                        atualB = atualB->next;
                        continue; // Ignorar mesma antena
                    }

                    int dx = atualB->coluna - atualA->coluna;
                    int dy = atualB->linha - atualA->linha;

                    if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) {
                        printf("Interferência entre %c(%d,%d) e %c(%d,%d)\n",
                            freqA, atualA->coluna, atualA->linha,
                            freqB, atualB->coluna, atualB->linha);
                    }
                }
                atualB = atualB->next;
            }
        }
        atualA = atualA->next;
    }
}


