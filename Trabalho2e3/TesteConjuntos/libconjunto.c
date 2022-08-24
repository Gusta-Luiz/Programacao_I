#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

/* --------- Funcoes extras para a ordenacao e busca dentro de vetores ---------- */
/* insere o valor no vetor ordenado, mantendo a ordenação
 * Procura o lugar do valor dentro do vetor */
void insere_ordenado(int *vet, int card, int valor)
{
    int i = 0;
    while (i < card && valor > vet[i])
        i++;
    if (i == card)
        vet[i] = valor;
    else
    {
        int j = card;
        while (j > i)
        {
            vet[j] = vet[j-1];
            j--;
        }
        vet[i] = valor;
    }
}
/* Realiza a busca de um valor dentro de um vetor ordenado 
 * Retorna o indice do valor, ou -1 se nao encontrado */
int buscaBinaria(int *Vet, int a, int b, int val) 
{   
    if (a > b)
        return -1;
    int m = (a + b)/2;
    if (val == Vet[m])
        return (m);
    if (val < Vet[m])
        return buscaBinaria(Vet, a, (m-1), val);
    return buscaBinaria(Vet, (m+1), b, val);
}
/* -------------------------------------------------------- */

conjunto_t * cria_conjunto (int max)
{
    /* Cria a struct conjunto e testa o malloc */
    conjunto_t *c = (conjunto_t *) malloc (sizeof (conjunto_t));
    if (c == NULL) 
        return NULL;
    /* Inicializa os elementos da struct */
    c->max = max;
    c->card = 0;
    c->ptr = 0;
    /* Aloca o espaço do vetor e o testa */
    c->v = (int *) malloc (max * sizeof (int));
    if (c->v == NULL) 
    {
        free (c);
        return NULL;
    }
    return c;
}

conjunto_t * destroi_conjunto (conjunto_t *c)
{
    /* Limpa os espaços alocados começando pelo vetor da struct */
    free (c->v);
    /* Depois limpa a struct */
    free (c);
    return NULL;
}

int conjunto_vazio (conjunto_t *c)
{
    /* Se a cardinalidade for 0, o conjunto está vazio */
    if (c->card == 0)
        return 1;
    return 0;
}

int cardinalidade (conjunto_t *c)
{
    /* Retorna a cardinalidade do conjunto */
    return c->card;
}

int insere_conjunto (conjunto_t *c, int elemento)
{
    /* Testa se o conjunto está cheio */
    if (c->card == c->max)
        return -1;
    /* Testa se o elemento já existe no conjunto */
    int i;
    for (i = 0; i < c->card; i++)
    {
        if (c->v[i] == elemento)
            return 0;
    }
    /* Insere o elemento no vetor de modo ordenado */
    insere_ordenado(c->v, c->card, elemento);
    c->card++;
    return 1;
}

int retira_conjunto (conjunto_t *c, int elemento)
{
    /* Testa se o elemento existe no conjunto */
    int i = buscaBinaria(c->v, 0, (c->card-1), elemento);
    if (i == -1)
        return 0;
    elemento = c->v[i];
    /* Se o elemento não for o último, troca com o último e diminui a cardinalidade */
    if (i != c->card - 1)
        for (i = i; i < c->card - 1; i++)
            c->v[i] = c->v[i+1];
    /* Se o elemento for o ultimo do vetor, apenas diminui a cardinalidade */
    c->card--;
    return 1;

}

int pertence (conjunto_t *c, int elemento)
{
    /* Testa se o elemento existe no conjunto */
    if (buscaBinaria(c->v, 0, c->card, elemento) != -1)
        return 1;
    return 0;
}

int contido (conjunto_t *c1, conjunto_t *c2)
{
    /* Testa se o conjunto c1 está contido no conjunto c2 */
    int i;
    for (i = 0; i < c1->card; i++)
    {
        if (!pertence (c2, c1->v[i]))
            return 0;
    }
    return 1;
}

