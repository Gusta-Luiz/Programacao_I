#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libconjunto.h"

/*
Funcoes extras para a ordenacao e busca dentro de vetores.
    Insere o valor no vetor ordenado, mantendo a ordenação.
    Procura o lugar do valor dentro do vetor.
*/

/* troca os valores de valorA e valorB */
void troca(int *valorA, int *valorB)
{
    int aux;
    aux = *valorA;
    *valorA = *valorB;
    *valorB = aux;
}

/* Ordena um conjunto em ordem crescente. */
void ordena_conjunto(int vetor[], int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        int menor = i;
        int j;
        for (j = i + 1; j < tam; j++)
        {
            if (vetor[j] < vetor[menor])
                menor = j;
        }
        troca(vetor + menor, vetor + i);
    }
}

/* Busca um valor dentro do vetor */
int busca(int valor, int vetor[], int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (vetor[i] == valor)
            return i;
    }
    return -1;
}
/* -------------------------------------------------------- */

conjunto_t *cria_conjunto(int max)
{
    /* Cria a struct conjunto e testa o malloc */
    conjunto_t *conjunto = malloc(sizeof(conjunto_t));
    if (conjunto == NULL)
        return NULL;

    /* Aloca o espaço do vetor e o testa */
    conjunto->v = malloc(max * sizeof(int));
    if (conjunto->v == NULL)
    {
        free(conjunto);
        return NULL;
    }

    /* Inicializa os elementos da struct */
    conjunto->max = max;
    conjunto->card = 0;
    conjunto->ptr = 0;
    return conjunto;
}

conjunto_t *destroi_conjunto(conjunto_t *conjunto)
{
    if (conjunto == NULL)
        return NULL;
    /* Limpa os espaços alocados começando pelo vetor da struct */
    free(conjunto->v);
    /* Depois limpa a struct */
    free(conjunto);
    return NULL;
}

int conjunto_vazio(conjunto_t *conjunto)
{
    /* Se a cardinalidade for 0, o conjunto está vazio */
    if (conjunto->card == 0)
        return 1;
    return 0;
}

int cardinalidade(conjunto_t *conjunto)
{
    /* Retorna a cardinalidade do conjunto */
    return conjunto->card;
}

int insere_conjunto(conjunto_t *conjunto, int elemento)
{
    /* Testa se o conjunto está cheio */
    if (conjunto->card == conjunto->max)
        return -1;

    /* Testa se o elemento já existe no conjunto */
    if (busca(elemento, conjunto->v, conjunto->card) > -1)
        return 0;

    /* Insere o elemento no vetor de modo ordenado */
    conjunto->v[conjunto->card] = elemento;
    conjunto->card++;
    return 1;
}

int retira_conjunto(conjunto_t *conjunto, int elemento)
{
    int i;
    /* Testa se o elemento existe no conjunto */
    i = busca(elemento, conjunto->v, conjunto->card);
    if (i == -1)
        return 0;

    /* Se o elemento não for o último, troca com o último e diminui a cardinalidade */
    troca(&conjunto->v[i], &conjunto->v[conjunto->card - 1]);

    /* Se o elemento for o ultimo do vetor, apenas diminui a cardinalidade */
    conjunto->card--;
    return elemento;
}

int pertence(conjunto_t *conjunto, int elemento)
{
    if (busca(elemento, conjunto->v, conjunto->card) == -1)
        return 0;
    return 1;
}

int contido(conjunto_t *c1, conjunto_t *c2)
{
    /* Testa se o conjunto c1 está contido no conjunto c2 */
    int i;
    for (i = 0; i < c1->card; i++)
    {
        if (!pertence(c2, c1->v[i]))
            return 0;
    }
    return 1;
}

int sao_iguais(conjunto_t *c1, conjunto_t *c2)
{
    /* Testa se os conjuntos são iguais */
    if (c1->card != c2->card)
        return 0;
    return contido(c1, c2);
}

conjunto_t *cria_diferenca(conjunto_t *c1, conjunto_t *c2)
{
    /* Cria um novo conjunto e o testa */
    conjunto_t *diferenca = cria_conjunto(c1->max);
    if (diferenca == NULL)
        return 0;

    /* Insere os elementos de c1 que não estão em c2 no novo conjunto */    
    int i;
    for (i = 0; i < c1->card; i++)
    {
        if (!pertence(c2, c1->v[i]))
            insere_conjunto(diferenca, c1->v[i]);
    }
    return diferenca;
}

