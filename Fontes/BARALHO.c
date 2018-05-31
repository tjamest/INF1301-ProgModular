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

#define EQUIPE_IMPAR 1
#define EQUIPE_PAR 0
#define EMPATE1 -1
#define EMPATE2 -2
#define EMPATE3 -3

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

/***************************************************************************
*  Função: &Comparar cartas em um jogo de 2 jogadores
***************************************************************************/
int BAR_CompararCartas2Jogadores (LIS_tppLista pCabecaMesa, int *quemJoga) {

	BAR_tppCarta pVira = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pAposta = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCartaMesa = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;

	int i, qtdCartasPraComparar ;

	BAR_tpCondRet condRetBar ;

	BAR_tpValorCarta valorAposta, valorCarta ;
	BAR_tpNaipeCarta naipeAposta, naipeCarta ;

	qtdCartasPraComparar = LIS_ObterQtdElem(pCabecaMesa)-2 ;

	LIS_IrInicioLista(pCabecaMesa) ;
	pVira = BAR_ObterCartaCorr(pCabecaMesa) ;

	LIS_IrFinalLista(pCabecaMesa) ;
	pAposta = BAR_ObterCartaCorr(pCabecaMesa) ;

	//verifica se a carta apostada é manilha
	condRetBar = BAR_VerificarSeEhManilha(pAposta, pVira) ;

	//CARTA APOSTADA == MANILHA
	if (condRetBar == BAR_CondRetEhManilha) {

		LIS_IrInicioLista(pCabecaMesa) ;

		for (i = 0 ; i < qtdCartasPraComparar ; i++ ) {

			LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;

			//verifica se a carta da mesa é manilha
			condRetBar = BAR_VerificarSeEhManilha(pCartaMesa, pVira) ;

			//CARTA DA MESA == MANILHA (tem que comparar naipes)
			if (condRetBar == BAR_CondRetEhManilha) {

				naipeAposta = BAR_ObterNaipe(pAposta) ;
				naipeCarta = BAR_ObterNaipe(pCartaMesa) ;

				//apostador venceu
				if ((int)naipeAposta > (int)naipeCarta) {
					switch (*quemJoga) {
					case 1: return EQUIPE_IMPAR; break;
					case 2: return EQUIPE_PAR; break;
					}
				}

				//apostador perdeu
				else {
					switch (*quemJoga) {
					case 1: return EQUIPE_PAR; break;
					case 2: return EQUIPE_IMPAR; break;
					}
				}

			} //fim if

			//CARTA DA MESA != MANILHA (apostador venceu)
			else {
				switch (*quemJoga) {
				case 1: return EQUIPE_IMPAR; break;
				case 2: return EQUIPE_PAR; break;
				}
			} //fim else

		} //fim for

	} //fim if "se a carta apostada for manilha"

	//CARTA APOSTADA != MANILHA
	else {

		LIS_IrInicioLista(pCabecaMesa) ;

		for (i = 0 ; i < qtdCartasPraComparar ; i++ ) {

			LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;

			//verifica se a carta na mesa é manilha
			condRetBar = BAR_VerificarSeEhManilha(pCartaMesa, pVira) ;

			//CARTA DA MESA != MANILHA (tem que comparar valores)
			if (condRetBar == BAR_CondRetNaoEhManilha) {
				
				valorAposta = BAR_ObterValor(pAposta) ;
				valorCarta = BAR_ObterValor(pCartaMesa) ;

				//apostador venceu
				if ((int)valorAposta > (int)valorCarta) {
					switch (*quemJoga) {
					case 1: return EQUIPE_IMPAR; break;
					case 2: return EQUIPE_PAR; break;
					}
				} //fim if

				//empataram (empatar 3 vezes ninguem ganha ponto,  )
				else if ((int)valorAposta == (int)valorCarta) {
					return EMPATE1; 

				} //fim else if
				
				//apostador perdeu
				else {
					switch (*quemJoga) {
					case 1: return EQUIPE_PAR; break;
					case 2: return EQUIPE_IMPAR; break;
					} //fim switch 
				} //fim else

			} //fim if

			//CARTA DA MESA == MANILHA (apostador perdeu)
			else {
				switch (*quemJoga) {
				case 1: return EQUIPE_PAR; break;
				case 2: return EQUIPE_IMPAR; break;
				} //fim switch 
			}

		} //fim for

	} //fim else "se a carta apostada nao for manilha"

	return -10;
} /*************** Fim função: &Comparar cartas 2 jogadores ***************/

/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