int sao_iguais (conjunto_t *c1, conjunto_t *c2)
{
    /* Testa se os conjuntos são iguais */
    if (c1->card != c2->card)
        return 0;
    return contido (c1, c2);
}

conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2)
{
    /* Cria um novo conjunto e o testa */
    conjunto_t *aux = cria_conjunto (c1->max);
    if (aux == NULL)
        return 0;
    /* Insere os elementos de c1 que não estão em c2 no novo conjunto */
    int i;
    for (i = 0; i < c1->card; i++)
    {
        if (!pertence (c2, c1->v[i]))
            insere_conjunto (aux, c1->v[i]);
    }
    for (i = 0; i < c2->card; i++)
    {
        if (!pertence (c1, c2->v[i]))
            insere_conjunto (aux, c2->v[i]);
    }
    return aux;
}

conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2)
{
    /* Cria um novo conjunto e o testa */
    conjunto_t *aux = cria_conjunto (c1->max);
    if (aux == NULL)
        return 0;
    /* Insere os elementos de c1 que estão em c2 no novo conjunto */
    int i;
    for (i = 0; i < c1->card; i++)
    {
        if (pertence (c2, c1->v[i]))
            insere_conjunto (aux, c1->v[i]);
    }
    return aux;
}

conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2)
{
    /* Cria um novo conjunto e o testa */
    conjunto_t *aux = cria_conjunto (c1->max + c2->max);
    if (aux == NULL)
        return NULL;
    /* Insere os elementos de c1 no novo conjunto */
    int i;
    for (i = 0; i < c1->card; i++)
    {
        insere_conjunto (aux, c1->v[i]);
    }
    /* Insere os elementos de c2 no novo conjunto */
    for (i = 0; i < c2->card; i++)
    {
        insere_conjunto (aux, c2->v[i]);
    }
    return aux;
}

conjunto_t * cria_copia (conjunto_t *c)
{
    /*  */
    if (c->card == 0)
        return NULL;
    /* Cria um novo conjunto e o testa */
    conjunto_t *aux = cria_conjunto (c->max);
    if (aux == NULL)
        return 0;
    /* Insere os elementos de c no novo conjunto */
    int i;
    for (i = 0; i < c->card; i++)
    {
        insere_conjunto (aux, c->v[i]);
    }
    return aux;
}

conjunto_t * cria_subconjunto (conjunto_t *c, int n)
{
    /* Testa para que n não seja maior q a cardinalidade de c */
    if (n >= c->card || n < 0)
        return c;
    /* Cria um novo conjunto e o testa */
    conjunto_t *aux = cria_conjunto (n);
    if (aux == NULL)
        return c;
    /* Insere os elementos de c no novo conjunto */
    int i;
    for (i = 0; i < n; i++)
    {
        int x = (rand() % c->card);
        insere_conjunto (aux, c->v[x]);
    }
    return aux;
}

void imprime (conjunto_t *c)
{
    int i;
    printf ("Conjunto {");
    if (conjunto_vazio (c))
        printf ("Vazio");
    /* Imprime os elementos do conjunto */
    else
        for (i = 0; i < c->card; i++)
        {
            printf ("%d ", c->v[i]);
        }
    printf ("}\n");
}

int redimensiona (conjunto_t *c)
{
    /* Redimensiona o vetor de acordo com a cardinalidade */
    int *aux = realloc (c->v, c->max * 2 * (sizeof (int)));
    if (aux == NULL)
        return 0;
    c->v = aux;
    c->max = (c->max * 2);
    return 1;
}

/*
 * As funcoes abaixo permitem acessar elementos apontados pelo ponteiro 'ptr'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
 */

/* ARRUMAR ESSA PARTE: */
void iniciar_iterador (conjunto_t *c)
{
    return ;
}

int incrementar_iterador (conjunto_t *c, int *elemento)
{
    return 0;
}

int retirar_um_elemento (conjunto_t *c)
{
    return 0;
}