#include "LISTA.h"
#include "BARALHO.h"
#include   <stdio.h>
#include   <stdlib.h> 
#include   <string.h>
#include   <malloc.h>
#include   <time.h>
#include   <assert.h>

#define TAM 40

void PrintaBaralho(LIS_tppLista pCabecaBaralho) ;
BAR_tppCarta EmbaralhaVetorCartas(BAR_tppCarta vtCartas[]) ;

//declara um vetor (um vetor eh um ponteiro) pra tipo carta
BAR_tppCarta VetorAux[TAM];

int main (void) {

	LIS_tpCondRet CondRetLista;

	BAR_tppCarta vtCartas[TAM];

	BAR_tppCarta pCarta = EmbaralhaVetorCartas(vtCartas) ;

	LIS_tppLista pCabecaBaralho = BAR_CriarBaralho(vtCartas) ;

	PrintaBaralho(pCabecaBaralho);	

	return 0;
}

void PrintaBaralho (LIS_tppLista pCabecaBaralho) {
	
	//contador do for
	int i, valor, naipe;

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaBaralho);
	
	//printando as cartas
	for(i = 0; i < 27; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaBaralho);

		//obtem valor e naipe
		valor = (int)BAR_ObterValor (pCarta);
		naipe = (int)BAR_ObterNaipe (pCarta);

		//verificando com printf
		printf ("Valor: %d  Naipe: %d\n", valor, naipe);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;

	}//fim for
} /***************** Fim função: BAR &Printa baralho ***********************/


BAR_tppCarta EmbaralhaVetorCartas (BAR_tppCarta vtCartas[]) {

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

	return *vtCartas ;

}  /************ Fim função: BAR &Vetor de cartas embaralhado **************/