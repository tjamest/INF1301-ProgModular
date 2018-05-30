/***************************************************************************
*  $MCI Módulo de implementação: MES  Mesa
*
*  Arquivo gerado:              MESA.c
*  Letras identificadoras:      MES
*
*  Projeto: INF 1301 Jogo de Truco
*  Autores: gsc, jvr, tgf
*
*  $HA Histórico de evolução:
*  Versão  		Autor  			Data    	Observações
*     1     gsc, jvr, tgf    11/mai/2018    início desenvolvimento
***************************************************************************/

#include   <stdio.h>	//printf
#include   <stdlib.h>	//malloc, free
#include   <assert.h>	//assert

#define MESA_OWN
#include "MESA.h"
#include "BARALHO.h"
#include "LISTA.h"

#undef MESA_OWN


/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//ainda nao ha funcoes encapsuladas no modulo


/***********  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ******************/

/***************************************************************************
*  Função: MES  &Criar mesa
***************************************************************************/
LIS_tppLista MES_CriarMesa() {

	//criando ponteiro pra cabeca da lista mesa
	LIS_tppLista pCabecaMesa = LIS_CriarLista (BAR_DestruirCarta) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaMesa != NULL ) ;
	#endif

	return pCabecaMesa ;

} /***************** Fim função: MES &Criar lista***********************/

/***************************************************************************
*  Função: MES  &Criar mao
***************************************************************************/
LIS_tppLista MES_CriarMao() {

	//criando ponteiro pra cabeca da lista mao
	LIS_tppLista pCabecaMao = LIS_CriarLista (BAR_DestruirCarta) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaMao != NULL ) ;
	#endif

	return pCabecaMao ;

} /***************** Fim função: MES &Criar mao ***********************/

/***************************************************************************
*  Função: MES  &Criar lixo
***************************************************************************/
LIS_tppLista MES_CriarLixo() {

	//criando ponteiro pra cabeca da lista mao
	LIS_tppLista pCabecaLixo = LIS_CriarLista (BAR_DestruirCarta) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaLixo != NULL ) ;
	#endif

	return pCabecaLixo ;

} /***************** Fim função: MES &Criar mao ***********************/

/***************************************************************************
*  Função: MES  &Distribuir maos
***************************************************************************/
void MES_DistribuirMaos(LIS_tppLista pCabecaSuperior, int * numJogadores) {

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	switch (* numJogadores) {

	case 2:
		LIS_IrInicioLista(pCabecaSuperior) ;
		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		break;
	
	case 4:
		LIS_IrInicioLista(pCabecaSuperior) ;
		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao4 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;	
		break;
	
	case 6:
		LIS_IrInicioLista(pCabecaSuperior) ;
		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao4 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao5 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao6 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;	
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		break;
	} // fim switch

} /***************** Fim função: MES &Distribuir maos ***********************/


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//ainda nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: MES Mesa ******************/
