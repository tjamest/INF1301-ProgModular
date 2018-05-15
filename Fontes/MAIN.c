#include "LISTA.h"
#include "BARALHO.h"
#include "MESA.h"
#include   <stdio.h>	//printf
#include   <stdlib.h>	//rand e srand
#include   <string.h>	//strcmp
#include   <time.h>

#define TAM 40

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/

void PreencheVetorCartas(BAR_tppCarta vtCartas[]) ;
void EmbaralhaVetorCartas(BAR_tppCarta vtCartas[]) ;

void PrintaMesa(LIS_tppLista pCabecaMesa) ;
void PrintaMao(LIS_tppLista pCabecaMao) ;
void PrintaRegras() ;

void IniciarPartida () ;

int PrintaOpcoesInicio() ;
void ExecutaOpcaoInicio (int opcaoInicio) ;

int PrintaOpcoesJogadores() ;
void ExecutaOpcaoJogadores(int opcaoJogadores, 
						   LIS_tppLista pCabecaBaralho,
						   LIS_tppLista pCabecaMesa) ;

int PrintaOpcoesRegras();
void ExecutaOpcaoRegras();

int PrintaOpcoesPrimeiraJogada() ;
void ExecutaOpcaoPrimeiraJogada(int opcaoJogada,
								LIS_tppLista pCabecaMao, 
								LIS_tppLista pCabecaMesa) ;

/**************************************************************************/

BAR_tppCarta VetorAux[TAM];

/**************************************************************************/

int main (void) {

	int opcaoInicio ;

	//(1) iniciar, (2) regras, (3) sair
	opcaoInicio = PrintaOpcoesInicio() ;

	//cria vetor com cartas, embaralha o vetor
	//armazena as cartas na lista baralho
	//distribui as maos, transfere a vira pra mesa
	//sorteia quem começa
	//imprime a mesa e a mao
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
*  Função: &Printa mesa
***************************************************************************/
void PrintaMesa (LIS_tppLista pCabecaMesa) {
	
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

	//printando as cartas
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~~ MESA ~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
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
			printf (" VIRA - %s de %s\n", valorStr, naipeStr);
		}
		else {
			printf (" CARTA - %s de %s\n", valorStr, naipeStr);
		}

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;

	}//fim for

} /***************** Fim função: &Printa mesa *************************/

