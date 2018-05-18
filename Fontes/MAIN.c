#include "LISTA.h"
#include "BARALHO.h"
#include "MESA.h"
#include   <stdio.h>	//printf
#include   <stdlib.h>	//rand e srand
#include   <string.h>	//strcmp
#include   <time.h>
#include   <assert.h>

//1 PARTIDA formada por 12 RODADAS
//1 RODADA formada por 3 apostas
//1 APOSTA é uma jogada (apostar, dispensar, pedir truco, pedir seis, pedir doze, aceitar, correr)

//PODE PEDIR TRUCO MAS N PODE ESCONDER A CARTA NA PRIMEIRA RODADA

#define TAM 40

#define AUMENTOU_APOSTA 1
#define NAO_AUMENTOU_APOSTOU 0

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/

//criar e embaralhar vetor
void PreencherVetorCartas (BAR_tppCarta vtCartas[]) ;
void EmbaralharVetorCartas (BAR_tppCarta vtCartas[]) ;

//printar telas (com opcoes)
int PrintarTelaInicio () ;
int PrintarTelaRegras () ;
int PrintarTelaNumJogadores () ;
int PrintarTelaQuemComeca(int *quemComeca, LIS_tppLista pCabecaSuperior, int *valorRodada) ;
int PrintarTelaProximoJogador(int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores, int *valorRodada) ;

//printar listas
//void PrintarBaralho (LIS_tppLista pCabecaBaralho) ;
void PrintarLixo (LIS_tppLista pCabecaLixo) ;
void PrintarMesa (LIS_tppLista pCabecaMesa) ;
void PrintarMao (LIS_tppLista pCabecaMao) ;

//executar opcoes
void ExecutarOpcaoInicio(char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) ;
void ExecutarOpcaoRegras(char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) ;
void ExecutarOpcaoNumJogadores( char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) ;
void ExecutarOpcaoQuemComeca( char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior) ;
void ExecutarOpcaoProximoJogador( char *opcao, int *quemComeca, int *valorRodada, LIS_tppLista pCabecaSuperior) ;

/**************************************************************************/

BAR_tppCarta VetorAux[TAM];

int main (void) {

	//aloca memória para todas listas do jogo
	LIS_tppLista pCabecaSuperior = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//aloca memoria para ponteiros
	char * opcao = (char*)malloc(sizeof(char)) ;
	int * quemComeca = (int*)malloc(sizeof(int)) ;
	int * valorRodada = (int*)malloc(sizeof(int)) ;
	int * numJogadores = (int*)malloc(sizeof(int)) ;
	int numJogadas, AptosRodada, BptosRodada, AptosPartida, BptosPartida ;

	//cria e embaralha um vetor de cartas
	PreencherVetorCartas(VetorAux) ;
	EmbaralharVetorCartas(VetorAux) ;

	//cria a cabeça da lista de listas
	pCabecaSuperior = LIS_CriarLista(BAR_DestruirBaralho) ;

	//cria a lista baralho preenchida com as cartas embaralhadas
	pCabecaBaralho = BAR_CriarBaralho(VetorAux) ;

	//cria as 6 maos (vazias)
	pCabecaMao1 = MES_CriarMao() ;
	pCabecaMao2 = MES_CriarMao() ;
	pCabecaMao3 = MES_CriarMao() ;
	pCabecaMao4 = MES_CriarMao() ;
	pCabecaMao5 = MES_CriarMao() ;
	pCabecaMao6 = MES_CriarMao() ;

	//cria a mesa (vazia)
	pCabecaMesa = MES_CriarMesa() ;

	//cria o lixo (vazio)
	pCabecaLixo = LIS_CriarLista(BAR_DestruirBaralho) ;

	//insere as listas (baralho, maos, lixo e mesa) na lista de listas
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaBaralho) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao1) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao2) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao3) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao4) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao5) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao6) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaLixo) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMesa) ;

	//primeira aposta da primeira rodada começa
	*valorRodada = 1;

	//transfere a vira do baralho pra mesa
	BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

	//imprime a tela de abertura do jogo
	*opcao = PrintarTelaInicio() ;
	ExecutarOpcaoInicio(opcao, quemComeca, pCabecaSuperior, numJogadores) ;

	//após distribuir a vira e as maos e definir quem comeca
	//imprime a tela da primeira rodada/jogada
	*opcao = PrintarTelaQuemComeca(quemComeca, pCabecaSuperior, valorRodada) ;
	ExecutarOpcaoQuemComeca(opcao, quemComeca, pCabecaSuperior) ;

	//após a primeira jogada do primeiro jogador
	//imprime a tela da proxima jogada
	for (numJogadas = 1 ; numJogadas < *numJogadores ; numJogadas++) {

		*opcao = PrintarTelaProximoJogador(quemComeca, pCabecaSuperior, numJogadores, valorRodada) ;
		if (*opcao == 55) {

			switch(*valorRodada) {
			case 1: *valorRodada = 3; break;
			case 3: *valorRodada = 6; break;
			case 6: *valorRodada = 12; break;
			}

			*opcao = PrintarTelaCorrerAceitarAumentar(quemComeca, pCabecaSuperior, numJogadores, valorRodada) ;
			//ExecutarOpcaoCorrerAceitarAumentar(opcao, quemComeca, pCabecaSuperior) ;
		}
		else {
		ExecutarOpcaoProximoJogador(opcao, quemComeca, valorRodada, pCabecaSuperior) ;
		}


		//checa se a carta apostada ganha das cartas que ja estavam na mesa

	}

	//checagem dos resultados
	system("cls");
	PrintarMesa(pCabecaMesa) ;
	printf("\n JOGADOR 1:") ;
	PrintarMao(pCabecaMao1);
	printf("\n JOGADOR 2:") ;
	PrintarMao(pCabecaMao2);
	printf("\n JOGADOR 3:") ;
	PrintarMao(pCabecaMao3);
	printf("\n JOGADOR 4:") ;
	PrintarMao(pCabecaMao4);
	printf("\n JOGADOR 5:") ;
	PrintarMao(pCabecaMao5);
	printf("\n JOGADOR 6:") ;
	PrintarMao(pCabecaMao6);
	PrintarLixo(pCabecaLixo) ;

	
	return 0;
}


