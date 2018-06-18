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
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarListaDeListas.Antes de chamar 'LIS_CriarLista'") ;
	#endif
	
	//criando ponteiro pra cabeca da lista mesa
	LIS_tppLista pCabecaSuperior = LIS_CriarLista (BAR_DestruirBaralho) ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarListaDeListas.Depois de chamar 'LIS_CriarLista'") ;
	#endif
	
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

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarMesa.Antes de chamar 'LIS_CriarLista'") ;
	#endif
	
	//criando ponteiro pra cabeca da lista mesa
	LIS_tppLista pCabecaMesa = LIS_CriarLista (BAR_DestruirCarta) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarMesa.Depois de chamar 'LIS_CriarLista'") ;
	#endif

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

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarMao.Antes de chamar 'LIS_CriarLista'") ;
	#endif
	
	//criando ponteiro pra cabeca da lista mao
	LIS_tppLista pCabecaMao = LIS_CriarLista (BAR_DestruirCarta) ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarMao.Depois de chamar 'LIS_CriarLista'") ;
	#endif
	
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

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarLixo.Antes de chamar 'LIS_CriarLista'") ;
	#endif
	
	//criando ponteiro pra cabeca da lista mao
	LIS_tppLista pCabecaLixo = LIS_CriarLista (BAR_DestruirCarta) ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_CriarLixo.Depois de chamar 'LIS_CriarLista'") ;
	#endif
	
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

	#ifdef _DEBUG
		CNT_CONTAR("MES_DistribuirMaos.Antes de entrar no switch") ;
	#endif
	
	switch(qtdJogadores) {
			
	#ifdef _DEBUG
		CNT_CONTAR("MES_DistribuirMaos.Depois de entrar no switch") ;
	#endif
			
	case 2:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.2.Depois de entrar no case 2 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif
			
		LIS_IrInicioLista(pCabecaSuperior) ;
		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.2.Depois de chamar 'LIS_ObterValor' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.2.Depois de chamar 'BAR_TransferirCarta' e antes de sair do case 2") ;
		#endif
			
		break;
	
	case 4:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.4.Depois de entrar no case 4 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif	
			
		LIS_IrInicioLista(pCabecaSuperior) ;	
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.4.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;
		#endif
		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao4 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.4.Depois de chamar 'LIS_ObterValor' e 'LIS_ObterValor' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
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
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.4.Depois de chamar 'BAR_TransferirCarta' e antes de sair do case 4") ;
		#endif
			
		break;
	
	case 6:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.6.Depois de entrar no case 6 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif
			
		LIS_IrInicioLista(pCabecaSuperior) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.6.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;
		#endif
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
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.6.Depois de chamar 'LIS_ObterValor' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
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
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaos.6.Depois de chamar 'BAR_TransferirCarta' e antes de sair do case 6") ;
		#endif
			
		break;

	}//fim switch
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DistribuirMaos.Depois de sair do switch") ;
	#endif

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

	#ifdef _DEBUG
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.Antes de entrar no switch") ;
	#endif
	
	switch (numJogadores) {

	case 2:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de entrar no case 2 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif	
			
		LIS_IrInicioLista(pCabecaSuperior) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;
		#endif
		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.' e antes de preencher a mão 1") ;
		#endif

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de preencher a mão 1 e antes de preencher a mão 2") ;
		#endif

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depois de preencher a mão 2 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif

		LIS_IrInicioLista(pCabecaBaralho) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.2.Depis de chamar 'LIS_IrInicioLista' e antes de sair do case 2") ;
		#endif

		break;
	
	case 4:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de entrar no case 4 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif

		LIS_IrInicioLista(pCabecaSuperior) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;
		#endif
		pCabecaBaralho = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao4 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.' e antes de preencher a mão 1") ;
		#endif

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de preencher a mão 1 e antes de preencher a mão 2") ;
		#endif

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de preencher a mão 2 e antes de preencher a mão 3") ;
		#endif
		
		//preenche a mao 3
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de preencher a mão 3 e antes de preencher a mão 4") ;
		#endif

		//preenche a mao 4
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de preencher a mão 4 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif

		LIS_IrInicioLista(pCabecaBaralho) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.4.Depois de chamar 'LIS_IrInicioLista' e antes de sair do case 4") ;
		#endif

		break;
	
	case 6:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de entrar no case 6 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif
		
		LIS_IrInicioLista(pCabecaSuperior) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;
		#endif
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
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.' e antes de preencher a mão 1") ;
		#endif

		//preenche a mao 1
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 1 e antes de preencher a mão 2") ;
		#endif

		//preenche a mao 2
		LIS_AvancarElementoCorrente(pCabecaBaralho, 7) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 2 e antes de preencher a mão 3") ;
		#endif
		
		//preenche a mao 3
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao3) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 3 e antes de preencher a mão 4") ;
		#endif

		//preenche a mao 4
		LIS_AvancarElementoCorrente(pCabecaBaralho, 8) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao4) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 4 e antes de preencher a mão 5") ;
		#endif

		//preenche a mao 5
		LIS_AvancarElementoCorrente(pCabecaBaralho, 2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao5) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 5 e antes de preencher a mão 6") ;
		#endif

		//preenche a mao 6
		LIS_AvancarElementoCorrente(pCabecaBaralho, -13) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
		LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao6) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de preencher a mão 6 e antes de chamar 'LIS_IrInicioLista'") ;
		#endif

		LIS_IrInicioLista(pCabecaBaralho) ;
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.6.Depois de chamar 'LIS_IrInicioLista' e antes de sair do case 6") ;
		#endif

		break;

	} //fim switch
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DistribuirMaosParaTestarEmpates.Depois de sair do switch") ;
	#endif

} /***************** Fim função: MES &Distribuir maos ***********************/

