#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libconjunto.h"

/* Testa a criacao do conjunto e ve se ele realmente esta vazio */
conjunto_t* Teste_criacao (int tamanho)
{
    /* Cria conjunto */
    conjunto_t* c = cria_conjunto (tamanho);
    if (c == NULL)
    {
        printf ("ERRO: conjunto nao criado\n");
        return c;
    }
    printf ("OK: Conjunto criado com sucesso! \n");
    /* Testa se vazio: */
    if (! conjunto_vazio (c))
    {
        printf ("ERRO: Conjunto nao esta vazio! \n");
        return c;
    }
    printf ("OK: Conjunto vazio! \n");
    return c;
}

/* insere nelem elementos na lista, esperando que acuse pilha cheia */
void Teste_insere (conjunto_t* c, int valorini, int valorfim, int max)
{
    int i;
    for (i=valorini; i <= valorfim; i++)
    {
        int x = insere_conjunto (c, i);
        if (x == -1)
            printf ("ERRO: Conjunto cheio, nao inseriu %d\n", i);
        else if (x == 0)
            printf ("ERRO: elemento %d ja existente", i);
        else if (x == 1)
            printf ("OK: Enfileirou %d\n", i);
    }
    if (conjunto_vazio (c))
        printf ("ERRO: Conjunto vazio\n");
    else 
        printf ("OK: Conjunto nao vazio\n");
    if (cardinalidade(c) == max)
        printf ("OK: Cardinalidade correta (%d)\n", max);
    else
        printf ("ERRO: Cardinalidade incorreta\n");
}

void Teste_uniao (conjunto_t* c1, conjunto_t* c2)
{
    conjunto_t* aux = cria_uniao (c1, c2);
    if (aux == NULL)
        printf ("ERRO: Uniao nao criada\n");
    else
        printf ("OK: Uniao criada com sucesso\n");
    printf ("Conjunto 1: ");
    imprime (c1);
    printf ("Conjunto 2: ");
    imprime (c2);
    printf ("Uniao: ");
    imprime (aux);
    printf ("\n");
}

void Teste_diferenca (conjunto_t* c1, conjunto_t* c2)
{
    conjunto_t* aux = cria_diferenca (c1, c2);
    if (aux == NULL)
        printf ("ERRO: Diferenca nao criada\n");
    else
        printf ("OK: Diferenca criada com sucesso\n");
    printf ("Conjunto 1: ");
    imprime (c1);
    printf ("Conjunto 2: ");
    imprime (c2);
    printf ("Diferenca: ");
    imprime (aux);
    printf ("\n");
}

void Teste_interseccao (conjunto_t* c1, conjunto_t* c2)
{
    conjunto_t* aux = cria_interseccao (c1, c2);
    if (aux == NULL)
        printf ("ERRO: Interseccao nao criada\n");
    else
        printf ("OK: Interseccao criada com sucesso\n");
    printf ("Conjunto 1: ");
    imprime (c1);
    printf ("Conjunto 2: ");
    imprime (c2);
    printf ("Interseccao: ");
    imprime (aux);
    printf ("\n");
}

void Teste_copia (conjunto_t* c)
{
    conjunto_t* aux = cria_copia (c);
    if (aux == NULL || aux == 0)
        printf ("ERRO: Copia nao criada\n");
    else
        printf ("OK: Copia criada com sucesso\n");
    printf ("Conjunto: ");
    imprime (c);
    printf ("Copia: ");
    imprime (aux);
    printf ("\n");
    if (sao_iguais (c, aux))
        printf ("OK: Copia correta\n");
    else
        printf ("ERRO: Copia incorreta\n");
}

void Teste_retira (conjunto_t* c, int valorini, int valorfim)
{
    printf ("Conjunto: ");
    imprime (c);
    printf ("Desenfileirando todos os elementos\n");
    int i;
    for (i=valorini; i <= valorfim; i++)
    {
        int x = retira_conjunto (c, i);
        if (x == -1)
            printf ("ERRO: Conjunto vazio, nao desenfileirou %d\n", i);
        else if (x == 0)
            printf ("ERRO: elemento %d nao existente\n", i);
        else if (x == 1)
            printf ("OK: Desenfileirou %d\n", i);
    }
    if (conjunto_vazio (c))
        printf ("OK: Conjunto vazio\n");
    else 
        {
        printf ("ERRO: Conjunto nao vazio: restam %d elementos\n", cardinalidade(c));
        imprime (c);
        }
}