/*********************** FUNÇÕES DO VETOR CARTAS **************************/
/***************************************************************************
*  Função: &Preencher vetor cartas
***************************************************************************/
void PreencherVetorCartas (BAR_tppCarta vtCartas[]) {
	
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
*  Função: &Embaralhar vetor cartas
***************************************************************************/
void EmbaralharVetorCartas (BAR_tppCarta vtCartas[]) {

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


/**************** FUNÇÕES DE IMPRESSAO DE LISTAS NA TELA ******************/
/***************************************************************************
*  Função: &Printar baralho
***************************************************************************/
void PrintarBaralho (LIS_tppLista pCabecaBaralho) {

	int i, qtdCartas, valorInt, naipeInt;

	//string que representa o valor
	char * valorStr = (char*)malloc(sizeof(char));

	//string que representa o naipe
	char * naipeStr = (char*)malloc(sizeof(char));

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	LIS_IrInicioLista(pCabecaBaralho);

	//obtem a quantidade de elementos na mao
	qtdCartas = LIS_ObterQtdElem(pCabecaBaralho);
	
	//printando as cartas
	printf("\n BARALHO:\n") ;
	for(i = 0; i < qtdCartas; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaBaralho);

		//obtem valor e naipe
		valorInt = (int)BAR_ObterValor (pCarta);
		naipeInt = (int)BAR_ObterNaipe (pCarta);

		switch (valorInt) {
		case (0): valorStr = "4"; break;
		case (1): valorStr = "5"; break;
		case (2): valorStr = "6"; break;
		case (3): valorStr = "7"; break;
		case (4): valorStr = "Q"; break;
		case (5): valorStr = "J"; break;
		case (6): valorStr = "K"; break;
		case (7): valorStr = "A"; break;
		case (8): valorStr = "2"; break;
		case (9): valorStr = "3"; break;
		}

		switch (naipeInt) {
		case (0): naipeStr = "Ouros"; break;
		case (1): naipeStr = "Espadas"; break;
		case (2): naipeStr = "Copas"; break;
		case (3): naipeStr = "Paus"; break;
		}

		//printando a carta
		printf (" %d) %s de %s\n", i+1, valorStr, naipeStr);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaBaralho, 1) ;

	}//fim for

} /***************** Fim função: &Printa baralho *************************/