/***************************************************************************
*  Função: &Printa mao
***************************************************************************/
void PrintaMao (LIS_tppLista pCabecaMao) {
	
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
	printf("\n MAO:\n") ;
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
*  Função: &Printa regras
***************************************************************************/
void PrintaRegras() {

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~ REGRAS ~~~~~~~~~~~~~~~~~~\n");
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

}

/***************************************************************************
*  Função: &Printa opçoes inicio
***************************************************************************/
int PrintaOpcoesInicio () {

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

	printf("\n O que deseja fazer?\n\n");
	printf(" (1) Iniciar partida | (2) Voltar | (3) Sair\n\n");
	printf(" Opcao: ");
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
*  Função: &Iniciar partida
***************************************************************************/
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
	ExecutaOpcaoJogadores(opcaoJogadores, pCabecaBaralho, pCabecaMesa) ;
}

/***************************************************************************
*  Função: &Printa opçoes jogadores
***************************************************************************/
int PrintaOpcoesJogadores() {

	char * opcao = (char*)malloc(sizeof(char));

	printf(" Quantas pessoas irao jogar?\n\n");
	printf(" (1) Dois jogadores | (2) Quatro jogadores | (3) Seis jogadores\n\n");
	printf(" Opcao: ");
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
void ExecutaOpcaoJogadores (int opcaoJogadores, 
							LIS_tppLista pCabecaBaralho,
							LIS_tppLista pCabecaMesa) {

	int numJogadores, quemComeca, opcaoJogada;
	
	char * ok = (char*)malloc(sizeof(char)) ;
	LIS_tppLista pCabecaMao1, pCabecaMao2, pCabecaMao3,
				 pCabecaMao4, pCabecaMao5, pCabecaMao6;

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~ INICIAR PARTIDA ~~~~~~~~~~~~~\n") ;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	switch(opcaoJogadores) {

		case 49: //2 jogadores

			numJogadores = 2;

			pCabecaMao1 = MES_CriarMao() ;
			pCabecaMao2 = MES_CriarMao() ;

			MES_DistribuirMaos( pCabecaBaralho, 
								pCabecaMao1, pCabecaMao2, NULL,
								NULL, NULL, NULL, numJogadores) ;

			quemComeca = 1 + (rand() % 2) ;

			printf(" Jogador %d comeca (nao deixe que ninguem veja suas cartas).\n\n", quemComeca) ;
			printf(" Digite 'ok' para ver a mesa e sua mao.\n\n ") ;
			scanf_s(" %s", ok, 4);

			while (strcmp(ok, "ok") != 0) {
				scanf_s("%s", ok, 4);
			}

			system ("cls") ;
			PrintaMesa(pCabecaMesa) ;

			switch (quemComeca) {

			case 1: //primeiro jogador comeca
				PrintaMao(pCabecaMao1) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao1, pCabecaMesa) ;

				break;

			case 2: //segundo jogador comeca
				
				PrintaMao(pCabecaMao2) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;

				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao2, pCabecaMesa) ;

				break;
			}
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

			quemComeca = 1 + (rand() % 4) ;

			printf(" Jogador %d comeca (nao deixe que ninguem veja suas cartas).\n\n", quemComeca) ;
			printf(" Digite 'ok' para ver a mesa e sua mao.\n\n ") ;
			scanf_s(" %s", ok, 4);

			while (strcmp(ok, "ok") != 0) {
				scanf_s("%s", ok, 4);
			}

			system ("cls") ;
			PrintaMesa(pCabecaMesa) ;

			switch (quemComeca) {

			case 1: //primeiro jogador comeca
				
				PrintaMao(pCabecaMao1) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;

				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao1, pCabecaMesa) ;

				break;

			case 2: //segundo jogador comeca
				
				PrintaMao(pCabecaMao2) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao2, pCabecaMesa) ;

				break;

			case 3: //terceiro jogador comeca
				
				PrintaMao(pCabecaMao3) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;

				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao3, pCabecaMesa) ;

				break;

			case 4: //quarto jogador comeca
				
				PrintaMao(pCabecaMao4) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao4, pCabecaMesa) ;

				break;


			} //fim switch quemComeca
			break;

		case 51: // 6 jogadores
			
			numJogadores = 6;

			pCabecaMao1 = MES_CriarMao() ;
			pCabecaMao2 = MES_CriarMao() ;
			pCabecaMao3 = MES_CriarMao() ;
			pCabecaMao4 = MES_CriarMao() ;
			pCabecaMao5 = MES_CriarMao() ;
			pCabecaMao6 = MES_CriarMao() ;

			MES_DistribuirMaos( pCabecaBaralho, pCabecaMao1, pCabecaMao2, pCabecaMao3,
								pCabecaMao4, pCabecaMao5, pCabecaMao6, numJogadores) ;

			quemComeca = 1 + (rand() % 6) ;

			printf(" Jogador %d comeca (nao deixe que ninguem veja suas cartas).\n\n", quemComeca) ;
			printf(" Digite 'ok' para ver a mesa e sua mao.\n\n ") ;
			scanf_s(" %s", ok, 4);

			while (strcmp(ok, "ok") != 0) {
				scanf_s("%s", ok, 4);
			}

			system ("cls") ;
			PrintaMesa(pCabecaMesa) ;

			switch (quemComeca) {

			case 1: //primeiro jogador comeca
				
				PrintaMao(pCabecaMao1) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao1, pCabecaMesa) ;

				break;

			case 2: //segundo jogador comeca
				
				PrintaMao(pCabecaMao2) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao2, pCabecaMesa) ;

				break;

			case 3: //terceiro jogador comeca
				
				PrintaMao(pCabecaMao3) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao3, pCabecaMesa) ;

				break;

			case 4: //quarto jogador comeca
				
				PrintaMao(pCabecaMao4) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao4, pCabecaMesa) ;

				break;

			case 5: //quinto jogador comeca
				
				PrintaMao(pCabecaMao5) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao5, pCabecaMesa) ;

				break;

			case 6: //sexto jogador comeca
				
				PrintaMao(pCabecaMao6) ;

				//(1) apostar carta 1, (2) apostar carta 2, (3) apostar carta 3
				opcaoJogada = PrintaOpcoesPrimeiraJogada() ;
				
				//transfere 1 aposta pra mesa
				ExecutaOpcaoPrimeiraJogada(opcaoJogada, pCabecaMao6, pCabecaMesa) ;

				break;

			} //fim switch quemComeca

	} //fim switch opcao jogadores

	system ("cls") ;
	PrintaMesa(pCabecaMesa) ;
}

/***************************************************************************
*  Função: &Printar opcoes de jogadas
***************************************************************************/
int PrintaOpcoesPrimeiraJogada() {
	char * opcao = (char*)malloc(sizeof(char));

	printf(" \n O que deseja fazer?\n\n");
	printf(" (1) Apostar carta 1 | (2) Apostar carta 2 | (3) Apostar carta 3\n");
	printf(" Opcao: ");
	scanf_s(" %c",opcao, 1);

	while (*opcao != 49 && *opcao != 50 && *opcao != 51) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	return *opcao;

}

/***************************************************************************
*  Função: &Executa opcao da primeira jogada
***************************************************************************/
void ExecutaOpcaoPrimeiraJogada (int opcaoJogada, 
								LIS_tppLista pCabecaMao,
								LIS_tppLista pCabecaMesa) {
	switch (opcaoJogada) {

	case 49: 
		LIS_IrInicioLista(pCabecaMao);
		BAR_TransferirCarta(pCabecaMao,pCabecaMesa); break;
	case 50: 
		LIS_IrInicioLista(pCabecaMao);
		LIS_AvancarElementoCorrente(pCabecaMao, 1);
		BAR_TransferirCarta(pCabecaMao,pCabecaMesa); break;
	case 51: 
		LIS_IrInicioLista(pCabecaMao);
		LIS_AvancarElementoCorrente(pCabecaMao, 2);
		BAR_TransferirCarta(pCabecaMao,pCabecaMesa); break;

	} //fim switch opcaoJogada

}