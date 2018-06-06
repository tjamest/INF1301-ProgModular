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
//1 BATERIA DE APOSTA é formada por 2, 4 ou 6 jogadas

//TODO MUNDO PODE PEDIR TRUCO MAS N PODE ESCONDER A CARTA NA PRIMEIRA JOGADA

#define TAM 40

#define CORREU 0
#define EQUIPE_IMPAR 1
#define EQUIPE_PAR 2
#define EMPATE1 -1
#define EMPATE2 -2
#define EMPATE3 -3

//jogadores
#define NINGUEM 0
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

//parâmetros pra função obter qtd cartas
#define SEM_PRIMEIRA 0
#define COM_PRIMEIRA 1
#define SEM_ULTIMA 0
#define COM_ULTIMA 1

//parâmetros pra função determinar resultado
#define DESCONSIDERAR 0
#define CONSIDERAR 1

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
void PreencherVetorCartas (BAR_tppCarta vtCartas[]) ;
void EmbaralharVetorCartas (BAR_tppCarta vtCartas[]) ;

int DeterminarResultado(LIS_tppLista pCabecaSuperior, int quemJoga, int quemJogouAPrimeira, int qtdJogadores) ;
int DefinirQuemComeca(int qtdJogadores) ;
void IdentificarQuemJogouQual(int qtdJogadores, int quemJogouAPrimeira, int *quemJogouASegunda, int *quemJogouATerceira, 
							  int *quemJogouAQuarta, int *quemJogouAQuinta, int *quemJogouASexta) ;
int ProximoJogador(int quemJoga, int qtdJogadores) ;

//printar listas
void PrintarBaralho (LIS_tppLista pCabecaBaralho) ;
void PrintarLixo (LIS_tppLista pCabecaLixo) ;
void PrintarMesa (LIS_tppLista pCabecaMesa, int quemJogouAPrimeira, int qtdJogadores) ;
void PrintarMao (LIS_tppLista pCabecaMao) ;

//printar telas (com opcoes)
int PrintarTelaInicio () ;
int PrintarTelaRegras () ;
int PrintarTelaQtdJogadores () ;
int PrintarTelaJogada(int quemJoga, int valorRodada, int quemAumentou,
					  LIS_tppLista pCabecaSuperior,
					  int quemJogouAPrimeira, int qtdJogadores,
					  int pontosRodadaPar, int pontosRodadaImpar,
					  int pontosPartidaPar, int pontosPartidaImpar) ;

int PrintarTelaCorrerAceitarAumentar(int quemJoga, int valorRodada, int qtdJogadores,
									 LIS_tppLista pCabecaSuperior, 
									 int quemJogouAPrimeira,
									 int pontosRodadaPar, int pontosRodadaImpar, 
									 int pontosPartidaPar, int pontosPartidaImpar) ;

void PrintarTelaFimBateriaDeApostas(LIS_tppLista pCabecaSuperior, int valorRodada, int equipeVencedoraDaAposta,
									int qtdRodadas, int quemJogouAPrimeira, int qtdJogadores, int quemCorreu,
									int pontosRodadaPar, int pontosRodadaImpar,
									int pontosPartidaPar, int pontosPartidaImpar) ;

void PrintarTelaFimRodada(LIS_tppLista pCabecaSuperior, int valorRodada, int equipeVencedoraDaRodada,
						  int qtdRodadas,
						  int pontosRodadaPar, int pontosRodadaImpar,
						  int pontosPartidaPar, int pontosPartidaImpar) ;

int PrintarTelaFimPartida(LIS_tppLista pCabecaSuperior,
						  int equipeVencedoraDaPartida, int qtdPartidas,
						  int pontosPartidaPar, int pontosPartidaImpar) ;
//executar opcoes
int ExecutarOpcaoInicio(int opcao) ;
void ExecutarOpcaoRegras(int opcao) ;
int ExecutarOpcaoJogada(LIS_tppLista pCabecaSuperior, int quemJoga, int jogada, int valorRodada) ;
void ExecutarOpcaoApostarCarta (LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) ;
void ExecutarOpcaoDispensarCarta (LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) ;
/**************************************************************************/

BAR_tppCarta VetorAux[TAM];

