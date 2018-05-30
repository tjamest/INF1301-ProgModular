#include "LISTA.h"
#include "BARALHO.h"
#include "MESA.h"
#include   <stdio.h>	//printf
#include   <stdlib.h>	//rand e srand
#include   <string.h>	//strcmp
#include   <time.h>
#include   <assert.h>

//1 PARTIDA formada por varias RODADAS
//1 RODADA formada por 3 apostas
//1 APOSTA é uma jogada

//TODO MUNDO PODE PEDIR TRUCO MAS N PODE ESCONDER A CARTA NA PRIMEIRA RODADA

#define TAM 40

#define EQUIPE_IMPAR 1
#define EQUIPE_PAR 0
#define EMPATE1 -1
#define EMPATE2 -2
#define EMPATE3 -3
/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/

//criar e embaralhar vetor
void PreencherVetorCartas (BAR_tppCarta vtCartas[]) ;
void EmbaralharVetorCartas (BAR_tppCarta vtCartas[]) ;
void DeterminarVencedorDaRodada (LIS_tppLista pCabecaSuperior, int *quemJoga, int *numJogadores,
								 int *pontosRodadaPar, int *pontosRodadaImpar) ;
void TransferirCartasProLixo (LIS_tppLista pCabecaSuperior) ;
void AtualizarQuemJoga (int *quemJoga, int *numJogadores) ; 

//printar listas
void PrintarBaralho (LIS_tppLista pCabecaBaralho) ;
void PrintarLixo (LIS_tppLista pCabecaLixo) ;
void PrintarMesa (LIS_tppLista pCabecaMesa) ;
void PrintarMao (LIS_tppLista pCabecaMao) ;

//printar telas (com opcoes)
int PrintarTelaInicio () ;
int PrintarTelaRegras () ;
int PrintarTelaNumJogadores () ;
int PrintarTelaRodada(int *quemJoga, int *valorRodada, int *pontosRodadaPar, int *pontosRodadaImpar,
					  int *pontosPartidaPar, int *pontosPartidaImpar, LIS_tppLista pCabecaSuperior,
					  int *quemAumentouAposta) ;
int PrintarTelaCorrerAceitarAumentar(int * quemJoga, LIS_tppLista pCabecaSuperior, int *pontosPartidaPar,
									 int *pontosPartidaImpar, int *numJogadores, int *valorRodada,
									 int *pontosRodadaPar, int *pontosRodadaImpar) ;
//executar opcoes
void ExecutarOpcaoInicio(char *opcao, int *numJogadores) ;
void ExecutarOpcaoRegras(char *opcao, int *numJogadores) ;
void ExecutarOpcaoRodada(char *opcao, int *quemJoga, int *quemAumentouAposta, 
						 int *numJogadores, int *valorRodada, 
						 int *pontosRodadaPar, int *pontosRodadaImpar, LIS_tppLista pCabecaSuperior,
						 int *pontosPartidaPar, int *pontosPartidaImpar) ;
void ExecutarOpcaoCorrer(int *quemAumentouAposta, int *quemJoga, int *numJogadores,
						 LIS_tppLista pCabecaSuperior, int *valorRodada, 
						 int *pontosPartidaPar, int *pontosPartidaImpar,
						 int *pontosRodadaPar, int *pontosRodadaImpar) ;
void ExecutarOpcaoAceitar(int *quemAumentouAposta, int *quemJoga, int *numJogadores,
						 LIS_tppLista pCabecaSuperior, int *valorRodada, 
						 int *pontosPartidaPar, int *pontosPartidaImpar) ;

/**************************************************************************/

BAR_tppCarta VetorAux[TAM];

