#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "liblef.h"

/* Tipos de eventos: CHEGADA, SAIDA, DISSEMINACAO e FIM*/

#define COORD 1
#define VETOR 2

typedef struct coordenada {
    int x;
    int y;
} coordenada_t;

typedef struct vetor {
    int* vetor;
    int tam;
} vetor_t;

evento_t *copia_evento (evento_t *antigo)
{
    /* Aloca o espaco para o evento e seus dados criados e os preenchem */
    evento_t *evento = malloc(sizeof(evento_t));
    if (evento == NULL)
        return NULL;
    void *dados = malloc(antigo->tamanho);
    if (dados == NULL)
        return NULL;

    /* Copia os valores entre eventos */
    evento->tamanho = antigo->tamanho;
    evento->tipo = antigo->tipo;
    evento->destroidados = antigo->destroidados;
    evento->tempo = antigo->tempo;

    /* Copia os dados de acordo com seu tipo e tamanho */
    if (evento->tipo == COORD)
        memcpy(dados, antigo->dados, sizeof(coordenada_t));
    else if (evento->tipo == VETOR)
        memcpy(dados, antigo->dados, sizeof(vetor_t));
    else
        memcpy(dados, antigo->dados, evento->tamanho);
    evento->dados = dados;
    
    return evento;
}

lef_t *cria_lef ()
{
    /* aloca memoria para um struct e testa a mesma */
	lef_t *lef = malloc(sizeof(lef_t));
	if (lef == NULL)
	        return NULL;
    
    lef->Primeiro = NULL;
    return lef;
}

lef_t * destroi_lef (lef_t *l)
{
    /* Libera a memoria utilizada */
    while (l->Primeiro->prox != NULL)
    {
        printf("teste");
        nodo_lef_t *aux = l->Primeiro;
        l->Primeiro = l->Primeiro->prox;
        aux->evento->destroidados(aux->evento->dados);
        free(aux);
    }
    free(l);
    return NULL;
}

int adiciona_inicio_lef (lef_t *l, evento_t *evento)
{
    /* cria um novo nodo e evento e testa os mallocs */
    nodo_lef_t *nodo = malloc(sizeof(nodo_lef_t));
    if (nodo == NULL)
        return 0;
    evento_t *novo_evento = copia_evento(evento);
    if (novo_evento == NULL)
        return 0;
    
    /* copia a estrutura de evento recebida e a salva no novo nodo */
    nodo->evento = novo_evento;
    nodo->prox = NULL;

    /* Salva o nodo na primeira posicao e move o resto */
    nodo_lef_t *aux = l->Primeiro;
    l->Primeiro = nodo;
    nodo->prox = aux;

    return 1;
}

int adiciona_ordem_lef  (lef_t *l, evento_t *evento)
{
    /* cria um novo nodo e evento e testa os mallocs */
    nodo_lef_t *nodo = malloc(sizeof(nodo_lef_t));
    if (nodo == NULL)
        return 0;
    evento_t *novo_evento = copia_evento(evento);
    if (novo_evento == NULL)
        return 0;

    /* copia a estrutura de evento recebida e a salva no novo nodo */
    nodo->evento = novo_evento;
    nodo->prox = NULL;

    /* procura a posição para adicionar o nodo */
    /* Caso a lista esteja vazia: */
    if (l->Primeiro == NULL)
    {
        nodo->prox = NULL;
        l->Primeiro = nodo;
        return 1;
    }
    else if (l->Primeiro->evento->tempo > evento->tempo)
    {
        /* Caso o nodo deva ficar na primeira posicao */
        nodo_lef_t *aux = l->Primeiro;
        l->Primeiro = nodo;
        nodo->prox = aux;
        return 1;
    }
    else
    {
        /* Caso nao esteja vazia */
        nodo_lef_t *aux;
        for (aux = l->Primeiro; aux->prox != NULL; aux = aux->prox)
        {
            if (aux->prox->evento->tempo > evento->tempo)
            {
                /* Salva o nodo na posicao correta */
                nodo->prox = aux->prox;
                aux->prox = nodo;
                return 1;
            }
        }
        /* Salva o nodo na ultima posicao se nao encontrado */
        nodo->prox = NULL;
        aux->prox = nodo;
        return 1;
    }
}

evento_t * obtem_primeiro_lef (lef_t *l)
{
    /* Testa se a lista esta vazia */
    if (l->Primeiro == NULL)
        return NULL;
    
    /* retorna o primeiro evento da lista e aponta para o prox nodo */
    nodo_lef_t *aux = l->Primeiro;
    l->Primeiro = l->Primeiro->prox;

    return aux->evento;
}
