#pragma once
#if ! defined( MESA_ )
#define MESA_
/***************************************************************************
*  $MCD Módulo de definição: MES  MESA
*
*  Arquivo gerado:              MESA.h
*  Letras identificadoras:      MES
*
*  Projeto: INF 1301 Jogo de Truco
*  Gestor:
*  Autores: gsc, jvr, tgf
*
*  $HA Histórico de evolução:
*     Versão      Autor         Data            Observações
*     1            gsc        19/abr/2018     início desenvolvimento
*
*  $ED Descrição do módulo
*     
***************************************************************************/

#include "BARALHO.h"
#include "LISTA.h"

#if defined( MESA_OWN )
   #define MESA_EXT
#else
   #define MESA_EXT extern
#endif

/***************************************************************************
*  $FC Função: MES  &Criar Mesa
*
*  $ED Descrição da função
*     Cria uma mesa com uma carta vira.
*
*  $EP Parâmetros
*     Recebe um vetor embaralhado que armazena ponteiros pra tipo carta.
*	  Recebe a quantidade de pessoas que vao jogar.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca da mesa
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta mesa. 
***************************************************************************/
LIS_tppLista MES_CriarMesa() ;

/***************************************************************************
*  $FC Função: MES  &Criar Mao
*
*  $ED Descrição da função
*     Cria uma mão com 3 cartas.
*
*  $EP Parâmetros
*     Recebe um vetor embaralhado que armazena ponteiros pra tipo carta.
*	  Recebe o numero da mao.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca da mao
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta mao. 
***************************************************************************/
LIS_tppLista MES_CriarMao() ;

/***************************************************************************
*  $FC Função: MES  &Distribuir maos
*
*  $ED Descrição da função
*     Distribui as maos para os jogadores
*
*  $EP Parâmetros
*     Ponteiros para cabeca do baralho e das maos.
*	  Numero de jogadores.
***************************************************************************/
void MES_DistribuirMaos(LIS_tppLista pCabecaBaralho, 
						LIS_tppLista pCabecaMao1, 
						LIS_tppLista pCabecaMao2, 
						LIS_tppLista pCabecaMao3, 
						LIS_tppLista pCabecaMao4, 
						LIS_tppLista pCabecaMao5, 
						LIS_tppLista pCabecaMao6, 
						int numJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Obter valor manilha
*
*  $ED Descrição da função
*     Obtem o valor da carta manilha.
*
*  $EP Parâmetros
*     Ponteiros para cabeca da mesa.
***************************************************************************/
int MES_ObterValorManilha(LIS_tppLista pCabecaMesa) ;


#undef MESA_EXT

/**************** FIM DO MÓDULO DE DEFINIÇÃO: MES Mesa ********************/

#else
#endif