int main (void) {

	//declara e aloca memória para todas listas do jogo
	LIS_tppLista pCabecaSuperior = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaBaralhoAux = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//declara e aloca memoria para ponteiros
	int * pontosRodadaPar = (int*)malloc(sizeof(int)) ;
	int * pontosRodadaImpar = (int*)malloc(sizeof(int)) ;
	int * pontosPartidaPar = (int*)malloc(sizeof(int)) ;
	int * pontosPartidaImpar = (int*)malloc(sizeof(int)) ;
	char * opcao = (char*)malloc(sizeof(char)) ;
	int * quemJoga = (int*)malloc(sizeof(int)) ;
	int * quemAumentouAposta = (int*)malloc(sizeof(int)) ;
	int * valorRodada = (int*)malloc(sizeof(int)) ;
	int * numJogadores = (int*)malloc(sizeof(int)) ;
	int * vencedorAtual = (int*)malloc(sizeof(int)) ;

	//cria a cabeça da lista de listas
	pCabecaSuperior = LIS_CriarLista(BAR_DestruirBaralho) ;

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
	pCabecaLixo = MES_CriarLixo() ;

	//cria um vetor de cartas
	PreencherVetorCartas(VetorAux) ;

	//embaralha o vetor
	EmbaralharVetorCartas(VetorAux) ;

	//cria a lista baralho preenchida com as cartas embaralhadas
	pCabecaBaralho = BAR_CriarBaralho(VetorAux) ;

	//insere as listas (baralho, maos, lixo e mesa) na lista de listas
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaBaralho) ; //inicio
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao1) ; //1
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao2) ; //2
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao3) ; //3
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao4) ; //4
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao5) ; //5
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao6) ; //6
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaLixo) ; //7
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMesa) ; //final

	//imprime a tela de abertura do jogo
	*opcao = PrintarTelaInicio() ;
	ExecutarOpcaoInicio(opcao, numJogadores) ;

	//inicio da partida
	*pontosPartidaPar = 0 ;
	*pontosPartidaImpar = 0 ;

	//inicio das rodadas
	while (*pontosPartidaPar < 12 && *pontosPartidaImpar < 12) {

		*pontosRodadaPar = 0 ;
		*pontosRodadaImpar = 0 ;
		*valorRodada = 1;
		*quemAumentouAposta = 0 ;

		//se nao for a primeira rodada (tem que repreencher o baralho)
		if (LIS_ObterQtdElem(pCabecaBaralho) == 0) {

			//embaralha o vetor
			EmbaralharVetorCartas(VetorAux) ;

			//cria a lista baralho auxiliar preenchida com as cartas embaralhadas
			pCabecaBaralhoAux = BAR_CriarBaralho(VetorAux) ;

			//transfere as cartas desse baralho auxiliar pro baralho principal
			while (LIS_ObterQtdElem(pCabecaBaralhoAux) > 0) {
			LIS_IrInicioLista(pCabecaBaralhoAux) ;
			BAR_TransferirCarta(pCabecaBaralhoAux, pCabecaBaralho) ;
			} //fim while

		} //fim if

		//distribui as maos
		MES_DistribuirMaos(pCabecaSuperior, numJogadores) ;

		//transfere a vira do baralho pra mesa
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

		//define quem comeca
		switch (*numJogadores) {
		case 2: *quemJoga = 1 + (rand() % 2); break;
		case 4: *quemJoga = 1 + (rand() % 4); break;
		case 6: *quemJoga = 1 + (rand() % 6); break;
		} //fim switch

		//jogadores apostam
		while (*pontosRodadaPar < 2 && *pontosRodadaImpar < 2) {

			//imprime a tela da rodada
			*opcao = PrintarTelaRodada(quemJoga, valorRodada, pontosRodadaPar, pontosRodadaImpar,
										pontosPartidaPar, pontosPartidaImpar, pCabecaSuperior,
										quemAumentouAposta) ;

			*quemAumentouAposta = 0 ;

			//executa a jogada do jogador
			ExecutarOpcaoRodada(opcao, quemJoga, quemAumentouAposta,
								numJogadores, valorRodada, 
								pontosRodadaPar, pontosRodadaImpar, pCabecaSuperior,
								pontosPartidaPar, pontosPartidaImpar) ;

			//se alguem aumentou a aposta
			if (*quemAumentouAposta != 0) {
				*opcao = PrintarTelaCorrerAceitarAumentar(quemJoga, pCabecaSuperior, 
														  pontosPartidaPar, pontosPartidaImpar, 
														  numJogadores, valorRodada,
														  pontosRodadaPar, pontosRodadaImpar) ;
				switch (*opcao) {
				case 49: //correu
					ExecutarOpcaoCorrer(quemAumentouAposta, quemJoga, numJogadores,
										pCabecaSuperior, valorRodada, 
										pontosPartidaPar, pontosPartidaImpar,
										pontosRodadaPar, pontosRodadaImpar) ;
					break;
				case 50: //aceitou
					ExecutarOpcaoAceitar(quemAumentouAposta, quemJoga, numJogadores,
										pCabecaSuperior, valorRodada, 
										pontosPartidaPar, pontosPartidaImpar) ;
					break;
				case 51: //aumentou
					//ExecutarOpcaoAumentou() ;
					break;
				} //fim switch

				AtualizarQuemJoga(quemJoga,numJogadores) ;
			} //fim if "se alguem aumentou aposta"

		} //fim while apostas

		//atualiza pontuacao da partida
		if (*pontosRodadaPar == 2) {
			*pontosPartidaPar += *valorRodada ;
		} //fim if
		else {
			*pontosPartidaImpar += *valorRodada ;
		} //fim else

		TransferirCartasProLixo(pCabecaSuperior) ;

		//checagem dos resultados
		/*system("cls");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(" Equipe Par                 Equipe Impar\n") ;
		printf( " Partida: %d/12              Partida: %d/12\n", *pontosPartidaPar, *pontosPartidaImpar) ;
		printf(" Rodada: %d/2                Rodada: %d/2\n", *pontosRodadaPar, *pontosRodadaImpar) ;
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
		PrintarBaralho(pCabecaBaralho) ;
		PrintarMesa(pCabecaMesa) ;
		printf("\n JOGADOR 1:") ;
		PrintarMao(pCabecaMao1) ;
		printf("\n JOGADOR 2:") ;
		PrintarMao(pCabecaMao2) ;
		printf("\n JOGADOR 3:") ;
		PrintarMao(pCabecaMao3) ;
		printf("\n JOGADOR 4:") ;
		PrintarMao(pCabecaMao4) ;
		printf("\n JOGADOR 5:") ;
		PrintarMao(pCabecaMao5) ;
		printf("\n JOGADOR 6:") ;
		PrintarMao(pCabecaMao6) ;
		PrintarLixo(pCabecaLixo) ;*/
	
		} //fim while partida

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
*  Função: &Determinar vencedor da rodada
***************************************************************************/
void DeterminarVencedorDaRodada (LIS_tppLista pCabecaSuperior, int *quemJoga, int *numJogadores,
								 int *pontosRodadaPar, int *pontosRodadaImpar) {

	int qtdCartasApostadas,
		equipeVencedora, 
		i;

	int quemVenceuPrimeiraRodada = -1 ;

	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//caso nao seja a primeira aposta
	if (LIS_ObterQtdElem(pCabecaMesa) > 2) {
		
		switch(*numJogadores) {

		case 2: 
			equipeVencedora = BAR_CompararCartas2Jogadores(pCabecaMesa, quemJoga) ;

			switch (equipeVencedora) {

			case EQUIPE_PAR:

				if (*pontosRodadaPar == 0 && *pontosRodadaImpar == 0) {
					quemVenceuPrimeiraRodada = EQUIPE_PAR;
				}

				*pontosRodadaPar += 1 ;
				break ;

			case EQUIPE_IMPAR:

				if (*pontosRodadaPar == 0 && *pontosRodadaImpar == 0) {
					quemVenceuPrimeiraRodada = EQUIPE_IMPAR;
				}

				*pontosRodadaImpar += 1 ;
				break ;

			case EMPATE1:

				*pontosRodadaPar += 1 ;
				*pontosRodadaImpar += 1 ;
				break ;

			case EMPATE2:

				//caso alguem tenha vencido a primeira (essa equipe vence)
				switch (quemVenceuPrimeiraRodada) {
				case EQUIPE_PAR: *pontosRodadaPar = 2 ; break ;
				case EQUIPE_IMPAR: *pontosRodadaImpar = 2 ; break ;
				
				//caso tenha sido empate na primeira (ngm ganha ponto)
				default: break;
				} //fim switch

				break;

			case EMPATE3:
				break;
			} //fim switch

			//retirando as cartas apostadas da mesa
			qtdCartasApostadas = LIS_ObterQtdElem(pCabecaMesa)-1 ;

			for (i = 0; i < qtdCartasApostadas; i++) {
				LIS_IrFinalLista(pCabecaMesa) ;
				BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
			}

			break;

			/*
		case 4:
			equipeVencedora = BAR_CompararCartas2Jogadores(pCabecaMesa, quemJoga) ;
			return equipeVencedora ;
			break;

		case 6:
			equipeVencedora = BAR_CompararCartas2Jogadores(pCabecaMesa, quemJoga) ;
			return equipeVencedora ;
			break;
			*/

		} //fim switch

	} //fim if
} /************* Fim função: &Determinar vencedor da rodada ***************/

