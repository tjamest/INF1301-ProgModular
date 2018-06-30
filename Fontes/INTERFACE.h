#pragma once
#if ! defined( INTERFACE_ )
#define INTERFACE_
/***************************************************************************
*  $MCD Módulo de definição: INT  Interface do Usuario
*
*  Arquivo gerado:              INTERFACE.h
*  Letras identificadoras:      INT
*
*  Projeto: INF 1301 Jogo de Truco
*  Gestor:
*  Autores: gsc,jvr, tgf
*
*  $HA Histórico de evolução:
*     Versão      Autor        Data            Observações
*     1     	   gsc      01/jun/2018     início desenvolvimento
*
*  $ED Descrição do módulo
*	  Imprime telas no prompt de comando para o usuário escolher opções.
*	  Executa as opções escolhidas.  
***************************************************************************/

#include "MESA.h"
#include "BARALHO.h"
#include "LISTA.h" 

#if defined( INTERFACE_OWN )
   #define INTERFACE_EXT
#else
   #define INTERFACE_EXT extern
#endif

/***************************************************************************
*  $FC Função: MES  &Printar mesa
*
*  $ED Descrição da função
*     Imprime na tela as cartas que estao na lista mesa.
***************************************************************************/
void PrintarMesa (LIS_tppLista pCabecaMesa, int quemJogouAPrimeira, int qtdJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Printar mao
*
*  $ED Descrição da função
*     Imprime na tela as cartas que estao na lista mao.
***************************************************************************/
void PrintarMao (LIS_tppLista pCabecaMao) ;

//void PrintarBaralho (LIS_tppLista pCabecaBaralho) ;
//void PrintarLixo (LIS_tppLista pCabecaLixo) ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de inicio
*
*  $ED Descrição da função
*     Imprime a tela com as opcoes:
*	  "iniciar partida", "ver regras" e "sair".
*
*  $FV Valor retornado
*     Retorna a opcao escolhida. 
***************************************************************************/
int PrintarTelaInicio () ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de regras
*
*  $ED Descrição da função
*     Imprime a tela com as regras e as opcoes:
*	  "voltar" e "sair".
*
*  $FV Valor retornado
*     Retorna a opcao escolhida. 
***************************************************************************/
int PrintarTelaRegras () ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de quantidade de jogadores
*
*  $ED Descrição da função
*     Imprime a tela com as opcoes:
*	  "2 jogadores", "4 jogadores" e "6 jogadores".
*
*  $FV Valor retornado
*     Retorna a opcao escolhida. 
***************************************************************************/
int PrintarTelaQtdJogadores () ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de jogada
*
*  $ED Descrição da função
*     Imprime a tela com as opcoes:
*	  "apostar carta 1", "apostar carta 2", "apostar carta 3",
*	  "dispensar carta 1", "dispensar carta 2", "dispensar carta 3" e
*	  "aumentar valor da rodada".
*
*  $FV Valor retornado
*     Retorna a opcao escolhida. 
***************************************************************************/
int PrintarTelaJogada(int quemJoga, int valorRodada, int quemAumentou,
					  LIS_tppLista pCabecaSuperior,
					  int quemJogouAPrimeira, int qtdJogadores,
					  int pontosRodadaPar, int pontosRodadaImpar,
					  int pontosPartidaPar, int pontosPartidaImpar) ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de correr, aceitar ou aumentar
*
*  $ED Descrição da função
*     Imprime a tela com as opcoes:
*	  "correr", "aceitar" e "aumentar"
*
*  $FV Valor retornado
*     Retorna a opcao escolhida. 
***************************************************************************/
int PrintarTelaCorrerAceitarAumentar(int quemJoga, int valorRodada, int qtdJogadores,
									 LIS_tppLista pCabecaSuperior, 
									 int quemJogouAPrimeira,
									 int pontosRodadaPar, int pontosRodadaImpar, 
									 int pontosPartidaPar, int pontosPartidaImpar) ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de fim de bateria de apostas
*
*  $ED Descrição da função
*     Imprime a tela com os resultados da bateria de apostas.
***************************************************************************/
void PrintarTelaFimBateriaDeApostas(LIS_tppLista pCabecaSuperior, int equipeVencedoraDaAposta,
									int qtdRodadas, int quemJogouAPrimeira, int qtdJogadores, int quemCorreu,
									int pontosRodadaPar, int pontosRodadaImpar,
									int pontosPartidaPar, int pontosPartidaImpar) ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de fim de rodada
*
*  $ED Descrição da função
*     Imprime a tela com os resultados da rodada.
***************************************************************************/
void PrintarTelaFimRodada(LIS_tppLista pCabecaSuperior, int valorRodada, int equipeVencedoraDaRodada,
						  int qtdRodadas,
						  int pontosRodadaPar, int pontosRodadaImpar,
						  int pontosPartidaPar, int pontosPartidaImpar) ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de fim de partida
*
*  $ED Descrição da função
*     Imprime a tela com os resultados da partida.
***************************************************************************/
int PrintarTelaFimPartida(LIS_tppLista pCabecaSuperior,
						  int equipeVencedoraDaPartida, int qtdPartidas,
						  int pontosPartidaPar, int pontosPartidaImpar) ;

/***************************************************************************
*  $FC Função: MES  &Printar tela de mão de onze
*
*  $ED Descrição da função
*     Imprime a tela as mãos da equipe com onze pontos.
***************************************************************************/
int PrintarTelaMaoDeOnze(int qtdJogadores, LIS_tppLista pCabecaSuperior, 
						 int pontosPartidaPar, int pontosPartidaImpar) ;

/***************************************************************************
*  $FC Função: MES  &Executar opcao de inicio
*
*  $ED Descrição da função
*     Executa a opcao escolhida na tela de inicio.
*
*  $FV Valor retornado
*     Retorna a quantidade de jogadores. 
***************************************************************************/
int ExecutarOpcaoInicio(int opcao) ;

/***************************************************************************
*  $FC Função: MES  &Executar opcao de regras
*
*  $ED Descrição da função
*     Executa a opcao escolhida na tela de regras.
*
*  $FV Valor retornado
*     Retorna a quantidade de jogadores. 
***************************************************************************/
int ExecutarOpcaoRegras(int opcao) ;

/***************************************************************************
*  $FC Função: MES  &Executar opcao de jogada
*
*  $ED Descrição da função
*     Executa a opcao escolhida na tela de jogada.
*
*  $FV Valor retornado
*     Retorna o valor da rodada (que pode ou não ter sido alterado). 
***************************************************************************/
int ExecutarOpcaoJogada(LIS_tppLista pCabecaSuperior, int quemJoga, int jogada, int valorRodada) ;

/***************************************************************************
*  $FC Função: MES  &Executar opcao de apostar carta
*
*  $ED Descrição da função
*     Transfere a carta escolhida da mão do jogador para a mesa.
***************************************************************************/
void ExecutarOpcaoApostarCarta (LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) ;

/***************************************************************************
*  $FC Função: MES  &Executar opcao de dispensar carta
*
*  $ED Descrição da função
*     Transfere a carta escolhida da mão do jogador para o lixo.
***************************************************************************/
void ExecutarOpcaoDispensarCarta (LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) ;
/**************************************************************************/

#ifdef _DEBUG
void Delay () ;
#endif

#undef INTERFACE_EXT

/********* Fim do módulo de definição: INT  Interface do usuario **********/

#else
#endif