/***************************************************************************
*  Função: &Esvaziar mesa
***************************************************************************/
void MES_EsvaziarMesa (LIS_tppLista pCabecaMesa, LIS_tppLista pCabecaLixo, int tipo) {

	#ifdef _DEBUG
		CNT_CONTAR("MES_EsvaziarMesa.Antes de entrar no switch") ;
	#endif
	
	switch (tipo) {

	case TIRA_VIRA:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_EsvaziarMesa.TIRA_VIRA.Depois de entrar no case TIRA_VIRA e antes de entrar no while") ;
		#endif

		while (LIS_ObterQtdElem(pCabecaMesa) > 0) {
			#ifdef _DEBUG
				CNT_CONTAR("MES_EsvaziarMesa.TIRA_VIRA.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
			#endif
			LIS_IrFinalLista(pCabecaMesa) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_EsvaziarMesa.TIRA_VIRA.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
			#endif
			BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_EsvaziarMesa.TIRA_VIRA.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
			#endif
		} //fim while
		#ifdef _DEBUG
			CNT_CONTAR("MES_EsvaziarMesa.TIRA_VIRA.Depois de sair do while e antes de sair do case TIRA_VIRA") ;
		#endif
		break;

	case DEIXA_VIRA:
		
		#ifdef _DEBUG
			CNT_CONTAR("MES_EsvaziarMesa.DEIXA_VIRA.Depois de entrar no case DEIXA_VIRA e antes de entrar no while") ;
		#endif
			
		while (LIS_ObterQtdElem(pCabecaMesa) > 1) {
			#ifdef _DEBUG
				CNT_CONTAR("MES_EsvaziarMesa.DEIX_VIRA.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
			#endif
			LIS_IrFinalLista(pCabecaMesa) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_EsvaziarMesa.DEIXA_VIRA.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
			#endif
			BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_EsvaziarMesa.DEIXA_VIRA.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
			#endif
		} //fim while
		#ifdef _DEBUG
			CNT_CONTAR("MES_EsvaziarMesa.DEIXA_VIRA.Depois de sair do while e antes de sair do case DEIXA_VIRA") ;
		#endif
		break;
		
	} //fim switch

} /******* fim função EsvaziaMesa*********/

/***************************************************************************
*  Função: &Obter quantidade de cartas
***************************************************************************/
int MES_ObterQtdCartas (LIS_tppLista pCabecaMesa, int tipoVira, int tipoUltimaApostada) {

	#ifdef _DEBUG
		CNT_CONTAR("MES_ObterQtdCartas.Antes de entrar no switch") ;
	#endif
	
	switch (tipoVira) {

	case COM_PRIMEIRA:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_ObterQtdCartas.COM_PRIMEIRA.Depois de entrar no case COM_PRIMEIRA e antes de entrar no switch") ;
		#endif

		switch (tipoUltimaApostada) {
		case COM_ULTIMA:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ObterQtdCartas.COM_PRIMEIRA.Depois de entrar no case COM_ULTIMA") ;
			#endif
			return LIS_ObterQtdElem(pCabecaMesa) ;
		case SEM_ULTIMA:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ObterQtdCartas.COM_PRIMEIRA.Depois de entrar no case SEM_ULTIMA") ;
			#endif
			return LIS_ObterQtdElem(pCabecaMesa)-1 ;
		} //fim switch

	case SEM_PRIMEIRA:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_ObterQtdCartas.SEM_PRIMEIRA.Depois de entrar no case SEM_PRIMEIRA e antes de entrar no switch") ;
		#endif

		switch (tipoUltimaApostada) {
		case COM_ULTIMA:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ObterQtdCartas.SEM_PRIMEIRA.Depois de entrar no case COM_ULTIMA") ;
			#endif
			return LIS_ObterQtdElem(pCabecaMesa)-1 ;
		case SEM_ULTIMA:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ObterQtdCartas.SEM_PRIMEIRA.Depois de entrar no case SEM_ULTIMA") ;
			#endif
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

	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Antes de chamar 'LIS_IrInicioLista'") ;
	#endif
	
	LIS_IrInicioLista(pCabecaSuperior) ;
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_ObterValor' e 'LIS_AvancarElem.Cor.'") ;
	#endif
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
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de chamar 'LIS_ObterValor e 'LIS_AvancarElem.Cor.' e antes de entrar no while pCabecaBaralho") ;
	#endif

	while (LIS_ObterQtdElem(pCabecaBaralho) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaBaralho.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
		#endif
		LIS_IrFinalLista(pCabecaBaralho) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaBaralho.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaBaralho, pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaBaralho.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
		#endif
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de sair do while pCabecaBaralho e antes de entrar no while pCabecaMao1") ;
	#endif

	while (LIS_ObterQtdElem(pCabecaMao1) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao1.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
		#endif
		LIS_IrFinalLista(pCabecaMao1) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao1.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaMao1, pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao1.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
		#endif
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de sair do while pCabecaMao1 e antes de entrar no while pCabecaMao2") ;
	#endif

	while (LIS_ObterQtdElem(pCabecaMao2) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao2.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
		#endif
		LIS_IrFinalLista(pCabecaMao2) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao2.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaMao2, pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao2.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
		#endif
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de sair do while pCabecaMao2 e antes de entrar no while pCabecaMao3") ;
	#endif

	while (LIS_ObterQtdElem(pCabecaMao3) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao3.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
		#endif
		LIS_IrFinalLista(pCabecaMao3) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao3.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaMao3, pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao3.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
		#endif
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de sair do while pCabecaMao3 e antes de entrar no while pCabecaMao4") ;
	#endif

	while (LIS_ObterQtdElem(pCabecaMao4) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao4.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
		#endif
		LIS_IrFinalLista(pCabecaMao4) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao4.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaMao4, pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao4.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
		#endif
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de sair do while pCabecaMao4 e antes de entrar no while pCabecaMao5") ;
	#endif

	while (LIS_ObterQtdElem(pCabecaMao5) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao5.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
		#endif
		LIS_IrFinalLista(pCabecaMao5) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao5.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaMao5, pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao5.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
		#endif
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de sair do while pCabecaMao5 e antes de entrar no while pCabecaMao6") ;
	#endif

	while (LIS_ObterQtdElem(pCabecaMao6) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao6.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
		#endif
		LIS_IrFinalLista(pCabecaMao6) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao6.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaMao6, pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMao6.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
		#endif
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de sair do while pCabecaMao6 e antes de entrar no while pCabecaMesa") ;
	#endif

	while (LIS_ObterQtdElem(pCabecaMesa) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMesa.Depois de entrar no while e antes de chamar 'LIS_IrFinalLista'") ;
		#endif
		LIS_IrFinalLista(pCabecaMesa) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMesa.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'BAR_TransferirCarta'") ;
		#endif
		BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_TransferirTodasCartasProLixo.pCabecaMesa.Depois de chamar 'BAR_TransferirCarta' e antes de sair do while") ;
		#endif
	}
	#ifdef _DEBUG
		CNT_CONTAR("MES_TransferirTodasCartasProLixo.Depois de sair do while pCabecaMesa") ;
	#endif

}

/***************************************************************************
*  Função: &Iniciar partida NAO TA FUNCIONANDO NAO SEI PQ
***************************************************************************/
int MES_IniciarPartida (LIS_tppLista pCabecaBaralho, LIS_tppLista pCabecaMao1, LIS_tppLista pCabecaMao2, 
						 LIS_tppLista pCabecaMao3, LIS_tppLista pCabecaMao4, LIS_tppLista pCabecaMao5,
						 LIS_tppLista pCabecaMao6, LIS_tppLista pCabecaLixo, LIS_tppLista pCabecaMesa,
						 LIS_tppLista pCabecaSuperior) {
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_IniciarPartida.Antes de chamar 'LIS_CriarLista' para cada cabeça") ;
	#endif
	
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
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_IniciarPartida.Depois de chamar 'LIS_CriarLista' para cada cabeça e antes de chamar 'LIS_IrInicioLista'") ;
	#endif

	LIS_IrInicioLista(pCabecaSuperior) ;
	#ifdef _DEBUG
		CNT_CONTAR("MES_IniciarPartida.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_InserirElementoApos'") ;
	#endif
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaBaralho) ;	//inicio
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao1) ;		//1
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao2) ;		//2
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao3) ;		//3
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao4) ;		//4
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao5) ;		//5
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao6) ;		//6
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaLixo) ;		//7
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMesa) ;		//final

	#ifdef _DEBUG
		CNT_CONTAR("MES_IniciarPartida.Depois de chamar 'LIS_InserirElementoApos'") ;
	#endif
	
	return 49;

} // fim funcao

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

	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCabecaMao.Antes de chamar 'LIS_IrInicioLista' para pCabecaSuperior") ;
	#endif
	
	LIS_IrInicioLista(pCabecaSuperior) ;
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCabecaMao.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_AvancarElem.Cor.'") ;
	#endif
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCabecaMao.Depois de chamar 'LIS_AvancarElem.Cor.' e antes de chamar 'LIS_ObterValor'") ;
	#endif
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCabecaMesa.Depois de chamar 'LIS_ObterValor' e antes de chamar 'LIS_IrFinalLista' para pCabecaSuperior") ;
	#endif

	LIS_IrFinalLista(pCabecaSuperior) ;
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCabecaMesa.Depois de chamar 'LIS_IrFinalLista' e antes de chamar 'LIS_ObterValor'") ;
	#endif
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCartaVira.Depois de chamar 'LIS_ObterValor' e antes de chamar 'LIS_IrInicioLista' para pCabecaMesa") ;
	#endif

	LIS_IrInicioLista(pCabecaMesa) ;
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCartaVira.Depois de chamar 'LIS_IrInicioLista' para pCabecaMesa e antes de chamar 'BAR_ObterCartaCorr'") ;
	#endif
	pCartaVira = BAR_ObterCartaCorr(pCabecaMesa) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCartaAposta.Depois de chamar 'BAR_ObterCartaCorr' e antes de chamar 'LIS_IrFinalLista' para pCabecaMesa") ;
	#endif

	LIS_IrFinalLista(pCabecaMesa) ;
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.pCartaAposta.Depois de chamar 'LIS_IrFinalLista' para pCabecaMesa e antes de chamar 'BAR_ObterCartaCorr'") ;
	#endif
	pCartaAposta = BAR_ObterCartaCorr(pCabecaMesa) ;

	qtdCartasVencidas = 0 ;

	primeiroComQuemEmpatou = NINGUEM ;

	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.Antes de chamar 'MES_IdentificarQuemJogouQual'") ;
	#endif
	
	MES_IdentificarQuemJogouQual(qtdJogadores, quemJogouAPrimeira, quemJogouASegunda, quemJogouATerceira,
							 quemJogouAQuarta, quemJogouASexta, quemJogouAQuinta) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.Antes de chamar 'MES_IdentificarQuemJogouQual' e antes de entrar NO for") ;
	#endif

	for (i = 1; i <= MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA); i++) {

		#ifdef _DEBUG
			CNT_CONTAR("MES_DeterminarResultado.Depois de entrar NO for e antes de entrar no if 'pCartaMesa=Manilha'") ;
		#endif
		
		//CARTA APOSTADA == MANILHA
		if (BAR_VerificarSeEhManilha(pCartaAposta, pCartaVira) == BAR_CondRetEhManilha) {
			
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.EhManilha.Depois de entrar no if e antes de chamar 'LIS_IrInicioLista'") ;
			#endif

			LIS_IrInicioLista(pCabecaMesa) ;

			//se i = 1 -> i = primeira carta colocada na mesa
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.EhManilha.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_AvancarElem.Cor.'") ;
			#endif
			LIS_AvancarElementoCorrente(pCabecaMesa, i) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.EhManilha.Depois de chamar 'LIS_AvancarElem.Cor.' e antes de chamar 'BAR_ObterCartaCorr'") ;
			#endif
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;
			
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.EhManilha.Depois de chamar 'BAR_ObterCartaCorr' e antes de entrar no if 'pCartaMesa=Manilha'") ;
			#endif

			//CARTA DA MESA == MANILHA (tem que comparar naipes)
			if (BAR_VerificarSeEhManilha(pCartaMesa, pCartaVira) == BAR_CondRetEhManilha) {
				
				#ifdef _DEBUG
					CNT_CONTAR("MES_DeterminarResultado.EhManilha.if.Depois de entrar no if e antes de chamar 'BAR_ObterNaipe'") ;
				#endif
				
				naipeAposta = BAR_ObterNaipe(pCartaAposta) ;
				naipeCartaMesa = BAR_ObterNaipe(pCartaMesa) ;
				
				#ifdef _DEBUG
					CNT_CONTAR("MES_DeterminarResultado.EhManilha.if.Depois de chamar 'BAR_ObterNaipe' e antes de entrar no if 'apostador venceu?'") ;
				#endif

				//apostador venceu
				if ((int)naipeAposta > (int)naipeCartaMesa) {
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.EhManilha.if.venceu.Depois de entrar no if") ;
					#endif
					qtdCartasVencidas += 1 ;
				} //fim if

				//apostador perdeu
				else {
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.EhManilha.if.perdeu.Depois de entrar no else") ;
					#endif
					return 0 ;
				} //fim else

			} //fim if

			//CARTA DA MESA != MANILHA (apostador venceu)
			else {
				#ifdef _DEBUG
					CNT_CONTAR("MES_DeterminarResultado.EhManilha.else.Depois de entrar no else") ;
				#endif
				qtdCartasVencidas += 1 ;
			} //fim else

		} //fim if "se a carta apostada for manilha"

		//CARTA APOSTADA != MANILHA
		else {
			
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.Depois de entrar no else e antes de chamar 'LIS_IrInicioLista'") ;
			#endif

			LIS_IrInicioLista(pCabecaMesa) ;
			
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_AvancarElem.Cor.'") ;
			#endif

			LIS_AvancarElementoCorrente(pCabecaMesa, i) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.Depois de chamar 'LIS_AvancarElem.Cor.' e antes de chamar 'BAR_ObterCartaCorr'") ;
			#endif
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;
			
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.Depois de chamar 'BAR_ObterCartaCorr' e antes de entrar no if 'pCartaMesa!=Manilha'") ;
			#endif

			//CARTA DA MESA != MANILHA (tem que comparar valores)
			if (BAR_VerificarSeEhManilha(pCartaMesa, pCartaVira) == BAR_CondRetNaoEhManilha) {
				
				#ifdef _DEBUG
					CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.Depois de entrar no if e antes de chamar 'BAR_ObterValor'") ;
				#endif
				
				valorAposta = BAR_ObterValor(pCartaAposta) ;
				valorCartaMesa = BAR_ObterValor(pCartaMesa) ;
				
				#ifdef _DEBUG
					CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.Depois de chamar 'BAR_ObterValor' e antes de entrar no if 'apostador venceu?'") ;
				#endif

				//apostador venceu
				if ((int)valorAposta > (int)valorCartaMesa) {
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.venceu.Depois de entrar no if") ;
					#endif
					qtdCartasVencidas += 1 ;
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.venceu.Antes de sairr do if 'venceu'") ;
					#endif
				} //fim if

				//empataram
				else if ((int)valorAposta == (int)valorCartaMesa) {
					
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de entrar no if") ;
					#endif

					//verificar se tem alguma carta na mesa maior do que a que empatou
					pCartaQueEmpatou = pCartaMesa ;
					valorCartaQueEmpatou = valorCartaMesa ; 
					resultadoEmpate = CONSIDERAR ;
					
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Antes de entrar no for") ;
					#endif

					for (j = 1 ; j <= MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA); j++) {
						#ifdef _DEBUG
							CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de entrar no for e antes de chamar 'LIS_IrInicioLista'") ;
						#endif
						LIS_IrInicioLista(pCabecaMesa) ;
						#ifdef _DEBUG
							CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de chamar 'LIS_IrInicioLista' e antes de chamar 'LIS_AvancarElem.Cor.'") ;
						#endif
						LIS_AvancarElementoCorrente(pCabecaMesa, j) ;
						#ifdef _DEBUG
							CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de chamar 'LIS_AvancarElem.Cor.' e antes de chamar 'LIS_ObterValor'") ;
						#endif
						pCartaMesa = (BAR_tppCarta)LIS_ObterValor(pCabecaMesa) ;
						#ifdef _DEBUG
							CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de chamar 'LIS_ObterValor' e antes de chamar 'BAR_ObterValor'") ;
						#endif
						valorCartaMesa = BAR_ObterValor(pCartaMesa) ;
						
						#ifdef _DEBUG
							CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de chamar 'BAR_ObterValor' e antes de entrar no if 'CartaQueEmpatou<CartaMesa'") ;
						#endif

						if (valorCartaQueEmpatou < valorCartaMesa) {
							#ifdef _DEBUG
								CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de entrar no if 'CartaQueEmpatou<CartaMesa'") ;
							#endif
							resultadoEmpate = DESCONSIDERAR ;
						}
						#ifdef _DEBUG
							CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de sair do if 'CartaQueEmpatou<CartaMesa'") ;
						#endif
					} //fim for
					
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Depois de sair do for e antes de entrar no if '=CONSIDERAR'") ;
					#endif

					if (resultadoEmpate == CONSIDERAR) {
						
						#ifdef _DEBUG
							CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.Depois de entrar no if e antes de entrar no if '=NINGUEM'") ;
						#endif

						if (primeiroComQuemEmpatou == NINGUEM) {
							
							#ifdef _DEBUG
								CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Depois de entrar no if e antes de entrar no switch") ;
							#endif

							switch (i) {
							case 1:
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Depois de entrar no case 1") ;
								#endif
								primeiroComQuemEmpatou = quemJogouAPrimeira ;
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Antes de sair do case 1") ;
								#endif
								break ;
							case 2:
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Depois de entrar no case 2") ;
								#endif
								primeiroComQuemEmpatou = *quemJogouASegunda ;
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Antes de sair do case 2") ;
								#endif
								break ;
							case 3:
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Depois de entrar no case 3") ;
								#endif
								primeiroComQuemEmpatou = *quemJogouATerceira ;
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Antes de sair do case 3") ;
								#endif
								break ;
							case 4:
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Depois de entrar no case 4") ;
								#endif
								primeiroComQuemEmpatou = *quemJogouAQuarta ;
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Antes de sair do case 4") ;
								#endif
								break ;
							case 5:
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Depois de entrar no case 5") ;
								#endif
								primeiroComQuemEmpatou = *quemJogouAQuinta ;
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Antes de sair do case 5") ;
								#endif
								break ;
							case 6:
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Depois de entrar no case 6") ;
								#endif
								primeiroComQuemEmpatou = *quemJogouASexta ;
								#ifdef _DEBUG
									CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Antes de sair do case 6") ;
								#endif
								break ;
							} //fim switch
							
							#ifdef _DEBUG
								CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.CONSIDERAR.NINGUEM.Depois de sair do switch") ;
							#endif

						} //fim if

					}//fim if considerar

					//desconsiderar empate (perdeu)
					else {
						#ifdef _DEBUG
							CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.DESCONSIDERAR.Depois de entrar no else") ;
						#endif
						return 0 ;
					}
					
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.empataram.Antes de sair do else if 'empataram'") ;
					#endif

				} //fim else if empataram
				
				//apostador perdeu
				else {
					#ifdef _DEBUG
						CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.perdeu.Depois de entrar no else") ;
					#endif
					return 0 ;
				} //fim else
				
				#ifdef _DEBUG
					CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.if.Antes de sair do if") ;
				#endif

			} //fim if

			//CARTA DA MESA == MANILHA (apostador perdeu)
			else {
				#ifdef _DEBUG
					CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.else.Depois de entrar no else") ;
				#endif
				return 0 ;
			} //fim else
			
			#ifdef _DEBUG
				CNT_CONTAR("MES_DeterminarResultado.NaoEhManilha.Antes de sair do else 'NaoEhManilha'") ;
			#endif

		} //fim else "se a carta apostada nao for manilha"
		
		#ifdef _DEBUG
			CNT_CONTAR("MES_DeterminarResultado.Antes de sair DO for") ;
		#endif

	} //fim for
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DeterminarResultado.Depois de sair DO for e antes de entrar no if 'venceu todas as cartas?'") ;
	#endif

	//se venceu todas cartas colocadas na mesa
	if (qtdCartasVencidas == MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA)) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_DeterminarResultado.Depois de entrar no if 'venceu todas as cartas?'") ;
		#endif
		return quemJoga ;
	}

	//se nao venceu e ainda nao retornou 0, só pode ter empatado
	else {
		#ifdef _DEBUG
			CNT_CONTAR("MES_DeterminarResultado.Depois de entrar no else 'venceu todas as cartas?'") ;
		#endif
		return primeiroComQuemEmpatou ;
	}

	return 0 ;
} /*************** Fim função: &Determinar resultado ***************/

