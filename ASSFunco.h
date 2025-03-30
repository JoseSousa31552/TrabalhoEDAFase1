#pragma once
#include "Structs.h"


antena* CriarAntena(int coluna, int linha, char frequencia);
antena* CarregarAntenasDoFicheiro(const char* nome_ficheiro);
antena* procurarantena(antena* h, int l, int c);
antena* insereOrdenado(antena* inicio, antena* novo);
antena* removerantena(antena* h, int linha, int coluna);
void mostrarMatrizAntenas(antena* lista_antenas);
void libertarListaAntenas(antena* lista);
nefasto* criarEfeitoNefasto(int x, int y);
nefasto* calcularEfeitoNefastoFinal(antena* lista);
void mostrarMatrizNefastos(antena* lista_antenas, nefasto* lista_nefastos);
void libertarListaNefasto(nefasto* lnefasto);

