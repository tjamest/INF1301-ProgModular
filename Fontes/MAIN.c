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
//1 APOSTA é uma jogada

//TODO MUNDO PODE PEDIR TRUCO MAS N PODE ESCONDER A CARTA NA PRIMEIRA RODADA

#define TAM 40

#define EQUIPE_IMPAR 1
#define EQUIPE_PAR 0

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/

//criar e embaralhar vetor
void PreencherVetorCartas (BAR_tppCarta vtCartas[]) ;
void EmbaralharVetorCartas (BAR_tppCarta vtCartas[]) ;
void DeterminarVencedorDaRodada (LIS_tppLista pCabecaMesa, int *quemComeca, int *numJogadores,
								 int *pontosRodadaPar, int *pontosRodadaImpar) ;
int CompararCartas2Jogadres (LIS_tppLista pCabecaMesa, int *quemComeca) ;

//printar listas
void PrintarBaralho (LIS_tppLista pCabecaBaralho) ;
void PrintarLixo (LIS_tppLista pCabecaLixo) ;
void PrintarMesa (LIS_tppLista pCabecaMesa) ;
void PrintarMao (LIS_tppLista pCabecaMao) ;

//printar telas (com opcoes)
int PrintarTelaInicio () ;
int PrintarTelaRegras () ;
int PrintarTelaNumJogadores () ;
int PrintarTelaRodada(int *quemComeca, int *numJogadores, int *valorRodada, int *vencedorAtual,
					  int *pontosRodadaPar, int *pontosRodadaImpar,
					  int *pontosPartidaPar, int *pontosPartidaImpar, LIS_tppLista pCabecaSuperior) ;

//executar opcoes
void ExecutarOpcaoInicio(char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) ;
void ExecutarOpcaoRegras(char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) ;
void ExecutarOpcaoNumJogadores(char *opcao, int *quemComeca, LIS_tppLista pCabecaSuperior, int *numJogadores) ;
void ExecutarOpcaoRodada(char *opcao, int *quemComeca, int *numJogadores, 
						 int *pontosRodadaPar, int *pontosRodadaImpar, LIS_tppLista pCabecaSuperior) ;

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
	int * vencedorAtual = (int*)malloc(sizeof(int)) ;
	int * pontosRodadaPar = (int*)malloc(sizeof(int)) ;
	int * pontosRodadaImpar = (int*)malloc(sizeof(int)) ;
	int * pontosPartidaPar = (int*)malloc(sizeof(int)) ;
	int * pontosPartidaImpar = (int*)malloc(sizeof(int)) ;

	int i;
	BAR_tpCondRet condRetBar ;

	*pontosRodadaPar = 0 ;
	*pontosRodadaImpar = 0 ;
	*pontosPartidaPar = 0 ;
	*pontosPartidaImpar = 0 ;

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
	condRetBar = BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

	//imprime a tela de abertura do jogo
	*opcao = PrintarTelaInicio() ;
	ExecutarOpcaoInicio(opcao, quemComeca, pCabecaSuperior, numJogadores) ;

	//após distribuir a vira e as maos e definir quem comeca
	while (*pontosRodadaPar != 2 && *pontosRodadaImpar != 2) {

		//jogadores apostam
		for (i = 0; i < *numJogadores; i++) {

			//imprime a tela da rodada
			*opcao = PrintarTelaRodada(quemComeca, numJogadores, valorRodada, vencedorAtual,
									   pontosRodadaPar, pontosRodadaImpar,
									   pontosPartidaPar, pontosPartidaImpar, pCabecaSuperior) ;

			//executa a jogada do jogador
			ExecutarOpcaoRodada(opcao, quemComeca, numJogadores, pontosRodadaPar,
								pontosRodadaImpar, pCabecaSuperior) ;

			//atualiza quem joga
			if (*quemComeca == *numJogadores) {
				*quemComeca = 1 ;
			} //fim if
			else {
				*quemComeca += 1;
			} //fim else

		} //fim for

		//cartas apostadas vao pro lixo
		for (i = 0; i < *numJogadores; i++) {
			LIS_IrFinalLista(pCabecaMesa);
			condRetBar = BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
		}

	} //fim while

	//atualiza pontuacao da partida
	if (*pontosRodadaPar == 2) {
		*pontosPartidaPar += *valorRodada ;
	} //fim if
	else {
		*pontosPartidaImpar += *valorRodada ;
	} //fim else

	//checagem dos resultados
	system("cls");
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " Equipe Par                 Equipe Impar\n") ;
	printf(		   " Partida: %d/12              Partida: %d/12\n", *pontosPartidaPar, *pontosPartidaImpar) ;
	printf(		   " Rodada: %d/2                Rodada: %d/2\n", *pontosRodadaPar, *pontosRodadaImpar) ;
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	PrintarMesa(pCabecaMesa) ;
	printf("\n JOGADOR 1:") ;
	PrintarMao(pCabecaMao1) ;
	printf("\n JOGADOR 2:") ;
	PrintarMao(pCabecaMao2) ;/*
	printf("\n JOGADOR 3:") ;
	PrintarMao(pCabecaMao3) ;
	printf("\n JOGADOR 4:") ;
	PrintarMao(pCabecaMao4) ;
	printf("\n JOGADOR 5:") ;
	PrintarMao(pCabecaMao5) ;
	printf("\n JOGADOR 6:") ;
	PrintarMao(pCabecaMao6) ;*/
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

} /***************** Fim função: &Preencher vetor cartas *******************/

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

} /***************** Fim função: &Embaralhar vetor cartas ******************/

