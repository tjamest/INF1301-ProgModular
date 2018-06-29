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
#include   <time.h>

#define MESA_OWN

#include "MESA.h"
#include "BARALHO.h"
#include "LISTA.h"

#ifdef _DEBUG
   	#include "Generico.h"
	#include "CEspDin.h"
   	#include "Conta.h"
   	#include "..\\tabelas\\IdTiposEspaco.def"
#endif

//jogadores
#define NINGUEM 0
#define JOGADOR1 1
#define JOGADOR2 2
#define JOGADOR3 3
#define JOGADOR4 4
#define JOGADOR5 5
#define JOGADOR6 6

//parametros pra funcao MES_EsvaziarMesa
#define DEIXA_VIRA 0
#define TIRA_VIRA 1

//paramestros pra funcao MES_ObterQtdCartas
#define SEM_PRIMEIRA 0
#define COM_PRIMEIRA 1
#define SEM_ULTIMA 0
#define COM_ULTIMA 1

//parâmetros pra função MES_DeterminarResultado
#define DESCONSIDERAR 0
#define CONSIDERAR 1

#undef MESA_OWN


/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//ainda nao ha funcoes encapsuladas no modulo


/***********  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ******************/

/***************************************************************************
*  Função: MES  &Criar lista de listas
***************************************************************************/
LIS_tppLista MES_CriarListaDeListas() {
	
	LIS_tppLista pCabecaSuperior ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarListaDeListas - Depois de entrar e declarar variaveis") ;
	#endif

	//criando ponteiro pra cabeca da lista mesa
	pCabecaSuperior = LIS_CriarLista (BAR_DestruirBaralho) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaSuperior != NULL ) ;
		CNT_CONTAR("MES_CriarListaDeListas - Depois de atribuir valor NaoNULL e antes de sair") ;
	#endif

	return pCabecaSuperior ;

} /***************** Fim função: MES &Criar lista de listas *****************/

/***************************************************************************
*  Função: MES  &Criar mesa
***************************************************************************/
LIS_tppLista MES_CriarMesa() {

	LIS_tppLista pCabecaMesa ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarMesa - Depois de entrar e declarar variaveis") ;
	#endif
	
	//criando ponteiro pra cabeca da lista mesa
	pCabecaMesa = LIS_CriarLista (BAR_DestruirCarta) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaMesa != NULL ) ;
		CNT_CONTAR("MES_CriarMesa - Depois de atribuir valor NaoNULL e antes de sair") ;
	#endif

	return pCabecaMesa ;

} /***************** Fim função: MES &Criar mesa ***********************/

/***************************************************************************
*  Função: MES  &Criar mao
***************************************************************************/
LIS_tppLista MES_CriarMao() {

	LIS_tppLista pCabecaMao ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarMao - Depois de entrar e declarar variaveis") ;
	#endif
	
	//criando ponteiro pra cabeca da lista mao
	pCabecaMao = LIS_CriarLista (BAR_DestruirCarta) ;
	
	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaMao != NULL ) ;
		CNT_CONTAR("MES_CriarMao - Depois de atribuir valor NaoNULL e antes de sair") ;
	#endif

	return pCabecaMao ;

} /***************** Fim função: MES &Criar mao ***********************/

/***************************************************************************
*  Função: MES  &Criar lixo
***************************************************************************/
LIS_tppLista MES_CriarLixo() {

	LIS_tppLista pCabecaLixo ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarLixo - Depois de entrar e declarar variaveis") ;
	#endif
	
	//criando ponteiro pra cabeca da lista mao
	pCabecaLixo = LIS_CriarLista (BAR_DestruirCarta) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaLixo != NULL ) ;
		CNT_CONTAR("MES_CriarLixo - Depois de atribuir valor NaoNULL e antes de sair") ;
	#endif

	return pCabecaLixo ;

} /***************** Fim função: MES &Criar lixo ***********************/