/***************************************************************************
*  Função: &Definir quem comeca
***************************************************************************/
int MES_DefinirQuemComeca(int qtdJogadores) {

	int quemComeca = NINGUEM ;

	//função suporte da rand que faz gerar números diferentes sempre
	srand ((unsigned)time(NULL));
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DefinirQuemComeca.Antes de entrar no while") ;
	#endif

	while (quemComeca == NINGUEM) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_DefinirQuemComeca.Depois de entrar no while e antes de entrar no switch") ;
		#endif
		switch (qtdJogadores) {
		case 2: 
			#ifdef _DEBUG
				CNT_CONTAR("MES_DefinirQuemComeca.Depois de entrar no case 2") ;
			#endif
			quemComeca = 1 + (rand() % 2) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_DefinirQuemComeca.Antes de sair no case 2") ;
			#endif
			break ;
		case 4: 
			#ifdef _DEBUG
				CNT_CONTAR("MES_DefinirQuemComeca.Depois de entrar no case 4") ;
			#endif
			quemComeca = 1 + (rand() % 4) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_DefinirQuemComeca.Antes de sair no case 4") ;
			#endif
			break ;
		case 6: 
			#ifdef _DEBUG
				CNT_CONTAR("MES_DefinirQuemComeca.Depois de entrar no case 6") ;
			#endif
			quemComeca = 1 + (rand() % 6) ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_DefinirQuemComeca.Antes de sair no case 6") ;
			#endif
			break ;
		} //fim switch
		#ifdef _DEBUG
			CNT_CONTAR("MES_DefinirQuemComeca.Depois de sair do switch e antes de sair do while") ;
		#endif
	}//fim while
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_DefinirQuemComeca.Depois de sair do while") ;
	#endif

	return quemComeca;
} //fim funcao

