/***************************************************************************
*  $MCI Módulo de implementação: BAR  Baralho
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Projeto: INF 1301 Jogo de Truco
*  Autores: gsc, jvr, tgf
*
*  $HA Histórico de evolução:
*  Versão  		Autor  			Data    	Observações
*	  3			 gsc		 11/mai/2018	criada a TransferirCarta
*	  2			 gsc		 10/mai/2018	revisão para entrega na data
*     1     gsc, jvr, tgf    19/abr/2018    início desenvolvimento
***************************************************************************/

#include   <stdio.h>	//printf
#include   <stdlib.h>	//malloc, free
#include   <assert.h>	//assert

#define BARALHO_OWN
#include "BARALHO.h"
#include "LISTA.h"

#undef BARALHO_OWN

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//nao ha funcoes encapsuladas no modulo

/***************************************************************************
*  $TC Tipo de dados: BAR tpCarta
*
*  $ED Descrição do tipo
*     Estrutura de uma carta, que tem um valor e um naipe.
***************************************************************************/
typedef struct BAR_tagCarta {
	BAR_tpValorCarta valor ;
	BAR_tpNaipeCarta naipe ;
} BAR_tpCarta;

/***********  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ******************/

/***************************************************************************
*  Função: BAR  &Criar baralho
***************************************************************************/
LIS_tppLista BAR_CriarBaralho(BAR_tppCarta vtCartas[]) {

	int i ; //contador
	
	//cria uma lista retornando um ponteiro pra cabeca da lista
	LIS_tppLista pCabecaBaralho = LIS_CriarLista (BAR_DestruirCarta) ;

	//declara uma variável que armazena a condição de
	//retorno de funções de manipulação da lista
	LIS_tpCondRet condRetLista;
	
	//preenche um por um usando o vetor embaralhado
	for (i = 0; i < TAM; i++){
		
		BAR_tppCarta pCarta;
		pCarta = vtCartas[i] ;
	
		//é inserido um elemento na lista Baralho e 
		//seu valor é um ponteiro pra um tipo Carta
		condRetLista = LIS_InserirElementoApos (pCabecaBaralho, pCarta) ;

		//assertiva de saída
		if (condRetLista != LIS_CondRetOK){
			printf("\nNão inseriu carta no baralho.");
			return NULL;
		}//fim if

	}//fim for

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaBaralho) ;

	return pCabecaBaralho ;
   
} /***************** Fim função: BAR &Criar baralho ***********************/

/****************************************************************************
*  $FC Função: BAR  &Criar Carta
****************************************************************************/
BAR_tppCarta BAR_CriarCarta (BAR_tpValorCarta valor, BAR_tpNaipeCarta naipe) {

	//declara um ponteiro pra um tipo carta e aloca memoria
	BAR_tppCarta pCarta = (BAR_tppCarta) malloc(sizeof(BAR_tpCarta)) ;
	
	//atribui valor e naipe a um tipo carta
	pCarta->valor = valor ;
	pCarta->naipe = naipe ;
	
	//retorna um ponteiro pra um tipo carta
	return pCarta ;
	
} /******************** Fim função: BAR &Criar Carta ***********************/

/***************************************************************************
*  Função: BAR  &Destruir carta
***************************************************************************/
void BAR_DestruirCarta(void * pCarta) {

	#ifdef _DEBUG
		assert( pCarta != NULL ) ;
	#endif

	free(pCarta) ;
} /************ Fim função: BAR &Destruir carta ****************************/

/***************************************************************************
*  Função: BAR  &Obter carta
***************************************************************************/
BAR_tppCarta BAR_ObterCartaCorr(LIS_tppLista pCabecaBaralho) {

	//obtem o valor corrente de uma lista e retorna
	BAR_tppCarta pCarta = (BAR_tppCarta)LIS_ObterValor (pCabecaBaralho) ;

	return pCarta;
} /***************** Fim função: BAR &Obter carta **************************/

/***************************************************************************
*  Função: BAR  &Obter naipe
****************************************************************************/
BAR_tpNaipeCarta BAR_ObterNaipe(BAR_tppCarta pCarta) {

	#ifdef _DEBUG
		assert( pCarta != NULL ) ;
	#endif

	return pCarta->naipe;
} /***************** Fim função: BAR &Obter naipe **************************/

/***************************************************************************
*  Função: BAR  &Obter valor
****************************************************************************/
BAR_tpValorCarta BAR_ObterValor(BAR_tppCarta pCarta) {
	
	#ifdef _DEBUG
		assert( pCarta != NULL ) ;
	#endif

	return pCarta->valor;
} /***************** Fim função: BAR &Obter valor **************************/

/***************************************************************************
*  Função: BAR  &Transferir carta
****************************************************************************/
void BAR_TransferirCarta(LIS_tppLista pOrigem, LIS_tppLista pDestino) {

	LIS_tpCondRet CondRetLista ;

	BAR_tppCarta pCarta = BAR_ObterCartaCorr(pOrigem) ;

	CondRetLista = LIS_InserirElementoApos(pDestino, pCarta) ;

	CondRetLista = LIS_ExcluirPtrParaElemento(pOrigem) ;

} /***************** Fim função: BAR &Transferir carta *********************/

/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
