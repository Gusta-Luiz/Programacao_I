#include "liblef.h"
#include "libfila.h"
#include "libconjunto.h"

/* Estrutura unica para o Mundo, com algumas definicoes fixas
 * e variaveis para o andamento da simulacao */
typedef struct mundo {
    int tempo;            /* Tempo atual do mundo */
    lef_t *lef;           /* Lista de eventos futuros */
    conjunto_t *pessoas;  /* Conjunto com todas os ids dos pessoas */
    conjunto_t *locais;   /* Conjunto com todos os ids dos locais */
    conjunto_t *rumores;  /* Conjunto de todos os rumores */
} mundo_t;

/* Estrutura que cada PESSOA no mundo tera, com valores unicos */
typedef struct pessoa {
    int id;               /* Identificador unico */
    int extroversao;      /* Nivel de 0 - 100 */
    int paciencia;        /* Nivel de 0 - 100 */
    int idade;            /* Idade da pessoa */
    conjunto_t *rumores;  /* Todos os rumores conhecidos */
} pessoa_t;

/* Cada LOCAL tera uma estrutura como essa, com valores diferentes */
typedef struct local {
    int id;               /* Identificador unico */
    conjunto_t *pessoas;  /* Conjunto com Pessoas presentes no local e o Max*/
    fila_t *fila_espera;  /* Fila de espera fora do local */
    coordenada_t *lugar;   /* Localizacao do local no mundo */
} local_t;

/* Utilizada para localizar um local no plano cartesiano do MUNDO */
typedef struct coordenada {
    int x;               /* Coordenada x no plano */
    int y;               /* Coordenada y no plano */
} coordenada_t;

/* Estrutura do evento de chegada */
typedef struct chegada_saida {
    int id;               /* Identificador unico */
    int tempo;            /* Tempo de chegada / saiu */
    local_t *local;            /* Local de chegada / saiu */
    pessoa_t *pessoa;           /* Pessoa que chegou / saiu */
} chegada_saida_t;

/* Estrutura do evento de conversa */
typedef struct conversa {
    int id;               /* Identificador unico */
    int tempo;            /* Tempo de conversa */
    local_t *local;            /* Local de conversa */
    pessoa_t *pessoa;          /* Pessoa que iniciou a conversa */
} conversa_t;

/*----------------------------------------------------------*/

/* Cria a estrutura MUNDO com os valores definidos na entrada
 * Retorna NULL em caso de falha, ou a struct MUNDO em sucesso */
mundo_t * Cria_Mundo ();

/* Cria o conjunto de RUMORES com no maximo NRumores e o preenche 
 * Com rumores de 0 a NRumores-1, em ordem, retorna 0 em caso de erro*/
int Cria_Rumor (mundo_t *Mundo);

/* Cria um LOCAL vazio e o insere no conjunto MUNDO
 * Retorna 0 em caso de falha, ou 1 em sucesso */
int Cria_Local (mundo_t *Mundo, int id);

/* Cria uma pessoa com atributos aleatorios e um rumor conhecido 
 * Retorna 0 em caso de erro*/
int Cria_Pessoa (mundo_t *Mundo, int id);