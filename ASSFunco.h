#pragma once
/*****************************************************************//**
 * \file   ASSFunco.h
 * \brief  Assinatura das funções
 * 
 * \author José
 * \date   April 2025
 *********************************************************************/
#include "Structs.h"


antena* CriarAntena(int coluna, int linha, char frequencia);
antena* CarregarAntenasDoFicheiro(const char* nome_ficheiro);
antena* procurarantena(antena* h, int l, int c);
antena* insereOrdenado(antena* inicio, antena* novo);
antena* removerantena(antena* h, int linha, int coluna);
void mostrarMatrizAntenas(antena* lista_antenas);
antena* libertarListaAntenas(antena* lista);
nefasto* criarEfeitoNefasto(int x, int y);
nefasto* calcularEfeitoNefastoFinal(antena* lista);
void mostrarMatrizNefastos(antena* lista_antenas, nefasto* lista_nefastos);
void libertarListaNefasto(nefasto* lnefasto);
int efeitoJaExiste(nefasto* lista, int x, int y);
