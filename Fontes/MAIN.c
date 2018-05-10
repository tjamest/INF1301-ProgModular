#include "LISTA.h"
#include "BARALHO.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 40

void PrintaBaralho(LIS_tppLista pCabecaBaralho);

int main (void) {

	//contador do for
	int i;

	LIS_tpCondRet CondRetLista;

	//ponteiro pra cabeca do baralho
	LIS_tppLista pCabecaBaralho = BAR_CriarBaralho();

	//declara ponteiro temporario pra carta
	BAR_tppCarta pCarta;
	
	//printa todas cartas do baralho
	PrintaBaralho(pCabecaBaralho);

	//vai pro final da lista
	IrFinalLista(pCabecaBaralho);

	//obtem a ultima carta
	pCarta = BAR_ObterCarta (pCabecaBaralho);

	//destroi o ultimo elemento
    CondRetLista = LIS_ExcluirElemento(pCabecaBaralho) ;

	//vai pro inicio da lista
	IrInicioLista(pCabecaBaralho);
	printf ("\n");

	//printa todas cartas do baralho
	PrintaBaralho(pCabecaBaralho);

	//vai pro final da lista
	IrFinalLista(pCabecaBaralho);

	//obtem a ultima carta
	pCarta = BAR_ObterCarta (pCabecaBaralho);

	//destroi o ultimo elemento
    CondRetLista = LIS_ExcluirElemento(pCabecaBaralho) ;

	//vai pro inicio da lista
	IrInicioLista(pCabecaBaralho);
	printf ("\n");

	//printa todas cartas do baralho
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
	
	//printando as cartas
	for(i = 0; i < TAM; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCarta (pCabecaBaralho);

		//obtem valor e naipe
		valor = (int)BAR_ObterValor (pCarta);
		naipe = (int)BAR_ObterNaipe (pCarta);

		//verificando com printf
		printf ("Valor: %d  Naipe: %d\n", valor, naipe);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;

	}//fim for
}