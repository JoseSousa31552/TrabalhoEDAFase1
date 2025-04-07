/*****************************************************************//**
 * \file   Funcoes.c
 * \brief
 *
 * \author José
 * \date   March 2025
 *********************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "Structs.h"
#include "ASSFunco.h"
#pragma warning(disable : 4996)
int MAX_COLUNAS = 0;
int MAX_LINHAS = 0;


/**
 * .
 * CriarAntena
 * \param coluna
 * \param linha
 * \param frequencia
 * \return
 */
antena* CriarAntena(int coluna, int linha, char frequencia) {
    antena* aux;
    aux = (antena*)malloc(sizeof(antena));
    if (aux != NULL) {
        aux->coluna = coluna;
        aux->linha = linha;
        aux->frequencia = frequencia;
        aux->next = NULL;
    }
    return aux;


}

/**
 * .
 * CarregarAntenasDoFicheiro
 * \param nome_ficheiro
 * \return
 */
antena* CarregarAntenasDoFicheiro(const char* nome_ficheiro) {
    FILE* fp = fopen(nome_ficheiro, "r");
    if (fp == NULL) {
        return NULL;
    }

    antena* lista = NULL;
    antena* ultima = NULL;
    char linha[256];
    int l = 0;
    MAX_COLUNAS = 0;


    while (fgets(linha, sizeof(linha), fp)) {
        int comp = strlen(linha);


        if (linha[comp - 1] == '\n' || linha[comp - 1] == '\r') {      //testar \r
            linha[comp - 1] = '\0';
            comp--;
        }

        if (comp > MAX_COLUNAS) {
            MAX_COLUNAS = comp;
        }

        for (int c = 0; c < comp; c++) {
            char fre = linha[c];


            if (fre != '.') {
                antena* ant = CriarAntena(c, l, fre);


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
 * .
 * procurarantena
 * \param h
 * \param l
 * \param c
 * \return
 */
antena* procurarantena(antena* h, int l, int c) {
    antena* aux = h;
    while (aux != NULL) {
        if (aux->linha == l && aux->coluna == c) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}


/**
 * .
 * insereOrdenado
 * \param inicio
 * \param novo
 * \return
 */
antena* insereOrdenado(antena* inicio, antena* novo) {

    if (novo == NULL) return inicio;


    if (procurarantena(inicio, novo->linha, novo->coluna) != NULL) {
        free(novo);
        return inicio;
    }

    if (inicio == NULL) {
        inicio = novo;
        return inicio;
    }


    if ((novo->linha < inicio->linha) || (novo->linha == inicio->linha && novo->coluna < inicio->coluna)) {
        novo->next = inicio;
        inicio = novo;
        return inicio;
    }

    antena* atual = inicio;
    antena* anterior = atual;

    while ((atual->linha < novo->linha || (atual->linha == novo->linha && atual->coluna < novo->coluna)) && atual->next != NULL) {

        anterior = atual;
        atual = atual->next;

    }
    if ((atual->linha == novo->linha && atual->coluna > novo->coluna)) {
        novo->next = atual;
        anterior->next = novo;
        return inicio;

    }

    if (atual->linha < novo->linha && atual->coluna < novo->coluna) {
        atual->next = novo;
        return inicio;

    }
   
    return inicio;
}



/**
 * .
 * removerantena
 * \param h
 * \param linha
 * \param coluna
 * \return
 */
antena* removerantena(antena* h, int linha, int coluna) {

    if (h == NULL) {
        return NULL;
    }
    if (procurarantena(h, linha, coluna) == NULL) return NULL;



    if (h->linha == linha && h->coluna == coluna) {
        antena* aux = h;
        h = h->next;
        free(aux);
        return h;
    }

    antena* aux = h;
    antena* auxAnt = aux;

    while (aux && (aux->linha != linha || aux->coluna != coluna)) {
        auxAnt = aux;
        aux = aux->next;
    }

    if (aux) {
        auxAnt->next = aux->next;
        free(aux);
    }

    return h;
}


/**
 * mostrarMatrizAntenas
 * \param lista_antenas Lista de antenas carregadas
 */
void mostrarMatrizAntenas(antena* lista) {
    printf("\nMatriz de Antenas (%dx%d):\n", MAX_LINHAS, MAX_COLUNAS);

    for (int l = 0; l < MAX_LINHAS; l++) {
        for (int c = 0; c < MAX_COLUNAS; c++) {
            antena* ant = procurarantena(lista, l, c);
            if (ant != NULL) {
                printf("%c ", ant->frequencia);
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

/**
 * .
 * Função para libertar a memoria
 * \param lista
 */
antena* libertarListaAntenas(antena* lista) {
    antena* atual = lista;

    while (atual != NULL) {
        antena* proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    return lista;
}

/**
 * .
 * criarEfeitoNefasto
 * \param x
 * \param y
 * \return
 */
nefasto* criarEfeitoNefasto(int x, int y) {
    nefasto* novo = (nefasto*)malloc(sizeof(nefasto));
    if (novo != NULL) {
        novo->nx = x;
        novo->ny = y;
        novo->next = NULL;
    }
    return novo;
}

/**
 * .
 * calcularEfeitoNefastoFinal
 * \param lista
 * \return
 */
nefasto* calcularEfeitoNefastoFinal(antena* lista) {
    nefasto* nefastos = NULL;
    antena* atual = lista;
    

    while (atual != NULL) {
        antena* comparar = atual->next;

        while (comparar != NULL) {
            if (atual->frequencia == comparar->frequencia) {

                int diff_linha = comparar->linha - atual->linha;
                int diff_coluna = comparar->coluna - atual->coluna;


                int nefasto_linha = comparar->linha + diff_linha;
                int nefasto_coluna = comparar->coluna + diff_coluna;


                if (nefasto_linha >= 0 && nefasto_coluna >= 0 && nefasto_linha < MAX_LINHAS && nefasto_coluna < MAX_COLUNAS) {
                    nefasto* novo = criarEfeitoNefasto(nefasto_linha, nefasto_coluna);
                    novo->next = nefastos;
                    nefastos = novo;
                }


                nefasto_linha = atual->linha - diff_linha;
                nefasto_coluna = atual->coluna - diff_coluna;


                if (nefasto_linha >= 0 && nefasto_coluna >= 0 && nefasto_linha < MAX_LINHAS && nefasto_coluna < MAX_COLUNAS) {
                    nefasto* novo2 = criarEfeitoNefasto(nefasto_linha, nefasto_coluna);
                    novo2->next = nefastos;
                    nefastos = novo2;
                }
            }
            comparar = comparar->next;
        }
        atual = atual->next;
    }

    return nefastos;
}


/**
 * .
 * mostrarMatrizComNefastos
 * Exibe a matriz mostrando antenas e pontos nefastos
 * \param lista_antenas Lista de antenas
 * \param lista_nefastos Lista de pontos nefastos
 */
void mostrarMatrizNefastos(antena* lista_antenas, nefasto* lista_nefastos) {
    printf("\nMatriz com Efeitos Nefastos (%dx%d):\n", MAX_LINHAS, MAX_COLUNAS);
    for (int l = 0; l < MAX_LINHAS; l++) {
        for (int c = 0; c < MAX_COLUNAS; c++) {
            antena* ant = procurarantena(lista_antenas, l, c);

            if (ant != NULL) {
                printf("%c ", ant->frequencia);
            }
            else {
                nefasto* n = lista_nefastos;
                int ehnefasto = 0;

                while (n != NULL && ehnefasto == 0) {
                    if (n->nx == l && n->ny == c) {
                        ehnefasto = 1;
                    }
                    n = n->next;
                }

                if (ehnefasto) {
                    printf("# ");
                }
                else {
                    printf(". ");
                }
            }
        }
        printf("\n");
    }
}



/**
 * .
 * libertarListaNefasto
 * Função para libertar a memoria
 * \param lista
 */
void libertarListaNefasto(nefasto* lnefasto) {
    nefasto* atual = lnefasto;

    while (atual != NULL) {
        nefasto* proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}

