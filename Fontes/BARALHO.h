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
*	    3		         gsc		     10/mai/2018	  revisão para entrega na data
*     2       gsc, jvr, tgf   31/abr/2018     criação da função CriarBaralho
*     1            gsc        19/abr/2018     início desenvolvimento
*
*  $ED Descrição do módulo
*     Cria um baralho pegando elementos previamente embaralhados em um vetor;
*     Cria cartas para serem armazenadas na lista baralho;
*	  Obter o valor e naipe de cartas.
*	  Destrói uma carta.
***************************************************************************/

#include "LISTA.h"
#define TAM 40

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
typedef enum {

   BAR_CondRetOK,                 // Concluiu corretamente
   BAR_CondRetNaoCriouBaralho,    // Não criou ponteiro pro tpLista
   BAR_CondRetNaoCriouCarta,      // Não criou ponteiro pro tpCarta
   BAR_CondRetNaoCriouMaoJogador, // Não criou ponteiro pro tpLista
   BAR_CondRetNaoCriouMesa,       // Não criou ponteiro pro tpLista
   BAR_CondRetNaoDestruiu,        // Não liberou ponteiro
   BAR_CondRetFaltouMemoria,      // Faltou memoria 
   BAR_CondRetParamIncorretos     // Parâmetros da função incorretos

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
*     Cria um baralho com cartas.
*
*  $EP Parâmetros
*     Recebe um vetor embaralhado que armazena ponteiros pra tipo carta.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca do baralho
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem este baralho. 
***************************************************************************/
LIS_tppLista BAR_CriarBaralho(BAR_tppCarta vtCartas[TAM]);


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
*
*  $EP Parâmetros
*     Recebe ponteiro pra um tipo void.
*
***************************************************************************/
void BAR_DestruirCarta(void * pCarta);


/***************************************************************************
*  $FC Função: BAR  &Obter Carta
*
*  $EP Parâmetros
*  	  Recebe ponteiro pra cabeca da lista do baralho.
*
*  $ED Descrição da função
*     Obtém um ponteiro pra um tipo carta criado.
*
*  $FV Valor retornado
*     Retorna um ponteiro pra um tipo carta.
*
***************************************************************************/
BAR_tppCarta BAR_ObterCartaCorr(LIS_tppLista pCabecaBaralho) ;


/***************************************************************************
*  $FC Função: BAR  &Obter Naipe
*
*  $EP Parâmetros
*  	  Recebe um ponteiro pra um tipo carta.
*
*  $ED Descrição da função
*     Obtém o naipe de uma carta.
*
*  $FV Valor retornado
*     Retorna um tipo de naipe de carta.
*
***************************************************************************/
BAR_tpNaipeCarta BAR_ObterNaipe(BAR_tppCarta pCarta) ;


/***************************************************************************
*  $FC Função: BAR  &Obter valor
*
*  $EP Parâmetros
*     Recebe um ponteiro pra um tipo carta.
*
*  $ED Descrição da função
*     Obtém o valor de uma carta.
*
*  $FV Valor retornado
*     Retorna um tipo de valor de carta.
*
***************************************************************************/
BAR_tpValorCarta BAR_ObterValor(BAR_tppCarta pCarta);


#undef BARALHO_EXT

/**************** FIM DO MÓDULO DE DEFINIÇÃO: BAR Baralho *****************/

#else
#endif
