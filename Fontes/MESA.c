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

#define DEIXA_VIRA 0
#define TIRA_VIRA 1

#define SEM_PRIMEIRA 0
#define COM_PRIMEIRA 1
#define SEM_ULTIMA 0
#define COM_ULTIMA 1

#undef MESA_OWN


/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//ainda nao ha funcoes encapsuladas no modulo


/***********  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ******************/

/***************************************************************************
*  Função: MES  &Criar lista de listas
***************************************************************************/
LIS_tppLista MES_CriarListaDeListas() {

	//criando ponteiro pra cabeca da lista mesa
	LIS_tppLista pCabecaSuperior = LIS_CriarLista (BAR_DestruirBaralho) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaSuperior != NULL ) ;
	#endif

	return pCabecaSuperior ;

} /***************** Fim função: MES &Criar lista de listas *****************/

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

} /***************** Fim função: MES &Criar mesa ***********************/

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

} /***************** Fim função: MES &Criar lixo ***********************/

/***************************************************************************
*  Função: MES  &Distribuir maos
***************************************************************************/
void MES_DistribuirMaos(LIS_tppLista pCabecaSuperior, int qtdJogadores) {

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	switch(qtdJogadores) {
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

	}//fim switch

} /***************** Fim função: MES &Distribuir maos ***********************/

/***************************************************************************
*  Função: MES  &Distribuir maos para testar empates
***************************************************************************/
void MES_DistribuirMaosParaTestarEmpates(LIS_tppLista pCabecaSuperior, int numJogadores) {

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	switch (numJogadores) {

	case 2:

		LIS_IrInicioLista(pCabecaSuperior) ;
		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;

		LIS_IrInicioLista(pCabecaBaralho) ;

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

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		
		//preenche a mao 3
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;

		//preenche a mao 4
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;

		LIS_IrInicioLista(pCabecaBaralho) ;

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

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		
		//preenche a mao 3
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;

		//preenche a mao 4
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;

		//preenche a mao 5
		LIS_AvancarElementoCorrente(pCabecaBaralho, 2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;

		//preenche a mao 6
		LIS_AvancarElementoCorrente(pCabecaBaralho, -13) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;

		LIS_IrInicioLista(pCabecaBaralho) ;

		break;

	} //fim switch

} /***************** Fim função: MES &Distribuir maos ***********************/

/***************************************************************************
*  Função: &Esvaziar mesa
***************************************************************************/
void MES_EsvaziarMesa (LIS_tppLista pCabecaMesa, LIS_tppLista pCabecaLixo, int tipo) {

	switch (tipo) {

	case TIRA_VIRA:

		while (LIS_ObterQtdElem(pCabecaMesa) > 0) {
			LIS_IrFinalLista(pCabecaMesa) ;
			BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
		} //fim while
		break;

	case DEIXA_VIRA:

		while (LIS_ObterQtdElem(pCabecaMesa) > 1) {
			LIS_IrFinalLista(pCabecaMesa) ;
			BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
		} //fim while
		break;

	} //fim switch

} /******* fim função EsvaziaMesa*********/

/***************************************************************************
*  Função: &Obter quantidade de cartas
***************************************************************************/
int MES_ObterQtdCartas (LIS_tppLista pCabecaMesa, int tipoVira, int tipoUltimaApostada) {

	switch (tipoVira) {

	case COM_PRIMEIRA:

		switch (tipoUltimaApostada) {
		case COM_ULTIMA:
			return LIS_ObterQtdElem(pCabecaMesa) ;
		case SEM_ULTIMA:
			return LIS_ObterQtdElem(pCabecaMesa)-1 ;
		} //fim switch

	case SEM_PRIMEIRA:

		switch (tipoUltimaApostada) {
		case COM_ULTIMA:
			return LIS_ObterQtdElem(pCabecaMesa)-1 ;
		case SEM_ULTIMA:
			return LIS_ObterQtdElem(pCabecaMesa)-2 ;
		} //fim switch

	} //fim switch

	return 0;

} /*************** FIM FUNÇÃO: Obter quantidade de cartas *****************/

/***************************************************************************
*  Função: &Transferir todas cartas pro lixo
***************************************************************************/
void MES_TransferirTodasCartasProLixo (LIS_tppLista pCabecaSuperior) {

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

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
	LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	while (LIS_ObterQtdElem(pCabecaBaralho) > 0) {
		LIS_IrFinalLista(pCabecaBaralho) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao1) > 0) {
		LIS_IrFinalLista(pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaMao1, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao2) > 0) {
		LIS_IrFinalLista(pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaMao2, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao3) > 0) {
		LIS_IrFinalLista(pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaMao3, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao4) > 0) {
		LIS_IrFinalLista(pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaMao4, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao5) > 0) {
		LIS_IrFinalLista(pCabecaMao5) ;
		BAR_TransferirCarta(pCabecaMao5, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao6) > 0) {
		LIS_IrFinalLista(pCabecaMao6) ;
		BAR_TransferirCarta(pCabecaMao6, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMesa) > 0) {
		LIS_IrFinalLista(pCabecaMesa) ;
		BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
	}

}

/***************************************************************************
*  Função: &Iniciar partida NAO TA FUNCIONANDO NAO SEI PQ
***************************************************************************/
int MES_IniciarPartida (LIS_tppLista pCabecaBaralho, LIS_tppLista pCabecaMao1, LIS_tppLista pCabecaMao2, 
						 LIS_tppLista pCabecaMao3, LIS_tppLista pCabecaMao4, LIS_tppLista pCabecaMao5,
						 LIS_tppLista pCabecaMao6, LIS_tppLista pCabecaLixo, LIS_tppLista pCabecaMesa,
						 LIS_tppLista pCabecaSuperior) {

	pCabecaSuperior = LIS_CriarLista (BAR_DestruirBaralho) ;

	pCabecaBaralho = LIS_CriarLista (BAR_DestruirCarta) ;

	pCabecaMao1 = LIS_CriarLista (BAR_DestruirCarta) ;

	pCabecaMao2 = LIS_CriarLista (BAR_DestruirCarta) ;

	pCabecaMao3 = LIS_CriarLista (BAR_DestruirCarta) ;

	pCabecaMao4 = LIS_CriarLista (BAR_DestruirCarta) ;

	pCabecaMao5 = LIS_CriarLista (BAR_DestruirCarta) ;

	pCabecaMao6 = LIS_CriarLista (BAR_DestruirCarta) ;

	pCabecaLixo = LIS_CriarLista (BAR_DestruirCarta) ;

	pCabecaMesa = LIS_CriarLista (BAR_DestruirCarta) ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaBaralho) ;	//inicio
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao1) ;		//1
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao2) ;		//2
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao3) ;		//3
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao4) ;		//4
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao5) ;		//5
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao6) ;		//6
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaLixo) ;		//7
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMesa) ;		//final

	return 49;

} // fim funcao


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//ainda nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: MES Mesa ******************/
