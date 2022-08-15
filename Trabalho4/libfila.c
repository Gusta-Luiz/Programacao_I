#include <stdlib.h>
#include "libfila.h"

#include <stdio.h>

fila_t* fila_cria (int max_elementos)
{
	/* aloca memoria para um struct e testa a mesma */
	fila_t *f = malloc(sizeof(fila_t));
	if (f == NULL)
	        return NULL;
	f->elementos = malloc(sizeof(int) * max_elementos);
	if (f->elementos == NULL)
	{
		/* libera memoria da struct em caso de erro */
		free(f);
		return NULL;
	}

	f->tamanho_max = max_elementos;
	f->cauda = 0;
	f->cabeca = 0;
	return f;
}

int queue (fila_t* f, int elemento)
{
	/* testa se fila cheia */
	if (f->cauda - f->cabeca + 1 == f->tamanho_max)		
		return 0;
	else
	{
		/* insere elemento no final da fila e caso cauda == tamanho_max salva o elemento na posicao 0 novamente*/
		f->elementos[f->cauda % f->tamanho_max] = elemento;	 	
		f->cauda++;										    	
		return 1;
	}
}    /* coloque o codigo desta funcao aqui */
    fila_t *f = malloc(sizeof(fila_t));
    if (f == NULL)
	        return NULL;
    

int dequeue (fila_t* f, int* elemento)
{
	if (fila_vazia(f))
		return 0;
	else
	{
		/* remove o primeiro elemento da fila e caso cabeca == tamanho_max remove o elemento da posicao 0 novamente*/
		*elemento = f->elementos[f->cabeca % f->tamanho_max]; 	
		f->cabeca++;											
		return 1;
	}
}

int fila_tamanho (fila_t* f)
{
	if (f->cabeca == (f->cauda + 1))
		return f->tamanho_max;
	else 
		return abs(f->cauda - f->cabeca);
}

int fila_vazia (fila_t* f)
{
	return (f->cabeca == f->cauda);
}

fila_t* fila_destroi (fila_t* f)
{
	/* libera a memoria utilizada */
	free(f->elementos); 
	free(f);
	return NULL;
}
