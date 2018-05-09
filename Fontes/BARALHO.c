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
*  Versão  	Autor    	Data    	Observações
*     1     gsc, jvr, tgf    19/abr/2018    início desenvolviment
***************************************************************************/

#include   <stdio.h>
#include   <stdlib.h> 
#include   <string.h>
#include   <malloc.h>
#include   <time.h>
#include   <assert.h>

#define BARALHO_OWN
#include "BARALHO.h"
#include "LISTA.h"

#undef BARALHO_OWN

#define TAM 40


/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//não há funções encapsuladas no módulo

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
LIS_tppLista BAR_CriarBaralho() {

	int i; //contador
	int valor = 0, naipe = 0;

	//cria uma lista retornando um ponteiro pra cabeca da lista
	LIS_tppLista pCabecaBaralho = LIS_CriarLista (BAR_DestruirCarta) ;
		
	//declara um vetor (um vetor eh um ponteiro) pra tipo carta
	BAR_tppCarta VetorAux[TAM] ;
	
	//declara uma variável que armazena a condição de
	//retorno de funções de manipulação da lista
	LIS_tpCondRet condRetLista;

	//preenchendo o vetor de cartas de forma ordenada
	for (i = 0; i < TAM; i++, valor++) {
		
		//faz a transformacao de int pra tipo especifico
		BAR_tpValorCarta Valor = (BAR_tpValorCarta) valor;
		BAR_tpNaipeCarta Naipe = (BAR_tpNaipeCarta) naipe;

		BAR_tppCarta pCarta = BAR_CriarCarta(Valor, Naipe);
		VetorAux[i] = pCarta;

		if (i == 9 || i == 19 || i == 29) {

			//reinicia o preenchimento do valor de 0 a 9
			valor = -1 ;
			//passa pro proximo naipe
			naipe++;

		} //fim if
	} //fim for
	
	//função suporte da rand que faz gerar números diferentes sempre
	srand ((unsigned)time(NULL));

	//embaralhando o vetor (troca os indices aleatoriamente)
	for (i = 0; i < TAM; i++){

		//declara um ponteiro pra um tipo carta
		BAR_tppCarta pCartaAux;
		
		//gera um número aleatorio entre 0 e 39
		int random = rand() % TAM ;

		//embaralhando os indices
		pCartaAux = VetorAux[i] ;
		VetorAux[i] = VetorAux[random] ;
		VetorAux[random] = pCartaAux ;
		
	} //fim for
	
	//preenche um por um usando o vetor embaralhado
	for (i = 0; i < TAM; i++){
		
		BAR_tppCarta pCarta;
		pCarta = VetorAux[i] ;
	
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
*  Função: BAR  &Destruir baralho
***************************************************************************/
void BAR_DestruirBaralho(void * pCabecaBaralho) {

	#ifdef _DEBUG
		assert( pCabecaBaralho != NULL ) ;
	#endif

	free(pCabecaBaralho) ;	
} /************* Fim função: BAR &Destruir baralho ************************/


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
BAR_tppCarta BAR_ObterCarta(LIS_tppLista pCabecaBaralho) {

	//declara e aloca memoria pra um ponteiro pra tipo carta
	BAR_tppCarta pCarta = (BAR_tppCarta)malloc(sizeof(BAR_tpCarta)) ;

	//ponteiro pra tipo carta recebe o pValor do ElemLista
	pCarta = (BAR_tppCarta)LIS_ObterValor (pCabecaBaralho) ;

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


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//não há funções encapsuladas no módulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
