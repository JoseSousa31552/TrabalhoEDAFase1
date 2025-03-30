#pragma once
/*****************************************************************//**
 * \file   Funcoes.h
 * \brief
 *
 * \author Jose
 * \date   March 2025
 *********************************************************************/




typedef struct antena {

	int coluna;
	int linha;
	char frequencia;

	struct antena* next;

}antena;

typedef struct nefasto {
	int nx;
	int ny;
	struct nefasto* next;
}nefasto;

extern int MAX_COLUNAS;
extern int MAX_LINHAS;