/***************************************************************************
*  Função: &Printar mesa
***************************************************************************/
void PrintarMesa (LIS_tppLista pCabecaMesa) {
	
	int i, qtdCartas, valorInt, naipeInt;

	//string que representa o valor
	char * valorStr = (char*)malloc(sizeof(char));

	//string que representa o naipe
	char * naipeStr = (char*)malloc(sizeof(char));

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	LIS_IrInicioLista(pCabecaMesa);

	//obtendo a quantidade de cartas na mesa
	qtdCartas = LIS_ObterQtdElem(pCabecaMesa) ;

	for(i = 0; i < qtdCartas; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaMesa);

		//obtem valor e naipe
		valorInt = (int)BAR_ObterValor (pCarta);
		naipeInt = (int)BAR_ObterNaipe (pCarta);

		switch (valorInt) {
		case (0): valorStr = "4"; break;
		case (1): valorStr = "5"; break;
		case (2): valorStr = "6"; break;
		case (3): valorStr = "7"; break;
		case (4): valorStr = "Q"; break;
		case (5): valorStr = "J"; break;
		case (6): valorStr = "K"; break;
		case (7): valorStr = "A"; break;
		case (8): valorStr = "2"; break;
		case (9): valorStr = "3"; break;
		}

		switch (naipeInt) {
		case (0): naipeStr = "Ouros"; break;
		case (1): naipeStr = "Espadas"; break;
		case (2): naipeStr = "Copas"; break;
		case (3): naipeStr = "Paus"; break;
		}

		if (i == 0) {
			printf ("      MESA:\n") ;
			printf ("  VIRA - %s de %s\n", valorStr, naipeStr);
		}
		else {
			printf (" CARTA - %s de %s\n", valorStr, naipeStr);
		}

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;

	}//fim for

} /***************** Fim função: &Printa mesa *************************/

/***************************************************************************
*  Função: &Printar mao
***************************************************************************/
void PrintarMao (LIS_tppLista pCabecaMao) {

	int i, qtdCartas, valorInt, naipeInt;

	//string que representa o valor
	char * valorStr = (char*)malloc(sizeof(char));

	//string que representa o naipe
	char * naipeStr = (char*)malloc(sizeof(char));

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	LIS_IrInicioLista(pCabecaMao);

	//obtem a quantidade de elementos na mao
	qtdCartas = LIS_ObterQtdElem(pCabecaMao);
	
	//printando as cartas
	printf("\n      MAO:\n") ;
	for(i = 0; i < qtdCartas; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaMao);

		//obtem valor e naipe
		valorInt = (int)BAR_ObterValor (pCarta);
		naipeInt = (int)BAR_ObterNaipe (pCarta);

		switch (valorInt) {
		case (0): valorStr = "4"; break;
		case (1): valorStr = "5"; break;
		case (2): valorStr = "6"; break;
		case (3): valorStr = "7"; break;
		case (4): valorStr = "Q"; break;
		case (5): valorStr = "J"; break;
		case (6): valorStr = "K"; break;
		case (7): valorStr = "A"; break;
		case (8): valorStr = "2"; break;
		case (9): valorStr = "3"; break;
		}

		switch (naipeInt) {
		case (0): naipeStr = "Ouros"; break;
		case (1): naipeStr = "Espadas"; break;
		case (2): naipeStr = "Copas"; break;
		case (3): naipeStr = "Paus"; break;
		}

		//printando a carta
		printf (" %d) %s de %s\n", i+1, valorStr, naipeStr);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaMao, 1) ;

	}//fim for

} /***************** Fim função: &Printa mao *************************/

/***************************************************************************
*  Função: &Printar lixo
***************************************************************************/
void PrintarLixo (LIS_tppLista pCabecaLixo) {

	int i, qtdCartas, valorInt, naipeInt;

	//string que representa o valor
	char * valorStr = (char*)malloc(sizeof(char));

	//string que representa o naipe
	char * naipeStr = (char*)malloc(sizeof(char));

	//condicao de retorno da manipulacao da lista
	LIS_tpCondRet CondRetLis;

	//declarando ponteiro temporario pra carta
	BAR_tppCarta pCarta;

	//elemento corrente passa a ser o primeiro
	LIS_IrInicioLista(pCabecaLixo);

	//obtem a quantidade de elementos na mao
	qtdCartas = LIS_ObterQtdElem(pCabecaLixo);
	
	//printando as cartas
	printf("\n      LIXO:\n") ;
	for(i = 0; i < qtdCartas; i++) {

		//obtem o ponteiro pra uma carta
		pCarta = BAR_ObterCartaCorr (pCabecaLixo);

		//obtem valor e naipe
		valorInt = (int)BAR_ObterValor (pCarta);
		naipeInt = (int)BAR_ObterNaipe (pCarta);

		switch (valorInt) {
		case (0): valorStr = "4"; break;
		case (1): valorStr = "5"; break;
		case (2): valorStr = "6"; break;
		case (3): valorStr = "7"; break;
		case (4): valorStr = "Q"; break;
		case (5): valorStr = "J"; break;
		case (6): valorStr = "K"; break;
		case (7): valorStr = "A"; break;
		case (8): valorStr = "2"; break;
		case (9): valorStr = "3"; break;
		}

		switch (naipeInt) {
		case (0): naipeStr = "Ouros"; break;
		case (1): naipeStr = "Espadas"; break;
		case (2): naipeStr = "Copas"; break;
		case (3): naipeStr = "Paus"; break;
		}

		//printando a carta
		printf (" %d) %s de %s\n", i+1, valorStr, naipeStr);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaLixo, 1) ;

	}//fim for

} /***************** Fim função: &Printa lixo *************************/