void Teste_pertence (conjunto_t* c, int v1, int v2, int v3)
{
    printf ("Conjunto: ");
    imprime (c);
    if (pertence (c, v1))
        printf ("OK: %d pertence ao conjunto\n", v1);
    else
        printf ("ERRO: %d nao pertence ao conjunto\n", v1);

    if (pertence (c, v2))
        printf ("OK: %d pertence ao conjunto\n", v2);
    else
        printf ("ERRO: %d nao pertence ao conjunto\n", v2);

    if (pertence (c, v3))
        printf ("OK: %d pertence ao conjunto\n", v3);
    else
        printf ("ERRO: %d nao pertence ao conjunto\n", v3);
}

void Teste_Subconjunto (conjunto_t* c1)
{
    printf ("Conjunto 1: ");
    imprime (c1);
    srand (time(NULL));
    int num = (rand() % (c1->card+1));
    conjunto_t* aux = cria_subconjunto (c1, num);
    printf ("Sub-Conjunto: ");
    imprime (aux);
    if (contido (aux, c1))
        printf ("OK: Conjunto 1 eh subconjunto de Conjunto 2\n");
    else
        printf ("ERRO: Conjunto 1 nao eh subconjunto de Conjunto 2\n");
}

void Teste_redmensiona (conjunto_t* c)
{
    Teste_insere (c, 1, 6, 5);
    printf ("Conjunto: ");
    imprime (c);
    printf ("\nRedimensionando..\n\n");
    redimensiona (c);
    Teste_insere (c, 6, 11, 10);
    printf ("Conjunto: ");
    imprime (c);
}

int main ()
{
    conjunto_t* c1;
    conjunto_t* c2;
    int Tam = 5;

    printf ("\n----------------------------------------------\n");
    printf ("Teste 1: Criacao de dois conjuntos com 5 elementos\n");
    c1 = Teste_criacao (Tam);
    printf ("Esperado: Conjunto criado e vazio (0 erros)\n\n");
    c2 = Teste_criacao (Tam);
    printf ("Esperado: Conjunto criado e vazio (0 erros)\n");

    printf ("\n----------------------------------------------\n");
    printf ("Teste 2: Insercao de 5 elementos nos conjuntos\n");
    printf ("---> Conjunto 1: \n");
    Teste_insere (c1, 1, 5, Tam);
    imprime (c1);
    printf ("Esperado: Inseriu 5 elementos de 1 a 5 e cardinalidade 5(0 erros)\n\n");
    printf ("---> Conjunto 2: \n");
    Teste_insere (c2, 4, 8, Tam);
    imprime (c2);
    printf ("Esperado: Inseriu 5 elementos de 4 a 8 e cardinalidade 5(0 erros)\n");

    printf ("\n----------------------------------------------\n");
    printf ("Teste 3: uniao, diferenca e interseccao entre conjuntos\n");
    Teste_uniao (c1, c2);
    printf ("Esperado: Uniao criada com sucesso e elementos corretos (0 erros)\n\n");
    Teste_diferenca (c1, c2);
    printf ("Esperado: Diferenca criada com sucesso e elementos corretos (0 erros)\n\n");
    Teste_interseccao (c1, c2);
    printf ("Esperado: Interseccao criada com sucesso e elementos corretos (0 erros)\n");

    printf ("\n----------------------------------------------\n");
    printf ("Teste 4: Copia e igualdade entre conjuntos\n");
    Teste_copia (c1);
    printf ("Esperado: Copia criada com sucesso e elementos iguais (0 erros)\n");

    printf ("\n----------------------------------------------\n");
    printf ("Teste 5: Retirada de elementos dos conjuntos\n");
    printf ("---> Conjunto 1: \n");
    Teste_retira (c1, 1, 5);
    printf ("Esperado: Retirou de 1 a 5 e esta vazio (0 erros)\n");

    printf ("\n----------------------------------------------\n");
    printf ("Teste 7: pertence\n");
    Teste_pertence (c2, 4, 6, 10);
    printf ("Esperado: 4 e 6 pertencem e 10 nao pertence (1 erro)\n");

    printf ("\n----------------------------------------------\n");
    printf ("Teste 9: sub-conjunto e pertencimento\n");
    printf ("---> Conjunto: \n");
    imprime (c2);
    Teste_Subconjunto (c2);
    printf ("Esperado: Subconjunto criado e contido dentro de c1 (0 erros)\n");

    printf ("\n----------------------------------------------\n");
    printf ("Teste 10: Redimensionando\n");
    Teste_redmensiona(c1);
    printf ("Esperado: Insercao de 1 a 5 e depois de 6 a 10 (2 erros em 6 e 11)\n");
    

    printf ("\n----------------------------------------------\n");
    printf ("Teste x: Limpeza de memoria e free()\n");
    printf ("Limpando memoria... Checar valgrind para possiveis erros\n");
    destroi_conjunto (c1);
    destroi_conjunto (c2);
    return 0;
}