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

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//nao ha funcoes encapsuladas no modulo


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
	LIS_IrInicioLista(pCabecaBaralho) ;

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
void BAR_DestruirCarta(void * pLista) {

	LIS_tpCondRet condRetLista ;

	#ifdef _DEBUG
		assert( pLista != NULL ) ;
	#endif

	condRetLista = LIS_ExcluirElemento(pLista) ;

} /************ Fim função: BAR &Destruir carta ****************************/

/***************************************************************************
*  Função: BAR  &Destruir baralho
***************************************************************************/
void BAR_DestruirBaralho(void * pLista) {

	LIS_tpCondRet condRetLista ;

	#ifdef _DEBUG
		assert( pLista != NULL ) ;
	#endif

	condRetLista = LIS_ExcluirElemento(pLista) ;
} /************ Fim função: BAR &Destruir baralho ****************************/

/***************************************************************************
*  Função: BAR  &Obter carta corrente
***************************************************************************/
BAR_tppCarta BAR_ObterCartaCorr(LIS_tppLista pCabecaLista) {

	//obtem o valor corrente de uma lista e retorna
	BAR_tppCarta pCarta = (BAR_tppCarta)LIS_ObterValor (pCabecaLista) ;
	
	//assertiva de saída
	#ifdef _DEBUG
		assert( pCarta != NULL ) ;
    #endif

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
BAR_tpCondRet BAR_TransferirCarta(LIS_tppLista pOrigem, LIS_tppLista pDestino) {

	LIS_tpCondRet CondRetLista ;

	BAR_tppCarta pCarta = BAR_ObterCartaCorr(pOrigem) ;
	
	//assertiva de saida
	if (pCarta == NULL) { 
		return BAR_CondRetNaoObteveCarta ;
	}

	CondRetLista = LIS_InserirElementoApos(pDestino, pCarta) ;

	//assertiva de saida
	if (CondRetLista == LIS_CondRetFaltouMemoria) {
		return BAR_CondRetNaoInseriuCarta ;
	}

	CondRetLista = LIS_ExcluirPtrParaElemento(pOrigem) ;

	//assertiva de saida
	if (CondRetLista == LIS_CondRetListaVazia) {
		return BAR_CondRetNaoExcluiuPtrParaElem ;
	}

	return BAR_CondRetOK ;

} /***************** Fim função: BAR &Transferir carta *********************/

/***************************************************************************
*  Função: BAR  &Verificar se eh manilha
****************************************************************************/
BAR_tpCondRet BAR_VerificarSeEhManilha(BAR_tppCarta pAposta, BAR_tppCarta pVira) {

	//declara valor especifico pra vira e pra carta apostada
	BAR_tpValorCarta valorEspVira, valorEspAposta, valorEspManilha;

	//obtem o valor tpValorCarta da carta que acabou de ser apostada e da vira
	valorEspAposta = BAR_ObterValor(pAposta) ;
	valorEspVira = BAR_ObterValor(pVira) ;

	if ((int)valorEspVira == 9) {

		(int)valorEspManilha = 0 ;

		if (valorEspAposta == valorEspManilha) {
			return BAR_CondRetEhManilha ;
		} //fim if
		
		else {
			return BAR_CondRetNaoEhManilha ;
		} //fim else

	} //fim if

	else {

		(int)valorEspManilha = ((int)valorEspVira) + 1 ;

		if (valorEspAposta == valorEspManilha) {
			return BAR_CondRetEhManilha ;
		} //fim if
		
		else {
			return BAR_CondRetNaoEhManilha ;
		} //fim else

	} //fim else
}

/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
