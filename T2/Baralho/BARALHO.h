#if ! defined( BARALHO_ )
#define BARALHO_
/***************************************************************************
*  $MCD Módulo de definição: BAR  Baralho
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Projeto: INF 1301 Jogo de Truco
*  Gestor:
*  Autores: gsc, jvr, tgf
*
*  $HA Histórico de evolução:
*     Versão      Autor         Data            Observações
*     2       gsc, jvr, tgf   31/abr/2018     criação da função CriarBaralho
*     1            gsc        19/abr/2018     início desenvolvimento
*
*  $ED Descrição do módulo
*     Cria um baralho (lista) de 40 (ou vamos fazer com 52?) cartas (sem os 8,
*     9, 10 e coringa) pegando elementos previamente embaralhados em um vetor;
*     Cria as mãos dos jogadores (lista de 3 elementos, que são 3 cartas);
*     Cria uma lista que armazena as cartas apostadas na mesa e a manilha;
*     Destrói esse baralho.
***************************************************************************/

#include "LISTA.h"

#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

/**************** DECLARAÇÕES EXPORTADAS PELO MÓDULO **********************/

// Tipo referência para uma carta
typedef struct BAR_tagCarta * BAR_tppCarta ;


/***************************************************************************
*  $TC Tipo de dados: BAR Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de carta.
***************************************************************************/
typedef enum { //não tenho certeza se algumas dessas condições de retorno devem existir

   BAR_CondRetOK,                 // 0 Concluiu corretamente
   BAR_CondRetNaoCriouBaralho,    // 1 Não criou ponteiro pro tpLista
   BAR_CondRetNaoCriouCarta,      // 2 Não criou ponteiro pro tpCarta
   BAR_CondRetNaoCriouMaoJogador, // 3 Não criou ponteiro pro tpLista
   BAR_CondRetNaoCriouMesa,       // 4 Não criou ponteiro pro tpLista
   BAR_CondRetNaoDestruiu,        // 5 Não liberou ponteiro
   BAR_CondRetFaltouMemoria,      // 6 Faltou memoria 
   BAR_CondRetParamIncorretos     // 7 Parâmetros da função incorretos

} BAR_tpCondRet;


/***************************************************************************
*  $TC Tipo de dados: BAR tpValorCarta
*
*  $ED Descrição do tipo
*     Domínio dos possíveis valores de uma carta.
***************************************************************************/
typedef enum {
   _4,               // 0
   _5,               // 1
   _6,               // 2
   _7,               // 3
   _Q,               // 4
   _J,               // 5
   _K,               // 6
   _A,               // 7                        
   _2,               // 8
   _3,               // 9
} BAR_tpValorCarta ;


/***************************************************************************
*  $TC Tipo de dados: BAR tpNaipeCarta
*
*  $ED Descrição do tipo
*     Dominio dos possiveis naipes de uma carta.
***************************************************************************/
typedef enum {
  Ouros,          // 0
  Espadas,        // 1
  Copas,          // 2
  Paus            // 3
} BAR_tpNaipeCarta ;


/***************************************************************************



/***************************************************************************
*  $FC Função: BAR  &Criar Baralho
*
*  $ED Descrição da função
*     Cria um baralho (tpLista) de 40 elementos (tpCarta) sem os 8, 9, 10
*     e coringas.
*
*  $EP Parâmetros
*     
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para o início do baralho
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem este baralho.
*
*     Se ocorrer algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido. 
***************************************************************************/
LIS_tppLista BAR_CriarBaralho();


/***************************************************************************
*  $FC Função: BAR  &Criar Carta
*
*  $ED Descrição da função
*     Cria uma variável tipo carta com valores definidos.
*
*  $EP Parâmetros
*     BAR_tpValorCarta e BAR_tpNaipeCarta
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para tpCarta.
*	  Este ponteiro será utilizado para adicionar carta em um vetor.
***************************************************************************/
BAR_tppCarta BAR_CriarCarta (BAR_tpValorCarta valor, BAR_tpNaipeCarta naipe);


/***************************************************************************
*  $FC Função: BAR  &Destruir Carta
*
*  $ED Descrição da função
*     Destrói uma carta.
***************************************************************************/
void BAR_DestruirCarta(void * pCarta);
//se não receber void e retornar ponteiro pra void não
//tem como passar ela como parâmetro pra LIS_CriarLista
//quando for criar uma "lista inferior" (lista de elementos cartas)


/***************************************************************************
*  $FC Função: BAR  &Destruir Baralho
*
*  $ED Descrição da função
*     Destrói a lista baralho fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
***************************************************************************/
void BAR_DestruirBaralho(void * pBaralho);
//se não receber void e retornar ponteiro pra void não
//tem como passar ela como parâmetro pra LIS_CriarLista
//quando for criar a "lista superior" (lista de elementos listas)


#undef BARALHO_EXT

/**************** FIM DO MÓDULO DE DEFINIÇÃO: BAR Baralho *****************/

#else
#endif