/***************************************************************************
*  Função: &Transferir cartas pro lixo
***************************************************************************/
void TransferirCartasProLixo (LIS_tppLista pCabecaSuperior) {

	BAR_tpCondRet condRetBar ;

	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

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
	LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	while (LIS_ObterQtdElem(pCabecaBaralho) > 0) {
		LIS_IrFinalLista(pCabecaBaralho) ;
		condRetBar = BAR_TransferirCarta(pCabecaBaralho, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao1) > 0) {
		LIS_IrFinalLista(pCabecaMao1) ;
		condRetBar = BAR_TransferirCarta(pCabecaMao1, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao2) > 0) {
		LIS_IrFinalLista(pCabecaMao2) ;
		condRetBar = BAR_TransferirCarta(pCabecaMao2, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao3) > 0) {
		LIS_IrFinalLista(pCabecaMao3) ;
		condRetBar = BAR_TransferirCarta(pCabecaMao3, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao4) > 0) {
		LIS_IrFinalLista(pCabecaMao4) ;
		condRetBar = BAR_TransferirCarta(pCabecaMao4, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao5) > 0) {
		LIS_IrFinalLista(pCabecaMao5) ;
		condRetBar = BAR_TransferirCarta(pCabecaMao5, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMao6) > 0) {
		LIS_IrFinalLista(pCabecaMao6) ;
		condRetBar = BAR_TransferirCarta(pCabecaMao6, pCabecaLixo) ;
	}

	while (LIS_ObterQtdElem(pCabecaMesa) > 0) {
		LIS_IrFinalLista(pCabecaMesa) ;
		condRetBar = BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
	}

}