/***************************************************************************
*  Função: &Identificar quem jogou qual
***************************************************************************/
void MES_IdentificarQuemJogouQual(int qtdJogadores, int quemJogouAPrimeira, int *quemJogouASegunda, int *quemJogouATerceira, 
							  int *quemJogouAQuarta, int *quemJogouAQuinta, int *quemJogouASexta) {
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_IdentificarQuemJogouQual.Antes de entrar no switch") ;
	#endif

	//identificando quem jogou qual
	switch (quemJogouAPrimeira) {

	case JOGADOR1:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR1.Depois de entrar no case e antes de entrar no switch") ;
		#endif

		switch (qtdJogadores) {
		case 2:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR1.Depois de entrar no case 2") ;
			#endif
			*quemJogouASegunda = JOGADOR2;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR1.Antes de sair do case 2") ;
			#endif
			break;
		case 4:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR1.Depois de entrar no case 4") ;
			#endif
			*quemJogouASegunda = JOGADOR2 ;
			*quemJogouATerceira = JOGADOR3 ;
			*quemJogouAQuarta = JOGADOR4 ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR1.Antes de sair do case 4") ;
			#endif
			break;
		case 6:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR1.Depois de entrar no case 6") ;
			#endif
			*quemJogouASegunda = JOGADOR2 ;
			*quemJogouATerceira = JOGADOR3 ;
			*quemJogouAQuarta = JOGADOR4 ;
			*quemJogouAQuinta = JOGADOR5 ;
			*quemJogouASexta = JOGADOR6 ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR1.Antes de sair do case 6") ;
			#endif
			break;
		} //fim switch qtd jogadores
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR1.Depois de sair do switch e antes de sair do case") ;
		#endif

		break;

	case JOGADOR2:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR2.Depois de entrar no case e antes de entrar no switch") ;
		#endif
		
		switch (qtdJogadores) {
		case 2:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR2.Depois de entrar no case 2") ;
			#endif
			*quemJogouASegunda = JOGADOR1;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR2.Antes de sair do case 2") ;
			#endif
			break;
		case 4:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR2.Depois de entrar no case 4") ;
			#endif
			*quemJogouASegunda = JOGADOR3 ;
			*quemJogouATerceira = JOGADOR4 ;
			*quemJogouAQuarta = JOGADOR1 ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR2.Antes de sair do case 4") ;
			#endif
			break;
		case 6:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR2.Depois de entrar no case 6") ;
			#endif
			*quemJogouASegunda = JOGADOR3 ;
			*quemJogouATerceira = JOGADOR4 ;
			*quemJogouAQuarta = JOGADOR5 ;
			*quemJogouAQuinta = JOGADOR6 ;
			*quemJogouASexta = JOGADOR1 ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR2.Antes de sair do case 6") ;
			#endif
			break;
		} //fim switch qtd jogadores
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR2.Depois de sair do switch e antes de sair do case") ;
		#endif

		break ;

	case JOGADOR3:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR3.Depois de entrar no case e antes de entrar no switch") ;
		#endif
		
		switch (qtdJogadores) {
		case 4:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR3.Depois de entrar no case 4") ;
			#endif
			*quemJogouASegunda = JOGADOR4 ;
			*quemJogouATerceira = JOGADOR1 ;
			*quemJogouAQuarta = JOGADOR2 ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR3.Antes de sair do case 4") ;
			#endif
			break;
		case 6:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR3.Depois de entrar no case 6") ;
			#endif
			*quemJogouASegunda = JOGADOR4 ;
			*quemJogouATerceira = JOGADOR5 ;
			*quemJogouAQuarta = JOGADOR6 ;
			*quemJogouAQuinta = JOGADOR1 ;
			*quemJogouASexta = JOGADOR2 ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR3.Antes de sair do case 6") ;
			#endif
			break;
		} //fim switch qtd jogadores
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR3.Depois de sair do switch e antes de sair do case") ;
		#endif

		break ;

	case JOGADOR4:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR4.Depois de entrar no case e antes de entrar no switch") ;
		#endif
		
		switch (qtdJogadores) {
		case 4:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR4.Depois de entrar no case 4") ;
			#endif
			*quemJogouASegunda = JOGADOR1 ;
			*quemJogouATerceira = JOGADOR2 ;
			*quemJogouAQuarta = JOGADOR3 ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR4.Antes de sair do case 4") ;
			#endif
			break;
		case 6:
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR4.Depois de entrar no case 6") ;
			#endif
			*quemJogouASegunda = JOGADOR5 ;
			*quemJogouATerceira = JOGADOR6 ;
			*quemJogouAQuarta = JOGADOR1 ;
			*quemJogouAQuinta = JOGADOR2 ;
			*quemJogouASexta = JOGADOR3 ;
			#ifdef _DEBUG
				CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR4.Antes de sair do case 6") ;
			#endif
			break;
		} //fim switch qtd jogadores
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR4.Depois de sair do switch e antes de sair do case") ;
		#endif

		break ;

	case JOGADOR5:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR5.Depois de entrar no case") ;
		#endif

		*quemJogouASegunda = JOGADOR6 ;
		*quemJogouATerceira = JOGADOR1 ;
		*quemJogouAQuarta = JOGADOR2 ;
		*quemJogouAQuinta = JOGADOR3 ;
		*quemJogouASexta = JOGADOR4 ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR5.Antes de sair do case") ;
		#endif
		break ;

	case JOGADOR6:
			
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR6.Depois de entrar no case") ;
		#endif

		*quemJogouASegunda = JOGADOR1 ;
		*quemJogouATerceira = JOGADOR2 ;
		*quemJogouAQuarta = JOGADOR3 ;
		*quemJogouAQuinta = JOGADOR4 ;
		*quemJogouASexta = JOGADOR5 ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_IdentificarQuemJogouQual.JOGADOR6.Antes de sair do case") ;
		#endif
		break ;

	} //fim switch quem jogou a primeira
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_IdentificarQuemJogouQual.Depois de sair do switch") ;
	#endif

} //fim funcao

