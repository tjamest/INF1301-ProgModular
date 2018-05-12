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
void PrintaRegras() ;

void IniciarPartida () ;

int PrintaOpcoesInicio() ;
void ExecutaOpcaoInicio (int opcaoInicio) ;

int PrintaOpcoesJogadores() ;
void ExecutaOpcaoJogadores(int opcaoJogadores, LIS_tppLista pCabecaBaralho) ;

int PrintaOpcoesRegras();
void ExecutaOpcaoRegras();

/**************************************************************************/
BAR_tppCarta VetorAux[TAM];
/**************************************************************************/

int main (void) {

	int opcaoInicio;

	opcaoInicio = PrintaOpcoesInicio() ;
	ExecutaOpcaoInicio(opcaoInicio) ;

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
	LIS_IrInicioLista(pCabecaBaralho);

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
	LIS_IrInicioLista(pCabecaMesa);

	//obtendo a quantidade de cartas na mesa
	qtdCartas = LIS_ObterQtdElem(pCabecaMesa) ;

	//printando as cartas
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~~ MESA ~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	for(i = 0; i < qtdCartas; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaMesa);

		//obtem valor e naipe
		valor = (int)BAR_ObterValor (pCarta);
		naipe = (int)BAR_ObterNaipe (pCarta);

		if (i == 0) {
			printf("VIRA - Valor %d  Naipe %d\n", valor, naipe) ;
		}
		else {
			printf ("CARTA %d - Valor %d  Naipe %d\n", i, valor, naipe);
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
	LIS_IrInicioLista(pCabecaMao);

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

/***************************************************************************
*  Função: &Printa regras
***************************************************************************/
void PrintaRegras() {

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~ REGRAS ~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	printf("FORCA DAS CARTAS:\n");
	printf("4 = 0 (mais fraca)\n");
	printf("5 = 1\n");
	printf("6 = 2\n");
	printf("7 = 3\n");
	printf("Q = 4\n");
	printf("J = 5\n");
	printf("K = 6\n");
	printf("A = 7\n");
	printf("2 = 8\n");
	printf("3 = 9 (mais forte)\n\n");

	printf("FORCA DOS NAIPES:\n");
	printf("Ouros   = 0 (mais fraco)\n");
	printf("Espadas = 1\n");
	printf("Copas   = 2\n");
	printf("Paus    = 3 (mais forte)\n\n");

}

/***************************************************************************
*  Função: &Printa opçoes inicio
***************************************************************************/
int PrintaOpcoesInicio () {

	char * opcao = (char*)malloc(sizeof(char));

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf("(1) Iniciar partida | (2) Regras | (3) Exit\n");
	printf("Opcao: ");
	scanf_s(" %c",opcao, 1);

	while (*opcao != 49 && *opcao != 50 && *opcao != 51) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	return *opcao;
}

/***************************************************************************
*  Função: &Executa opcao inicio
***************************************************************************/
void ExecutaOpcaoInicio (int opcaoInicio) {

	int opcaoRegras;
	
	switch (opcaoInicio){

		case 49: //iniciar partida
			IniciarPartida() ;			
			break;

		case 50: //regras
			PrintaRegras();
			opcaoRegras = PrintaOpcoesRegras() ;
			ExecutaOpcaoRegras(opcaoRegras) ;
			break;

		case 51: //exit
			exit(0);

	} //fim switch opcao inicio
}

/***************************************************************************
*  Função: &Printa opçoes regras
***************************************************************************/
int PrintaOpcoesRegras() {

	char * opcao = (char*)malloc(sizeof(char));

	printf("(1) Iniciar Partida | (2) Voltar | (3) Exit\n");
	printf("Opcao: ");
	scanf_s(" %c",opcao, 1);

	while (*opcao != 49 && *opcao != 50 && *opcao != 51) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	return *opcao;
}

/***************************************************************************
*  Função: &Executa opcao regras
***************************************************************************/
void ExecutaOpcaoRegras (int opcaoRegras) {

	int opcaoInicio;
	
	switch (opcaoRegras){

		case 49: //iniciar partida
			IniciarPartida() ;
			break;

		case 50: //voltar
			opcaoInicio = PrintaOpcoesInicio();
			ExecutaOpcaoInicio (opcaoInicio);
			break;

		case 51: //exit
			exit(0);

	} //fim switch opcao inicio
}

/***************************************************************************
*  Função: &Printa opçoes jogadores
***************************************************************************/
int PrintaOpcoesJogadores() {

	char * opcao = (char*)malloc(sizeof(char));

	printf("Quantas pessoas irao jogar?\n");
	printf("(1) Dois jogadores | (2) Quatro jogadores | (3) Seis jogadores\n");
	printf("Opcao: ");
	scanf_s(" %c",opcao, 1);

	while (*opcao != 49 && *opcao != 50 && *opcao != 51) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	return *opcao;
}

/***************************************************************************
*  Função: &Executa opçao jogadores
***************************************************************************/
void ExecutaOpcaoJogadores (int opcaoJogadores, LIS_tppLista pCabecaBaralho) {

	int numJogadores;
	LIS_tppLista pCabecaMao1, pCabecaMao2, pCabecaMao3,
				 pCabecaMao4, pCabecaMao5, pCabecaMao6;

	switch(opcaoJogadores) {

		case 49: //2 jogadores
			numJogadores = 2;
			pCabecaMao1 = MES_CriarMao() ;
			pCabecaMao2 = MES_CriarMao() ;
			MES_DistribuirMaos( pCabecaBaralho, 
								pCabecaMao1, pCabecaMao2, NULL,
								NULL, NULL, NULL, numJogadores) ;
			break;

		case 50: // 4 jogadores
			numJogadores = 4;
			pCabecaMao1 = MES_CriarMao() ;
			pCabecaMao2 = MES_CriarMao() ;
			pCabecaMao3 = MES_CriarMao() ;
			pCabecaMao4 = MES_CriarMao() ;
			MES_DistribuirMaos( pCabecaBaralho, 
								pCabecaMao1, pCabecaMao2, pCabecaMao3,
								pCabecaMao4, NULL, NULL, numJogadores) ;
			break;

		case 51: // 6 jogadores
			numJogadores = 6;
			pCabecaMao1 = MES_CriarMao() ;
			pCabecaMao2 = MES_CriarMao() ;
			pCabecaMao3 = MES_CriarMao() ;
			pCabecaMao4 = MES_CriarMao() ;
			pCabecaMao5 = MES_CriarMao() ;
			pCabecaMao6 = MES_CriarMao() ;
			MES_DistribuirMaos( pCabecaBaralho, 
								pCabecaMao1, pCabecaMao2, pCabecaMao3,
								pCabecaMao4, pCabecaMao5, pCabecaMao6, 
								numJogadores) ;
			break;

	} //fim switch opcao jogadores

}

void IniciarPartida() {

	int opcaoJogadores;

	//declara o vetor que armazena os ponteiros pras cartas
	BAR_tppCarta vtCartas[TAM] ;

	//variavel que armazena a condicao de retorno
	//da funcao que transfere cartas
	BAR_tpCondRet CondRetBaralho ;

	//declara ponteiros pras cabecas das listas
	LIS_tppLista pCabecaBaralho, pCabecaMesa;

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~ INICIAR PARTIDA ~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	//preenche um vetor com 40 cartas e embaralha os indices
	PreencheVetorCartas(vtCartas) ;
	EmbaralhaVetorCartas(vtCartas) ;

	//cria um baralho com 40 cartas
	pCabecaBaralho = BAR_CriarBaralho(vtCartas) ;

	//cria uma mesa sem cartas
	pCabecaMesa = MES_CriarMesa() ;

	//vira vai pra mesa
	CondRetBaralho = BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

	//determina quantos jogadores vao jogar
	opcaoJogadores = PrintaOpcoesJogadores() ;

	//distribui as cartas de acordo com a quantidade de jogadores
	ExecutaOpcaoJogadores(opcaoJogadores, pCabecaBaralho) ;

	PrintaMesa(pCabecaMesa) ;
}