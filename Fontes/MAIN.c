#include "LISTA.h"
#include "BARALHO.h"
#include "MESA.h"
#include   <stdio.h>	//printf
#include   <stdlib.h>	//rand e srand
#include   <time.h>

#define TAM 40

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
void PreencheVetorCartas(BAR_tppCarta vtCartas[]) ;
void EmbaralhaVetorCartas(BAR_tppCarta vtCartas[]) ;
void PrintaBaralho(LIS_tppLista pCabecaBaralho) ;
void PrintaMesa(LIS_tppLista pCabecaMesa) ;
void PrintaMao(LIS_tppLista pCabecaMao, int numMao) ;
/**************************************************************************/
//declara um vetor que armazena ponteiro pra tipo carta
BAR_tppCarta VetorAux[TAM];
/**************************************************************************/
int main (void) {

	int numJogadores, 
		valorManilha ;

	//declara o vetor que armazena os ponteiros pras cartas
	BAR_tppCarta vtCartas[TAM] ;

	//declara ponteiros pras cabecas das listas
	LIS_tppLista pCabecaBaralho,
				 pCabecaMesa,
				 pCabecaMao1,
				 pCabecaMao2,
				 pCabecaMao3,
				 pCabecaMao4,
				 pCabecaMao5,
				 pCabecaMao6;

	printf("Quantas pessoas vao jogar?\n");
	scanf_s("%d", &numJogadores);

	//preenche o vetor e embaralha os indices
	PreencheVetorCartas(vtCartas) ;
	EmbaralhaVetorCartas(vtCartas) ;

	//cria um baralho com 40 cartas
	pCabecaBaralho = BAR_CriarBaralho(vtCartas) ;

	//cria uma mesa sem cartas
	pCabecaMesa = MES_CriarMesa() ;

	//cria maos sem cartas
	pCabecaMao1 = MES_CriarMao() ;
	pCabecaMao2 = MES_CriarMao() ;
	pCabecaMao3 = MES_CriarMao() ;
	pCabecaMao4 = MES_CriarMao() ;
	pCabecaMao5 = MES_CriarMao() ;
	pCabecaMao6 = MES_CriarMao() ;

	//vira vai pra mesa
	BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

	//distribui as maos
	MES_DistribuirMaos(pCabecaBaralho, 
					   pCabecaMao1, pCabecaMao2, pCabecaMao3,
					   pCabecaMao4, pCabecaMao5, pCabecaMao6, 
					   numJogadores) ;

	PrintaBaralho(pCabecaBaralho) ;
	PrintaMesa(pCabecaMesa) ;
	PrintaMao(pCabecaMao1, 1) ;
	PrintaMao(pCabecaMao2, 2) ;
	PrintaMao(pCabecaMao3, 3) ;
	PrintaMao(pCabecaMao4, 4) ;
	PrintaMao(pCabecaMao5, 5) ;
	PrintaMao(pCabecaMao6, 6) ;

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
	
	int i, qtdCartas, valor, naipe ;

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaBaralho);

	qtdCartas = LIS_ObterQtdElem(pCabecaBaralho) ;
	
	//printando as cartas
	printf("\n     BARALHO:\n") ;
	for(i = 0; i < qtdCartas; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaBaralho);

		//obtem valor e naipe
		valor = (int)BAR_ObterValor (pCarta);
		naipe = (int)BAR_ObterNaipe (pCarta);

		if (pCabecaBaralho == NULL) {
			return;
		}

		//verificando com printf
		printf ("Carta %d - Valor %d  Naipe %d\n", i+1, valor, naipe);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;

	}//fim for

} /***************** Fim função: &Printa baralho **********************/

/***************************************************************************
*  Função: &Printa mesa
***************************************************************************/
void PrintaMesa (LIS_tppLista pCabecaMesa) {
	
	int i, qtdCartas, valor, naipe;

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaMesa);

	//obtem a quantidade de elementos na mesa
	qtdCartas = LIS_ObterQtdElem(pCabecaMesa);

	//printando as cartas
	printf("\n     MESA:\n") ;
	for(i = 0; i < qtdCartas; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaMesa);

		//obtem valor e naipe
		valor = (int)BAR_ObterValor (pCarta);
		naipe = (int)BAR_ObterNaipe (pCarta);

		if (i == 0) {
			printf("Vira - Valor %d  Naipe %d\n", valor, naipe) ;
		}
		else {
			printf ("Carta %d - Valor %d  Naipe %d\n", i, valor, naipe);
		}

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;

	}//fim for

} /***************** Fim função: &Printa mesa *************************/

/***************************************************************************
*  Função: &Printa mao
***************************************************************************/
void PrintaMao (LIS_tppLista pCabecaMao, int numMao) {
	
	int i, qtdCartas, valor, naipe;

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaMao);

	//obtem a quantidade de elementos na mao
	qtdCartas = LIS_ObterQtdElem(pCabecaMao);
	
	//printando as cartas
	printf("\n     JOGADOR %d:\n", numMao) ;
	for(i = 0; i < qtdCartas; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaMao);

		//obtem valor e naipe
		valor = (int)BAR_ObterValor (pCarta);
		naipe = (int)BAR_ObterNaipe (pCarta);

		//verificando com printf
		printf ("Carta %d - Valor %d  Naipe %d\n", i+1, valor, naipe);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaMao, 1) ;

	}//fim for

} /***************** Fim função: &Printa mao *************************/