int main (void) {

	//declara e aloca memória para todas listas do jogo
	LIS_tppLista pCabecaSuperior = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;	//inicio
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//1
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//2
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//3
	LIS_tppLista pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//4
	LIS_tppLista pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//5
	LIS_tppLista pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//6
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//7
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//final

	//declara variaveis
	int opcao,								//opcao de inicio de jogo escolhida (iniciar, regras, qtd jogadores, ir pro inicio, sair)
		jogada,								//jogada escolhida (apostar 123, dispensar 123, aumentar, correr, aceitar)
		valorRodada ,						//valor da rodada corrente
		pontosRodadaPar ,					//quantidade de bateria de apostas ganhas da equipe par
		pontosRodadaImpar ,					//quantidade de bateria de apostas ganhas da equipe impar
		pontosPartidaPar ,					//quantidade de rodadas ganhas da equipe par
		pontosPartidaImpar ,				//quantidade de rodadas ganhas da equipe impar
		quemJoga ,							//quem ta na vez
		quemJogouAPrimeira ,				//quem colocou a primeira carta na mesa
		quemAumentou ,						//quem pediu truco, seis ou doze
		quemCorreu ,						//quem correu do pedido de aumento de aposta
		qtdJogadores ,						//quantidade de jogadores 
		qtdRodadas ,						//quantidade de rodadas concluidas
		qtdPartidas ,						//quantidade de partidas iniciadas
		qtdJogadas ,						//quantidade de jogadas feitas	
		qtdEmpates ,						//quantidade de empates
		qtdCartasViradas ,					//quantidade de cartas apostadas pra baixo (dispensadas)
		qtdJogadasNoAumentoDeAposta,		//qtd de jogadas no loop 'correr aceitar aumentar'
		qtdBateriasDeApostas ,				//quantidade de baterias de apostas (3 é a ultima da rodada)
		atualJogadorVencedor,				//quem é o atual vencedor das apostas de cartas
		equipeVencedoraDaPrimeiraAposta,	//equipe que venceu a primeira bateria de apostas
		equipeVencedoraDaAposta ,			//equipe que venceu a atual bateria de apostas
		equipeVencedoraDaRodada ,			//equipe que venceu a rodada
		equipeVencedoraDaPartida ,			//equipe que venceu a partida
		resultado ;							//resultado da rodada

	//cria a cabeça da lista de listas
	pCabecaSuperior = MES_CriarListaDeListas() ;

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
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaBaralho) ;	//inicio
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao1) ;		//1
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao2) ;		//2
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao3) ;		//3
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao4) ;		//4
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao5) ;		//5
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMao6) ;		//6
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaLixo) ;		//7
	LIS_InserirElementoApos(pCabecaSuperior, pCabecaMesa) ;		//final

	opcao = 49 ;

	//inicio da partida
	while (opcao == 49) {

		//imprime a tela de abertura do jogo
		opcao = PrintarTelaInicio() ;
		qtdJogadores = ExecutarOpcaoInicio(opcao) ;
	
		//define quem comeca
		quemJoga = DefinirQuemComeca(qtdJogadores) ;

		qtdPartidas = 0 ;
		pontosPartidaPar = 0 ;
		pontosPartidaImpar = 0 ;
		qtdRodadas = 0 ;

		//preenche um vetor com cartas
		PreencherVetorCartas(VetorAux) ;

		//inicio da rodada
		while (pontosPartidaPar < 12 && pontosPartidaImpar < 12) {

			atualJogadorVencedor = 0 ;
			quemAumentou = NINGUEM ;
			quemJogouAPrimeira = NINGUEM ;

			pontosRodadaPar = 0 ;
			pontosRodadaImpar = 0 ;
			valorRodada = 1;

			qtdCartasViradas = 0 ;
			qtdJogadas = 0 ;
			qtdEmpates = 0 ;
			qtdBateriasDeApostas = 0 ;

			qtdRodadas += 1 ;

			//embaralha o vetor de cartas (comentar em caso de testes de empate)
			//EmbaralharVetorCartas(VetorAux) ;

			//preenche o baralho
			BAR_PreencherBaralho(pCabecaBaralho, VetorAux) ;

			//distribui as maos
			//MES_DistribuirMaos(pCabecaSuperior, qtdJogadores) ;

			//distribui as maos para testar empates (deve-se coomentar a funçao embaralhar)
			//(para testar empates com manilha deve-se transferir a vira pra mesa antes)
			MES_DistribuirMaosParaTestarEmpates(pCabecaSuperior, qtdJogadores) ;

			//transfere a vira do baralho pra mesa
			BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

			//inicio da jogada
			while (pontosRodadaPar < 2 && pontosRodadaImpar < 2) {

				quemCorreu = NINGUEM ;
				qtdJogadas += 1 ;

				//imprime tela com as opçoes de jogadas
				jogada = PrintarTelaJogada(quemJoga, valorRodada, quemAumentou,
										   pCabecaSuperior,
										   quemJogouAPrimeira, qtdJogadores,
										   pontosRodadaPar, pontosRodadaImpar,
										   pontosPartidaPar, pontosPartidaImpar) ;

				//executa a jogada escolhida (APOSTAR / DISPENSAR / AUMENTAR)
				valorRodada = ExecutarOpcaoJogada(pCabecaSuperior, quemJoga, jogada, valorRodada) ;

				//se for a primeira carta a ser apostada
				if (MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, COM_ULTIMA) == 1 && 
				   (jogada == 49 || jogada == 50 || jogada == 51)) {

					quemJogouAPrimeira = quemJoga ;
				}

				//APOSTOU CARTA
				if (jogada >= 49 && jogada <= 51) {

					//TEM QUE COMPARAR CARTAS
					if ((MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA) - qtdCartasViradas) > 0) {

						//determina o resultado da aposta (VENCEU / PERDEU / EMPATOU)
						//retorna quemJoga se venceu, primeiro jogador com quem empatou se empatou e 0 se perdeu
						resultado = DeterminarResultado(pCabecaSuperior, quemJoga, quemJogouAPrimeira, qtdJogadores) ;

						//JOGADOR VENCEU TODAS CARTAS DA MESA
						if (resultado == quemJoga) {

							//se foi a ultima jogada da bateria de apostas
							if ( qtdJogadas == qtdJogadores) {
								atualJogadorVencedor = quemJoga ;
							}

							//se nao foi a ultima jogada da bateria de apostas
							else {
								atualJogadorVencedor = quemJoga ;
								quemJoga = ProximoJogador(quemJoga, qtdJogadores) ;
							}

						} //fim if "se venceu"

						//JOGADOR EMPATOU COM ALGUMA CARTA DA MESA
						else if (resultado != quemJoga && resultado != 0) {

							//se foi a ultima jogada da bateria de apostas
							if ( qtdJogadas == qtdJogadores) {

								//quem joga na proxima é quem pôs a primeira carta q empatou
								quemJoga = resultado ;
								atualJogadorVencedor = NINGUEM ;
							}

							//se nao foi a ultima jogada da bateria de apostas
							else {
								quemJoga = ProximoJogador(quemJoga, qtdJogadores) ;
								atualJogadorVencedor = NINGUEM ;
							}

						} //fim else if "empatou com alguma carta da mesa"

						//JOGADOR PERDEU						
						else {
							quemJoga = ProximoJogador(quemJoga, qtdJogadores) ;
						}

					} //fim if "se tem que comparar cartas"

					//NAO TEM CARTA PRA COMPARAR
					else {

						atualJogadorVencedor = quemJoga ;

						//pq eh a primeira jogada de aposta e nao acabou as jogadas
						if (qtdJogadas != qtdJogadores) {
							quemJoga = ProximoJogador(quemJoga, qtdJogadores) ;
						}

						//pq ngm apostou nada
						else {
							quemJoga = atualJogadorVencedor ;
						}
					}

				} // fim if "apostou carta"

				//DISPENSOU CARTA
				else if (jogada >= 52 && jogada <= 54) {
					qtdCartasViradas += 1 ;
					quemJoga = ProximoJogador(quemJoga, qtdJogadores) ;
				}

				//AUMENTOU APOSTA
				else {

					quemAumentou = quemJoga ;
					qtdJogadasNoAumentoDeAposta = 0 ;
					quemJoga = ProximoJogador(quemJoga, qtdJogadores) ;

					while( jogada != 49 && qtdJogadasNoAumentoDeAposta < qtdJogadores/2){ 

						jogada = PrintarTelaCorrerAceitarAumentar(quemJoga, valorRodada, qtdJogadores,
																  pCabecaSuperior,
																  quemJogouAPrimeira,
																  pontosRodadaPar, pontosRodadaImpar,
																  pontosPartidaPar,pontosPartidaImpar) ;
						//CORREU
						if (jogada == 49) {

							qtdJogadasNoAumentoDeAposta += 1 ;

							switch (valorRodada) {
							case 3: 
								valorRodada = 1;
								break;
							case 6:
								valorRodada = 3;
								break;
							case 12:
								valorRodada = 6;
								break;
							} //fim switch

							quemCorreu = quemJoga ;
							equipeVencedoraDaAposta = CORREU ;
							atualJogadorVencedor = quemAumentou ;
							quemJoga = quemAumentou ;

							PrintarTelaFimBateriaDeApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta,
														   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
														   pontosRodadaPar, pontosRodadaImpar,
														   pontosPartidaPar, pontosPartidaImpar) ;

							//rodada acaba e equipe de quem aumentou ganha
							switch (quemAumentou % 2) {
							case 0: 
								pontosRodadaPar = 2;
								break;
							case 1:
								pontosRodadaImpar = 2;
								break;
							} //fim switch

							quemAumentou = 0 ;

							MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

						} // fim if "correu"

						//AUMENTOU
						else if (jogada == 51) {

							qtdJogadasNoAumentoDeAposta = 0 ;

							quemAumentou = quemJoga ;

							if (jogada == 51) {
								jogada = 55;
							}

							valorRodada = ExecutarOpcaoJogada(pCabecaSuperior, quemJoga, jogada, valorRodada) ;

							quemJoga = ProximoJogador(quemJoga, qtdJogadores) ;

						} //fim else if "aumentou"

						//ACEITOU
						else {
							qtdJogadasNoAumentoDeAposta += 1 ;
							quemJoga = quemAumentou ;
						} //fim else "aceitou"

					} // fim while

					qtdJogadas -= 1;

				} //fim else "aumentou aposta"

				//TODOS JA FIZERAM JOGADAS (ATUALIZA PONTUACAO DA RODADA)
				if (qtdJogadas == qtdJogadores) {

					qtdBateriasDeApostas += 1 ;

					//ALGUEM VENCEU
					if (atualJogadorVencedor >= 1 && atualJogadorVencedor <= 6) {

						switch (atualJogadorVencedor%2) {

						//EQUIPE PAR VENCEU
						case 0:
							pontosRodadaPar += 1 ;
							equipeVencedoraDaAposta = EQUIPE_PAR ;

							//se for a primeira bateria de apostas
							if (pontosRodadaPar == 1 && pontosRodadaImpar == 0) {
								equipeVencedoraDaPrimeiraAposta = EQUIPE_PAR ;
							}

							break;

						//EQUIPE IMPAR VENCEU
						case 1:
							pontosRodadaImpar += 1 ;
							equipeVencedoraDaAposta = EQUIPE_IMPAR ;

							//se for a primeira bateria de apostas
							if (pontosRodadaPar == 0 && pontosRodadaImpar == 1) {
								equipeVencedoraDaPrimeiraAposta = EQUIPE_IMPAR ;
							}

							break;

						} //fim switch

						PrintarTelaFimBateriaDeApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta,
													   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
													   pontosRodadaPar, pontosRodadaImpar,
													   pontosPartidaPar, pontosPartidaImpar) ;

						MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

						quemJoga = atualJogadorVencedor;
						qtdCartasViradas = 0 ;
						qtdJogadas = 0;

					} //fim if "alguem venceu"

					//EMPATE
					else {

						switch (qtdBateriasDeApostas) {
					
						//EMPATE NA PRIMEIRA BATERIA DE APOSTAS
						case 1:
							equipeVencedoraDaAposta = EMPATE1 ;
							equipeVencedoraDaPrimeiraAposta = EMPATE1 ;
							pontosRodadaImpar += 1 ;
							pontosRodadaPar += 1 ;

							PrintarTelaFimBateriaDeApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta,
														   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
														   pontosRodadaPar, pontosRodadaImpar,
														   pontosPartidaPar, pontosPartidaImpar) ;

							MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

							//quemJoga = atualJogadorVencedor;
							qtdJogadas = 0;

							break;

						//EMPATE NA SEGUNDA BATERIA DE APOSTAS
						case 2:

							//SE NA PRIMEIRA EMPATOU
							if (equipeVencedoraDaPrimeiraAposta == EMPATE1) {

								equipeVencedoraDaAposta = EMPATE2 ;

								PrintarTelaFimBateriaDeApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta,
															   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
															   pontosRodadaPar, pontosRodadaImpar,
															   pontosPartidaPar, pontosPartidaImpar) ;

								MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

								//quemJoga = atualJogadorVencedor;
								qtdJogadas = 0;
								qtdCartasViradas = 0 ;
							}

							//SE NA PRIMEIRA ALGUEM GANHOU
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

								PrintarTelaFimBateriaDeApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta,
															   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
															   pontosRodadaPar, pontosRodadaImpar,
															   pontosPartidaPar, pontosPartidaImpar) ;

								MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

								//quemJoga = atualJogadorVencedor;
								qtdJogadas = 0;
								qtdCartasViradas = 0 ;

							} //fim else

							break;

						//EMPATE NA TERCEIRA BATERIA DE APOSTAS
						case 3:

							//SE NA PRIMEIRA EMPATOU
							if (equipeVencedoraDaPrimeiraAposta == EMPATE1) {

								equipeVencedoraDaAposta = EMPATE3 ;

								PrintarTelaFimBateriaDeApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta,
															   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
															   pontosRodadaPar, pontosRodadaImpar,
															   pontosPartidaPar, pontosPartidaImpar) ;

								MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

								pontosRodadaPar = 2 ;
								pontosRodadaImpar = 2 ;
								qtdJogadas = 0;
								qtdCartasViradas = 0 ;

							} //fim if

							//SE NA PRIMEIRA ALGUEM GANHOU
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

								PrintarTelaFimBateriaDeApostas(pCabecaSuperior, valorRodada, equipeVencedoraDaAposta,
															   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
															   pontosRodadaPar, pontosRodadaImpar,
															   pontosPartidaPar, pontosPartidaImpar) ;

								MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

								qtdJogadas = 0;
								qtdCartasViradas = 0 ;

							} //fim else
						
							break;

						} //fim switch

					} //fim else "empate"

					//FIM DA RODADA (ATUALIZA PONTUACAO DA PARTIDA)
					if (pontosRodadaPar == 2 || pontosRodadaImpar == 2) {

						//EQUIPE PAR VENCEU A RODADA
						if (pontosRodadaImpar < 2) {
							equipeVencedoraDaRodada = EQUIPE_PAR ;
							pontosPartidaPar += valorRodada ;
							PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada,
												 qtdRodadas,
												 pontosRodadaPar, pontosRodadaImpar,
												 pontosPartidaPar, pontosPartidaImpar) ;
						}

						//EQUIPE IMPAR VENCEU A RODADA
						else if (pontosRodadaPar < 2) {
							equipeVencedoraDaRodada = EQUIPE_IMPAR ;
							pontosPartidaImpar += valorRodada ;
							PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, 
												 qtdRodadas,
												 pontosRodadaPar, pontosRodadaImpar,
												 pontosPartidaPar, pontosPartidaImpar) ;
						}

						//RODADA EMPATOU
						else {
							equipeVencedoraDaRodada = NINGUEM ;
							PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada,
												 qtdRodadas,
												 pontosRodadaPar, pontosRodadaImpar,
												 pontosPartidaPar, pontosPartidaImpar) ;
						}

						MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

					} //fim if "se a rodada acabou"

				} //fim if "se todo mundo ja fez sua jogada"

				//NEM TODOS JA FIZERAM JOGADAS
				else {

					//ALGUEM CORREU
					if (pontosRodadaPar == 2 || pontosRodadaImpar == 2) {

						//EQUIPE PAR VENCEU A RODADA
						if (pontosRodadaImpar < 2) {
							equipeVencedoraDaRodada = EQUIPE_PAR ;
							pontosPartidaPar += valorRodada ;
							PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada,
												 qtdRodadas,
												 pontosRodadaPar, pontosRodadaImpar,
												 pontosPartidaPar, pontosPartidaImpar) ;
						}

						//EQUIPE IMPAR VENCEU A RODADA
						else if (pontosRodadaPar < 2) {
							equipeVencedoraDaRodada = EQUIPE_IMPAR ;
							pontosPartidaImpar += valorRodada ;
							PrintarTelaFimRodada(pCabecaSuperior, valorRodada, equipeVencedoraDaRodada, 
												 qtdRodadas,
												 pontosRodadaPar, pontosRodadaImpar,
												 pontosPartidaPar, pontosPartidaImpar) ;
						}

						MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

					} //fim if alguem correu

				} //fim else nem todos fizeram jogadas

			} //fim while jogada

			//LIMPA
			MES_TransferirTodasCartasProLixo(pCabecaSuperior) ;

			//ALGUEM VENCEU A PARTIDA
			if (pontosPartidaPar >= 12 || pontosPartidaImpar >= 12) {

				qtdPartidas += 1 ;

				//EQUIPE PAR VENCEU A PARTIDA
				if (pontosPartidaPar >= 12 && pontosPartidaImpar < 12) {
					equipeVencedoraDaPartida = EQUIPE_PAR ;
				}

				//EQUIPE IMPAR VENCEU A PARTIDA
				else {
					equipeVencedoraDaPartida = EQUIPE_IMPAR ;
				}

			} // fim if "alguem venceu a partida"
	
		} //fim while rodada

		opcao = PrintarTelaFimPartida(pCabecaSuperior, equipeVencedoraDaPartida, qtdPartidas,
									  pontosPartidaPar, pontosPartidaImpar) ;

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
*  Função: &Determinar resultado
***************************************************************************/
int DeterminarResultado (LIS_tppLista pCabecaSuperior, int quemJoga, int quemJogouAPrimeira, int qtdJogadores) {

	BAR_tppCarta pCartaVira = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCartaAposta = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCartaQueEmpatou = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	BAR_tppCarta pCartaMesa = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;
	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	int * quemJogouASegunda = (int*)malloc(sizeof(int)) ;
	int * quemJogouATerceira = (int*)malloc(sizeof(int)) ;
	int * quemJogouAQuarta = (int*)malloc(sizeof(int)) ;
	int * quemJogouAQuinta = (int*)malloc(sizeof(int)) ;
	int * quemJogouASexta = (int*)malloc(sizeof(int)) ;

	int i, j, qtdCartasVencidas, primeiroComQuemEmpatou, resultadoEmpate;

	BAR_tpValorCarta valorAposta, valorCartaMesa, valorCartaQueEmpatou ;
	BAR_tpNaipeCarta naipeAposta, naipeCartaMesa ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrInicioLista(pCabecaMesa) ;
	pCartaVira = BAR_ObterCartaCorr(pCabecaMesa) ;

	LIS_IrFinalLista(pCabecaMesa) ;
	pCartaAposta = BAR_ObterCartaCorr(pCabecaMesa) ;

	qtdCartasVencidas = 0 ;

	primeiroComQuemEmpatou = NINGUEM ;

	IdentificarQuemJogouQual(qtdJogadores, quemJogouAPrimeira, quemJogouASegunda, quemJogouATerceira,
							 quemJogouAQuarta, quemJogouASexta, quemJogouAQuinta) ;

	for (i = 1; i <= MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA); i++) {

		//CARTA APOSTADA == MANILHA
		if (BAR_VerificarSeEhManilha(pCartaAposta, pCartaVira) == BAR_CondRetEhManilha) {

			LIS_IrInicioLista(pCabecaMesa) ;

			//se i = 1 -> i = primeira carta colocada na mesa
			LIS_AvancarElementoCorrente(pCabecaMesa, i) ;
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;

			//CARTA DA MESA == MANILHA (tem que comparar naipes)
			if (BAR_VerificarSeEhManilha(pCartaMesa, pCartaVira) == BAR_CondRetEhManilha) {

				naipeAposta = BAR_ObterNaipe(pCartaAposta) ;
				naipeCartaMesa = BAR_ObterNaipe(pCartaMesa) ;

				//apostador venceu
				if ((int)naipeAposta > (int)naipeCartaMesa) {
					qtdCartasVencidas += 1 ;
				} //fim if

				//apostador perdeu
				else {
					return 0 ;
				} //fim else

			} //fim if

			//CARTA DA MESA != MANILHA (apostador venceu)
			else {
				qtdCartasVencidas += 1 ;
			} //fim else

		} //fim if "se a carta apostada for manilha"

		//CARTA APOSTADA != MANILHA
		else {

			LIS_IrInicioLista(pCabecaMesa) ;

			LIS_AvancarElementoCorrente(pCabecaMesa, i) ;
			pCartaMesa = BAR_ObterCartaCorr(pCabecaMesa) ;

			//CARTA DA MESA != MANILHA (tem que comparar valores)
			if (BAR_VerificarSeEhManilha(pCartaMesa, pCartaVira) == BAR_CondRetNaoEhManilha) {
				
				valorAposta = BAR_ObterValor(pCartaAposta) ;
				valorCartaMesa = BAR_ObterValor(pCartaMesa) ;

				//apostador venceu
				if ((int)valorAposta > (int)valorCartaMesa) {
					qtdCartasVencidas += 1 ;
				} //fim if

				//empataram
				else if ((int)valorAposta == (int)valorCartaMesa) {

					//verificar se tem alguma carta na mesa maior do que a que empatou
					pCartaQueEmpatou = pCartaMesa ;
					valorCartaQueEmpatou = valorCartaMesa ; 
					resultadoEmpate = CONSIDERAR ;

					for (j = 1 ; j <= MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA); j++) {
						LIS_IrInicioLista(pCabecaMesa) ;
						LIS_AvancarElementoCorrente(pCabecaMesa, j) ;
						pCartaMesa = (BAR_tppCarta)LIS_ObterValor(pCabecaMesa) ;
						valorCartaMesa = BAR_ObterValor(pCartaMesa) ;

						if (valorCartaQueEmpatou < valorCartaMesa) {
							resultadoEmpate = DESCONSIDERAR ;
						}
					} //fim for

					if (resultadoEmpate == CONSIDERAR) {

						if (primeiroComQuemEmpatou == NINGUEM) {

							switch (i) {
							case 1:
								primeiroComQuemEmpatou = quemJogouAPrimeira ;
								break ;
							case 2:
								primeiroComQuemEmpatou = *quemJogouASegunda ;
								break ;
							case 3:
								primeiroComQuemEmpatou = *quemJogouATerceira ;
								break ;
							case 4:
								primeiroComQuemEmpatou = *quemJogouAQuarta ;
								break ;
							case 5:
								primeiroComQuemEmpatou = *quemJogouAQuinta ;
								break ;
							case 6:
								primeiroComQuemEmpatou = *quemJogouASexta ;
								break ;
							} //fim switch

						} //fim if

					}//fim if considerar

					//desconsiderar empate (perdeu)
					else {
						return 0 ;
					}

				} //fim else if empataram
				
				//apostador perdeu
				else {
					return 0 ;
				} //fim else

			} //fim if

			//CARTA DA MESA == MANILHA (apostador perdeu)
			else {
				return 0 ;
			} //fim else

		} //fim else "se a carta apostada nao for manilha"

	} //fim for

	//se venceu todas cartas colocadas na mesa
	if (qtdCartasVencidas == MES_ObterQtdCartas(pCabecaMesa, SEM_PRIMEIRA, SEM_ULTIMA)) {
		return quemJoga ;
	}

	//se nao venceu e ainda nao retornou 0, só pode ter empatado
	else {
		return primeiroComQuemEmpatou ;
	}

	return 0 ;
} /*************** Fim função: &Determinar resultado ***************/

