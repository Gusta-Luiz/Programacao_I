#include <stdlib.h>
#include "libfila.h"

fila_t* fila_cria ()
{
    /* aloca memoria para um struct e testa a mesma */
	fila_t *f = malloc(sizeof(fila_t));
	if (f == NULL)
	        return NULL;
    /* inicializa a fila */
    f->cabeca = NULL;
    f->cauda = NULL;
    f->tamanho = 0;
    return f;
}

int queue (fila_t* f, int elemento)
{
    /* cria um novo nodo, adiciona o valor, e testa o malloc */
    nodo_f_t *nodo = malloc(sizeof(nodo_f_t));
    if (nodo == NULL)
        return 0;
    nodo->chave = elemento;
    nodo->prox = NULL;

    if (f->tamanho == 0)
        /* caso este seja o primeiro nodo criado */
        f->cabeca = nodo;
    else
        /* caso nao seja o primeiro nodo criado */
        f->cauda->prox = nodo;

    /* aponta o nodo anterior para o atual e adiciona no tamanho */
    f->cauda = nodo;
    f->tamanho++;
    return 1;
}

int dequeue (fila_t* f, int* elemento)
{
    if (f->tamanho == 0)
        return 0;
    /* salva elemento do nodo */
    *elemento = f->cabeca->chave;
    /* libera o primeiro nodo, e aponta o cabeca para o proximo */
    nodo_f_t *aux = f->cabeca;
    f->cabeca = f->cabeca->prox;
    free(aux);
    f->tamanho--;
    return 1;
}

int fila_tamanho (fila_t* f)
{
    /* retorna o tamanho atual da fila */
    return f->tamanho;
}

int fila_vazia (fila_t* f)
{
    /* testa se esta vazia */
    if (f->tamanho == 0)
        return 1;
    else
        return 0;
}

fila_t* fila_destroi (fila_t* f)
{
    /* Libera a memoria utilizada */
    while (f->cabeca != NULL)
    {
        nodo_f_t *aux = f->cabeca;
        f->cabeca = f->cabeca->prox;
        free(aux);
    }
    free(f);
    return NULL;
}
