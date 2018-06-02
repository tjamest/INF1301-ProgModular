#include "LISTA.h"
#include "BARALHO.h"
#include "MESA.h"
#include   <stdio.h>	//printf
#include   <stdlib.h>	//rand e srand
#include   <string.h>	//strcmp
#include   <time.h>
#include   <assert.h>

//1 PARTIDA formada por varias RODADAS
//1 RODADA formada por 3 baterias de apostas
//1 BATERIA DE APOSTA é formada por 2 a 6 jogadas

//TODO MUNDO PODE PEDIR TRUCO MAS N PODE ESCONDER A CARTA NA PRIMEIRA JOGADA

#define TAM 40

#define NINGUEM_VENCEU 0
#define EQUIPE_IMPAR 1
#define EQUIPE_PAR 2
#define EMPATE1 -1
#define EMPATE2 -2
#define EMPATE3 -3

//resultados de apostar ou dispensar carta
#define JOGADA_PERDEU -1
#define JOGADA_EMPATOU 0
#define JOGADA_VENCEU 1

//jogadores
#define JOGADOR1 1
#define JOGADOR2 2
#define JOGADOR3 3
#define JOGADOR4 4
#define JOGADOR5 5
#define JOGADOR6 6

//jogadas
#define APOSTAR_CARTA_1 49
#define APOSTAR_CARTA_2 50
#define APOSTAR_CARTA_3 51
#define DISPENSAR_CARTA_1 52
#define DISPENSAR_CARTA_2 53
#define DISPENSAR_CARTA_3 54
#define AUMENTAR_APOSTA 55

//parâmetros pra função esvaziar mesa
#define DEIXA_VIRA 0
#define TIRA_VIRA 1

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/

void PreencherVetorCartas (BAR_tppCarta vtCartas[]) ;
void EmbaralharVetorCartas (BAR_tppCarta vtCartas[]) ;

int DeterminarResultadoDaAposta (LIS_tppLista pCabecaSuperior, int quemJoga, int numJogadores) ;

int VerResultadoEntre2Jogadores (LIS_tppLista pCabecaSuperior, int quemJoga) ; 

int DefineQuemComeca(int numJogadores) ;

//printar listas
void PrintarBaralho (LIS_tppLista pCabecaBaralho) ;
void PrintarLixo (LIS_tppLista pCabecaLixo) ;
void PrintarMesa (LIS_tppLista pCabecaMesa) ;
void PrintarMao (LIS_tppLista pCabecaMao) ;

//printar telas (com opcoes)
int PrintarTelaInicio () ;
int PrintarTelaRegras () ;
int PrintarTelaNumJogadores () ;
int PrintarTelaJogada(int quemJoga, int valorRodada, LIS_tppLista pCabecaSuperior,
					  int pontosRodadaPar, int pontosRodadaImpar,
					  int pontosPartidaPar, int pontosPartidaImpar) ;

int PrintarTelaCorrerAceitarAumentar(int * quemJoga, LIS_tppLista pCabecaSuperior, int *pontosPartidaPar,
									 int *pontosPartidaImpar, int *numJogadores, int *valorRodada,
									 int *pontosRodadaPar, int *pontosRodadaImpar) ;

int PrintarTelaMostrarDispensar(int *quemJoga, int *valorRodada, int *pontosRodadaPar, int *pontosRodadaImpar, 
								int *pontosPartidaPar, int *pontosPartidaImpar, LIS_tppLista pCabecaSuperior) ;

void PrintarTelaFimApostas(LIS_tppLista pCabecaSuperior, int valorRodada, int equipeVencedoraDaAposta, int numRodadas,
						  int pontosRodadaPar, int pontosRodadaImpar,
						  int pontosPartidaPar, int pontosPartidaImpar) ;

void PrintarTelaFimRodada(LIS_tppLista pCabecaSuperior, int valorRodada, int equipeVencedoraDaRodada, int numRodadas,
						  int pontosRodadaPar, int pontosRodadaImpar,
						  int pontosPartidaPar, int pontosPartidaImpar) ;
//executar opcoes
int ExecutarOpcaoInicio(int opcao) ;
void ExecutarOpcaoRegras(int opcao) ;
void ExecutarOpcaoJogada(LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) ;
void ExecutarOpcaoApostarCarta (LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) ;

void ExecutarEmpate1(LIS_tppLista pCabecaSuperior, int *valorRodada, int equipeVencedoraDaAposta, int *numRodadas,
					 int *pontosRodadaPar, int *pontosRodadaImpar, 
					 int *pontosPartidaPar, int *pontosPartidaImpar, int *quemVenceuPrimeiraAposta, int *quemJoga) ;

void ExecutarEmpate2(LIS_tppLista pCabecaSuperior, int *valorRodada, int equipeVencedoraDaAposta, int *numRodadas,
					 int *pontosRodadaPar, int *pontosRodadaImpar, 
					 int *pontosPartidaPar, int *pontosPartidaImpar, int *quemVenceuPrimeiraAposta, int *quemJoga) ;

void ExecutarEmpate3(LIS_tppLista pCabecaSuperior, int *valorRodada, int equipeVencedoraDaAposta, int *numRodadas,
					 int *pontosRodadaPar, int *pontosRodadaImpar, 
					 int *pontosPartidaPar, int *pontosPartidaImpar, int *quemVenceuPrimeiraAposta, int *quemJoga) ;
/**************************************************************************/

BAR_tppCarta VetorAux[TAM];