/***************************************************************************
*  Função: &Definir quem comeca
***************************************************************************/
int DefinirQuemComeca(int qtdJogadores) {

	//função suporte da rand que faz gerar números diferentes sempre
	srand ((unsigned)time(NULL));

	switch (qtdJogadores) {
		case 2: 
			return 1 + (rand() % 2) ;
		case 4: 
			return 1 + (rand() % 4) ;
		case 6: 
			return 1 + (rand() % 6) ;
	} //fim switch

	return 0;
} //fim funcao

/***************************************************************************
*  Função: &Identificar quem jogou qual
***************************************************************************/
void IdentificarQuemJogouQual(int qtdJogadores, int quemJogouAPrimeira, int *quemJogouASegunda, int *quemJogouATerceira, 
							  int *quemJogouAQuarta, int *quemJogouAQuinta, int *quemJogouASexta) {

	//identificando quem jogou qual
	switch (quemJogouAPrimeira) {

	case JOGADOR1:

		switch (qtdJogadores) {
		case 2:
			*quemJogouASegunda = JOGADOR2;
			break;
		case 4:
			*quemJogouASegunda = JOGADOR2 ;
			*quemJogouATerceira = JOGADOR3 ;
			*quemJogouAQuarta = JOGADOR4 ;
			break;
		case 6:
			*quemJogouASegunda = JOGADOR2 ;
			*quemJogouATerceira = JOGADOR3 ;
			*quemJogouAQuarta = JOGADOR4 ;
			*quemJogouAQuinta = JOGADOR5 ;
			*quemJogouASexta = JOGADOR6 ;
			break;
		} //fim switch qtd jogadores

		break;

	case JOGADOR2:
		
		switch (qtdJogadores) {
		case 2:
			*quemJogouASegunda = JOGADOR1;
			break;
		case 4:
			*quemJogouASegunda = JOGADOR3 ;
			*quemJogouATerceira = JOGADOR4 ;
			*quemJogouAQuarta = JOGADOR1 ;
			break;
		case 6:
			*quemJogouASegunda = JOGADOR3 ;
			*quemJogouATerceira = JOGADOR4 ;
			*quemJogouAQuarta = JOGADOR5 ;
			*quemJogouAQuinta = JOGADOR6 ;
			*quemJogouASexta = JOGADOR1 ;
			break;
		} //fim switch qtd jogadores

		break ;

	case JOGADOR3:
		
		switch (qtdJogadores) {
		case 4:
			*quemJogouASegunda = JOGADOR4 ;
			*quemJogouATerceira = JOGADOR1 ;
			*quemJogouAQuarta = JOGADOR2 ;
			break;
		case 6:
			*quemJogouASegunda = JOGADOR4 ;
			*quemJogouATerceira = JOGADOR5 ;
			*quemJogouAQuarta = JOGADOR6 ;
			*quemJogouAQuinta = JOGADOR1 ;
			*quemJogouASexta = JOGADOR2 ;
			break;
		} //fim switch qtd jogadores

		break ;

	case JOGADOR4:
		
		switch (qtdJogadores) {
		case 4:
			*quemJogouASegunda = JOGADOR1 ;
			*quemJogouATerceira = JOGADOR2 ;
			*quemJogouAQuarta = JOGADOR3 ;
			break;
		case 6:
			*quemJogouASegunda = JOGADOR5 ;
			*quemJogouATerceira = JOGADOR6 ;
			*quemJogouAQuarta = JOGADOR1 ;
			*quemJogouAQuinta = JOGADOR2 ;
			*quemJogouASexta = JOGADOR3 ;
			break;
		} //fim switch qtd jogadores

		break ;

	case JOGADOR5:

		*quemJogouASegunda = JOGADOR6 ;
		*quemJogouATerceira = JOGADOR1 ;
		*quemJogouAQuarta = JOGADOR2 ;
		*quemJogouAQuinta = JOGADOR3 ;
		*quemJogouASexta = JOGADOR4 ;
		break ;

	case JOGADOR6:

		*quemJogouASegunda = JOGADOR1 ;
		*quemJogouATerceira = JOGADOR2 ;
		*quemJogouAQuarta = JOGADOR3 ;
		*quemJogouAQuinta = JOGADOR4 ;
		*quemJogouASexta = JOGADOR5 ;
		break ;

	} //fim switch quem jogou a primeira

} //fim funcao