/********************* FUNÇÕES DE IMPRESSAO DE TELAS **********************/
/***************************************************************************
*  Função: &Printar tela inicial
***************************************************************************/
int PrintarTelaInicio () {

	char * opcao = (char*)malloc(sizeof(char));

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" O que deseja fazer?\n\n");
	printf(" (1) Iniciar partida | (2) Ver regras | (3) Sair\n\n");
	printf(" Opcao: ");
	scanf_s(" %c", opcao, 1);

	while (*opcao != 49 && *opcao != 50 && *opcao != 51) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	return *opcao;
}

/***************************************************************************
*  Função: &Printar tela de regras
***************************************************************************/
int PrintarTelaRegras() {

	char * opcao = (char*)malloc(sizeof(char));

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	printf(" FORCA DAS CARTAS:      FORCA DOS NAIPES:\n\n");
	printf(" 4 (mais fraca)         Ouros (mais fraco)\n");
	printf(" 5                      Espadas\n");
	printf(" 6                      Copas\n");
	printf(" 7                      Paus  (mais forte)\n");
	printf(" Q\n");
	printf(" J\n");
	printf(" K\n");
	printf(" A\n");
	printf(" 2\n");
	printf(" 3 (mais forte)\n\n");

	printf("\n O que deseja fazer?\n\n");
	printf(" (1) Voltar | (2) Sair\n\n");
	printf(" Opcao: ");
	scanf_s(" %c",opcao, 1);

	while (*opcao != 49 && *opcao != 50) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");

	return *opcao;

}

/***************************************************************************
*  Função: &Printar tela de numero de jogadores
***************************************************************************/
int PrintarTelaNumJogadores () {

	char * opcao = (char*)malloc(sizeof(char));

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" Quantas pessoas irao jogar?\n\n");
	printf(" (1) Dois jogadores | (2) Quatro jogadores | (3) Seis jogadores\n\n");
	printf(" Opcao: ");
	scanf_s(" %c", opcao, 1);

	while (*opcao != 49 && *opcao != 50 && *opcao != 51) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	return *opcao;
}