int main (void) {

	//declara e aloca memória para todas listas do jogo
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

	//declara variaveis
	int jogada,
		opcao,
		valorRodada ,
		pontosRodadaPar ,
		pontosRodadaImpar ,
		pontosPartidaPar ,
		pontosPartidaImpar ,
		quemJoga ,
		numJogadores ,
		numRodadas ,
		numJogadas ,
		numEmpates ,
		numBateriasDeApostas ,
		atualJogadorVencedor,
		equipeVencedoraDaPrimeiraAposta,
		equipeVencedoraDaAposta ,
		equipeVencedoraDaRodada ,
		resultado ;

	//cria a cabeça da lista de listas
	pCabecaSuperior = LIS_CriarLista(BAR_DestruirBaralho) ;

	//cria a lista baralho (vazia)
	pCabecaBaralho = BAR_CriarBaralho() ;

	//cria as 6 maos (vazias)
	pCabecaMao1 = MES_CriarMao() ;
	pCabecaMao2 = MES_CriarMao() ;
	pCabecaMao3 = MES_CriarMao() ;
	pCabecaMao4 = MES_CriarMao() ;
	pCabecaMao5 = MES_CriarMao() ;
	pCabecaMao6 = MES_CriarMao() ;

	//cria o lixo (vazio)
	pCabecaLixo = MES_CriarLixo() ;

	//cria a mesa (vazia)
	pCabecaMesa = MES_CriarMesa() ;

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
	opcao = PrintarTelaInicio() ;
	numJogadores = ExecutarOpcaoInicio(opcao) ;
	
	//define quem comeca
	quemJoga = DefineQuemComeca(numJogadores) ;
	
	//inicio da partida
	pontosPartidaPar = 0 ;
	pontosPartidaImpar = 0 ;
	numRodadas = 0 ;

	//preenche um vetor com cartas
	PreencherVetorCartas(VetorAux) ;

	//inicio da rodada
	while (pontosPartidaPar < 12 && pontosPartidaImpar < 12) {

		pontosRodadaPar = 0 ;
		pontosRodadaImpar = 0 ;
		numJogadas = 0 ;
		numEmpates = 0 ;
		numBateriasDeApostas = 0 ;
		valorRodada = 1;
		numRodadas += 1 ;

		//embaralha o vetor de cartas (comentar em caso de testes de empate)
		//EmbaralharVetorCartas(VetorAux) ;

		//preenche o baralho
		BAR_PreencherBaralho(pCabecaBaralho, VetorAux) ;

		//distribui as maos
		//MES_DistribuirMaos(pCabecaSuperior, numJogadores) ;
		MES_DistribuirMaosParaTestarEmpates(pCabecaSuperior, numJogadores) ;

		//transfere a vira do baralho pra mesa
		BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

		//inicio da jogada
		while (pontosRodadaPar < 2 && pontosRodadaImpar < 2) {

			numJogadas += 1 ;

			//imprime tela com as opçoes de jogadas
			jogada = PrintarTelaJogada(quemJoga, valorRodada, pCabecaSuperior,
										pontosRodadaPar, pontosRodadaImpar,
									    pontosPartidaPar, pontosPartidaImpar) ;

			//executa a jogada escolhida (APOSTAR / DISPENSAR / AUMENTAR)
			ExecutarOpcaoJogada(pCabecaSuperior, quemJoga, jogada) ;

			//se apostou carta
			if (jogada >= 49 && jogada <= 51) {

				//se tem que comparar cartas
				if (LIS_ObterQtdElem(pCabecaMesa) > 2) {

					//determina o resultado da jogada (VENCEU / PERDEU / EMPATOU)
					resultado = DeterminarResultadoDaAposta(pCabecaSuperior,
															quemJoga,
															numJogadores) ;
					//se venceu
					if (resultado == JOGADA_VENCEU) {
						atualJogadorVencedor = quemJoga ;
					} //fim if "se venceu"

					else if (resultado == JOGADA_EMPATOU) {
						//empatouCom = ;//jogador com quem empatou
						//quemJoga = //jogador com quem empatou
						numEmpates += 1 ;
						atualJogadorVencedor = -10 ;
					}

				} //fim if "se tem que comparar cartas"

				//se nao tem carta pra comparar
				else {
					atualJogadorVencedor = quemJoga ;
				}

			} // fim if "se apostou carta"

			//se dispensou carta
			else if (jogada >= 52 && jogada <= 54) {

			}

			//se aumentou a aposta
			else {

			}

			//se todo mundo ja fez sua jogada
			if (numJogadas == numJogadores) {

				numBateriasDeApostas += 1 ;

				//se o atual jogador vencedor for um jogador (se nao tiver sido empate)
				if (atualJogadorVencedor >= 1 && atualJogadorVencedor <= 6) {

					switch (atualJogadorVencedor%2) {
					case 0: //equipe par
						pontosRodadaPar += 1 ;
						equipeVencedoraDaAposta = EQUIPE_PAR ;

						//se for a primeira bateria de apostas
						if (pontosRodadaPar == 1 && pontosRodadaImpar == 0) {
							equipeVencedoraDaPrimeiraAposta = EQUIPE_PAR ;
						}

						break;
					case 1: //equipe impar
						pontosRodadaImpar += 1 ;
						equipeVencedoraDaAposta = EQUIPE_IMPAR ;

						//se for a primeira bateria de apostas
						if (pontosRodadaPar == 0 && pontosRodadaImpar == 1) {
							equipeVencedoraDaPrimeiraAposta = EQUIPE_IMPAR ;
						}

						break;
					} //fim switch

					PrintarTelaFimApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
										  pontosRodadaPar, pontosRodadaImpar,
										  pontosPartidaPar, pontosPartidaImpar) ;

					MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

					quemJoga = atualJogadorVencedor;
					numJogadas = 0;

				} //fim if "se o atual jogador vencedor eh um jogador"

				//se tiver sido empate
				else {

					switch (numBateriasDeApostas) {
					case 1: //na primeira bateria de apostas
						equipeVencedoraDaAposta = EMPATE1 ;
						equipeVencedoraDaPrimeiraAposta = EMPATE1 ;
						pontosRodadaImpar += 1 ;
						pontosRodadaPar += 1 ;

						PrintarTelaFimApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
										  pontosRodadaPar, pontosRodadaImpar,
										  pontosPartidaPar, pontosPartidaImpar) ;

						MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

						//quemJoga = atualJogadorVencedor;
						numJogadas = 0;

						break;

					case 2: //na segunda bateria de apostas

						//se tiver sido empate na primeira bateria de apostas tambem
						if (equipeVencedoraDaPrimeiraAposta == EMPATE1) {

							equipeVencedoraDaAposta = EMPATE2 ;

							PrintarTelaFimApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
											  pontosRodadaPar, pontosRodadaImpar,
											  pontosPartidaPar, pontosPartidaImpar) ;

							MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

							//quemJoga = atualJogadorVencedor;
							numJogadas = 0;
						}

						//se teve vencedor na primeira bateria de apostas (essa equipe vence)
						else {
							switch (equipeVencedoraDaPrimeiraAposta) {
							case EQUIPE_PAR: 
								pontosRodadaPar += 1 ;
								equipeVencedoraDaAposta = EQUIPE_PAR ;
								break;
							case EQUIPE_IMPAR:
								pontosRodadaImpar += 1 ;
								equipeVencedoraDaAposta = EQUIPE_IMPAR ;
								break;
							} //fim switch

							PrintarTelaFimApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
												  pontosRodadaPar, pontosRodadaImpar,
												  pontosPartidaPar, pontosPartidaImpar) ;

							MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

							//quemJoga = atualJogadorVencedor;
							numJogadas = 0;

						} //fim else

						break;

					case 3: //empate na terceira bateria de apostas

						equipeVencedoraDaAposta = EMPATE3 ;

						PrintarTelaFimApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
												pontosRodadaPar, pontosRodadaImpar,
											    pontosPartidaPar, pontosPartidaImpar) ;

						pontosRodadaPar = 2 ;
						pontosRodadaImpar = 2 ;

						MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

						//quemJoga = atualJogadorVencedor;
						numJogadas = 0;
						

						break;
					} //fim switch

				} //fim else "se tiver sido empate"

			} //fim if "se todo mundo ja fez sua jogada"

			//se ainda falta gente fazer jogada
			else {
				if (quemJoga == numJogadores) {	
					quemJoga = 1;
				}
				else {
					quemJoga += 1;
				}
			} //fim else

		} //fim while jogada

		//se a rodada acabou nessa jogada
		if (pontosRodadaPar == 2 || pontosRodadaImpar == 2) {

			//se a equipe par venceu
			if (pontosRodadaImpar < 2) {
				equipeVencedoraDaRodada = EQUIPE_PAR ;
				pontosPartidaPar += valorRodada ;
				PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, numRodadas,
									 pontosRodadaPar, pontosRodadaImpar,
									 pontosPartidaPar, pontosPartidaImpar) ;
			}

			//se a equipe impar venceu
			else if (pontosRodadaPar < 2) {
				equipeVencedoraDaRodada = EQUIPE_IMPAR ;
				pontosPartidaImpar += valorRodada ;
				PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, numRodadas,
									 pontosRodadaPar, pontosRodadaImpar,
									 pontosPartidaPar, pontosPartidaImpar) ;
			}

			//se empatou
			else {
				equipeVencedoraDaRodada = NINGUEM_VENCEU ;
				PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, numRodadas,
									 pontosRodadaPar, pontosRodadaImpar,
									 pontosPartidaPar, pontosPartidaImpar) ;
			}

			MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

		} //fim "se a rodada acabou nessa jogada"

		//limpa as listas
		MES_TransferirTodasCartasProLixo(pCabecaSuperior) ;
	
	} //fim while rodada

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
*  Função: &Ver quem ganhou entre 2 jogadores
***************************************************************************/
int VerResultadoEntre2Jogadores (LIS_tppLista pCabecaSuperior, int quemJoga) {

	BAR_tppCarta pVira = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pAposta = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCartaMesa = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	int i ;
	int quemVenceu = NINGUEM_VENCEU ;

	BAR_tpValorCarta valorAposta, valorCartaMesa ;
	BAR_tpNaipeCarta naipeAposta, naipeCartaMesa ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrInicioLista(pCabecaMesa) ;
	pVira = BAR_ObterCartaCorr(pCabecaMesa) ;

	LIS_IrFinalLista(pCabecaMesa) ;
	pAposta = BAR_ObterCartaCorr(pCabecaMesa) ;

	//CARTA APOSTADA == MANILHA
	if (BAR_VerificarSeEhManilha(pAposta, pVira) == BAR_CondRetEhManilha) {

		LIS_IrInicioLista(pCabecaMesa) ;

		for (i = 0 ; i < LIS_ObterQtdElem(pCabecaMesa)-2 ; i++ ) {

			LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;

			//CARTA DA MESA == MANILHA (tem que comparar naipes)
			if (BAR_VerificarSeEhManilha(pCartaMesa, pVira) == BAR_CondRetEhManilha) {

				naipeAposta = BAR_ObterNaipe(pAposta) ;
				naipeCartaMesa = BAR_ObterNaipe(pCartaMesa) ;

				//apostador venceu
				if ((int)naipeAposta > (int)naipeCartaMesa) {
					switch (quemJoga) {
					case JOGADOR1: 
						return JOGADOR1 ; 
						break;
					case JOGADOR2: 
						return JOGADOR2 ; 
						break;
					} //fim switch
				} //fim if

				//apostador perdeu
				else {
					switch (quemJoga) {
					case JOGADOR1: 
						return JOGADOR2 ; 
						break ;
					case JOGADOR2: 
						return JOGADOR1 ; 
						break ;
					} //fim switch
				} //fim else

			} //fim if

			//CARTA DA MESA != MANILHA (apostador venceu)
			else {
				switch (quemJoga) {
				case JOGADOR1: 
					return JOGADOR1 ; 
					break;
				case JOGADOR2: 
					return JOGADOR2 ; 
					break;
				} // fim switch
			} //fim else

		} //fim for

	} //fim if "se a carta apostada for manilha"

	//CARTA APOSTADA != MANILHA
	else {

		LIS_IrInicioLista(pCabecaMesa) ;

		LIS_AvancarElementoCorrente(pCabecaMesa, 1) ;
		pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;

		//CARTA DA MESA != MANILHA (tem que comparar valores)
		if (BAR_VerificarSeEhManilha(pCartaMesa, pVira) == BAR_CondRetNaoEhManilha) {
				
			valorAposta = BAR_ObterValor(pAposta) ;
			valorCartaMesa = BAR_ObterValor(pCartaMesa) ;

			//apostador venceu
			if ((int)valorAposta > (int)valorCartaMesa) {
				switch (quemJoga) {
				case 1: 
					return EQUIPE_IMPAR ; 
					break;
				case 2: 
					return EQUIPE_PAR ; 
					break;
				} // fim switch
			} //fim if

			//empataram
			else if ((int)valorAposta == (int)valorCartaMesa) {

				switch (LIS_ObterQtdElem(pCabecaMao)) {

				case 0: //empataram na terceira jogada

					//quemJoga passa a ser o jogador seguinte
					if (quemJoga == 2) {
						quemJoga = 1 ;
					}
					else { 
						quemJoga += 1 ;
					}
					return EMPATE3;
					break;

				case 1:	//empataram na segunda jogada

					//quemJoga passa a ser o jogador seguinte
					if (quemJoga == 2) {
						quemJoga = 1 ;
					}
					else { 
						quemJoga += 1 ;
					}
					return EMPATE2;
					break;

				case 2: //empataram na primeira jogada

					//quemJoga passa a ser o jogador seguinte
					if (quemJoga == 2) {
						quemJoga = 1 ;
					}
					else { 
						quemJoga += 1 ;
					}
					return EMPATE1;
					break;

				} //fim switch

			} //fim else if
				
			//apostador perdeu
			else {
				switch (quemJoga) {
				case JOGADOR1: 
					return JOGADOR2 ; 
					break;
				case JOGADOR2: 
					return JOGADOR1 ; 
					break;
				} //fim switch 
			} //fim else

		} //fim if

		//CARTA DA MESA == MANILHA (apostador perdeu)
		else {
			switch (quemJoga) {
			case JOGADOR1: 
				return JOGADOR2 ; 
				break;
			case JOGADOR2: 
				return JOGADOR1 ; 
				break;
			} //fim switch
		} //fim else

	} //fim else "se a carta apostada nao for manilha"

	return -10;
} /*************** Fim função: &Comparar cartas 2 jogadores ***************/