/***************************************************************************
*  Função: &Proximo jogador
***************************************************************************/
int MES_ProximoJogador(int quemJoga, int qtdJogadores) {
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_ProximoJogador.Antes de entrar no switch") ;
	#endif

	switch (qtdJogadores) {
	case 2: 
		#ifdef _DEBUG
			CNT_CONTAR("MES_ProximoJogador.2.Depois de entrar no switch e antes de entrar no switch") ;
		#endif
		switch (quemJoga) {
		case 1:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.2.Depois de entrar no case 1") ;
			#endif
			return 2;
		case 2:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.2.Depois de entrar no case 2") ;
			#endif
			return 1;
		}
	case 4:
		#ifdef _DEBUG
			CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no switch e antes de entrar no switch") ;
		#endif
		switch (quemJoga) {
		case 1:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 1") ;
			#endif
			return 2;
		case 2:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 2") ;
			#endif
			return 3;
		case 3:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 3") ;
			#endif
			return 4;
		case 4:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 4") ;
			#endif
			return 1;
		}
	case 6:
		#ifdef _DEBUG
			CNT_CONTAR("MES_ProximoJogador.6.Depois de entrar no switch e antes de entrar no switch") ;
		#endif
		switch (quemJoga) {
		case 1:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 1") ;
			#endif
			return 2;
		case 2:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 2") ;
			#endif
			return 3;
		case 3:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 3") ;
			#endif
			return 4;
		case 4:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 4") ;
			#endif
			return 5;
		case 5:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 5") ;
			#endif
			return 6;
		case 6:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogador.4.Depois de entrar no case 6") ;
			#endif
			return 1;
		}
	}
	return 0 ;
} //fim funcao

