#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

fila_t * cria_fila ()
{
    /* Cria a struct fila e testa o malloc */
    fila_t *f = (fila_t *) malloc(sizeof (fila_t));
    if (f == NULL) 
        return NULL;
    /* Inicializa os elementos da struct */
    f->ini = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

fila_t * destroi_fila (fila_t *f)
{
    /* Libera a memoria utilizada */
    while (f->ini != NULL)
    {
        nodo_f_t *aux = f->ini;
        f->ini = f->ini->prox;
        free(aux);
    }
    free(f);
    return NULL;
}

int fila_vazia (fila_t *f)
{
    /* testa se esta vazia */
    if (f->tamanho == 0)
        return 1;
    else
        return 0;
}

int tamanho_fila (fila_t *f)
{
    /* retorna o tamanho atual da fila */
    return f->tamanho;
}

int insere_fila (fila_t *f, int elemento)
{
    /* cria um novo nodo, adiciona o valor, e testa o malloc */
    nodo_f_t *nodo = malloc(sizeof(nodo_f_t));
    if (nodo == NULL)
        return 0;
    nodo->chave = elemento;
    nodo->prox = NULL;
    if (f->tamanho == 0)
        /* caso este seja o primeiro nodo criado */
        f->ini = nodo;
    else
        /* caso nao seja o primeiro nodo criado */
        f->fim->prox = nodo;
    /* aponta o nodo anterior para o atual e adiciona no tamanho */
    f->fim = nodo;
    f->tamanho++;
    return 1;
}

int retira_fila (fila_t *f, int *elemento)
{
    if (f->tamanho == 0)
        return 0;
    /* salva elemento do nodo */
    *elemento = f->ini->chave;
    /* libera o primeiro nodo, e aponta o ini para o proximo */
    nodo_f_t *aux = f->ini;
    f->ini = f->ini->prox;
    free(aux);
    f->tamanho--;
    return 1;
}