/***************************************************************************
*  Função: &Determinar vencedor da aposta
***************************************************************************/
int DeterminarResultadoDaAposta (LIS_tppLista pCabecaSuperior, int quemJoga, int numJogadores) {

	int resultado ;

	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
		
	switch(numJogadores) {

	case 2: 

		resultado = VerResultadoEntre2Jogadores(pCabecaSuperior, quemJoga) ;

		if (resultado == EMPATE1 || resultado == EMPATE2 || resultado == EMPATE3) {
			return JOGADA_EMPATOU;
		} //fim if

		else if (resultado == quemJoga) {
			return JOGADA_VENCEU ;
		} //fim else if

		else {
			return JOGADA_PERDEU ;
		} //fim else

	} //fim switch

	return -10;

} /************* Fim função: &Determinar vencedor da aposta ***************/

/***************************************************************************
*  Função: &Definir quem comeca
***************************************************************************/
int DefineQuemComeca(int numJogadores) {

	switch (numJogadores) {
		case 2: 
			return 1 + (rand() % 2) ;
		case 4: 
			return 1 + (rand() % 4) ;
		case 6: 
			return 1 + (rand() % 6) ;
	} //fim switch

	return 0;
} //fim funcao

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
			printf ("                   MESA:\n") ;
			printf ("              VIRA - %s de %s\n", valorStr, naipeStr);
		}
		else {
			printf ("             CARTA - %s de %s\n", valorStr, naipeStr);
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
	printf("\n                   MAO:\n") ;
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
		printf ("               %d) %s de %s\n", i+1, valorStr, naipeStr);

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
int PrintarTelaJogada(int quemJoga, int valorRodada, LIS_tppLista pCabecaSuperior,
					  int pontosRodadaPar, int pontosRodadaImpar, 
					  int pontosPartidaPar, int pontosPartidaImpar) {

	char * jogada = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//inicio da rodada e da jogada
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	//tela de confirmacao 
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (quemJoga) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " Equipe Par                 Equipe Impar\n") ;
	printf(		   " Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	printf(		   " Rodada: %d/2                Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	printf(" Jogador %d joga (nao deixe que ninguem veja suas cartas).\n\n", quemJoga) ;
	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", jogada, 1);

	while (*jogada != 49) {
		scanf_s(" %c", jogada, 1);
	} //fim while

	system("cls");

	//tela da jogada
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	switch (quemJoga) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " Equipe Par                 Equipe Impar\n") ;
	printf(		   " Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	printf(		   " Rodada: %d/2                Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	PrintarMesa(pCabecaMesa) ;
	PrintarMao(pCabecaMao) ;

	printf("\n Valor da rodada: %d\n", valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;

	switch (LIS_ObterQtdElem(pCabecaMao)) {

	case 1: //1 carta na mao
		printf(" (1) Apostar carta 1\n") ;
		printf(" (4) Dispensar carta 1\n") ;

		switch (valorRodada) {
		case 1: printf(" (7) Pedir truco\n\n"); break;
		case 3: printf(" (7) Pedir seis\n\n"); break;
		case 6: printf(" (7) Pedir doze\n\n"); break;
		} //fim switch

		printf(" Opcao: ") ;
		scanf_s(" %c", jogada, 1) ;

		while (*jogada != 49 && *jogada != 52 && *jogada != 55) {
			scanf_s(" %c", jogada, 1);
		} //fim while

		system("cls");
		break;

	case 2: //2 cartas na mao
		printf(" (1) Apostar carta 1   | (2) Apostar carta 2 \n") ;
		printf(" (4) Dispensar carta 1 | (5) Dispensar carta 2\n") ;

		switch (valorRodada) {
		case 1: printf(" (7) Pedir truco\n\n"); break;
		case 3: printf(" (7) Pedir seis\n\n"); break;
		case 6: printf(" (7) Pedir doze\n\n"); break;
		} //fim switch

		printf(" Opcao: ") ;
		scanf_s(" %c", jogada, 1) ;

		while (*jogada != 49 && *jogada != 50 && *jogada != 52 && *jogada != 53 && *jogada != 55 ) {
			scanf_s(" %c", jogada, 1);
		} //fim while

		system("cls");
		break;

	case 3: //3 cartas na mao (primeira jogada)
		printf(" (1) Apostar carta 1   | (2) Apostar carta 2   | (3) Apostar carta 3\n") ;

		switch (valorRodada) {
		case 1: printf(" (7) Pedir truco\n\n"); break;
		case 3: printf(" (7) Pedir seis\n\n"); break;
		case 6: printf(" (7) Pedir doze\n\n"); break;
		} //fim switch

		printf(" Opcao: ") ;
		scanf_s(" %c", jogada, 1) ;

		while (*jogada != 49 && *jogada != 50 && *jogada != 51 && *jogada != 55) {
			scanf_s(" %c", jogada, 1);
		} //fim while

		system("cls");
		break;

	} //fim switch

	system("cls") ;
	return *jogada ;
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

/***************************************************************************
*  Função: &Printar tela mostrar ou dispensar
***************************************************************************/
int PrintarTelaMostrarDispensar(int *quemJoga, int *valorRodada, int *pontosRodadaPar, int *pontosRodadaImpar, 
								int *pontosPartidaPar, int *pontosPartidaImpar, LIS_tppLista pCabecaSuperior) {

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
		printf(" (1) Mostrar carta 1\n") ;
		printf(" (4) Dispensar carta 1\n") ;
		printf(" Opcao: ") ;
		scanf_s(" %c", opcao, 1) ;

		while (*opcao != 49 && *opcao != 52) {
			scanf_s(" %c", opcao, 1);
		} //fim while

		system("cls");
		break;

	case 2: //2 cartas na mao
		printf(" (1) Mostrar carta 1   | (2) Mostrar carta 2 \n") ;
		printf(" (4) Dispensar carta 1 | (5) Dispensar carta 2\n") ;

		printf(" Opcao: ") ;
		scanf_s(" %c", opcao, 1) ;

		while (*opcao != 49 && *opcao != 50 && *opcao != 52 && *opcao != 53 ) {
			scanf_s(" %c", opcao, 1);
		} //fim while

		system("cls");
		break;

	} //fim switch

	system("cls") ;
	return *opcao ;
}

/***************************************************************************
*  Função: &Printar tela fim da rodada
***************************************************************************/
void PrintarTelaFimRodada(LIS_tppLista pCabecaSuperior, int valorRodada, 
						  int equipeVencedoraDaRodada, int numRodadas,
						  int pontosRodadaPar, int pontosRodadaImpar,
						  int pontosPartidaPar, int pontosPartidaImpar) {

	char * opcao = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	//tela fim rodada 
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~~~~ RODADA %d ~~~~~~~~~~~~~~~~\n", numRodadas) ;

	switch (equipeVencedoraDaRodada) {

	case EQUIPE_PAR:
		printf(	   "        Equipe PAR venceu a rodada\n") ; 
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                  Equipe Impar\n") ;
		printf(	   " Partida: %d(+%d)/12           Partida: %d/12\n", pontosPartidaPar-1, valorRodada, pontosPartidaImpar) ;
		printf(	   " Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ; 
		break ;

	case EQUIPE_IMPAR:
		printf(	   "       Equipe IMPAR venceu a rodada\n") ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                 Equipe Impar\n") ;
		printf(	   " Partida: %d/12            Partida: %d(+%d)/12\n", pontosPartidaPar, pontosPartidaImpar-1, valorRodada) ;
		printf(	   " Rodada: %d/2                Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case NINGUEM_VENCEU:
		printf(	   "               Rodada empatou\n") ;
		printf(	   "         (nenhuma das equipes pontua)\n") ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                  Equipe Impar\n") ;
		printf(	   " Partida: %d/12               Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   " Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar-1, pontosRodadaImpar-1) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
		break ;

	} //fim switch

	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", opcao, 1);

	while (*opcao != 49) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	
		
} //fim função

/***************************************************************************
*  Função: &Printar tela fim das apostas
***************************************************************************/
void PrintarTelaFimApostas(LIS_tppLista pCabecaSuperior, int valorRodada, 
						  int equipeVencedoraDaAposta, int numRodadas,
						  int pontosRodadaPar, int pontosRodadaImpar,
						  int pontosPartidaPar, int pontosPartidaImpar) {

	char * opcao = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	//tela fim apostas 
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~~~~ RODADA %d ~~~~~~~~~~~~~~~~\n", numRodadas) ;

	switch (equipeVencedoraDaAposta) {

	case EMPATE3:
		printf(	   "    Terceira bateria de apostas empatou\n") ;
		printf(	   "        (nenhuma das equipes pontua)\n") ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                  Equipe Impar\n") ;
		printf(	   " Partida: %d/12               Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   " Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EMPATE2:
		printf(	   "     Segunda bateria de apostas empatou\n") ;
		printf(	   "        (nenhuma das equipes pontua)\n") ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                  Equipe Impar\n") ;
		printf(	   " Partida: %d/12               Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   " Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EMPATE1:
		printf(	   "     Primeira bateria de apostas empatou \n") ;
		printf(	   "         (as duas equipes pontuam)\n") ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                Equipe Impar\n") ;
		printf(	   " Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   " Rodada: %d(+1)/2           Rodada: %d(+1)/2\n", pontosRodadaPar-1, pontosRodadaImpar-1) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EQUIPE_PAR:
		printf(	   "      Equipe PAR venceu a(s) aposta(s)\n") ; 
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                 Equipe Impar\n") ;
		printf(	   " Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   " Rodada: %d(+1)/2            Rodada: %d/2\n", pontosRodadaPar-1, pontosRodadaImpar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EQUIPE_IMPAR:
		printf(	   "     Equipe IMPAR venceu a(s) aposta(s)\n") ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                Equipe Impar\n") ;
		printf(	   " Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   " Rodada: %d/2               Rodada: %d(+1)/2\n", pontosRodadaPar, pontosRodadaImpar-1) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	} //fim switch

	printf("\n") ;
	PrintarMesa(pCabecaMesa) ;
	printf("\n") ;

	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", opcao, 1);

	while (*opcao != 49) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	
		
} //fim função


/********************* FUNÇÕES DE EXECUCAO DE OPÇÕES **********************/
/***************************************************************************
*  Função: &Executar opcao da tela de inicio
***************************************************************************/
int ExecutarOpcaoInicio (int opcao) {

	switch(opcao) {

	case 49: //(1) iniciar partida

		opcao = PrintarTelaNumJogadores ();
		switch(opcao) {
		case 49: 
			return 2;
		case 50: 
			return 4;
		case 51: 
			return 6;
		}
		break;

	case 50: //(2) ver regras

		opcao = PrintarTelaRegras();
		ExecutarOpcaoRegras(opcao);
		break;

	case 51: //(3) sair
		exit(0);
		break;

	} //fim switch

	return 0;
}

/***************************************************************************
*  Função: &Executar opcao da tela de regras
***************************************************************************/
void ExecutarOpcaoRegras (int opcao) {

	switch(opcao) {
	case 49: //(1) voltar
		opcao = PrintarTelaInicio();
		ExecutarOpcaoInicio(opcao);
		break;
	case 50: //(2) sair
		exit(0);
		break;
	}
}


/***************************************************************************
*  Função: &Executar opcao da tela da rodada
***************************************************************************/
void ExecutarOpcaoJogada(LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) {

	//int qtdAceitos = 0 ;
	//int i, quemPediuTruco ;

	//declarando ponteiros e alocando pras cabecas da mao, mesa e lixo
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMaoProx = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//armazenando ponteiro pra lista mesa e lista lixo
	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	//armazenando ponteiro pra lista mao de quem vai fazer a jogada
	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_IrInicioLista(pCabecaMao) ;

	switch(jogada) {

	case APOSTAR_CARTA_1: //(1)

		ExecutarOpcaoApostarCarta (pCabecaSuperior, quemJoga, jogada) ;
		break;

	case APOSTAR_CARTA_2: //(2)

		ExecutarOpcaoApostarCarta (pCabecaSuperior, quemJoga, jogada) ;
		break;
		

	case APOSTAR_CARTA_3: //(3)

		ExecutarOpcaoApostarCarta (pCabecaSuperior, quemJoga, jogada) ;
		break;
		
/*	case DISPENSAR_CARTA_1: //(4)

		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		
		//em um jogo de 2 jogadores
		switch (*numJogadores) {

		case 2: //2 jogadores

			switch (LIS_ObterQtdElem(pCabecaMesa)) {
			case 1: //caso só tenha a vira na mesa (o proximo dispensa e os dois ganham 1 ponto ou mostra e ganha)

				if (*quemJoga == *numJogadores) { 
						*quemJoga = 1 ;
				}
				else {
					*quemJoga += 1 ;
				}

				*opcao = PrintarTelaMostrarDispensar(quemJoga, valorRodada, pontosRodadaPar, pontosRodadaImpar, 
													 pontosPartidaPar, pontosPartidaImpar, pCabecaSuperior) ;

				LIS_IrInicioLista(pCabecaSuperior) ;
				LIS_AvancarElementoCorrente(pCabecaSuperior, *quemJoga) ;
				pCabecaMaoProx = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

				LIS_IrInicioLista(pCabecaMaoProx) ;

				switch(*opcao) {
				case 49: //mostrar carta 1
					BAR_TransferirCarta(pCabecaMaoProx, pCabecaMesa) ;
					break;
				case 50: //mostrar carta 2
					LIS_AvancarElementoCorrente(pCabecaMaoProx, 1) ;
					BAR_TransferirCarta(pCabecaMaoProx, pCabecaMesa) ;
					break;
				case 52: //dispensar carta 1
					BAR_TransferirCarta(pCabecaMaoProx, pCabecaLixo) ;
					break;
				case 53: //dispensar carta 2
					LIS_AvancarElementoCorrente(pCabecaMaoProx, 1) ;
					BAR_TransferirCarta(pCabecaMaoProx, pCabecaLixo) ;
					break;
				}


			case 2: //caso tenha uma aposta na mesa (quem dispensa perde)

				switch (*quemJoga) {
				case 1:	
					*quemJoga = 2 ;
					*pontosRodadaPar += 1 ; 
					break ;
				case 2: 
					*quemJoga = 1 ;
					*pontosRodadaImpar += 1 ;
					break ;
				} //fim switch "quemJoga"

				//retirando as cartas apostadas da mesa
				for (i = 0; i < LIS_ObterQtdElem(pCabecaMesa)-1; i++) {
					LIS_IrFinalLista(pCabecaMesa) ;
					BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
				} //fim for

				break; //fim case "caso tenha uma aposta na mesa"
			} //fim switch "QtdElem na mesa"

			break; //fim case "2 jogadores"

		case 4: //4 jogadores
			break;

		case 6: //6 jogadores
			break;

		} //fim switch "numJogadores"

		break;

	case DISPENSAR_CARTA_2: //(5)

		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		
		//em um jogo de 2 jogadores
		switch (*numJogadores) {

		case 2: //2 jogadores

			switch (LIS_ObterQtdElem(pCabecaMesa)) {
			case 1: //caso só tenha a vira na mesa (o proximo dispensa e os dois ganham 1 ponto ou mostra e ganha)

				if (*quemJoga == *numJogadores) { 
						*quemJoga = 1 ;
				}
				else {
					*quemJoga += 1 ;
				}

				*opcao = PrintarTelaMostrarDispensar(quemJoga, valorRodada, pontosRodadaPar, pontosRodadaImpar, 
													 pontosPartidaPar, pontosPartidaImpar, pCabecaSuperior) ;

				LIS_IrInicioLista(pCabecaSuperior) ;
				LIS_AvancarElementoCorrente(pCabecaSuperior, *quemJoga) ;
				pCabecaMaoProx = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

				LIS_IrInicioLista(pCabecaMaoProx) ;

				switch(*opcao) {
				case 49: //mostrar carta 1
					BAR_TransferirCarta(pCabecaMaoProx, pCabecaMesa) ;
					break;
				case 50: //mostrar carta 2
					LIS_AvancarElementoCorrente(pCabecaMaoProx, 1) ;
					BAR_TransferirCarta(pCabecaMaoProx, pCabecaMesa) ;
					break;
				case 52: //dispensar carta 1
					BAR_TransferirCarta(pCabecaMaoProx, pCabecaLixo) ;
					break;
				case 53: //dispensar carta 2
					LIS_AvancarElementoCorrente(pCabecaMaoProx, 1) ;
					BAR_TransferirCarta(pCabecaMaoProx, pCabecaLixo) ;
					break;
				}


			case 2: //caso tenha uma aposta na mesa (quem dispensa perde)

				switch (*quemJoga) {
				case 1:	
					*quemJoga = 2 ;
					*pontosRodadaPar += 1 ; 
					break ;
				case 2: 
					*quemJoga = 1 ;
					*pontosRodadaImpar += 1 ;
					break ;
				} //fim switch "quemJoga"

				//retirando as cartas apostadas da mesa
				for (i = 0; i < LIS_ObterQtdElem(pCabecaMesa)-1; i++) {
					LIS_IrFinalLista(pCabecaMesa) ;
					BAR_TransferirCarta(pCabecaMesa, pCabecaLixo) ;
				} //fim for

				break; //fim case "caso tenha uma aposta na mesa"
			} //fim switch "QtdElem na mesa"

			break; //fim case "2 jogadores"

		case 4: //4 jogadores
			break;

		case 6: //6 jogadores
			break;

		} //fim switch "numJogadores"

		break;

	case DISPENSAR_CARTA_3: //(6)

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

		break;

	case AUMENTAR_APOSTA: //(7)

		switch(*valorRodada) {
		case 1: *valorRodada = 3; break;
		case 3: *valorRodada = 6; break;
		case 6: *valorRodada = 12; break;
		}

		//salva o jogador que pediu truco
		quemPediuTruco = *quemJoga ;

		//quemJoga passa a ser o jogador seguinte
		if (*quemJoga == *numJogadores) {
			*quemJoga = 1 ;
		}
		else { 
			*quemJoga += 1 ;
		}

		switch(*numJogadores) {
			
		case 2: //2 jogadores
			
			while (*opcao != '49' && *opcao != '50' && *opcao != '51') {

				*opcao = PrintarTelaCorrerAceitarAumentar(quemJoga, pCabecaSuperior, pontosPartidaPar,
													  pontosPartidaImpar, numJogadores, valorRodada,
													  pontosRodadaPar, pontosRodadaImpar) ;
				switch (*opcao) {

				case 49: //correu

					switch (*quemJoga) {
					case EQUIPE_PAR: *pontosRodadaImpar += 1 ; break ;
					case EQUIPE_IMPAR: *pontosRodadaPar += 1 ; break ;
					} //fim switch

					*valorRodada = 1 ;
					break; //fim correu

				case 50: //aceitou

					//quem joga passa a ser o proximo
					if (*quemJoga == *numJogadores) {
						*quemJoga = 1 ;
					}
					else { 
						*quemJoga += 1 ;
					}

					//imprime a tela da rodada
					*opcao = PrintarTelaJogada(quemJoga, valorRodada, pontosRodadaPar, pontosRodadaImpar,
											   pontosPartidaPar, pontosPartidaImpar, pCabecaSuperior) ;

					//executa a jogada do jogador
					ExecutarOpcaoJogada(opcao, quemJoga, numJogadores, valorRodada, 
										pontosRodadaPar, pontosRodadaImpar, pCabecaSuperior,
										pontosPartidaPar, pontosPartidaImpar, numRodadas,
										quemVenceuPrimeiraAposta) ;

					if (LIS_ObterQtdElem(pCabecaMesa) == 2) {
						//imprime a tela da rodada
						*opcao = PrintarTelaJogada(quemJoga, valorRodada, pontosRodadaPar, pontosRodadaImpar,
												   pontosPartidaPar, pontosPartidaImpar, pCabecaSuperior) ;

						//executa a jogada do jogador
						ExecutarOpcaoJogada(opcao, quemJoga, numJogadores, valorRodada, 
											pontosRodadaPar, pontosRodadaImpar, pCabecaSuperior,
											pontosPartidaPar, pontosPartidaImpar, numRodadas,
											quemVenceuPrimeiraAposta) ;
					} //fim if

					break; //fim aceitou

				case 51: //aumentou
					break; //fim aumentou

				} //fim switch

			} //fim while

			break; //fim 2 jogadores
*/
/*		case 4: //4 jogadores
			break; //fim 4 jogadores

		case 6: //6 jogadores
			break; //fim 6 jogadores

		} //fim switch
*/
	} //fim switch

} /******************* FIM FUNÇÃO: Executar opcao rodada *************/

/***************************************************************************
*  Função: &Executar opcao apostar carta
***************************************************************************/
void ExecutarOpcaoApostarCarta (LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) {

	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	//int equipeVencedoraDaAposta,
	//	  equipeVencedoraDaRodada ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrInicioLista(pCabecaMao) ;

	switch (jogada) {
	case APOSTAR_CARTA_1:
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		break;

	case APOSTAR_CARTA_2:
		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		break;

	case APOSTAR_CARTA_3:
		LIS_AvancarElementoCorrente(pCabecaMao, 2) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaMesa) ;
		break; 
	} // fim switch "opcao"

/*	//se nao for a primeira carta a ser colocada na mesa
	if (LIS_ObterQtdElem(pCabecaMesa) > 2) {

		equipeVencedoraDaAposta = DeterminarEquipeVencedoraDaAposta(pCabecaSuperior, quemJoga, numJogadores,
																	pontosRodadaPar, pontosRodadaImpar,
																	pontosPartidaPar, pontosPartidaImpar, 
																	valorRodada, numRodadas, 
																	quemVenceuPrimeiraAposta) ;
		switch(equipeVencedoraDaAposta) {
		case EQUIPE_PAR:

			//se for a primeira aposta (segue a rodada)
			if (*pontosRodadaPar == 0 && *pontosRodadaImpar == 0) {

				*quemVenceuPrimeiraAposta = JOGADOR2 ;

				PrintarTelaFimApostas (pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
									   pontosRodadaPar, pontosRodadaImpar, 
									   pontosPartidaPar, pontosPartidaImpar) ;

				MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

			} //fim if

			//se for a segunda aposta e a primeira empatou ou equipe par venceu (acaba a rodada)
			else if (*pontosRodadaPar == 1) {

				equipeVencedoraDaRodada = EQUIPE_PAR ;

				PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, numRodadas,
									 pontosRodadaPar, pontosRodadaImpar, 
									 pontosPartidaPar, pontosPartidaImpar) ;

				MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

			} //fim else if
				
			//se for a segunda aposta e a equipe par perdeu primeira (segue a rodada)
			else {

				PrintarTelaFimApostas (pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
										pontosRodadaPar, pontosRodadaImpar, 
										pontosPartidaPar, pontosPartidaImpar) ;

				MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

			} //fim else

			equipeVencedoraDaAposta = EQUIPE_PAR ;
			*pontosRodadaPar += 1 ;
			*quemJoga = JOGADOR2 ;

			if (*pontosRodadaPar == 2) {
				*pontosPartidaPar += *valorRodada ;
			}

			break;

		case EQUIPE_IMPAR:

			//se for a primeira aposta (segue a rodada)
			if (*pontosRodadaPar == 0 && *pontosRodadaImpar == 0) {

				*quemVenceuPrimeiraAposta = JOGADOR1 ;

				PrintarTelaFimApostas (pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
										pontosRodadaPar, pontosRodadaImpar, 
										pontosPartidaPar, pontosPartidaImpar) ;

				MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

			} //fim if

			//se for a segunda aposta e a primeira empatou ou equipe impar venceu (acaba a rodada)
			else if (*pontosRodadaImpar == 1) {

				equipeVencedoraDaRodada = EQUIPE_IMPAR ;

				PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, numRodadas,
										pontosRodadaPar, pontosRodadaImpar, 
										pontosPartidaPar, pontosPartidaImpar) ;

				MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

				if (*pontosRodadaImpar == 2) {
					*pontosPartidaImpar += *valorRodada ;
				}

			} //fim else if
				
			//se for a segunda aposta e equipe impar perdeu primeira (segue a rodada)
			else {

				PrintarTelaFimApostas (pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
										pontosRodadaPar, pontosRodadaImpar, 
										pontosPartidaPar, pontosPartidaImpar) ;

				MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

			} //fim else

			equipeVencedoraDaAposta = EQUIPE_IMPAR ;
			*pontosRodadaImpar += 1 ;
			*quemJoga = JOGADOR1 ;

			if (*pontosRodadaImpar == 2) {
				*pontosPartidaImpar += *valorRodada ;
			}

			break;

		case EMPATE1:

			ExecutarEmpate1(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
							pontosRodadaPar, pontosRodadaImpar, 
							pontosPartidaPar, pontosPartidaImpar, quemVenceuPrimeiraAposta, quemJoga) ;
			break;

		case EMPATE2:

			ExecutarEmpate2(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
							pontosRodadaPar, pontosRodadaImpar, 
							pontosPartidaPar, pontosPartidaImpar, quemVenceuPrimeiraAposta, quemJoga) ;
			break ;

		case EMPATE3:

			ExecutarEmpate3(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
							pontosRodadaPar, pontosRodadaImpar, 
							pontosPartidaPar, pontosPartidaImpar, quemVenceuPrimeiraAposta, quemJoga) ;
			break ;

		} //fim switch "equipeVencedoraDaAposta"

	} //fim if "se nao for a primeira carta a ser colocada na mesa"

	//se for a primeira carta colocada na mesa
	else {
		switch (*quemJoga) {
		case 1: *quemJoga = 2; break;
		case 2: *quemJoga = 1; break;
		} //fim switch
	} //fim else
*/
} //fim funcao

/***************************************************************************
*  Função: &Executar opcao dispensar carta
***************************************************************************/
void ExecutarOpcaoDispensarCarta (LIS_tppLista pCabecaSuperior, int *quemJoga, int *numJogadores,
								  int *pontosRodadaPar, int *pontosRodadaImpar,
								  int *pontosPartidaPar, int *pontosPartidaImpar,
								  int *valorRodada, int *numRodadas,
								  int *quemVenceuPrimeiraAposta, char *opcao) {

	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, *quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrInicioLista(pCabecaMao) ;

	switch (*opcao) {
	case 52: //dispensar carta 1
		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		break;

	case 53: //dispensar carta 2
		LIS_AvancarElementoCorrente(pCabecaMao, 1) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		break;

	case 54: //dispensar carta 3
		LIS_AvancarElementoCorrente(pCabecaMao, 2) ;
		BAR_TransferirCarta(pCabecaMao, pCabecaLixo) ;
		break; 
	} // fim switch "opcao"

/*	switch (LIS_ObterQtdElem(pCabecaMesa)) {

	case 1: //caso só tenha a vira na mesa (proximo jogador deve mostrar ou dispensar)
		break; //fim case 1

	case 2: //caso o outro jogador ja tenha apostado (quem dispensou perde)

		switch (*quemJoga) {
		case JOGADOR1:
			equipeVencedoraDaAposta = EQUIPE_PAR ;
			*pontosRodadaPar += 1 ;
			break;
		case JOGADOR2:
			equipeVencedoraDaAposta = EQUIPE_IMPAR ;
			*pontosRodadaImpar += 1 ;
			break;
		} // fim switch "quemJoga"

		//se a equipe par venceu a rodada
		if (*pontosRodadaPar == 2 && *pontosRodadaImpar < 2) {

			equipeVencedoraDaRodada = EQUIPE_PAR ;

			PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, numRodadas,
								 pontosRodadaPar, pontosRodadaImpar, 
								 pontosPartidaPar, pontosPartidaImpar) ;

			*pontosPartidaPar += *valorRodada ;
		}

		//se a equipe impar venceu a rodada
		else if (*pontosRodadaImpar == 2 && *pontosRodadaPar < 2) {

			equipeVencedoraDaRodada = EQUIPE_IMPAR ;

			PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, numRodadas,
									 pontosRodadaPar, pontosRodadaImpar, 
									 pontosPartidaPar, pontosPartidaImpar) ;

			*pontosPartidaImpar += *valorRodada ;
		}

		//se empatou a rodada
		else if (*pontosRodadaImpar == 2 && *pontosRodadaPar == 2) {

			PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta, numRodadas,
								 pontosRodadaPar, pontosRodadaImpar, 
								 pontosPartidaPar, pontosPartidaImpar) ;
		}

		//se empatou a aposta
		else {


		}
		break; //fim case "caso o outro jogador ja tenha apostado"

	} //fim switch "qtd elem na mesa"
*/
} //fim função

/***************************************************************************
*  Função: &Executar empate na segunda aposta
***************************************************************************/
void ExecutarEmpate2(LIS_tppLista pCabecaSuperior, int *valorRodada, int equipeVencedoraDaAposta, int *numRodadas,
					 int *pontosRodadaPar, int *pontosRodadaImpar, 
					 int *pontosPartidaPar, int *pontosPartidaImpar, int *quemVenceuPrimeiraAposta, int *quemJoga) {

	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	int equipeVencedoraDaRodada ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	switch (*quemVenceuPrimeiraAposta) {

	case NINGUEM_VENCEU: //(segue a rodada)

		switch(*quemJoga) {
			case JOGADOR1: 
				*quemJoga = JOGADOR2 ; 
				break ;
			case JOGADOR2: 
				*quemJoga = JOGADOR1 ;
				break ;
		} //fim switch

		MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

		break; //fim case ngm venceu a primeira

	case EQUIPE_PAR: //(acaba a rodada)

		equipeVencedoraDaRodada = EQUIPE_PAR ;

		MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

		*pontosRodadaPar += 1 ;
		*quemJoga = JOGADOR2 ;
		*pontosPartidaPar += *valorRodada ;

		break; //fim case equipe par venceu a primeira

	case EQUIPE_IMPAR: //(acaba a rodada)

		equipeVencedoraDaRodada = EQUIPE_IMPAR ;

		MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

		*pontosRodadaImpar += 1 ;
		*quemJoga = JOGADOR1 ;
		*pontosPartidaImpar += *valorRodada ;

		break; //fim case equipe impar venceu a primeira

	} //fim switch "quemVenceuPrimeiraAposta"
}