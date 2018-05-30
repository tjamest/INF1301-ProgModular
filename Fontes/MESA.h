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
*     Cria uma mesa vazia.
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
*     Cria uma mão vazia.
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
*     Distribui as maos para os jogadores.
*
*  $EP Parâmetros
*     Ponteiros para cabeca do baralho e das maos.
*	  Numero de jogadores.
***************************************************************************/
void MES_DistribuirMaos(LIS_tppLista pCabecaSuperior, int *numJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Criar Lixo
*
*  $ED Descrição da função
*     Cria o lixo vazio.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca da mao
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem este lixo. 
***************************************************************************/
LIS_tppLista MES_CriarLixo() ;


#undef MESA_EXT

/**************** FIM DO MÓDULO DE DEFINIÇÃO: MES Mesa ********************/

#else
#endif