conjunto_t *cria_interseccao(conjunto_t *c1, conjunto_t *c2)
{
    /* Cria um novo conjunto e o testa */
    conjunto_t *interseccao = cria_conjunto(c1->max);
    if (interseccao == NULL)
        return 0;

    /* Insere os elementos de c1 que estão em c2 no novo conjunto */
    int i;
    for (i = 0; i < c1->card; i++)
    {
        if (pertence(c2, c1->v[i]))
            insere_conjunto(interseccao, c1->v[i]);
    }

    return interseccao;
}

conjunto_t *cria_uniao(conjunto_t *c1, conjunto_t *c2)
{
    /* Cria um novo conjunto e o testa */
    conjunto_t *aux = cria_conjunto(c1->max + c2->max);
    if (aux == NULL)
        return NULL;
    /* Insere os elementos de c1 no novo conjunto */
    int i;
    for (i = 0; i < c1->card; i++)
    {
        insere_conjunto(aux, c1->v[i]);
    }
    /* Insere os elementos de c2 no novo conjunto */
    for (i = 0; i < c2->card; i++)
    {
        insere_conjunto(aux, c2->v[i]);
    }
    return aux;
}

conjunto_t *cria_copia(conjunto_t *conjunto)
{
    if (conjunto->card == 0)
        return 0;

    /* Cria um novo conjunto e o testa */
    conjunto_t *aux = cria_conjunto(conjunto->card);
    if (aux == NULL)
        return NULL;

    aux->card = conjunto->card;
    aux->max = conjunto->max;
    aux->ptr = conjunto->ptr;

    /* copia os valores para o novo conjunto */
    int i;
    for (i = 0; i < conjunto->card; i++)
    {
        aux->v[i] = conjunto->v[i];
    }

    return aux;
}

conjunto_t *cria_subconjunto(conjunto_t *conjunto, int n)
{
    /* Testa para que n não seja maior q a cardinalidade de conjunto */
    if (n >= conjunto->card)
        return cria_copia(conjunto);

    /* Cria um novo conjunto e o testa */
    conjunto_t *aux = cria_conjunto(n);
    if (aux == NULL)
        return 0;
    aux->max = n;
    /* Retorna subconjunto vazio se o conjunto for vazio */
    if (conjunto->card == 0)
        return aux;

    /* Insere os elementos de conjunto no novo conjunto */
    int cheio = 0;
    int indice_aleatorio;
    while (cheio < n)
    {
        indice_aleatorio = rand() % conjunto->card;
        if (insere_conjunto(aux, conjunto->v[indice_aleatorio]))
            cheio++;
    }
    return aux;
}

void imprime(conjunto_t *conjunto)
{
    int i;
    ordena_conjunto(conjunto->v, conjunto->card);

    printf("Conjunto { ");
    if (conjunto_vazio(conjunto))
        printf("Vazio ");
    /* Imprime os elementos do conjunto */
    else
        for (i = 0; i < conjunto->card; i++)
        {
            printf("%d ", conjunto->v[i]);
        }
    printf("}\n");
}
/* Redimensiona o vetor dobrando seu tamanho de acordo com a cardinalidade */
int redimensiona(conjunto_t *conjunto)
{

    int *redimensionamento;
    redimensionamento = realloc(conjunto->v, conjunto->max * 2 * (sizeof(int)));
    if (redimensionamento == NULL)
        return 0;

    conjunto->v = redimensionamento;
    conjunto->max *= 2;
    return 1;
}

/*
 * As funcoes abaixo permitem acessar elementos apontados pelo ponteiro 'ptr'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
 */

void iniciar_iterador(conjunto_t *conjunto)
{
    /*Indice aleatorio do vetor*/
    conjunto->ptr = 0;
}

int incrementar_iterador(conjunto_t *conjunto, int *elemento)
{
    if (conjunto->ptr == conjunto->card)
    {
        return 0;
    }
    *elemento = conjunto->v[conjunto->ptr];
    conjunto->ptr++;

    return 1;
}

int retirar_um_elemento(conjunto_t *conjunto)
{
    return retira_conjunto(conjunto, conjunto->v[rand() % conjunto->card]);
}