/***************************************************************************
*  Função: &Comparar cartas em um jogo de 2 jogadores
***************************************************************************/
int CompararCartas2Jogadores (LIS_tppLista pCabecaMesa, int *quemComeca) {

	BAR_tppCarta pVira = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pAposta = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCarta = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;

	int i, qtdCartasNaMesa ;
	int apostadorVenceu = 0 ;

	BAR_tpCondRet condRetBar ;

	BAR_tpValorCarta valorAposta, valorCarta ;
	BAR_tpNaipeCarta naipeAposta, naipeCarta ;

	qtdCartasNaMesa = LIS_ObterQtdElem(pCabecaMesa) ;

	LIS_IrInicioLista(pCabecaMesa) ;
	pVira = BAR_ObterCartaCorr(pCabecaMesa) ;

	LIS_IrFinalLista(pCabecaMesa) ;
	pAposta = BAR_ObterCartaCorr(pCabecaMesa) ;

	condRetBar = BAR_VerificarSeEhManilha(pAposta, pVira) ;

	//CARTA APOSTADA == MANILHA
	if (condRetBar == BAR_CondRetEhManilha) {

		LIS_IrInicioLista(pCabecaMesa) ;

		for (i = 2 ; i < qtdCartasNaMesa ; i++ ) {

			LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;
			pCarta = BAR_ObterCartaCorr(pCabecaMesa) ;

			condRetBar = BAR_VerificarSeEhManilha(pCarta, pVira) ;

			//CARTA DA MESA == MANILHA (tem que comparar naipes)
			if (condRetBar == BAR_CondRetEhManilha) {

				naipeAposta = BAR_ObterNaipe(pAposta) ;
				naipeCarta = BAR_ObterNaipe(pCarta) ;

				if ((int)naipeAposta > (int)naipeCarta) {
					apostadorVenceu += 1 ;
				}
				else {
					apostadorVenceu += 0 ;
				}

			} //fim if

			//CARTA DA MESA != MANILHA (apostador venceu)
			else {
				apostadorVenceu += 1 ;
			} //fim else

		} //fim for

		//se o apostador venceu todas cartas da mesa
		if (apostadorVenceu == (qtdCartasNaMesa - 2)) {
			if ((*quemComeca % 2) == 0) { return EQUIPE_PAR ; }
			else { return EQUIPE_IMPAR ; }
		} //fim if

		//se o apostador nao venceu todas cartas da mesa
		else {
			if ((*quemComeca % 2) == 0) { return EQUIPE_IMPAR ; }
			else { return EQUIPE_PAR ; }
		} //fim else
	} //fim if

	//CARTA APOSTADA != MANILHA
	else {

		LIS_IrInicioLista(pCabecaMesa) ;

		for (i = 2 ; i < qtdCartasNaMesa ; i++ ) {

			LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;
			pCarta = BAR_ObterCartaCorr(pCabecaMesa) ;

			//verifica se a carta na mesa é manilha
			condRetBar = BAR_VerificarSeEhManilha(pCarta, pVira) ;

			//CARTA DA MESA != MANILHA (tem que comparar valores)
			if (condRetBar == BAR_CondRetNaoEhManilha) {
				
				valorAposta = BAR_ObterValor(pAposta) ;
				valorCarta = BAR_ObterValor(pCarta) ;

				if ((int)valorAposta > (int)valorCarta) {
					apostadorVenceu += 1 ;
				} //fim if

			} //fim if

		} //fim for

		//se o apostador venceu todas cartas da mesa
		if (apostadorVenceu == (qtdCartasNaMesa - 2)) {
			if ((*quemComeca % 2) == 0) { 
				return EQUIPE_PAR ;
			}
			else { 
				return EQUIPE_IMPAR ;
			}
		} //fim if

		//se o apostador nao venceu todas cartas da mesa
		else {
			if ((*quemComeca % 2) == 0) { 
				return EQUIPE_IMPAR ;
			}
			else { 
				return EQUIPE_PAR ;
			}
		} //fim else

	} //fim else "se a carta apostada nao for manilha"
} /*************** Fim função: &Comparar cartas 2 jogadores ***************/

