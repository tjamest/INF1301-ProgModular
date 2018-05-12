#include "LISTA.h"
#include "BARALHO.h"
#include "MESA.h"
#include   <stdio.h>
#include   <stdlib.h> 
#include   <string.h>
#include   <malloc.h>
#include   <time.h>
#include   <assert.h>

//tamanho de um baralho sem os 8, 9, 10 e coringas
#define TAM 40

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
void PreencheVetorCartas(BAR_tppCarta vtCartas[]) ;
void EmbaralhaVetorCartas(BAR_tppCarta vtCartas[]) ;
void PrintaBaralho(LIS_tppLista pCabecaBaralho) ;
void PrintaMesa(LIS_tppLista pCabecaMesa) ;
/**************************************************************************/

//declara um vetor que armazena ponteiro pra tipo carta
BAR_tppCarta VetorAux[TAM];

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
int main (void) {

	//declara o vetor que armazena os ponteiros pras cartas
	BAR_tppCarta vtCartas[TAM] ;

	//declara ponteiros pras cabecas das listas
	LIS_tppLista pCabecaBaralho ;
	LIS_tppLista pCabecaMesa ;
//	LIS_tppLista pCabecaMao1 ;

	//preenche o vetor e embaralha os indices
	PreencheVetorCartas(vtCartas) ;
	EmbaralhaVetorCartas(vtCartas) ;

	//ponteiros que apontam pras cabecas de listas
	pCabecaBaralho = BAR_CriarBaralho(vtCartas) ;

	pCabecaMesa = LIS_CriarLista(BAR_DestruirCarta) ;

	BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

	//printa as listas
	PrintaBaralho(pCabecaBaralho) ;	
	PrintaMesa(pCabecaMesa) ;

	return 0;
}

/***************************************************************************
*  Função: &Preenche vetor cartas
***************************************************************************/
void PreencheVetorCartas (BAR_tppCarta vtCartas[]) {
	
	int i ,
		valor = 0,
		naipe = 0 ;

	//preenchendo o vetor de cartas de forma ordenada
	for (i = 0; i < TAM; i++, valor++) {
		
		//faz a transformacao de int pra tipo especifico
		BAR_tpValorCarta Valor = (BAR_tpValorCarta) valor;
		BAR_tpNaipeCarta Naipe = (BAR_tpNaipeCarta) naipe;

		BAR_tppCarta pCarta = BAR_CriarCarta(Valor, Naipe);
		vtCartas[i] = pCarta;

		if (i == 9 || i == 19 || i == 29) {

			//reinicia o preenchimento do valor de 0 a 9
			valor = -1 ;
			//passa pro proximo naipe
			naipe++;

		} //fim if
	} //fim for

	//return *vtCartas ;

} /***************** Fim função: &Preenche vetor cartas *******************/


/***************************************************************************
*  Função: &Embaralha vetor cartas
***************************************************************************/
void EmbaralhaVetorCartas (BAR_tppCarta vtCartas[]) {

	int i ,
		valor = 0,
		naipe = 0 ;

	//preenchendo o vetor de cartas de forma ordenada
	for (i = 0; i < TAM; i++, valor++) {
		
		//faz a transformacao de int pra tipo especifico
		BAR_tpValorCarta Valor = (BAR_tpValorCarta) valor;
		BAR_tpNaipeCarta Naipe = (BAR_tpNaipeCarta) naipe;

		BAR_tppCarta pCarta = BAR_CriarCarta(Valor, Naipe);
		vtCartas[i] = pCarta;

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
		pCartaAux = vtCartas[i] ;
		vtCartas[i] = vtCartas[random] ;
		vtCartas[random] = pCartaAux ;
		
	} //fim for

	//return *vtCartas ;

} /***************** Fim função: &Embaralha vetor cartas ******************/


/***************************************************************************
*  Função: &Printa baralho
***************************************************************************/
void PrintaBaralho (LIS_tppLista pCabecaBaralho) {
	
	int i, valor, naipe ;

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaBaralho);
	
	//printando as cartas
	printf("\nCartas na lista baralho:\n") ;
	for(i = 0; i < TAM; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaBaralho);

		//obtem valor e naipe
		valor = (int)BAR_ObterValor (pCarta);
		naipe = (int)BAR_ObterNaipe (pCarta);

		if (pCabecaBaralho == NULL) {
			return;
		}

		//verificando com printf
		printf ("Carta %d - Valor: %d  Naipe: %d\n", i+1, valor, naipe);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;

	}//fim for

} /***************** Fim função: &Printa baralho **********************/


/***************************************************************************
*  Função: &Printa mesa
***************************************************************************/
void PrintaMesa (LIS_tppLista pCabecaMesa) {
	
	int i, valor, naipe;

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaMesa);
	
	//printando as cartas
	printf("\nCartas na lista mesa:\n") ;
	for(i = 0; i < 4; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaMesa);

		//obtem valor e naipe
		valor = (int)BAR_ObterValor (pCarta);
		naipe = (int)BAR_ObterNaipe (pCarta);

		//verificando com printf
		printf ("Carta %d - Valor: %d  Naipe: %d\n", i+1, valor, naipe);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;

	}//fim for

} /***************** Fim função: &Printa mesa *************************/