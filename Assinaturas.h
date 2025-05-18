#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "STRUCT.h"

Vertice* CriarVertice(char frequencia, int linha, int coluna);
Vertice* CarregarAntenasDoFicheiro(const char* nome_ficheiro);
bool ExisteVertice(Vertice* inicio, int l, int c);
Vertice* ProcurarVertice(Vertice* h, int l, int c);
Vertice* InsereOrdenado(Vertice* inicio, Vertice* novo, bool* res);
void ShowGraph(Vertice* graph);
Vertice* RemoverVertice(Vertice* h, int linha, int coluna, bool* res);
Vertice* LibertarVertice(Vertice* lista);


ADJ* CriaAdj(char frequencia, int linha, int coluna);
ADJ* InsereAdj(ADJ* ListaAdja, int l, int c, char frequencia);
bool ConstruirAdjacencias(Vertice* lista);
bool ConstruirAdjacenciasTodas(Vertice* lista);
void ApagaADJ(ADJ* AdjacenciaApag);
ADJ* ElimiminaAdj(ADJ* ListAdj, int l, int c, bool* res);
ADJ* ElimiminaAllAdj(ADJ* listAdj, bool* res);
Vertice* RemoverAdjacenciasParaVertice(Vertice* lista, int linha, int coluna, bool* res);


Graph* CriaGraph();
Graph* InsereVerticeGraph(Graph* h, Vertice* novo, bool* res);
Graph* InsereAdjGraph(Graph* h, int lOrigem, int cOrigem, int lDestino, int cDestino, bool* res);
Graph* EliminaAdjGraph(Graph* g, int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, bool* res);
Vertice* OndeEstaVerticeGraph(Graph* g, int linha, int coluna);
bool ExisteVerticeGraph(Graph* g, int linha, int coluna);
Graph* EliminaVerticeGraph(Graph* g, int linha, int coluna, bool* res);
void ShowGaphLA(Graph* g);

bool InserirQueue(int fila[], int* fim, int valor);
int RemoverQueue(int fila[], int* inicio);
bool VaziaQueue(int fim, int inicio);
void ApanhaVertice(Vertice* v);
bool BreadthFirstTraversalLA(Graph* g, int linhan, int colunan);
Vertice* ResetVertices(Vertice* inicio);

bool isStackEmpty(int top);
bool push(int stack[], int* top, int valor);
int pop(int stack[], int* top);
Vertice* GetAdjNaoVisitado(Vertice* lstVertices, int linha, int coluna);
bool DepthFirstTraversal(Graph* g, int linOrigem, int colOrigem);
void ImprimirCaminho(int* linhas, int* colunas, int tamanho);
bool  MostrarTodosCaminhosDFS(Graph* g, Vertice* atual, Vertice* destino, int* caminhoLinhas, int* caminhoColunas, int profundidade);
bool ProcurarTodosOsCaminhos(Graph* g, int linOrigem, int colOrigem, int linDestino, int colDestino);
void CalcularInterferenciasAB(Graph* grafo, char freqA, char freqB);


