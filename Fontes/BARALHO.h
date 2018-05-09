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
   BAR_CondRetParamIncorretos    // 7 Parâmetros da função incorretos

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
*     Cria um baralho de 40 cartas (sem os 8, 9, 10 e coringas)
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca do baralho
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem este baralho. 
***************************************************************************/
LIS_tppLista BAR_CriarBaralho();


/***************************************************************************
*  $FC Função: BAR  &Criar Carta
*
*  $ED Descrição da função
*     Cria uma variável tipo carta com valores definidos.
*
*  $EP Parâmetros
*     Recebe o valor e naipe de uma carta a ser criada.
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


/***************************************************************************
*  $FC Função: BAR  &Obter Carta
*
*  $EP Parâmetros
*  LIS_tppLista pCabecaBaralho: ponteiro pra cabeca da lista do baralho.
*
*  $ED Descrição da função
*     Obtém um ponteiro pra um tipo carta criado.
***************************************************************************/
BAR_tppCarta BAR_ObterCarta(LIS_tppLista pCabecaBaralho) ;


/***************************************************************************
*  $FC Função: BAR  &Obter Naipe
*
*  $EP Parâmetros
*  BAR_tppCarta pCarta: ponteiro pra uma carta.
*
*  $ED Descrição da função
*     Obtém o naipe de uma carta.
***************************************************************************/
BAR_tpNaipeCarta BAR_ObterNaipe(BAR_tppCarta pCarta) ;


/***************************************************************************
*  $FC Função: BAR  &Obter valor
*
*  $EP Parâmetros
*  BAR_tppCarta pCarta: ponteiro pra uma carta.
*
*  $ED Descrição da função
*     Obtém o valor de uma carta.
***************************************************************************/
BAR_tpValorCarta BAR_ObterValor(BAR_tppCarta pCarta);


#undef BARALHO_EXT

/**************** FIM DO MÓDULO DE DEFINIÇÃO: BAR Baralho *****************/

#else
#endif