/***************************************************************************
*  Função: &Checar vencedor da rodada
***************************************************************************/
void DeterminarVencedorDaRodada (LIS_tppLista pCabecaMesa, int *quemComeca, int *numJogadores,
								 int *pontosRodadaPar, int *pontosRodadaImpar) {

	int qtdCartasNaMesa, equipeVencedora ;

	qtdCartasNaMesa = LIS_ObterQtdElem(pCabecaMesa) ;

	//caso nao seja a primeira aposta
	if (qtdCartasNaMesa > 2) {
		
		switch(*numJogadores) {

		case 2: 
			equipeVencedora = CompararCartas2Jogadores(pCabecaMesa, quemComeca) ;

			switch (equipeVencedora) {
			case 0:
				*pontosRodadaPar += 1 ;
				break ;
			case 1:
				*pontosRodadaImpar += 1 ;
				break ;
			} //fim switch

			break;

			/*
		case 4:
			equipeVencedora = CompararCartas2Jogadores(pCabecaMesa, quemComeca) ;
			return equipeVencedora ;
			break;

		case 6:
			equipeVencedora = CompararCartas2Jogadores(pCabecaMesa, quemComeca) ;
			return equipeVencedora ;
			break;
			*/
		} //fim switch

	} //fim if
} /***************** Fim função: &Checar vencedor da rodada ***************/


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
*  Função: &Printar tela da rodada
***************************************************************************/
int PrintarTelaRodada(int *quemComeca, int *numJogadores, int *valorRodada, int *vencedorAtual, 
					  int *pontosRodadaPar, int *pontosRodadaImpar, 
					  int *pontosPartidaPar, int *pontosPartidaImpar, LIS_tppLista pCabecaSuperior) {

	char * ok = (char*)malloc(sizeof(char)) ;
	char * opcao = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//inicio da rodada e da jogada
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	//tela de confirmacao
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemComeca) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemComeca); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemComeca); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemComeca); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemComeca); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemComeca); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemComeca); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" Jogador %d joga (nao deixe que ninguem veja suas cartas).\n\n", *quemComeca) ;
	printf(" Digite 'ok' para ver a mesa e sua mao.\n\n ") ;
	scanf_s(" %s", ok, 4);
	system("cls");

	//tela da jogada
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemComeca) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemComeca); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemComeca); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemComeca); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemComeca); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemComeca); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemComeca); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " Equipe Par                 Equipe Impar\n") ;
	printf(		   " Partida: %d/12              Partida: %d/12\n", *pontosPartidaPar, *pontosPartidaImpar) ;
	printf(		   " Rodada: %d/2                Rodada: %d/2\n", *pontosRodadaPar, *pontosRodadaImpar) ;
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	PrintarMesa(pCabecaMesa) ;
	PrintarMao(pCabecaMao) ;

	printf("\n Valor da rodada: %d", *valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;

	switch (LIS_ObterQtdElem(pCabecaMao)) {

	case 1: //1 carta na mao
		printf(" (1) Apostar carta 1\n") ;
		printf(" (4) Dispensar carta 1\n") ;

		switch (*valorRodada) {
		case 1: printf(" (7) Pedir truco\n\n"); break;
		case 3: printf(" (7) Pedir seis\n\n"); break;
		case 6: printf(" (7) Pedir doze\n\n"); break;
		} //fim switch

		printf(" Opcao: ") ;
		scanf_s(" %c", opcao, 1) ;

		while (*opcao != 49 && *opcao != 52 && *opcao != 55) {
			scanf_s(" %c", opcao, 1);
		} //fim while

		system("cls");
		break;

	case 2: //2 cartas na mao
		printf(" (1) Apostar carta 1   | (2) Apostar carta 2 \n") ;
		printf(" (4) Dispensar carta 1 | (5) Dispensar carta 2\n") ;

		switch (*valorRodada) {
		case 1: printf(" (7) Pedir truco\n\n"); break;
		case 3: printf(" (7) Pedir seis\n\n"); break;
		case 6: printf(" (7) Pedir doze\n\n"); break;
		} //fim switch

		printf(" Opcao: ") ;
		scanf_s(" %c", opcao, 1) ;

		while (*opcao != 49 && *opcao != 50 && *opcao != 52 && *opcao != 53 && *opcao != 55 ) {
			scanf_s(" %c", opcao, 1);
		} //fim while

		system("cls");
		break;

	case 3: //3 cartas na mao
		printf(" (1) Apostar carta 1   | (2) Apostar carta 2   | (3) Apostar carta 3\n") ;
		printf(" (4) Dispensar carta 1 | (5) Dispensar carta 2 | (6) Dispensar carta 3\n") ;

		switch (*valorRodada) {
		case 1: printf(" (7) Pedir truco\n\n"); break;
		case 3: printf(" (7) Pedir seis\n\n"); break;
		case 6: printf(" (7) Pedir doze\n\n"); break;
		} //fim switch

		printf(" Opcao: ") ;
		scanf_s(" %c", opcao, 1) ;

		while (*opcao < 49 && *opcao > 55) {
			scanf_s(" %c", opcao, 1);
		} //fim while

		system("cls");
		break;

	} //fim switch

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
void ExecutarOpcaoRodada(char *opcao, int *quemComeca, int *numJogadores,
						 int *pontosRodadaPar, int *pontosRodadaImpar, LIS_tppLista pCabecaSuperior) {

	//declarando ponteiros e alocando pras cabecas da mao, mesa e lixo
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//armazenando ponteiro pra lista mesa e lista lixo
	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//armazenando ponteiro pra lista mao de quem vai fazer a jogada no pCabecaMao
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemComeca) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_IrInicioLista(pCabecaMao) ;

	switch(*opcao) {

	case 49: //(1) apostar carta 1
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		DeterminarVencedorDaRodada(pCabecaMesa, quemComeca, numJogadores, pontosRodadaPar, pontosRodadaImpar) ;
		break;

	case 50: //(2) apostar carta 2
		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		DeterminarVencedorDaRodada(pCabecaMesa, quemComeca, numJogadores, pontosRodadaPar, pontosRodadaImpar) ;
		break;

	case 51: //(3) apostar carta 3
		LIS_AvancarElementoCorrente(pCabecaMao, 2) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		DeterminarVencedorDaRodada(pCabecaMesa, quemComeca, numJogadores, pontosRodadaPar, pontosRodadaImpar) ;
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

	case 55: //(7) pedir truco/seis/doze
		//*opcao = PrintarTelaAumentouAposta() ;
		//ExecutarOpcaoAumentouAposta() ;
		break;

	} //fim switch

}