#pragma once
/*****************************************************************//**
 * \file   STRUCT.h
 * \brief
 *
 * \author José
 * \date   May 2025
 *********************************************************************/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CAMINHO 10000
#define MAX 1000
#pragma warning(disable : 4996)
extern int MAX_COLUNAS;
extern int MAX_LINHAS;

typedef struct Vertice {
	char frequencia;
	int linha;
	int coluna;
	bool visitado;
	struct Vertice* next;
	struct ADJ* adnext;

}Vertice;

typedef struct ADJ {
	char freque; 
	int l; 
	int c; 

	struct ADJ* prox;

}ADJ;


typedef struct Graph {
	Vertice* InicioGraph;	
	int NumeroVertices;		
}Graph;