/***************************************************************************
*  Função: &Atualizar quem joga
***************************************************************************/
void AtualizarQuemJoga(int *quemJoga, int *numJogadores) {
		if (*quemJoga == *numJogadores) { *quemJoga = 1 ; }
		else { *quemJoga += 1 ; }
}


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

} /***************** Fim função: &Printar baralho *************************/

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

} /***************** Fim função: &Printar mesa *************************/

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

} /***************** Fim função: &Printar mao *************************/

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
int PrintarTelaRodada(int *quemJoga, int *valorRodada, int *pontosRodadaPar, int *pontosRodadaImpar, 
					  int *pontosPartidaPar, int *pontosPartidaImpar, LIS_tppLista pCabecaSuperior,
					  int *quemAumentouAposta) {

	char * opcao = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//inicio da rodada e da jogada
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	//tela de confirmacao
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemJoga) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" Jogador %d joga (nao deixe que ninguem veja suas cartas).\n\n", *quemJoga) ;
	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", opcao, 1);

	while (*opcao != 49) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");

	//tela da jogada
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemJoga) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " Equipe Par                 Equipe Impar\n") ;
	printf(		   " Partida: %d/12              Partida: %d/12\n", *pontosPartidaPar, *pontosPartidaImpar) ;
	printf(		   " Rodada: %d/2                Rodada: %d/2\n", *pontosRodadaPar, *pontosRodadaImpar) ;
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	PrintarMesa(pCabecaMesa) ;
	PrintarMao(pCabecaMao) ;

	printf("\n Valor da rodada: %d\n", *valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;

	switch (LIS_ObterQtdElem(pCabecaMao)) {

	case 1: //1 carta na mao
		printf(" (1) Apostar carta 1\n") ;
		printf(" (4) Dispensar carta 1\n") ;

		if (*quemAumentouAposta != *quemJoga) {
			switch (*valorRodada) {
			case 1: printf(" (7) Pedir truco\n\n"); break;
			case 3: printf(" (7) Pedir seis\n\n"); break;
			case 6: printf(" (7) Pedir doze\n\n"); break;
			} //fim switch
		} //fim if
		else {
			printf ("\n");
		} //fim else

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

		if (*quemAumentouAposta != *quemJoga) {
			switch (*valorRodada) {
			case 1: printf(" (7) Pedir truco\n\n"); break;
			case 3: printf(" (7) Pedir seis\n\n"); break;
			case 6: printf(" (7) Pedir doze\n\n"); break;
			} //fim switch
		} //fim if
		else {
			printf ("\n");
		} //fim else

		printf(" Opcao: ") ;
		scanf_s(" %c", opcao, 1) ;

		while (*opcao != 49 && *opcao != 50 && *opcao != 52 && *opcao != 53 && *opcao != 55 ) {
			scanf_s(" %c", opcao, 1);
		} //fim while

		system("cls");
		break;

	case 3: //3 cartas na mao (primeira jogada)
		printf(" (1) Apostar carta 1   | (2) Apostar carta 2   | (3) Apostar carta 3\n") ;

		if (*quemAumentouAposta != *quemJoga) {
			switch (*valorRodada) {
			case 1: printf(" (7) Pedir truco\n\n"); break;
			case 3: printf(" (7) Pedir seis\n\n"); break;
			case 6: printf(" (7) Pedir doze\n\n"); break;
			} //fim switch
		} //fim if
		else {
			printf ("\n");
		} //fim else

		printf(" Opcao: ") ;
		scanf_s(" %c", opcao, 1) ;

		while (*opcao != 49 && *opcao != 50 && *opcao != 51 && *opcao != 55) {
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
int PrintarTelaCorrerAceitarAumentar(int * quemJoga, LIS_tppLista pCabecaSuperior, 
									 int *pontosPartidaPar, int *pontosPartidaImpar, 
									 int *numJogadores, int *valorRodada,
									 int *pontosRodadaPar, int *pontosRodadaImpar) {

	//aloca memoria pra opcao de jogada escolhida										
	char * opcao = (char*)malloc(sizeof(char)) ;

	//declara e aloca memoria pra cabeca da mao e da mesa
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//armazena ponteiro pra cabeca da lista mesa em pCabecaMesa
	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//tela de confirmacao
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemJoga) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" Jogador %d joga (nao deixe que ninguem veja suas cartas).\n\n", *quemJoga) ;
	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", opcao, 1);

	system("cls") ;

	//printa cabeçalho da tela
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (*quemJoga) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", *quemJoga); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", *quemJoga); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " Equipe Par                 Equipe Impar\n") ;
	printf(		   " Partida: %d/12              Partida: %d/12\n", *pontosPartidaPar, *pontosPartidaImpar) ;
	printf(		   " Rodada: %d/2                Rodada: %d/2\n", *pontosRodadaPar, *pontosRodadaImpar) ;
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	PrintarMesa(pCabecaMesa) ;
	PrintarMao(pCabecaMao) ;

	printf("\n Valor da rodada: %d\n", *valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;
	printf(" (1) Correr   | (2) Aceitar") ;

	switch (*valorRodada) {
	case 3: printf("   | (3) Pedir seis\n\n"); break;
	case 6: printf("   | (3) Pedir doze\n\n"); break;
	case 12: printf("\n\n"); break;
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
void ExecutarOpcaoInicio (char *opcao, int *numJogadores) {

	switch(*opcao) {

	case 49: //(1) iniciar partida

		*opcao = PrintarTelaNumJogadores ();
		switch(*opcao) {
		case 49: *numJogadores = 2; break;
		case 50: *numJogadores = 4; break;
		case 51: *numJogadores = 6; break;
		}
		break;

	case 50: //(2) ver regras

		*opcao = PrintarTelaRegras();
		ExecutarOpcaoRegras(opcao, numJogadores);
		break;

	case 51: //(3) sair
		exit(0);
		break;

	} //fim switch

}

/***************************************************************************
*  Função: &Executar opcao da tela de regras
***************************************************************************/
void ExecutarOpcaoRegras (char *opcao, int *numJogadores) {

	switch(*opcao) {
	case 49: //(1) voltar
		*opcao = PrintarTelaInicio();
		ExecutarOpcaoInicio(opcao, numJogadores);
		break;
	case 50: //(2) sair
		exit(0);
		break;
	}
}


/***************************************************************************
*  Função: &Executar opcao da tela da rodada
***************************************************************************/
void ExecutarOpcaoRodada(char *opcao, int *quemJoga, int *quemAumentouAposta, 
						 int *numJogadores, int *valorRodada,
						 int *pontosRodadaPar, int *pontosRodadaImpar, LIS_tppLista pCabecaSuperior,
						 int *pontosPartidaPar, int *pontosPartidaImpar) {
	int i ;

	//declarando ponteiros e alocando pras cabecas da mao, mesa e lixo
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//armazenando ponteiro pra lista mesa e lista lixo
	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//armazenando ponteiro pra lista mao de quem vai fazer a jogada
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_IrInicioLista(pCabecaMao) ;

	switch(*opcao) {

	case 49: //(1) apostar carta 1

		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		DeterminarVencedorDaRodada(pCabecaSuperior, quemJoga, numJogadores,
								   pontosRodadaPar, pontosRodadaImpar) ;
		AtualizarQuemJoga(quemJoga, numJogadores) ;
		break;

	case 50: //(2) apostar carta 2

		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		DeterminarVencedorDaRodada(pCabecaSuperior, quemJoga, numJogadores,
								   pontosRodadaPar, pontosRodadaImpar) ;
		AtualizarQuemJoga(quemJoga, numJogadores) ;
		break;

	case 51: //(3) apostar carta 3

		LIS_AvancarElementoCorrente(pCabecaMao, 2) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		DeterminarVencedorDaRodada(pCabecaSuperior, quemJoga, numJogadores,
								   pontosRodadaPar, pontosRodadaImpar) ;
		AtualizarQuemJoga(quemJoga, numJogadores) ;
		break;

	case 52: //(4) dispensar carta 1

		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		
		//em um jogo de 2 jogadores
		if (*numJogadores == 2) {

			switch (*quemJoga) {
			case 1:	*pontosRodadaPar += 1 ; break ;
			case 2: *pontosRodadaImpar += 1 ; break ;
			} //fim switch

			//retirando as cartas apostadas da mesa
			for (i = 0; i < LIS_ObterQtdElem(pCabecaMesa)-1; i++) {
				LIS_IrFinalLista(pCabecaMesa) ;
				BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
			} //fim for

		} //fim if "em um jogo de 2 jogadores"

		AtualizarQuemJoga(quemJoga, numJogadores) ;
		break;

	case 53: //(5) dispensar carta 2

		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;

		//em um jogo de 2 jogadores
		if (*numJogadores == 2) {

			switch (*quemJoga) {
			case 1:	*pontosRodadaPar += 1 ; break ;
			case 2: *pontosRodadaImpar += 1 ; break ;
			} //fim switch

			//retirando as cartas apostadas da mesa
			for (i = 0; i < LIS_ObterQtdElem(pCabecaMesa)-1; i++) {
				LIS_IrFinalLista(pCabecaMesa) ;
				BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
			} //fim for

		} //fim if "em um jogo de 2 jogadores"

		AtualizarQuemJoga(quemJoga, numJogadores) ;
		break;

	case 54: //(6) dispensar carta 3

		LIS_AvancarElementoCorrente(pCabecaMao, 2) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;

		//em um jogo de 2 jogadores
		if (*numJogadores == 2) {

			switch (*quemJoga) {
			case 1:	*pontosRodadaPar += 1 ; break ;
			case 2: *pontosRodadaImpar += 1 ; break ;
			} //fim switch

			//retirando as cartas apostadas da mesa
			for (i = 0; i < LIS_ObterQtdElem(pCabecaMesa)-1; i++) {
				LIS_IrFinalLista(pCabecaMesa) ;
				BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
			} //fim for
			
		} //fim if "em um jogo de 2 jogadores"

		AtualizarQuemJoga(quemJoga, numJogadores) ;
		break;

	case 55: //(7) pedir truco/seis/doze

		switch(*valorRodada) {
		case 1: *valorRodada = 3; break;
		case 3: *valorRodada = 6; break;
		case 6: *valorRodada = 12; break;
		}

		//salva o jogador que pediu truco
		*quemAumentouAposta = *quemJoga ;

		//quemJoga passa a ser o jogador seguinte
		AtualizarQuemJoga(quemJoga, numJogadores) ;

	} //fim switch
} /******************* FIM FUNÇÃO: AAAAAAAAAAAAAAAA *************/

void ExecutarOpcaoCorrer(int *quemAumentouAposta, int *quemJoga, int *numJogadores,
						 LIS_tppLista pCabecaSuperior, int *valorRodada, 
						 int *pontosPartidaPar, int *pontosPartidaImpar,
						 int *pontosRodadaPar, int *pontosRodadaImpar) {

	switch (*numJogadores) {

	case 2: //2 jogadores

		switch (*quemJoga) {
		case 1: 
			*pontosPartidaPar += *valorRodada ; 
			*pontosRodadaPar = 0 ;
			*pontosRodadaImpar = 0 ;
			break ;
		case 2: 
			*pontosPartidaImpar += *valorRodada ;
			*pontosRodadaPar = 0 ;
			*pontosRodadaImpar = 0 ;
			break ;
		} //fim switch
		break;

	case 4: //4 jogadores
		break;

	case 6: //6 jogadores
		break;

	} //fim switch

} //fim funcao

void ExecutarOpcaoAceitar(int *quemAumentouAposta, int *quemJoga, int *numJogadores,
						  LIS_tppLista pCabecaSuperior, int *valorRodada, 
						  int *pontosPartidaPar, int *pontosPartidaImpar) {

	switch (*numJogadores) {

	case 2: //2 jogadores
		break;

	case 4: //4 jogadores
		break;

	case 6: //6 jogadores
		break;

	} //fim switch

} //fim funcao