/***************************************************************************
*  Função: &Printar tela de quem comeca
***************************************************************************/
int PrintarTelaQuemComeca(int *quemComeca, LIS_tppLista pCabecaSuperior, int *valorRodada) {

	char * ok = (char*)malloc(sizeof(char)) ;
	char * opcao = (char*)malloc(sizeof(char)) ;

	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrInicioLista(pCabecaSuperior) ;

	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//tela de confirmacao
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemComeca) {
	case 1: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 2: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 3: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 4: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 5: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 6: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" Jogador %d comeca (nao deixe que ninguem veja suas cartas).\n\n", *quemComeca) ;
	printf(" Digite 'ok' para ver a mesa e sua mao.\n\n ") ;
	scanf_s(" %s", ok, 4);
	system("cls");

	//proxima tela
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemComeca) {
	case 1: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 2: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 3: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 4: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 5: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 6: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	PrintarMesa(pCabecaMesa) ;
	PrintarMao(pCabecaMao) ;

	printf("\n Valor da rodada: %d\n", *valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;
	printf(" (1) Apostar carta 1   | (2) Apostar carta 2   | (3) Apostar carta 3\n") ;

	if (LIS_ObterQtdElem(pCabecaMao) < 3) {

		printf(" (4) Dispensar carta 1   | (5) Dispensar carta 2   | (6) Dispensar carta 3\n") ;
		switch (*valorRodada) {
		case 1: printf(" (7) Pedir truco\n\n"); break;
		case 3: printf(" (7) Pedir seis\n\n"); break;
		case 6: printf(" (7) Pedir doze\n\n"); break;
		}

	} //fim if

	else {

		switch (*valorRodada) {
		case 1: printf(" (4) Pedir truco\n\n"); break;
		case 3: printf(" (4) Pedir seis\n\n"); break;
		case 6: printf(" (4) Pedir doze\n\n"); break;
		} //fim switch
	} //fim else

	printf(" Opcao: ") ;
	scanf_s(" %c", opcao, 1) ;

	while (*opcao < 49 && *opcao > 52) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls") ;
	return *opcao ;

}

/***************************************************************************
*  Função: &Printar tela do proximo jogador
***************************************************************************/
int PrintarTelaProximoJogador(int * quemComeca, LIS_tppLista pCabecaSuperior,
							  int *numJogadores, int *valorRodada) {

	char * ok = (char*)malloc(sizeof(char)) ;
	char * opcao = (char*)malloc(sizeof(char)) ;

	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrInicioLista(pCabecaSuperior) ;

	if (*quemComeca == *numJogadores) {
		*quemComeca = 1 ;
	}
	else {
		*quemComeca += 1;
	}

	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//tela de confirmacao
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemComeca) {
	case 1: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 2: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 3: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 4: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 5: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 6: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" Digite 'ok' para ver a mesa e sua mao.\n\n ") ;
	scanf_s(" %s", ok, 4);
	system("cls");

	//proxima tela
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemComeca) {
	case 1: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 2: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 3: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 4: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 5: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 6: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	PrintarMesa(pCabecaMesa) ;
	PrintarMao(pCabecaMao) ;

	printf("\n Valor da rodada: %d\n", *valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;
	printf(" (1) Apostar carta 1   | (2) Apostar carta 2   | (3) Apostar carta 3\n") ;
	printf(" (4) Dispensar carta 1 | (5) Dispensar carta 2 | (6) Dispensar carta 3\n") ;

	switch (*valorRodada) {
	case 1: printf(" (7) Pedir truco\n\n"); break;
	case 3: printf(" (7) Pedir seis\n\n"); break;
	case 6: printf(" (7) Pedir doze\n\n"); break;
	}

	printf(" Opcao: ") ;
	scanf_s(" %c", opcao, 1) ;

	while (*opcao < 49 && *opcao > 55) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls") ;
	return *opcao ;

}

/***************************************************************************
*  Função: &Printar tela de correr, aceitar ou aumentar
***************************************************************************/
int PrintarTelaCorrerAceitarAumentar(int * quemComeca, LIS_tppLista pCabecaSuperior,
									 int *numJogadores, int *valorRodada) {

	//aloca memoria pra opcao de jogada escolhida										
	char * opcao = (char*)malloc(sizeof(char)) ;

	//declara e aloca memoria pras cabecas de mao de uma só equipe e da mesa
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//armazena ponteiro pra cabeca da lista mesa em pCabecaMesa
	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//quemComeca passa a ser o jogador seguinte
	if (*quemComeca == *numJogadores) {
		*quemComeca = 1 ;
	}
	else {
		*quemComeca += 1;
	}

	//printa cabeçalho da tela
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemComeca) {
	case 1: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 2: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 3: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 4: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 5: printf("~~~~~~~~~~~~ EQUIPE A JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	case 6: printf("~~~~~~~~~~~~ EQUIPE B JOGADOR %d ~~~~~~~~~~~\n", *quemComeca); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
	pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	PrintarMesa(pCabecaMesa) ;
	PrintarMao(pCabecaMao1) ;

	switch(*quemComeca) {

	case 1: //armazena a lista mao do jogador 3 e do jogador 5
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		break ;
	
	case 2: //armazena a lista mao do jogador 4 e do jogador 6
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		break ;

	case 3: //armazena a lista mao do jogador 5 e do jogador 1
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_IrInicioLista(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		break ;

	case 4: //armazena a lista mao do jogador 6 e do jogador 2
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_IrInicioLista(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		break ;

	case 5: //armazena a lista mao do jogador 1 e do jogador 3
		LIS_IrInicioLista(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		break ;

	case 6: //armazena a lista mao do jogador 2 e do jogador 4
		LIS_IrInicioLista(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
		pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		break ;
	}

	printf("\n Valor da rodada: %d\n", *valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;
	printf(" (1) Correr   | (2) Aceitar   |") ;

	switch (*valorRodada) {
	case 1: printf(" (3) Pedir seis\n\n"); break;
	case 3: printf(" (3) Pedir doze\n\n"); break;
	}

	printf(" Opcao: ") ;
	scanf_s(" %c", opcao, 1) ;

	while (*opcao < 49 && *opcao > 52) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls") ;
	return *opcao ;

}


/********************* FUNÇÕES DE EXECUCAO DE OPÇÕES **********************/
/***************************************************************************
*  Função: &Executar opcao da tela de inicio
***************************************************************************/
void ExecutarOpcaoInicio (char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) {

	switch(*opcao) {
	case 49: //(1) iniciar partida
		*opcao = PrintarTelaNumJogadores ();
		ExecutarOpcaoNumJogadores(opcao, quemComeca, pCabecaSuperior, numJogadores);
		break;
	case 50: //(2) ver regras
		*opcao = PrintarTelaRegras(); 
		ExecutarOpcaoRegras(opcao, quemComeca, pCabecaSuperior, numJogadores);
		break;
	case 51: //(3) sair
		exit(0);
		break;
	}

}

/***************************************************************************
*  Função: &Executar opcao da tela de regras
***************************************************************************/
void ExecutarOpcaoRegras (char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) {

	switch(*opcao) {
	case 49: //(1) voltar
		*opcao = PrintarTelaInicio();
		ExecutarOpcaoInicio(opcao, quemComeca, pCabecaSuperior, numJogadores);
		break;
	case 50: //(2) sair
		exit(0);
		break;
	}
}

/***************************************************************************
*  Função: &Executar opcao da tela de numero de jogadores
***************************************************************************/
void ExecutarOpcaoNumJogadores(char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) {

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrInicioLista(pCabecaSuperior) ;
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

	LIS_IrInicioLista(pCabecaSuperior) ;

	switch(*opcao) {
	case 49: //2 jogadores

		*numJogadores = 2 ;

		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao1) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMao2) ;

		*quemComeca = 1 + (rand() % 2) ;

		break;

	case 50: //4 jogadores

		*numJogadores = 4 ;

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

		*quemComeca = 1 + (rand() % 4) ;
		break;

	case 51: //6 jogadores

		*numJogadores = 6 ;

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

		*quemComeca = 1 + (rand() % 6) ;
		break;
		
	} //fim switch *opcao numJogadores

}

/***************************************************************************
*  Função: &Executar opcao da tela de quem comeca
***************************************************************************/
void ExecutarOpcaoQuemComeca(char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior) {

	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	switch(*opcao) {
	case 49: //(1) apostar carta 1

		LIS_IrInicioLista(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
		pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

		LIS_IrInicioLista(pCabecaMao) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;

		break;

	case 50: //(2) apostar carta 2
		
		LIS_IrInicioLista(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
		pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

		LIS_IrInicioLista(pCabecaMao) ;
		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;

		break;

	case 51: //(3) apostar carta 3
		
		LIS_IrInicioLista(pCabecaSuperior) ;
		LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
		pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

		LIS_IrInicioLista(pCabecaMao) ;
		LIS_AvancarElementoCorrente(pCabecaMao, 2) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;

		break;
	} //fim switch

}

/***************************************************************************
*  Função: &Executar opcao da tela do proximo jogador
***************************************************************************/
void ExecutarOpcaoProximoJogador(char *opcao, int *quemComeca, int *valorRodada,
								 LIS_tppLista pCabecaSuperior) {
	int valorRodadaAnterior ;

	//declarando e alocando espaco pra mao, mesa e lixo
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//armazenando ponteiro pra lista lixo no pCabecaLixo
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, 7) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//armazenando ponteiro pra lista mesa no pCabecaMesa
	LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//armazenando ponteiro pra lista mao de quem vai fazer a jogada no pCabecaMao
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_IrInicioLista(pCabecaMao) ;

	switch(*opcao) {

	case 49: //(1) apostar carta 1

		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		break;

	case 50: //(2) apostar carta 2
	
		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		break;

	case 51: //(3) apostar carta 3
		
		LIS_AvancarElementoCorrente(pCabecaMao, 2) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		break;

	case 52: //(4) dispensar carta 1

		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		break;

	case 53: //(5) dispensar carta 2

		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		break;

	case 54: //(6) dispensar carta 3

		LIS_AvancarElementoCorrente(pCabecaMao, 2) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		break;

	case 55: //(7) pedir truco, seis, doze

		valorRodadaAnterior = *valorRodada;

		switch (valorRodadaAnterior) {
		case 1: *valorRodada = 3; break;
		case 3: *valorRodada = 6; break;
		case 6: *valorRodada = 12; break;
		}
		break;

	} //fim switch*/

}