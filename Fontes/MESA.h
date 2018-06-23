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
*  $TC Tipo de dados: MES Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de MES.
***************************************************************************/
typedef enum {
   MES_CondRetOK,
   MES_CondRetNaoDistribuiuMaos,
   MES_CondRetNaoEsvaziouMesa,
   MES_CondRetNaoEsvaziouLixo,		
   MES_CondRetNaoTransferiuTodasCartasProLixo,
   MES_CondRetNaoIdentificouQuemJogouQual
} MES_tpCondRet;

/***************************************************************************
*  $FC Função: MES  &Iniciar Partida NAO TA FUNCIONANDO NAO SEI PQ
*
*  $ED Descrição da função
*     Cria as listas.
*
*  $FV Valor retornado
*     Retorna o valor 49 que inicia o loop da partida. 
***************************************************************************//*
int MES_IniciarPartida (LIS_tppLista pCabecaBaralho, LIS_tppLista pCabecaMao1, LIS_tppLista pCabecaMao2, 
						LIS_tppLista pCabecaMao3, LIS_tppLista pCabecaMao4, LIS_tppLista pCabecaMao5,
						LIS_tppLista pCabecaMao6, LIS_tppLista pCabecaLixo, LIS_tppLista pCabecaMesa,
						LIS_tppLista pCabecaSuperior) ;

/***************************************************************************
*  $FC Função: MES  &Criar Lista de Listas
*
*  $ED Descrição da função
*     Cria uma lista que terá elementos tipo ponteiro pra lista.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca da lista
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta lista. 
***************************************************************************/
LIS_tppLista MES_CriarListaDeListas() ;

/***************************************************************************
*  $FC Função: MES  &Criar Mesa
*
*  $ED Descrição da função
*     Cria uma lista mesa vazia.
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
*     Cria uma lista mão vazia.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca da mao
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta mao. 
***************************************************************************/
LIS_tppLista MES_CriarMao() ;

/***************************************************************************
*  $FC Função: MES  &Criar lixo
*
*  $ED Descrição da função
*     Cria a lista lixo vazia.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca do lixo
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta mao. 
***************************************************************************/
LIS_tppLista MES_CriarLixo() ;

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
MES_tpCondRet MES_DistribuirMaos(LIS_tppLista pCabecaSuperior, int numJogadores) ;
//void MES_DistribuirMaosParaTestarEmpates(LIS_tppLista pCabecaSuperior, int numJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Esvaziar mesa
*
*  $ED Descrição da função
*     Tira as cartas da lista mesa e põe na lista lixo.
*
*  $EP Parâmetros
*     Ponteiros para cabeca da mesa, cabeca do lixo e tipo, que pode ser:
*	  TIRA_VIRA ou DEIXA_VIRA caso seja apenas o fim de uma aposta ou fim
*	  de uma rodada.
***************************************************************************/
MES_tpCondRet MES_EsvaziarMesa (LIS_tppLista pCabecaMesa, LIS_tppLista pCabecaLixo, int tipo) ;

/***************************************************************************
*  $FC Função: MES  &Esvaziar lixo
*
*  $ED Descrição da função
*     Tira as cartas da lista mesa e põe na lista lixo.
*
*  $EP Parâmetros
*     Ponteiro para cabeca do lixo.
***************************************************************************/
MES_tpCondRet MES_EsvaziarLixo (LIS_tppLista pCabecaLixo) ;

/***************************************************************************
*  $FC Função: MES  &Obter quantidade de cartas
*
*  $ED Descrição da função
*     Obtem a quantidade de cartas na mesa.
*
*  $EP Parâmetros
*     Ponteiros para cabeca da mesa, e tipos, que podem ser:
*	  COM_PRIMEIRA ou SEM_PRIMEIRA e COM_ULTIMA e SEM_ULTIMA.
***************************************************************************/
int MES_ObterQtdCartas (LIS_tppLista pCabecaMesa, int tipoVira, int tipoUltimaApostada) ;

/***************************************************************************
*  $FC Função: MES  &Transferir todas cartas pro lixo
*
*  $EP Parâmetros
*     Recebe uma lista de listas de cartas e transfere todos elementos
*	  de todas listas pra penultima lista (lixo).
***************************************************************************/
void MES_TransferirTodasCartasProLixo(LIS_tppLista pCabecaSuperior) ;

int MES_DeterminarResultado(LIS_tppLista pCabecaSuperior, int quemJoga, int quemJogouAPrimeira, int qtdJogadores) ;

int MES_DefinirQuemComeca(int qtdJogadores) ;

void MES_IdentificarQuemJogouQual(int qtdJogadores, int quemJogouAPrimeira, int *quemJogouASegunda, int *quemJogouATerceira, 
							  	  int *quemJogouAQuarta, int *quemJogouAQuinta, int *quemJogouASexta) ;

int MES_ProximoJogador(int quemJoga, int qtdJogadores) ;

int MES_ProximoJogadorDaMesmaEquipe(int quemJoga, int qtdJogadores) ;

#undef MESA_EXT

/**************** FIM DO MÓDULO DE DEFINIÇÃO: MES Mesa ********************/

#else
#endif