/***************************************************************************
*  Função: MES  &Distribuir maos
***************************************************************************/
MES_tpCondRet MES_DistribuirMaos(LIS_tppLista pCabecaSuperior, int qtdJogadores) {

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_DistribuirMaos - Depois de entrar e declarar variaveis") ;
	#endif
	
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

		if (LIS_ObterQtdElem(pCabecaMao1) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
			
		if (LIS_ObterQtdElem(pCabecaMao2) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}		

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

		if (LIS_ObterQtdElem(pCabecaMao1) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;

		if (LIS_ObterQtdElem(pCabecaMao2) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;


		if (LIS_ObterQtdElem(pCabecaMao3) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;	

		if (LIS_ObterQtdElem(pCabecaMao4) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}		
			
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

		if (LIS_ObterQtdElem(pCabecaMao1) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;

		if (LIS_ObterQtdElem(pCabecaMao2) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;

		if (LIS_ObterQtdElem(pCabecaMao3) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}	

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;	

		if (LIS_ObterQtdElem(pCabecaMao4) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}	

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;

		if (LIS_ObterQtdElem(pCabecaMao5) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}	

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;

		if (LIS_ObterQtdElem(pCabecaMao6) != 3) {
			return MES_CondRetNaoDistribuiuMaos ;
		}	
			
		break;

	}//fim switch
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DistribuirMaos - Depois de sair do switch e antes de retornar") ;
		CED_DefinirTipoEspaco( pCabecaBaralho, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao1, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao2, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao3, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao4, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao5, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao6, LIS_TipoEspacoLista ) ;
	#endif

	return MES_CondRetOK ;

} /***************** Fim função: MES &Distribuir maos ***********************/

/***************************************************************************
*  Função: MES  &Distribuir maos para testar empates (DEBUG)
***************************************************************************/
#ifdef _DEBUG
void MES_DistribuirMaosParaTestarEmpates(LIS_tppLista pCabecaSuperior, int numJogadores) {

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.Antes de entrar no switch") ;
	
	switch (numJogadores) {

	case 2:
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de entrar no case 2 e antes de chamar 'LIS_IrInicioLista'") ;	
			
		LIS_IrInicioLista(pCabecaSuperior) ;

		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;

		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.' e antes de preencher a mão 1") ;

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de preencher a mão 1 e antes de preencher a mão 2") ;

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de preencher a mão 2 e antes de chamar 'LIS_IrInicioLista'") ;

		LIS_IrInicioLista(pCabecaBaralho) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depis de chamar 'LIS_IrInicioLista' e antes de sair do case 2") ;

		break;
	
	case 4:
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de entrar no case 4 e antes de chamar 'LIS_IrInicioLista'") ;

		LIS_IrInicioLista(pCabecaSuperior) ;

		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;

		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao4 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.' e antes de preencher a mão 1") ;

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de preencher a mão 1 e antes de preencher a mão 2") ;

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de preencher a mão 2 e antes de preencher a mão 3") ;
		
		//preenche a mao 3
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de preencher a mão 3 e antes de preencher a mão 4") ;

		//preenche a mao 4
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de preencher a mão 4 e antes de chamar 'LIS_IrInicioLista'") ;

		LIS_IrInicioLista(pCabecaBaralho) ;

		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de chamar 'LIS_IrInicioLista' e antes de sair do case 4") ;

		break;
	
	case 6:
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de entrar no case 6 e antes de chamar 'LIS_IrInicioLista'") ;
		
		LIS_IrInicioLista(pCabecaSuperior) ;

		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;

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
			 
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.' e antes de preencher a mão 1") ;

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 1 e antes de preencher a mão 2") ;

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;

		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 2 e antes de preencher a mão 3") ;
		
		//preenche a mao 3
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;

	
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 3 e antes de preencher a mão 4") ;

		//preenche a mao 4
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 4 e antes de preencher a mão 5") ;

		//preenche a mao 5
		LIS_AvancarElementoCorrente(pCabecaBaralho, 2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 5 e antes de preencher a mão 6") ;

		//preenche a mao 6
		LIS_AvancarElementoCorrente(pCabecaBaralho, -13) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 6 e antes de chamar 'LIS_IrInicioLista'") ;

		LIS_IrInicioLista(pCabecaBaralho) ;
			
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de chamar 'LIS_IrInicioLista' e antes de sair do case 6") ;

		break;

	} //fim switch
	
	CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.Depois de sair do switch") ;

} /******** Fim função: MES &Distribuir maos para testar empates **********/
#endif

/***************************************************************************
*  Função: &Esvaziar mesa
***************************************************************************/
MES_tpCondRet MES_EsvaziarMesa (LIS_tppLista pCabecaMesa, LIS_tppLista pCabecaLixo, int tipo) {

	#ifdef _DEBUG
		CNT_CONTAR("MES_EsvaziarMesa - Depois de entrar") ;
	#endif
	
	switch (tipo) {

	case TIRA_VIRA:

		while (LIS_ObterQtdElem(pCabecaMesa) > 0) {

			LIS_IrFinalLista(pCabecaMesa) ;

			BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;

		} //fim while

		if (LIS_ObterQtdElem(pCabecaMesa) > 0) {

			return MES_CondRetNaoEsvaziouMesa ;
		}

		break;

	case DEIXA_VIRA:
			
		while (LIS_ObterQtdElem(pCabecaMesa) > 1) {

			LIS_IrFinalLista(pCabecaMesa) ;

			BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;

		} //fim while

		if (LIS_ObterQtdElem(pCabecaMesa) > 1) {

			return MES_CondRetNaoEsvaziouMesa ;
		}

		break;
		
	} //fim switch

	#ifdef _DEBUG
		CNT_CONTAR("MES_EsvaziarMesa - Depois de sair do switch e antes de retornar") ;
	#endif

	return MES_CondRetOK ;

} /******* fim função EsvaziaMesa*********/

/***************************************************************************
*  Função: &Obter quantidade de cartas
***************************************************************************/
int MES_ObterQtdCartas (LIS_tppLista pCabecaMesa, int tipoVira, int tipoUltimaApostada) {

	#ifdef _DEBUG
		CNT_CONTAR("MES_ObterQtdCartas - Depois de entrar") ;
	#endif
	
	switch (tipoVira) {

	case COM_PRIMEIRA:

		switch (tipoUltimaApostada) {
		case COM_ULTIMA:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ObterQtdCartas - ComPrimeira e ComUltima - Antes de retornar") ;
			#endif
			return LIS_ObterQtdElem(pCabecaMesa) ;
		case SEM_ULTIMA:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ObterQtdCartas - ComPrimeira e SemUltima - Antes de retornar") ;
			#endif
			return LIS_ObterQtdElem(pCabecaMesa)-1 ;
		} //fim switch

	case SEM_PRIMEIRA:

		switch (tipoUltimaApostada) {
		case COM_ULTIMA:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ObterQtdCartas - SemPrimeira e ComUltima - Antes de retornar") ;
			#endif
			return LIS_ObterQtdElem(pCabecaMesa)-1 ;
		case SEM_ULTIMA:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ObterQtdCartas - SemPrimeira e SemUltima - Antes de retornar") ;
			#endif
			return LIS_ObterQtdElem(pCabecaMesa)-2 ;
		} //fim switch

	} //fim switch

	return 0;

} /*************** FIM FUNÇÃO: Obter quantidade de cartas *****************/

/***************************************************************************
*  Função: &Transferir todas cartas pro lixo
***************************************************************************/
MES_tpCondRet MES_TransferirTodasCartasProLixo (LIS_tppLista pCabecaSuperior) {

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo - Depois de entrar e declarar variaveis") ;
	#endif
	
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
		if (BAR_TransferirCarta(pCabecaBaralho, pCabecaLixo) != BAR_CondRetOK) {
			return MES_CondRetNaoTransferiuTodasCartasProLixo ;
		}
	}

	while (LIS_ObterQtdElem(pCabecaMao1) > 0) {
		LIS_IrFinalLista(pCabecaMao1) ;
		if (BAR_TransferirCarta(pCabecaMao1, pCabecaLixo) != BAR_CondRetOK) {
			return MES_CondRetNaoTransferiuTodasCartasProLixo ;
		}
	}

	while (LIS_ObterQtdElem(pCabecaMao2) > 0) {
		LIS_IrFinalLista(pCabecaMao2) ;
		if (BAR_TransferirCarta(pCabecaMao2, pCabecaLixo) != BAR_CondRetOK) {
			return MES_CondRetNaoTransferiuTodasCartasProLixo ;
		}
	}

	while (LIS_ObterQtdElem(pCabecaMao3) > 0) {
		LIS_IrFinalLista(pCabecaMao3) ;
		if (BAR_TransferirCarta(pCabecaMao3, pCabecaLixo) != BAR_CondRetOK) {
			return MES_CondRetNaoTransferiuTodasCartasProLixo ;
		}
	}

	while (LIS_ObterQtdElem(pCabecaMao4) > 0) {
		LIS_IrFinalLista(pCabecaMao4) ;
		if (BAR_TransferirCarta(pCabecaMao4, pCabecaLixo) != BAR_CondRetOK) {
			return MES_CondRetNaoTransferiuTodasCartasProLixo ;
		}
	}
	
	while (LIS_ObterQtdElem(pCabecaMao5) > 0) {
		LIS_IrFinalLista(pCabecaMao5) ;
		if (BAR_TransferirCarta(pCabecaMao5, pCabecaLixo) != BAR_CondRetOK) {
			return MES_CondRetNaoTransferiuTodasCartasProLixo ;
		}
	}

	while (LIS_ObterQtdElem(pCabecaMao6) > 0) {
		LIS_IrFinalLista(pCabecaMao6) ;
		if (BAR_TransferirCarta(pCabecaMao6, pCabecaLixo) != BAR_CondRetOK) {
			return MES_CondRetNaoTransferiuTodasCartasProLixo ;
		}
	}
	
	while (LIS_ObterQtdElem(pCabecaMesa) > 0) {
		LIS_IrFinalLista(pCabecaMesa) ;
		if (BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) != BAR_CondRetOK) {
			return MES_CondRetNaoTransferiuTodasCartasProLixo ;
		}
	}

	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo - Antes de retornar") ;
		CED_DefinirTipoEspaco( pCabecaBaralho, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao1, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao2, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao3, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao4, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao5, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao6, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaLixo, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMesa, LIS_TipoEspacoLista ) ;
	#endif

	return MES_CondRetOK ;

} /*************** FIM FUNÇÃO: Transferir todas cartas pro lixo ***********/

/***************************************************************************
*  Função: &Determinar resultado
***************************************************************************/
int MES_DeterminarResultado (LIS_tppLista pCabecaSuperior, int quemJoga, int quemJogouAPrimeira, int qtdJogadores) {

	BAR_tppCarta pCartaVira = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCartaAposta = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCartaQueEmpatou = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCartaMesa = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	int * quemJogouASegunda = (int*)malloc(sizeof(int)) ;
	int * quemJogouATerceira = (int*)malloc(sizeof(int)) ;
	int * quemJogouAQuarta = (int*)malloc(sizeof(int)) ;
	int * quemJogouAQuinta = (int*)malloc(sizeof(int)) ;
	int * quemJogouASexta = (int*)malloc(sizeof(int)) ;

	int i, j, qtdCartasVencidas, primeiroComQuemEmpatou, resultadoEmpate;

	BAR_tpValorCarta valorAposta, valorCartaMesa, valorCartaQueEmpatou ;
	BAR_tpNaipeCarta naipeAposta, naipeCartaMesa ;
	
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrInicioLista(pCabecaMesa) ;
	pCartaVira = BAR_ObterCartaCorr(pCabecaMesa) ;

	LIS_IrFinalLista(pCabecaMesa) ;
	pCartaAposta = BAR_ObterCartaCorr(pCabecaMesa) ;

	qtdCartasVencidas = 0 ;

	primeiroComQuemEmpatou = NINGUEM ;
	
	MES_IdentificarQuemJogouQual(qtdJogadores, quemJogouAPrimeira, quemJogouASegunda, quemJogouATerceira,
							 quemJogouAQuarta, quemJogouASexta, quemJogouAQuinta) ;

	for (i = 1; i <= MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA); i++) {
		
		//CARTA APOSTADA == MANILHA
		if (BAR_VerificarSeEhManilha(pCartaAposta, pCartaVira) == BAR_CondRetEhManilha) {

			LIS_IrInicioLista(pCabecaMesa) ;

			//se i = 1 -> i = primeira carta colocada na mesa
			LIS_AvancarElementoCorrente(pCabecaMesa, i) ;
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;

			//CARTA DA MESA == MANILHA (tem que comparar naipes)
			if (BAR_VerificarSeEhManilha(pCartaMesa, pCartaVira) == BAR_CondRetEhManilha) {
				
				naipeAposta = BAR_ObterNaipe(pCartaAposta) ;
				naipeCartaMesa = BAR_ObterNaipe(pCartaMesa) ;

				//apostador venceu
				if ((int)naipeAposta > (int)naipeCartaMesa) {
					qtdCartasVencidas += 1 ;
				} //fim if

				//apostador perdeu
				else {
					return 0 ;
				} //fim else

			} //fim if

			//CARTA DA MESA != MANILHA (apostador venceu)
			else {
				qtdCartasVencidas += 1 ;
			} //fim else

		} //fim if "se a carta apostada for manilha"

		//CARTA APOSTADA != MANILHA
		else {

			LIS_IrInicioLista(pCabecaMesa) ;
			LIS_AvancarElementoCorrente(pCabecaMesa, i) ;
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;

			//CARTA DA MESA != MANILHA (tem que comparar valores)
			if (BAR_VerificarSeEhManilha(pCartaMesa, pCartaVira) == BAR_CondRetNaoEhManilha) {
				
				valorAposta = BAR_ObterValor(pCartaAposta) ;
				valorCartaMesa = BAR_ObterValor(pCartaMesa) ;

				//apostador venceu
				if ((int)valorAposta > (int)valorCartaMesa) {
					qtdCartasVencidas += 1 ;
				} //fim if

				//empataram
				else if ((int)valorAposta == (int)valorCartaMesa) {

					//verificar se tem alguma carta na mesa maior do que a que empatou
					pCartaQueEmpatou = pCartaMesa ;
					valorCartaQueEmpatou = valorCartaMesa ; 
					resultadoEmpate = CONSIDERAR ;

					for (j = 1 ; j <= MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA); j++) {
						LIS_IrInicioLista(pCabecaMesa) ;
						LIS_AvancarElementoCorrente(pCabecaMesa, j) ;
						pCartaMesa = (BAR_tppCarta)LIS_ObterValor(pCabecaMesa) ;
						valorCartaMesa = BAR_ObterValor(pCartaMesa) ;

						if (valorCartaQueEmpatou < valorCartaMesa) {
							resultadoEmpate = DESCONSIDERAR ;
						}
					} //fim for

					if (resultadoEmpate == CONSIDERAR) {

						if (primeiroComQuemEmpatou == NINGUEM) {

							switch (i) {
							case 1:
								primeiroComQuemEmpatou = quemJogouAPrimeira ;
								break ;
							case 2:
								primeiroComQuemEmpatou = *quemJogouASegunda ;
								break ;
							case 3:
								primeiroComQuemEmpatou = *quemJogouATerceira ;
								break ;
							case 4:
								primeiroComQuemEmpatou = *quemJogouAQuarta ;
								break ;
							case 5:
								primeiroComQuemEmpatou = *quemJogouAQuinta ;
								break ;
							case 6:
								primeiroComQuemEmpatou = *quemJogouASexta ;
								break ;
							} //fim switch

						} //fim if

					}//fim if considerar

					//desconsiderar empate (perdeu)
					else {
						return 0 ;
					}

				} //fim else if empataram
				
				//apostador perdeu
				else {
					return 0 ;
				} //fim else

			} //fim if

			//CARTA DA MESA == MANILHA (apostador perdeu)
			else {
				return 0 ;
			} //fim else

		} //fim else "se a carta apostada nao for manilha"

	} //fim for

	#ifdef _DEBUG
		CED_DefinirTipoEspaco( pCartaVira, LIS_TipoEspacoElemLista ) ;
		CED_DefinirTipoEspaco( pCartaAposta, LIS_TipoEspacoElemLista ) ;
		CED_DefinirTipoEspaco( pCartaQueEmpatou, LIS_TipoEspacoElemLista ) ;
		CED_DefinirTipoEspaco( pCartaMesa, LIS_TipoEspacoElemLista ) ;
		CED_DefinirTipoEspaco( pCabecaMao, LIS_TipoEspacoLista ) ;
		CED_DefinirTipoEspaco( pCabecaMesa, LIS_TipoEspacoLista ) ;
	#endif

	//se venceu todas cartas colocadas na mesa
	if (qtdCartasVencidas == MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA)) {
		return quemJoga ;
	}

	//se nao venceu e ainda nao retornou 0, só pode ter empatado
	else {
		return primeiroComQuemEmpatou ;
	}

} /****************** FIM FUNÇÃO: &Determinar resultado *******************/

/***************************************************************************
*  Função: &Definir quem comeca
***************************************************************************/
int MES_DefinirQuemComeca(int qtdJogadores) {

	int quemComeca = NINGUEM ;

	//função suporte da rand que faz gerar números diferentes sempre
	srand ((unsigned)time(NULL));

	while (quemComeca == NINGUEM) {
		switch (qtdJogadores) {
		case 2: 
			quemComeca = 1 + (rand() % 2) ;
			break ;
		case 4: 
			quemComeca = 1 + (rand() % 4) ;
			break ;
		case 6: 
			quemComeca = 1 + (rand() % 6) ;
			break ;
		} //fim switch
	}//fim while

	return quemComeca;
} /****************** FIM FUNÇÃO: &Definir quem comeca ********************/

/***************************************************************************
*  Função: &Identificar quem jogou qual
***************************************************************************/
MES_tpCondRet MES_IdentificarQuemJogouQual(int qtdJogadores, 
										   int quemJogouAPrimeira, int *quemJogouASegunda,
										   int *quemJogouATerceira, int *quemJogouAQuarta,
										   int *quemJogouAQuinta, int *quemJogouASexta) {

	#ifdef _DEBUG
		CNT_CONTAR("MES_IdentificarQuemJogouQual - Depois de entrar") ;
	#endif

	if (quemJogouAPrimeira < 1 || quemJogouAPrimeira > 6) {
		return MES_CondRetNaoIdentificouQuemJogouQual ;
	}

	//identificando quem jogou qual
	switch (quemJogouAPrimeira) {

	case JOGADOR1:

		switch (qtdJogadores) {
		case 2:
			*quemJogouASegunda = JOGADOR2;
			break;
		case 4:
			*quemJogouASegunda = JOGADOR2 ;
			*quemJogouATerceira = JOGADOR3 ;
			*quemJogouAQuarta = JOGADOR4 ;
			break;
		case 6:
			*quemJogouASegunda = JOGADOR2 ;
			*quemJogouATerceira = JOGADOR3 ;
			*quemJogouAQuarta = JOGADOR4 ;
			*quemJogouAQuinta = JOGADOR5 ;
			*quemJogouASexta = JOGADOR6 ;
			break;
		} //fim switch qtd jogadores

		break;

	case JOGADOR2:
		
		switch (qtdJogadores) {
		case 2:
			*quemJogouASegunda = JOGADOR1;
			break;
		case 4:
			*quemJogouASegunda = JOGADOR3 ;
			*quemJogouATerceira = JOGADOR4 ;
			*quemJogouAQuarta = JOGADOR1 ;
			break;
		case 6:
			*quemJogouASegunda = JOGADOR3 ;
			*quemJogouATerceira = JOGADOR4 ;
			*quemJogouAQuarta = JOGADOR5 ;
			*quemJogouAQuinta = JOGADOR6 ;
			*quemJogouASexta = JOGADOR1 ;
			break;
		} //fim switch qtd jogadores

		break ;

	case JOGADOR3:
		
		switch (qtdJogadores) {
		case 4:
			*quemJogouASegunda = JOGADOR4 ;
			*quemJogouATerceira = JOGADOR1 ;
			*quemJogouAQuarta = JOGADOR2 ;
			break;
		case 6:
			*quemJogouASegunda = JOGADOR4 ;
			*quemJogouATerceira = JOGADOR5 ;
			*quemJogouAQuarta = JOGADOR6 ;
			*quemJogouAQuinta = JOGADOR1 ;
			*quemJogouASexta = JOGADOR2 ;
			break;
		} //fim switch qtd jogadores

		break ;

	case JOGADOR4:
		
		switch (qtdJogadores) {
		case 4:
			*quemJogouASegunda = JOGADOR1 ;
			*quemJogouATerceira = JOGADOR2 ;
			*quemJogouAQuarta = JOGADOR3 ;
			break;
		case 6:
			*quemJogouASegunda = JOGADOR5 ;
			*quemJogouATerceira = JOGADOR6 ;
			*quemJogouAQuarta = JOGADOR1 ;
			*quemJogouAQuinta = JOGADOR2 ;
			*quemJogouASexta = JOGADOR3 ;
			break;
		} //fim switch qtd jogadores

		break ;

	case JOGADOR5:
		
		*quemJogouASegunda = JOGADOR6 ;
		*quemJogouATerceira = JOGADOR1 ;
		*quemJogouAQuarta = JOGADOR2 ;
		*quemJogouAQuinta = JOGADOR3 ;
		*quemJogouASexta = JOGADOR4 ;
		break ;

	case JOGADOR6:

		*quemJogouASegunda = JOGADOR1 ;
		*quemJogouATerceira = JOGADOR2 ;
		*quemJogouAQuarta = JOGADOR3 ;
		*quemJogouAQuinta = JOGADOR4 ;
		*quemJogouASexta = JOGADOR5 ;
		break ;

	} //fim switch quem jogou a primeira

	#ifdef _DEBUG
		CNT_CONTAR("MES_IdentificarQuemJogouQual - Depois de sair do switch e antes de retornar") ;
	#endif

	return MES_CondRetOK ;

} /*********** FIM FUNÇÃO: &Identificar quem jogou qual *******************/

/***************************************************************************
*  Função: &Proximo jogador
***************************************************************************/
int MES_ProximoJogador(int quemJoga, int qtdJogadores) {

	switch (qtdJogadores) {
	case 2: 
		switch (quemJoga) {
		case 1:
			return 2;
		case 2:
			return 1;
		}
	case 4:
		switch (quemJoga) {
		case 1:
			return 2;
		case 2:
			return 3;
		case 3:
			return 4;
		case 4:
			return 1;
		}
	case 6:
		switch (quemJoga) {
		case 1:
			return 2;
		case 2:
			return 3;
		case 3:
			return 4;
		case 4:
			return 5;
		case 5:
			return 6;
		case 6:
			return 1;
		}
	}
	return 0 ;
} /******************** FIM FUNÇÃO: &Proximo jogador **********************/

/***************************************************************************
*  Função: &Proximo jogador da mesma equipe
***************************************************************************/
int MES_ProximoJogadorDaMesmaEquipe(int quemJoga, int qtdJogadores) {

	switch (qtdJogadores) {
	case 2: 
		switch (quemJoga) {
		case 1:
			return 1;
		case 2:
			return 2;
		}
	case 4:

		switch (quemJoga) {
		case 1:
			return 3;
		case 2:
			return 4;
		case 3:
			return 1;
		case 4:
			return 2;
		}

	case 6:
		switch (quemJoga) {
		case 1:
			return 3;
		case 2:
			return 4;
		case 3:
			return 5;
		case 4:
			return 6;
		case 5:
			return 1;
		case 6:
			return 2;
		}
	}

	return 0 ;

} /********* FIM FUNÇÃO: &Proximo jogador da mesma equipe *****************/

/***************************************************************************
*  Função: &Esvaziar lixo
***************************************************************************/
MES_tpCondRet MES_EsvaziarLixo (LIS_tppLista pCabecaLixo) {

	#ifdef _DEBUG
		CNT_CONTAR("MES_EsvaziarLixo - Depois de entrar") ;
	#endif
	
	if (LIS_ObterQtdElem(pCabecaLixo) > 0) {
		LIS_EsvaziarLista (pCabecaLixo) ;

		if (LIS_ObterQtdElem(pCabecaLixo) != 0) {
			return MES_CondRetNaoEsvaziouLixo ;
		}
	}

	#ifdef _DEBUG
		CNT_CONTAR("MES_EsvaziarLixo - Antes de retornar") ;
	#endif

	return MES_CondRetOK ;

} /********************** FIM FUNÇÃO: &Esvaziar lixo ***********************/

/***************************************************************************
*  Função: &Destruir listas
***************************************************************************/
void MES_DestruirListas ( LIS_tppLista pCabecaSuperior, LIS_tppLista pCabecaBaralho,
						  LIS_tppLista pCabecaMao1, LIS_tppLista pCabecaMao2,
						  LIS_tppLista pCabecaMao3, LIS_tppLista pCabecaMao4,
						  LIS_tppLista pCabecaMao5, LIS_tppLista pCabecaMao6,
						  LIS_tppLista pCabecaLixo, LIS_tppLista pCabecaMesa) {
/*	#ifdef _DEBUG
		CNT_CONTAR("MES_DestruirListas - Depois de entrar") ;
	#endif
*/
	LIS_DestruirLista(pCabecaBaralho) ;
	LIS_DestruirLista(pCabecaMao1) ;
	LIS_DestruirLista(pCabecaMao2) ;
	LIS_DestruirLista(pCabecaMao3) ;
	LIS_DestruirLista(pCabecaMao4) ;
	LIS_DestruirLista(pCabecaMao5) ;
	LIS_DestruirLista(pCabecaMao6) ;
	LIS_DestruirLista(pCabecaLixo) ;
	LIS_DestruirLista(pCabecaMesa) ;
	free(pCabecaSuperior) ;
/*
	#ifdef _DEBUG
		CNT_CONTAR("MES_DestruirListas - Antes de retornar") ;
	#endif
*/
} /********************** FIM FUNÇÃO: &Destruir listas *********************/


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//ainda nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: MES Mesa *********************/