/***************************************************************************
*  Função: &Proximo jogador
***************************************************************************/
int ProximoJogador(int quemJoga, int qtdJogadores) {

	switch (qtdJogadores) {
	case 2: 
		switch (quemJoga) {
		case 1: return 2;
		case 2: return 1;
		}
	case 4:
		switch (quemJoga) {
		case 1: return 2;
		case 2: return 3;
		case 3: return 4;
		case 4: return 1;
		}
	case 6:
		switch (quemJoga) {
		case 1: return 2;
		case 2: return 3;
		case 3: return 4;
		case 4: return 5;
		case 5: return 6;
		case 6: return 1;
		}
	}
	return 0 ;
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
	qtdCartas = MES_ObterQtdCartas(pCabecaBaralho, COM_PRIMEIRA, COM_ULTIMA) ;
	
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
		case (10): valorStr = "X"; break;
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
void PrintarMesa (LIS_tppLista pCabecaMesa, int quemJogouAPrimeira, int qtdJogadores) {
	
	int i, 
		qtdCartas, 
		valorInt, 
		naipeInt ;

	int * quemJogouASegunda = (int*)malloc(sizeof(int)) ;
	int * quemJogouATerceira = (int*)malloc(sizeof(int)) ;
	int * quemJogouAQuarta = (int*)malloc(sizeof(int)) ;
	int * quemJogouAQuinta = (int*)malloc(sizeof(int)) ;
	int * quemJogouASexta = (int*)malloc(sizeof(int)) ;

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
	qtdCartas = MES_ObterQtdCartas(pCabecaMesa, COM_PRIMEIRA, COM_ULTIMA) ;

	//identifica qual jogador jogou qual carta através de quem jogou a primeira e da qtd de jogadores
	IdentificarQuemJogouQual(qtdJogadores, quemJogouAPrimeira, quemJogouASegunda, quemJogouATerceira, 
							 quemJogouAQuarta, quemJogouAQuinta, quemJogouASexta) ;

	for(i = 1; i <= qtdCartas; i++) {

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
		case (10): valorStr = "X"; break;
		}

		switch (naipeInt) {
		case (0): naipeStr = "Ouros"; break;
		case (1): naipeStr = "Espadas"; break;
		case (2): naipeStr = "Copas"; break;
		case (3): naipeStr = "Paus"; break;
		case (4): break;
		}

		switch (i) {
		case 1: //vira
			printf ("                  MESA:\n") ;
			printf ("              VIRA - %s de %s\n", valorStr, naipeStr);
			break;

		case 2: //primeira carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("         JOGADOR %d - %s\n", quemJogouAPrimeira, valorStr);
			}
			else {
				printf ("         JOGADOR %d - %s de %s\n", quemJogouAPrimeira, valorStr, naipeStr);
			}
			break;
		
		case 3: //segunda carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("         JOGADOR %d - %s\n", *quemJogouASegunda, valorStr);
			}
			else {
				printf ("         JOGADOR %d - %s de %s\n", *quemJogouASegunda, valorStr, naipeStr);
			}
			break;

		case 4: //terceira carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("         JOGADOR %d - %s\n", *quemJogouATerceira, valorStr);
			}
			else {
				printf ("         JOGADOR %d - %s de %s\n", *quemJogouATerceira, valorStr, naipeStr);
			}
			break;

		case 5: //quarta carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("         JOGADOR %d - %s\n", *quemJogouAQuarta, valorStr);
			}
			else {
				printf ("         JOGADOR %d - %s de %s\n", *quemJogouAQuarta, valorStr, naipeStr);
			}
			break;

		case 6: //quinta carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("         JOGADOR %d - %s\n", *quemJogouAQuinta, valorStr);
			}
			else {
				printf ("         JOGADOR %d - %s de %s\n", *quemJogouAQuinta, valorStr, naipeStr);
			}
			break;

		case 7: //sexta carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("         JOGADOR %d - %s\n", *quemJogouASexta, valorStr);
			}
			else {
				printf ("         JOGADOR %d - %s de %s\n", *quemJogouASexta, valorStr, naipeStr);
			}
			break;

		} // fim switch

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
	qtdCartas = MES_ObterQtdCartas(pCabecaMao, COM_PRIMEIRA, COM_ULTIMA);
	
	//printando as cartas
	printf("\n                  MAO:\n") ;
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
		case (10): valorStr = "X"; break;
		}

		switch (naipeInt) {
		case (0): naipeStr = "Ouros"; break;
		case (1): naipeStr = "Espadas"; break;
		case (2): naipeStr = "Copas"; break;
		case (3): naipeStr = "Paus"; break;
		}

		//printando a carta
		printf ("              %d) %s de %s\n", i+1, valorStr, naipeStr);

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

	//obtem a quantidade de elementos no lixo
	qtdCartas = MES_ObterQtdCartas(pCabecaLixo, COM_PRIMEIRA, COM_ULTIMA);
	
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
		case (10): valorStr = "X"; break;
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
int PrintarTelaQtdJogadores () {

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
int PrintarTelaJogada(int quemJoga, int valorRodada, int quemAumentou,
					  LIS_tppLista pCabecaSuperior,
					  int quemJogouAPrimeira, int qtdJogadores,
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

	PrintarMesa(pCabecaMesa, quemJogouAPrimeira, qtdJogadores) ;
	PrintarMao(pCabecaMao) ;

	printf("\n Valor da rodada: %d\n", valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;

	switch (MES_ObterQtdCartas(pCabecaMao, COM_PRIMEIRA, COM_ULTIMA)) {

	case 1: //1 carta na mao
		printf(" (1) Apostar carta 1\n") ;
		printf(" (4) Dispensar carta 1\n") ;

		if (quemAumentou != quemJoga) {
			switch (valorRodada) {
			case 1: printf(" (7) Pedir truco\n"); break;
			case 3: printf(" (7) Pedir seis\n"); break;
			case 6: printf(" (7) Pedir doze\n"); break;
			} //fim switch

			printf("\n");
			printf(" Opcao: ") ;
			scanf_s(" %c", jogada, 1) ;

			while (*jogada != 49 && *jogada != 52 && *jogada != 55) {
			scanf_s(" %c", jogada, 1);

			} //fim while
		} //fim if

		else {
			printf("\n");
			printf(" Opcao: ") ;
			scanf_s(" %c", jogada, 1) ;

			while (*jogada != 49 && *jogada != 52) {
				scanf_s(" %c", jogada, 1);
			} //fim while
		} //fim else

		system("cls");
		break;

	case 2: //2 cartas na mao
		printf(" (1) Apostar carta 1   | (2) Apostar carta 2 \n") ;
		printf(" (4) Dispensar carta 1 | (5) Dispensar carta 2\n") ;

		if (quemAumentou != quemJoga) {
			switch (valorRodada) {
			case 1: printf(" (7) Pedir truco\n"); break;
			case 3: printf(" (7) Pedir seis\n"); break;
			case 6: printf(" (7) Pedir doze\n"); break;
			} //fim switch

			printf("\n");
			printf(" Opcao: ") ;
			scanf_s(" %c", jogada, 1) ;

			while (*jogada != 49 && *jogada != 50 && *jogada != 52 && *jogada != 53 && *jogada != 55) {
			scanf_s(" %c", jogada, 1);

			} //fim while
		} //fim if

		else {
			printf("\n");
			printf(" Opcao: ") ;
			scanf_s(" %c", jogada, 1) ;

			while (*jogada != 49 && *jogada != 50 && *jogada != 52 && *jogada != 53) {
				scanf_s(" %c", jogada, 1);
			} //fim while
		} //fim else

		system("cls");
		break;

	case 3: //3 cartas na mao (primeira jogada)
		printf(" (1) Apostar carta 1   | (2) Apostar carta 2   | (3) Apostar carta 3\n") ;

		if (quemAumentou != quemJoga) {
			switch (valorRodada) {
			case 1: printf(" (7) Pedir truco\n"); break;
			case 3: printf(" (7) Pedir seis\n"); break;
			case 6: printf(" (7) Pedir doze\n"); break;
			} //fim switch

			printf("\n");
			printf(" Opcao: ") ;
			scanf_s(" %c", jogada, 1) ;

			while (*jogada != 49 && *jogada != 50 && *jogada != 51 && *jogada != 55) {
			scanf_s(" %c", jogada, 1);

			} //fim while
		} //fim if

		else {
			printf("\n");
			printf(" Opcao: ") ;
			scanf_s(" %c", jogada, 1) ;

			while (*jogada != 49 && *jogada != 50 && *jogada != 51) {
				scanf_s(" %c", jogada, 1);
			} //fim while
		} //fim else

		system("cls");
		break;

	} //fim switch

	system("cls") ;
	return *jogada ;
}

/***************************************************************************
*  Função: &Printar tela de correr, aceitar ou aumentar
***************************************************************************/
int PrintarTelaCorrerAceitarAumentar(int quemJoga, int valorRodada, int qtdJogadores,
									 LIS_tppLista pCabecaSuperior, 
									 int quemJogouAPrimeira,
									 int pontosRodadaPar, int pontosRodadaImpar, 
									 int pontosPartidaPar, int pontosPartidaImpar) {

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
	switch (quemJoga) {
	case 1: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 2: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	case 3: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 4: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	case 5: printf("~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~\n", quemJoga); break;
	case 6: printf("~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~\n", quemJoga); break;
	}
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" Jogador %d joga (nao deixe que ninguem veja suas cartas).\n\n", quemJoga) ;
	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", opcao, 1);

	system("cls") ;

	//printa cabeçalho da tela
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

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	PrintarMesa(pCabecaMesa, quemJogouAPrimeira, qtdJogadores) ;
	PrintarMao(pCabecaMao) ;

	printf("\n Valor da rodada: %d\n", valorRodada);

	printf(" \n O que deseja fazer?\n\n") ;
	printf(" (1) Correr   | (2) Aceitar") ;

	switch (valorRodada) {
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

return 0;
}


/***************************************************************************
*  Função: &Printar tela fim das apostas
***************************************************************************/
void PrintarTelaFimBateriaDeApostas(LIS_tppLista pCabecaSuperior, int valorRodada, 
									int equipeVencedoraDaAposta, int qtdRodadas,
									int quemJogouAPrimeira, int qtdJogadores, int quemCorreu,
									int pontosRodadaPar, int pontosRodadaImpar,
									int pontosPartidaPar, int pontosPartidaImpar) {

	char * opcao = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	//tela fim apostas 
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~~~~ RODADA %d ~~~~~~~~~~~~~~~~\n", qtdRodadas) ;

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
		
	case CORREU:

		switch (quemCorreu) {
		case JOGADOR1:
			equipeVencedoraDaAposta = EQUIPE_PAR ;
			break ;
		case JOGADOR2:
			equipeVencedoraDaAposta = EQUIPE_IMPAR ;
			break ;
		case JOGADOR3:
			equipeVencedoraDaAposta = EQUIPE_PAR ;
			break ;
		case JOGADOR4:
			equipeVencedoraDaAposta = EQUIPE_IMPAR ;
			break ;
		case JOGADOR5:
			equipeVencedoraDaAposta = EQUIPE_PAR ;
			break ;
		case JOGADOR6:
			equipeVencedoraDaAposta = EQUIPE_IMPAR ;
			break ;
		} //fim switch

		switch (equipeVencedoraDaAposta) {

		case EQUIPE_PAR: //EQUIPE PAR VENCEU

				printf(	   "      Equipe PAR venceu a(s) aposta(s)\n") ;
				printf(	   "            (jogador %d correu)\n", quemCorreu) ;
		
			switch (pontosRodadaPar) {

			case 0: //EQUIPE PAR TEM 0 PONTO
				printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
				printf(	   " Equipe Par                Equipe Impar\n") ;
				printf(	   " Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
				printf(	   " Rodada: %d(+2)/2           Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
				break;

			case 1: //EQUIPE PAR TEM 1 PONTO
				printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
				printf(	   " Equipe Par                Equipe Impar\n") ;
				printf(	   " Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
				printf(	   " Rodada: %d(+1)/2           Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
				break;

			} // fim switch "equipe par venceu"

			break;

		case EQUIPE_IMPAR: //EQUIPE IMPAR VENCEU

				printf(	   "      Equipe IMPAR venceu a(s) aposta(s)\n") ;
				printf(	   "            (jogador %d correu)\n", quemCorreu) ;

			switch (pontosRodadaImpar) {

			case 0: //EQUIPE IMPAR TEM 0 PONTO
				printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
				printf(	   " Equipe Par                Equipe Impar\n") ;
				printf(	   " Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
				printf(	   " Rodada: %d/2               Rodada: %d(+2)/2\n", pontosRodadaPar, pontosRodadaImpar) ;
				break;

			case 1: //EQUIPE IMPAR TEM 1 PONTO
				printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
				printf(	   " Equipe Par                Equipe Impar\n") ;
				printf(	   " Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
				printf(	   " Rodada: %d/2               Rodada: %d(+1)/2\n", pontosRodadaPar, pontosRodadaImpar) ;
				break;
			} // fim switch "equipe impar venceu"

			break;

		} // fim switch

		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	} //fim switch

	printf("\n") ;
	PrintarMesa(pCabecaMesa, quemJogouAPrimeira, qtdJogadores) ;
	printf("\n") ;

	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", opcao, 1);

	while (*opcao != 49) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");
	
		
} //fim função

/***************************************************************************
*  Função: &Printar tela fim da rodada
***************************************************************************/
void PrintarTelaFimRodada(LIS_tppLista pCabecaSuperior, int valorRodada, 
						  int equipeVencedoraDaRodada, int qtdRodadas,
						  int pontosRodadaPar, int pontosRodadaImpar,
						  int pontosPartidaPar, int pontosPartidaImpar) {

	char * opcao = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	//tela fim rodada 
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~~~~ RODADA %d ~~~~~~~~~~~~~~~~\n", qtdRodadas) ;

	switch (equipeVencedoraDaRodada) {

	case EQUIPE_PAR:
		printf(	   "        Equipe PAR venceu a rodada\n") ; 
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                  Equipe Impar\n") ;
		printf(	   " Partida: %d(+%d)/12           Partida: %d/12\n", pontosPartidaPar-(valorRodada), valorRodada, pontosPartidaImpar) ;
		printf(	   " Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ; 
		break ;

	case EQUIPE_IMPAR:
		printf(	   "       Equipe IMPAR venceu a rodada\n") ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par                 Equipe Impar\n") ;
		printf(	   " Partida: %d/12            Partida: %d(+%d)/12\n", pontosPartidaPar, pontosPartidaImpar-(valorRodada), valorRodada) ;
		printf(	   " Rodada: %d/2                Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
		break ;

	case NINGUEM:
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
*  Função: &Printar tela fim da partida
***************************************************************************/
int PrintarTelaFimPartida(LIS_tppLista pCabecaSuperior,
						  int equipeVencedoraDaPartida, int qtdPartidas,
						  int pontosPartidaPar, int pontosPartidaImpar) {

	char * opcao = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	//tela fim apostas 
	printf(		   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~\n") ;
	printf(		   "~~~~~~~~~~~~~~~~ PARTIDA %d ~~~~~~~~~~~~~~~~\n", qtdPartidas) ;

	switch (equipeVencedoraDaPartida) {

	case EQUIPE_PAR:
		printf(	   "        Equipe PAR venceu a partida\n") ; 
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par: 12            Equipe Impar: %d\n", pontosPartidaImpar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EQUIPE_IMPAR:
		printf(	   "       Equipe IMPAR venceu a partida\n") ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   " Equipe Par: %d            Equipe Impar: 12\n", pontosPartidaPar) ;
		printf(	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	} //fim switch

	//PrintarLixo(pCabecaLixo) ;
	//printf("\n") ;

	printf(" \n O que deseja fazer?\n\n") ;
	printf(" (1) Ir pro inicio | (2) Sair\n\n") ;
	printf(" Opcao: ");

	while (*opcao != 49 && *opcao != 50) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");

	return *opcao ;
	
} //fim função


/********************* FUNÇÕES DE EXECUCAO DE OPÇÕES **********************/
/***************************************************************************
*  Função: &Executar opcao da tela de inicio
***************************************************************************/
int ExecutarOpcaoInicio (int opcao) {

	switch(opcao) {

	case 49: //(1) iniciar partida

		opcao = PrintarTelaQtdJogadores ();
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
int ExecutarOpcaoJogada(LIS_tppLista pCabecaSuperior, int quemJoga, int jogada, int valorRodada) {

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
		
	case DISPENSAR_CARTA_1: //(4)
		ExecutarOpcaoDispensarCarta (pCabecaSuperior, quemJoga, jogada) ;
		break;

	case DISPENSAR_CARTA_2: //(5)
		ExecutarOpcaoDispensarCarta (pCabecaSuperior, quemJoga, jogada) ;
		break;

	case DISPENSAR_CARTA_3: //(6)
		ExecutarOpcaoDispensarCarta (pCabecaSuperior, quemJoga, jogada) ;
		break;

	case AUMENTAR_APOSTA: //(6)

		switch(valorRodada) {
		case 1:
			return 3;
		case 3:
			return 6;
		case 6:
			return 12;
		} //fim switch

	} //fim switch

	return valorRodada;

} /******************* FIM FUNÇÃO: Executar opcao rodada *************/

/***************************************************************************
*  Função: &Executar opcao apostar carta
***************************************************************************/
void ExecutarOpcaoApostarCarta (LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) {

	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	
	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

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

} //fim funcao

/***************************************************************************
*  Função: &Executar opcao dispensar carta
***************************************************************************/
void ExecutarOpcaoDispensarCarta (LIS_tppLista pCabecaSuperior, int quemJoga, int jogada) {

	LIS_tppLista pCabecaMao = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	BAR_tppCarta pCartaVirada = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, -1) ;
	pCabecaLixo = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	LIS_IrInicioLista(pCabecaMao) ;

	switch (jogada) {
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

	pCartaVirada = BAR_CriarCarta(_X, X) ;
	LIS_InserirElementoApos(pCabecaMesa, pCartaVirada) ;

} //fim função