/***************************************************************************
*  Função: &Proximo jogador da mesma equipe
***************************************************************************/
int MES_ProximoJogadorDaMesmaEquipe(int quemJoga, int qtdJogadores) {
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.Antes de entrar no switch") ;
	#endif

	switch (qtdJogadores) {
	case 2: 
		#ifdef _DEBUG
			CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no switch e antes de entrar no switch") ;
		#endif
		switch (quemJoga) {
		case 1:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 1") ;
			#endif
			return 1;
		case 2:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 2") ;
			#endif
			return 2;
		}
	case 4:
		#ifdef _DEBUG
			CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.4.Depois de entrar no switch e antes de entrar no switch") ;
		#endif
		switch (quemJoga) {
		case 1:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 1") ;
			#endif
			return 3;
		case 2:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 2") ;
			#endif
			return 4;
		case 3:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 3") ;
			#endif
			return 1;
		case 4:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 4") ;
			#endif
			return 2;
		}
	case 6:
		#ifdef _DEBUG
			CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.6.Depois de entrar no switch e antes de entrar no switch") ;
		#endif
		switch (quemJoga) {
		case 1:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 1") ;
			#endif
			return 3;
		case 2:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 2") ;
			#endif
			return 4;
		case 3:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 3") ;
			#endif
			return 5;
		case 4:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 4") ;
			#endif
			return 6;
		case 5:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 5") ;
			#endif
			return 1;
		case 6:
			#ifdef _DEBUG
				CNT_CONTAR("MES_ProximoJogadorDaMesmaEquipe.2.Depois de entrar no case 6") ;
			#endif
			return 2;
		}
	}
	return 0 ;
} //fim funcao

void MES_EsvaziarLixo (LIS_tppLista pCabecaLixo) {

	#ifdef _DEBUG
		CNT_CONTAR("MES_EsvaziarLixo.Antes de entrar no if") ;
	#endif
	
	if (LIS_ObterQtdElem(pCabecaLixo) > 0) {
		#ifdef _DEBUG
			CNT_CONTAR("MES_EsvaziarLixo.Depois de entrar no if e antes de chamar 'LIS_EsvaziarLista'") ;
		#endif
		LIS_EsvaziarLista (pCabecaLixo) ;
		#ifdef _DEBUG
			CNT_CONTAR("MES_EsvaziarLixo.Depois de chamar 'LIS_EsvaziarLista' e antes de sair do if") ;
		#endif
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("MES_EsvaziarLixo.Depois de sair do if") ;
	#endif

} //fim funçao


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//ainda nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: MES Mesa ******************/
