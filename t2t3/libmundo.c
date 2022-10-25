#include <stdlib.h>
#include "libmundo.h"
#include "liblef.h"
#include "libfila.h"
#include "libconjunto.h"

/*---------------------- Valores Fixos -----------------------*/
#define NTamMundo 150 /* Plano de 150x150 */
#define NRumores 30
#define NPessoas 100
#define NLocais 10
#define Fim 34944

#define CHEGADA 2
#define SAIDA 3
#define RUMOR 4
#define FIM 5

/*-------------------- Funcoes Auxiliares --------------------*/

int local_lotado (local_t *local)
{
    if (local->pessoas->card = local->pessoas->max)
        return 1;
    else
        return 0;
}

int aleat (int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

coordenada_t *calc_posicao ()
{
    coordenada_t *posicao = malloc (sizeof (coordenada_t));
    if (posicao == NULL)
        return NULL;
    posicao->x = aleat (0, NTamMundo);
    posicao->y = aleat (0, NTamMundo);
    return posicao;
}

/*------------------ Funcoes para a Criacao ------------------*/

mundo_t * Cria_Mundo (int N_pessoas, int N_locais, int N_rumores, int NxN_mundo)
{
    /* Aloca espaco para a struct MUNDO */
    mundo_t *MUNDO = malloc (sizeof (mundo_t));
    if (MUNDO == NULL)
        return  NULL;
    /* Inicializa o tempo atual em 0 */
    MUNDO->tempo = 0;
    /* Cria o conjunto de locais do mundo */
    MUNDO->locais = cria_conjunto (NLocais);
    if (MUNDO->locais == NULL)
        return NULL;
    /* Cria o conjunto de pessoas do mundo */
    MUNDO->pessoas = cria_conjunto (NPessoas);
    if (MUNDO->pessoas == NULL)
        return NULL;
    return MUNDO;
}

int Cria_Rumor (mundo_t *Mundo)
{
    /* Cria o conjunto de rumores e o inicializa */
    Mundo->rumores = cria_conjunto (NRumores);
    if (Mundo->rumores == NULL)
        return 0;
    /* Insere os rumores em ordem, de 1 a NRumores */
    int i;
    for (i = 0; i < Mundo->rumores->max; i++)
        insere_conjunto (Mundo->rumores, i);
    return 1;
}

int Cria_Local (mundo_t *Mundo, int id)
{
    /* Aloca espaco para a struct LOCAL */
    local_t *local = malloc (sizeof (local_t));
    if (local == NULL)
        return 0;
    /* Cria o conjunto de pessoas que podem estar no local */
    local->pessoas = cria_conjunto (aleat (1, NPessoas));
    if (local->pessoas == NULL)
        return 0;
    /* Cria a fila de pessoas que poderao esperar a entrada */
    local->fila_espera = cria_fila ();
    if (local->fila_espera == NULL)
        return 0;
    /* Posicao aleatoria no plano onde o local se encontra */
    local->lugar = calc_posicao ();
    if (local->lugar == NULL)
        return 0;
    /* Adiciona seu id */
    local->id = id;
    /* Adiciona o local recem criado ao conjunto de locais do MUNDO */
    if (insere_conjunto (Mundo->locais, local) == 0)
        return 0;
    return 1;
}

int Cria_Pessoa (mundo_t *Mundo, int id)
{
    /* Aloca espaco para a struct pessoa */
    pessoa_t *pessoa = malloc (sizeof (pessoa_t));
    if (pessoa == NULL)
        return 0;
    /* Aloca o espaco da lef */
    Mundo->lef = cria_lef ();
    if (Mundo->lef == NULL)
        return 0;
    /* Identificador unico */
    pessoa->id = id;
    /* Define o nivel de paciencia e extroversao da pessoa */
    pessoa->paciencia = aleat (0, 100);
    pessoa->extroversao = aleat (0, 100);
    /* Define a idade da pessoa, entre 18 a 100 */
    pessoa->idade = aleat (18, 100);
    /* Cria o conjunto de rumores conhecidos por esta pessoa
     * que inicialmente sera de 1 rumor apenas */
    pessoa->rumores = cria_subconjunto (Mundo->rumores, 1);
    if (pessoa->rumores == NULL)
        return 0;
    return 1;
}

/*-------------------- EVENTOS POSSIVEIS ---------------------*/

int insere_chegada_saida (evento_t *evento, int tempo, int tipo, local_t *local, pessoa_t *pessoa)
{
    evento->tempo = tempo;
    evento->tipo = tipo;
    ((chegada_saida_t*)evento->dados)->local = local;
    ((chegada_saida_t*)evento->dados)->pessoa = pessoa;
    return 1;
}

void Gerencia_LEF (mundo_t *mundo)
{
    /* Recebe o evento que deve ser realizado */
    evento_t *evento = obtem_primeiro_lef (mundo->lef);
    if (evento == NULL)
        return;
    /* Atualiza o tempo do mundo */
    mundo->tempo = evento->tempo;
    /* Verifica o tipo de evento */
    switch (evento->tipo)
    {
        case CHEGADA:
            Evento_Chegada (mundo, evento);
            break;
        case SAIDA:
            Evento_Saida (mundo, evento);
            break;
        case RUMOR:
            Evento_Rumor (mundo, evento);
            break;
        case FIM:
            Evento_Fim (mundo, evento);
            break;
    }

}

evento_t * Cria_chegada_saida (int tempo, int tipo, local_t *local, pessoa_t *pessoa)
{
    /* Cria e testa o malloc dos eventos */
    evento_t *evento = malloc (sizeof (evento_t));
    if (evento == NULL)
        return NULL;
    evento->tamanho = sizeof (chegada_saida_t);
    evento->dados = malloc (evento->tamanho);
    if (evento->dados == NULL)
        return NULL;

    /* Adiciona o conteudo dos eventos e dados */
    evento->tempo = tempo;
    evento->tipo = tipo;
    ((chegada_saida_t*)evento->dados)->local = local;
    ((chegada_saida_t*)evento->dados)->pessoa = pessoa;
    return evento;
}

evento_t * Cria_conversa (int tempo, pessoa_t *pessoa, local_t *local)
{
    /* Cria e testa o malloc do evento */
    evento_t *evento = malloc (sizeof (evento_t));
    if (evento == NULL)
        return NULL;
    evento->tamanho = sizeof (conversa_t);
    evento->dados = malloc (evento->tamanho);
    if (evento->dados == NULL)
        return NULL;
    
    /* Adiciona os dados do evento */
    evento->tempo = tempo;
    evento->tipo = RUMOR;
    ((conversa_t*)evento->dados)->pessoa = pessoa;
    ((conversa_t*)evento->dados)->local = local;
    return evento;

}

int Evento_chegada (mundo_t *mundo, evento_t *evento)
{
    if (local_lotado(((chegada_saida_t*)evento->dados)->local->fila_espera->tamanho))
        /* Se o local estiver lotado: */
        if (((chegada_saida_t*)evento->dados)->pessoa->paciencia % 4 - ((chegada_saida_t*)evento->dados)->local->fila_espera->tamanho > 0)
            {
            /* Se a pessoa tiver paciencia suficiente para esperar: */
            insere_fila (((chegada_saida_t*)evento->dados)->local->fila_espera, ((chegada_saida_t*)evento->dados)->pessoa->id);
            return 1;
            }
        else
        {
            /* Se a pessoa nao tiver paciencia suficiente para esperar: */
            /* Cria evento de saida */
            evento_t *Saida = Cria_chegada_saida (mundo->tempo, SAIDA, ((chegada_saida_t*)evento->dados)->local, ((chegada_saida_t*)evento->dados)->pessoa);
            adiciona_ordem_lef (mundo->lef, Saida);
            return 0;
        }
    /* Se o local nao estiver lotado: */
    int TempoPermanencia = (((chegada_saida_t*)evento->dados)->pessoa->paciencia % 10 + aleat (1, 6));
    
    /* Cria evento de saida */
    evento_t *Saida = Cria_chegada_saida (mundo->tempo + TempoPermanencia, SAIDA, ((chegada_saida_t*)evento->dados)->local, ((chegada_saida_t*)evento->dados)->pessoa);
    adiciona_ordem_lef (mundo->lef, Saida);

    /* Cria evento de disseminacao */
    int Num_Rumores = (((chegada_saida_t*)evento->dados)->pessoa->extroversao % 10); 
    conjunto_t *rumor = cria_subconjunto (((chegada_saida_t*)evento->dados)->pessoa->rumores, Num_Rumores);
    evento_t *Disseminacao = Cria_conversa (mundo->tempo + aleat(0, TempoPermanencia), ((chegada_saida_t*)evento->dados)->pessoa, ((chegada_saida_t*)evento->dados)->local);
    adiciona_ordem_lef (mundo->lef, Disseminacao);
}

Evento_Saida (mundo_t *mundo, evento_t *evento)
{
    /* Caso a fila nao esteja vazia */
    if (((chegada_saida_t*)evento->dados)->local->fila_espera->tamanho > 0)
    {
        /* Cria evento de chegada na fila */
        evento_t *chegada = Cria_chegada_saida (mundo->tempo, CHEGADA, ((chegada_saida_t*)evento->dados)->local, ((chegada_saida_t*)evento->dados)->pessoa);
        adiciona_inicio_lef (mundo->lef, chegada);
    }
    /* Caso nao tenha fila */
    else
    {
        /* Cria evento de chegada */
        evento_t *chegada = Cria_chegada_saida (mundo->tempo, CHEGADA, ((chegada_saida_t*)evento->dados)->local, ((chegada_saida_t*)evento->dados)->pessoa);
        adiciona_ordem_lef (mundo->lef, chegada);
    }
}
