	/***************************************************************************
*  $MCI Módulo de implementação: INT Interface
*
*  Arquivo gerado:              INTERFACE.c
*  Letras identificadoras:      INT
*
*  Projeto: INF 1301 Jogo de Truco
*  Autores: gsc, jvr, tgf
*
*  $HA Histórico de evolução:
*  Versão  		Autor  			Data    	Observações
*     1     gsc, jvr, tgf    02/jun/2018    início desenvolvimento
***************************************************************************/

#include "LISTA.h"
#include "BARALHO.h"
#include "MESA.h"
#include "INTERFACE.h"
#include <stdio.h>	//printf
#include <stdlib.h>	//rand e srand
#include <string.h>	//strcmp

#ifdef _DEBUG
	#include <assert.h> //assert
#endif

#define TAM 40

#define INICIALIZAR 0

//resultados
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

//parametros pra funcao MES_EsvaziarMesa
#define DEIXA_VIRA 0
#define TIRA_VIRA 1

//paramestros pra funcao MES_ObterQtdCartas
#define SEM_PRIMEIRA 0
#define COM_PRIMEIRA 1
#define SEM_ULTIMA 0
#define COM_ULTIMA 1

//parâmetros pra função MES_DeterminarResultado
#define DESCONSIDERAR 0
#define CONSIDERAR 1

BAR_tppCarta VetorAux[TAM];

int main (void) {

	//declara todas listas do jogo
	LIS_tppLista pCabecaSuperior ; 	//cabeca da lista de listas
	LIS_tppLista pCabecaBaralho ;	//inicio
	LIS_tppLista pCabecaMao1 ;		//1
	LIS_tppLista pCabecaMao2 ;		//2
	LIS_tppLista pCabecaMao3 ;		//3
	LIS_tppLista pCabecaMao4 ;		//4
	LIS_tppLista pCabecaMao5 ;		//5
	LIS_tppLista pCabecaMao6 ;		//6
	LIS_tppLista pCabecaLixo ;		//7
	LIS_tppLista pCabecaMesa ;		//final

	//declara variaveis
	int opcao ,								//opcao de inicio de jogo escolhida (iniciar, regras, qtd jogadores, ir pro inicio, sair)
		jogada ,							//jogada escolhida (apostar 123, dispensar 123, aumentar, correr, aceitar)
		valorRodada ,						//valor da rodada corrente
		pontosRodadaPar ,					//quantidade de bateria de apostas ganhas da equipe par
		pontosRodadaImpar ,					//quantidade de bateria de apostas ganhas da equipe impar
		pontosPartidaPar ,					//quantidade de rodadas ganhas da equipe par
		pontosPartidaImpar ,				//quantidade de rodadas ganhas da equipe impar
		quemJoga ,							//quem ta na vez
		quemJogouAPrimeira ,				//quem colocou a primeira carta na mesa
		quemAumentou ,						//quem pediu truco, seis ou doze
		quemCorreu ,						//quem correu do pedido de aumento de aposta
		qtdAceitos,							//quantidade de vezes que aceitaram o aumento de aposta
		qtdJogadores ,						//quantidade de jogadores 
		qtdRodadas ,						//quantidade de rodadas concluidas
		qtdPartidas ,						//quantidade de partidas iniciadas
		qtdJogadas ,						//quantidade de jogadas feitas	
		qtdEmpates ,						//quantidade de empates
		qtdCartasViradas ,					//quantidade de cartas apostadas pra baixo (dispensadas)
		qtdBateriasDeApostas ,				//quantidade de baterias de apostas (3 é a ultima da rodada)
		atualJogadorVencedor ,				//quem é o atual vencedor das apostas de cartas
		equipeVencedoraDaPrimeiraAposta ,	//equipe que venceu a primeira bateria de apostas
		equipeVencedoraDaAposta ,			//equipe que venceu a atual bateria de apostas
		equipeVencedoraDaRodada ,			//equipe que venceu a rodada
		equipeVencedoraDaPartida ,			//equipe que venceu a partida
		equipeComOnze ,						//equipe com onze pontos
		resultado ;							//resultado da rodada

	MES_tpCondRet mesaCondRet ;

	#ifdef _DEBUG
	BAR_tppCarta pCartaAux ;
	char * opcaoDebug = (char*)malloc(sizeof(char));
	#endif

	qtdPartidas = 0 ;
	qtdJogadores = 0 ;
	opcao = 0 ;
	equipeComOnze = 0 ;
	valorRodada = 0;

	while (opcao == 0) {

		opcao = PrintarTelaInicio() ;

		if (opcao == 50) {
			opcao = PrintarTelaRegras();
			if (opcao == 49) {
				opcao = 0 ;
			}
		} //fim if

	} //fim while
	
	//inicio da partida
	while (opcao == 49) {

		if (qtdPartidas > 0) {

			opcao = 0;

			while (opcao == 0) {

				opcao = PrintarTelaInicio() ;

				if (opcao == 50) {
					opcao = PrintarTelaRegras();
					if (opcao == 49) {
						opcao = 0 ;
					}
					else {
						return 0;
					}
				} //fim if

				else{
					if (opcao == 51) {
						return 0;
					}
				} //fim else

			} //fim while

		} //fim if

		#ifdef _DEBUG
		printf("Escolheu iniciar partida.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
		scanf(" %c", opcaoDebug);
		#endif

		equipeVencedoraDaAposta = INICIALIZAR ;
		equipeVencedoraDaPrimeiraAposta = INICIALIZAR ;
		equipeVencedoraDaPartida = INICIALIZAR ;
		qtdJogadores = INICIALIZAR ;

		opcao = PrintarTelaQtdJogadores() ;

		switch (opcao) {
		case 49:
			qtdJogadores = 2;
			break;
		case 50:
			qtdJogadores = 4;
			break;
		case 51:
			qtdJogadores = 6;
			break;
		} //fim switch

		#ifdef _DEBUG
		assert(qtdJogadores == 2 || qtdJogadores == 4 || qtdJogadores == 6) ;
		printf("Quantidade de jogadores definida.\n") ;
		Delay() ;
		#endif

		//aloca memória para todas listas do jogo
		pCabecaSuperior = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ; 	//cabeca da lista de listas
		pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;	//inicio
		pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//1
		pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//2
		pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//3
		pCabecaMao4 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//4
		pCabecaMao5 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//5
		pCabecaMao6 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//6
		pCabecaLixo = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//7
		pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;		//final

		//cria a cabeça da lista de listas
		pCabecaSuperior = MES_CriarListaDeListas() ;

		#ifdef _DEBUG
		assert( pCabecaSuperior != NULL ) ;
		printf("Lista de listas criada.\n") ;
		Delay() ;
		#endif

		//cria a lista baralho (vazia)
		pCabecaBaralho = BAR_CriarBaralho() ;

		#ifdef _DEBUG
		assert( pCabecaBaralho != NULL ) ;
		printf("Baralho criado.\n") ;
		Delay() ;
		#endif

		//cria as 6 maos (vazias)
		pCabecaMao1 = MES_CriarMao() ;
		pCabecaMao2 = MES_CriarMao() ;
		pCabecaMao3 = MES_CriarMao() ;
		pCabecaMao4 = MES_CriarMao() ;
		pCabecaMao5 = MES_CriarMao() ;
		pCabecaMao6 = MES_CriarMao() ;

		#ifdef _DEBUG
		assert( pCabecaMao1 != NULL ) ;
		assert( pCabecaMao2 != NULL ) ;
		assert( pCabecaMao3 != NULL ) ;
		assert( pCabecaMao4 != NULL ) ;
		assert( pCabecaMao5 != NULL ) ;
		assert( pCabecaMao6 != NULL ) ;
		printf("Maos criadas.\n") ;
		Delay() ;
		#endif

		//cria o lixo (vazio)
		pCabecaLixo = MES_CriarLixo() ;

		#ifdef _DEBUG
		assert( pCabecaLixo != NULL ) ;
		printf("Lixo criado.\n") ;
		Delay() ;
		#endif

		//cria a mesa (vazia)
		pCabecaMesa = MES_CriarMesa() ;

		#ifdef _DEBUG
		assert( pCabecaMesa != NULL ) ;
		printf("Mesa criada.\n") ;
		Delay() ;
		#endif

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

		#ifdef _DEBUG
		assert( LIS_ObterQtdElem(pCabecaSuperior) == 9 ) ;
		printf("Listas inseridas na lista de listas.\n") ;
		Delay() ;
		#endif
	
		//define quem comeca
		quemJoga = MES_DefinirQuemComeca(qtdJogadores) ;

		qtdPartidas++ ;
		pontosPartidaPar = 0 ;
		pontosPartidaImpar = 0 ;
		qtdRodadas = 0 ;

		#ifdef _DEBUG
			assert(quemJoga >= 1 && quemJoga <=6) ;
			printf("Quem comeca definido.\n") ;
			Delay() ;
		#endif

		//preenche um vetor com cartas
		BAR_PreencherVetorCartas(VetorAux) ;

		#ifdef _DEBUG
			assert ( (sizeof(VetorAux) / sizeof(VetorAux[0])) == 40 ) ;
			printf("Vetor cartas preenchido.\n") ;
			Delay() ;
		#endif

		//inicio da rodada
		while (pontosPartidaPar < 12 && pontosPartidaImpar < 12) {

			quemJogouAPrimeira = NINGUEM ;
			quemAumentou = NINGUEM ;
			atualJogadorVencedor = NINGUEM ;

			pontosRodadaPar = 0 ;
			pontosRodadaImpar = 0 ;

			qtdCartasViradas = 0 ;
			qtdJogadas = 0 ;
			qtdEmpates = 0 ;
			qtdBateriasDeApostas = 0 ;

			#ifdef _DEBUG
			pCartaAux = VetorAux[0] ;
			printf("Variaveis reiniciadas.\n") ;
			Delay() ;
			#endif

			qtdRodadas += 1 ;

			if ((pontosPartidaPar < 11 && pontosPartidaImpar < 11) ||
				(pontosPartidaPar == 11 && pontosPartidaImpar == 11)) {

				valorRodada = 1;

				//embaralha o vetor de cartas (comentar em caso de testes de empate)
				BAR_EmbaralharVetorCartas(VetorAux) ;

				#ifdef _DEBUG
				assert (pCartaAux != VetorAux[0]) ;
				printf("Vetor cartas embaralhado.\n") ;
				Delay() ;
				#endif

				//preenche o baralho
				BAR_PreencherBaralho(pCabecaBaralho, VetorAux) ;

				#ifdef _DEBUG
				assert (LIS_ObterQtdElem(pCabecaBaralho) == 40) ;
				printf("Baralho preenchido com o vetor embaralhado.\n") ;
				Delay() ;
				#endif

				//distribui as maos
				mesaCondRet = MES_DistribuirMaos(pCabecaSuperior, qtdJogadores) ;

				#ifdef _DEBUG
				assert (mesaCondRet == MES_CondRetOK) ;
				printf("Maos distribuidas.\n") ;
				Delay() ;
				#endif
			}
			
			//distribui as maos para testar empates (deve-se comentar a funçao embaralhar)
			//MES_DistribuirMaosParaTestarEmpates(pCabecaSuperior, qtdJogadores) ;
			
			//transfere a vira do baralho pra mesa
			BAR_TransferirCarta(pCabecaBaralho, pCabecaMesa) ;

			#ifdef _DEBUG
			assert (LIS_ObterQtdElem(pCabecaMesa) == 1) ;
			printf("Vira transferida pra mesa.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
			scanf(" %c", opcaoDebug);
			#endif

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

						//determina o resultado da aposta (quemJoga se VENCEU / 0 se PERDEU / primeirocComQuemEmpatou se EMPATOU)
						resultado = MES_DeterminarResultado(pCabecaSuperior, quemJoga, quemJogouAPrimeira, qtdJogadores) ;

						//JOGADOR VENCEU TODAS CARTAS DA MESA
						if (resultado == quemJoga) {

							//se foi a ultima jogada da bateria de apostas
							if ( qtdJogadas == qtdJogadores) {
								atualJogadorVencedor = quemJoga ;
							}

							//se nao foi a ultima jogada da bateria de apostas
							else {
								atualJogadorVencedor = quemJoga ;
								quemJoga = MES_ProximoJogador(quemJoga, qtdJogadores) ;

								#ifdef _DEBUG
									assert (quemJoga >= 0 && quemJoga <= 6) ;
									printf("(1) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
									scanf(" %c", opcaoDebug);
									Delay() ;
								#endif
							}

						} //fim if "se venceu"

						//JOGADOR EMPATOU COM A MAIOR CARTA DA MESA
						else if (resultado != quemJoga && resultado != 0) {

							//se foi a ultima jogada da bateria de apostas
							if (qtdJogadas == qtdJogadores) {

								//quem joga na proxima é quem pôs a primeira carta q empatou
								quemJoga = resultado ;
								atualJogadorVencedor = NINGUEM ;
							}

							//se nao foi a ultima jogada da bateria de apostas
							else {
								quemJoga = MES_ProximoJogador(quemJoga, qtdJogadores) ;
								atualJogadorVencedor = NINGUEM ;
								#ifdef _DEBUG
									assert (quemJoga >= 0 && quemJoga <= 6) ;
									printf("(2) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
									scanf(" %c", opcaoDebug);
									Delay() ;
								#endif
							}

						} //fim else if "empatou com alguma carta da mesa"

						//JOGADOR PERDEU						
						else {
							quemJoga = MES_ProximoJogador(quemJoga, qtdJogadores) ;

							#ifdef _DEBUG
								assert (quemJoga >= 0 && quemJoga <= 6) ;
								printf("(3) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
								scanf(" %c", opcaoDebug);
								Delay() ;
							#endif
						}

					} //fim if "se tem que comparar cartas"

					//NAO TEM CARTA PRA COMPARAR
					else {

						atualJogadorVencedor = quemJoga ;

						//pq eh a primeira jogada de aposta e nao acabou as jogadas
						if (qtdJogadas != qtdJogadores) {
							quemJoga = MES_ProximoJogador(quemJoga, qtdJogadores) ;

							#ifdef _DEBUG
								assert (quemJoga >= 0 && quemJoga <= 6) ;
								printf("(4) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
								scanf(" %c", opcaoDebug);
								Delay() ;
							#endif
						}

						//pq ngm apostou nada e acabaram as jogadas
						else {
							quemJoga = atualJogadorVencedor ;

							#ifdef _DEBUG
								assert (quemJoga >= 0 && quemJoga <= 6) ;
								printf("(5) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
								scanf(" %c", opcaoDebug);
								Delay() ;
							#endif
						}
					}

				} // fim if "apostou carta"

				//DISPENSOU CARTA
				else if (jogada >= 52 && jogada <= 54) {
					qtdCartasViradas += 1 ;
					quemJoga = MES_ProximoJogador(quemJoga, qtdJogadores) ;

					#ifdef _DEBUG
						assert (quemJoga >= 0 && quemJoga <= 6) ;
						printf("(6) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
						scanf(" %c", opcaoDebug);
						Delay() ;
					#endif
				}

				//AUMENTOU APOSTA
				else {

					qtdAceitos = 0 ;
					quemAumentou = quemJoga ;
					quemJoga = MES_ProximoJogador(quemJoga, qtdJogadores) ;

					#ifdef _DEBUG
						assert (quemJoga >= 0 && quemJoga <= 6) ;
						printf("(7) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
						scanf(" %c", opcaoDebug);
						Delay() ;
					#endif

					while( jogada != 49 && qtdAceitos < qtdJogadores/2){ 

						jogada = PrintarTelaCorrerAceitarAumentar(quemJoga, valorRodada, qtdJogadores,
																  pCabecaSuperior,
																  quemJogouAPrimeira,
																  pontosRodadaPar, pontosRodadaImpar,
																  pontosPartidaPar,pontosPartidaImpar) ;
						//CORREU
						if (jogada == 49) {

							#ifdef _DEBUG
								printf("Correu.\n") ;
								Delay() ;
							#endif

							switch (valorRodada) {
							case 3: 
								valorRodada = 1;
								break;
							case 6:
								valorRodada = 3;
								break;
							case 9:
								valorRodada = 6;
								break;
							case 12:
								valorRodada = 9;
								break;
							} //fim switch

							quemCorreu = quemJoga ;
							equipeVencedoraDaAposta = CORREU ;
							atualJogadorVencedor = quemAumentou ;
							quemJoga = quemAumentou ;

							#ifdef _DEBUG
								assert (quemJoga >= 0 && quemJoga <= 6) ;
								printf("(8) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
								scanf(" %c", opcaoDebug);
								Delay() ;
							#endif

							PrintarTelaFimBateriaDeApostas(pCabecaSuperior, equipeVencedoraDaAposta,
														   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
														   pontosRodadaPar, pontosRodadaImpar,
														   pontosPartidaPar, pontosPartidaImpar) ;

							//rodada acaba e equipe de quem aumentou ganha
							switch (quemCorreu%2) {
							case 0: 
								pontosRodadaImpar = 2;
								break;
							case 1:
								pontosRodadaPar = 2;
								break;
							} //fim switch

							quemAumentou = NINGUEM ;

							MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

						} // fim if "correu"

						//AUMENTOU
						else if (jogada == 51) {

							//restarta o loop
							qtdAceitos = 0 ;

							//quemAumentou = quemJoga ;

							if (jogada == 51) {
								jogada = 55;
							}

							valorRodada = ExecutarOpcaoJogada(pCabecaSuperior, quemJoga, jogada, valorRodada) ;

							quemJoga = MES_ProximoJogador(quemJoga, qtdJogadores) ;

							#ifdef _DEBUG
								assert (quemJoga >= 0 && quemJoga <= 6) ;
								printf("(9) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
								scanf(" %c", opcaoDebug);
								Delay() ;
							#endif

						} //fim else if "aumentou"

						//ACEITOU
						else {

							#ifdef _DEBUG
								printf("Aceitou.\n") ;
								Delay() ;
							#endif

							qtdAceitos += 1 ;
							quemJoga = MES_ProximoJogadorDaMesmaEquipe(quemJoga, qtdJogadores) ;

							#ifdef _DEBUG
								if (qtdAceitos != qtdJogadores/2) {
									assert (quemJoga >= 0 && quemJoga <= 6) ;
									printf("(10) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
									scanf(" %c", opcaoDebug);
									Delay() ;
								}
							#endif

						} //fim else "aceitou"

					} // fim while

					if (qtdAceitos == qtdJogadores/2) {
						quemJoga = quemAumentou ;

						#ifdef _DEBUG
							assert (quemJoga >= 0 && quemJoga <= 6) ;
							printf("(11) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
							scanf(" %c", opcaoDebug);
							Delay() ;
						#endif
					}

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

						PrintarTelaFimBateriaDeApostas(pCabecaSuperior, equipeVencedoraDaAposta,
													   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
													   pontosRodadaPar, pontosRodadaImpar,
													   pontosPartidaPar, pontosPartidaImpar) ;

						mesaCondRet = MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

						#ifdef _DEBUG
							assert (LIS_ObterQtdElem(pCabecaMesa) == 1) ;
							printf("(1) Mesa esvaziada deixando a vira.\n") ;
							Delay() ;
						#endif

						quemJoga = atualJogadorVencedor ;

						#ifdef _DEBUG
							assert (quemJoga >= 0 && quemJoga <= 6) ;
							printf("(12) Proximo jogador definido.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
							scanf(" %c", opcaoDebug);
							Delay() ;
						#endif

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

							PrintarTelaFimBateriaDeApostas(pCabecaSuperior, equipeVencedoraDaAposta,
														   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
														   pontosRodadaPar, pontosRodadaImpar,
														   pontosPartidaPar, pontosPartidaImpar) ;

							MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

							#ifdef _DEBUG
								assert (LIS_ObterQtdElem(pCabecaMesa) == 1) ;
								printf("(2) Mesa esvaziada deixando a vira.\n") ;
								Delay() ;
							#endif

							//quemJoga = atualJogadorVencedor;
							qtdJogadas = 0;

							break;

						//EMPATE NA SEGUNDA BATERIA DE APOSTAS
						case 2:

							//SE NA PRIMEIRA EMPATOU
							if (equipeVencedoraDaPrimeiraAposta == EMPATE1) {

								equipeVencedoraDaAposta = EMPATE2 ;

								PrintarTelaFimBateriaDeApostas(pCabecaSuperior, equipeVencedoraDaAposta,
															   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
															   pontosRodadaPar, pontosRodadaImpar,
															   pontosPartidaPar, pontosPartidaImpar) ;

								MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, DEIXA_VIRA) ;

								#ifdef _DEBUG
									assert (LIS_ObterQtdElem(pCabecaMesa) == 1) ;
									printf("(3) Mesa esvaziada deixando a vira.\n") ;
									Delay() ;
								#endif

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

								PrintarTelaFimBateriaDeApostas(pCabecaSuperior, equipeVencedoraDaAposta,
															   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
															   pontosRodadaPar, pontosRodadaImpar,
															   pontosPartidaPar, pontosPartidaImpar) ;

								MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

								#ifdef _DEBUG
									assert (LIS_ObterQtdElem(pCabecaMesa) == 0) ;
									printf("(4) Mesa esvaziada tirando a vira.\n") ;
									Delay() ;
								#endif

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

								PrintarTelaFimBateriaDeApostas(pCabecaSuperior, equipeVencedoraDaAposta,
															   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
															   pontosRodadaPar, pontosRodadaImpar,
															   pontosPartidaPar, pontosPartidaImpar) ;

								MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

								#ifdef _DEBUG
									assert (LIS_ObterQtdElem(pCabecaMesa) == 0) ;
									printf("(5) Mesa esvaziada tirando a vira.\n") ;
									Delay() ;
								#endif

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

								PrintarTelaFimBateriaDeApostas(pCabecaSuperior, equipeVencedoraDaAposta,
															   qtdRodadas, quemJogouAPrimeira, qtdJogadores, quemCorreu,
															   pontosRodadaPar, pontosRodadaImpar,
															   pontosPartidaPar, pontosPartidaImpar) ;

								MES_EsvaziarMesa(pCabecaMesa, pCabecaLixo, TIRA_VIRA) ;

								#ifdef _DEBUG
									assert (LIS_ObterQtdElem(pCabecaMesa) == 0) ;
									printf("(6) Mesa esvaziada tirando a vira.\n") ;
									Delay() ;
								#endif

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

						#ifdef _DEBUG
							assert (LIS_ObterQtdElem(pCabecaMesa) == 0) ;
							printf("(7) Mesa esvaziada tirando a vira.\n") ;
							Delay() ;
						#endif

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

						#ifdef _DEBUG
							assert (LIS_ObterQtdElem(pCabecaMesa) == 0) ;
							printf("(8) Mesa esvaziada tirando a vira.\n") ;
							Delay() ;
						#endif

					} //fim if alguem correu

				} //fim else nem todos fizeram jogadas

			} //fim while jogada

			//LIMPA
			MES_TransferirTodasCartasProLixo(pCabecaSuperior) ;

			#ifdef _DEBUG
				assert (LIS_ObterQtdElem(pCabecaBaralho) == 0) ;
				assert (LIS_ObterQtdElem(pCabecaMao1) == 0) ;
				assert (LIS_ObterQtdElem(pCabecaMao2) == 0) ;
				assert (LIS_ObterQtdElem(pCabecaMao3) == 0) ;
				assert (LIS_ObterQtdElem(pCabecaMao4) == 0) ;
				assert (LIS_ObterQtdElem(pCabecaMao5) == 0) ;
				assert (LIS_ObterQtdElem(pCabecaMao6) == 0) ;
				assert (LIS_ObterQtdElem(pCabecaMesa) == 0) ;
				assert (LIS_ObterQtdElem(pCabecaLixo) > 0) ;
				printf("Todas cartas foram transferidas pro lixo.\n") ;
				Delay() ;
			#endif

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

				MES_EsvaziarLixo (pCabecaLixo) ;

				#ifdef _DEBUG
				assert (LIS_ObterQtdElem(pCabecaLixo) == 0) ;
				printf("Lixo esvaziado.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
				scanf(" %c", opcaoDebug);
				#endif

			} // fim if "alguem venceu a partida"
			
			//ALGUEM TEM ONZE PONTOS
			else if (pontosPartidaPar == 11 || pontosPartidaImpar == 11) {

				#ifdef _DEBUG
				printf("Alguma equipe tem onze pontos.\n") ;
				Delay() ;
				#endif

				//SO UMA EQUIPE TEM ONZE PONTOS
				if ( ( pontosPartidaPar == 11 && pontosPartidaImpar < 11) ||
					 ( pontosPartidaPar < 11 && pontosPartidaImpar == 11) ) {

					if (pontosPartidaPar == 11 && pontosPartidaImpar < 11) {

						#ifdef _DEBUG
						printf("Apenas a equipe par tem onze pontos.\n") ;
						Delay() ;
						#endif

						equipeComOnze = EQUIPE_PAR ;
					}
					else if (pontosPartidaPar < 11 && pontosPartidaImpar == 11) {

						#ifdef _DEBUG
						printf("Apenas a equipe impar tem onze pontos.\n") ;
						Delay() ;
						#endif

						equipeComOnze = EQUIPE_IMPAR ;
					}

					if (( pontosPartidaPar == 11 && pontosPartidaImpar < 11) ||
						( pontosPartidaPar < 11 && pontosPartidaImpar == 11)) {
						opcao = 0;
					}

					while (opcao != 50 && pontosPartidaPar != pontosPartidaImpar ) {

						//embaralha o vetor de cartas (comentar em caso de testes de empate)
						BAR_EmbaralharVetorCartas(VetorAux) ;

						#ifdef _DEBUG
						assert (pCartaAux != VetorAux[0]) ;
						printf("Vetor cartas embaralhado.\n") ;
						Delay() ;
						#endif

						//preenche o baralho
						BAR_PreencherBaralho(pCabecaBaralho, VetorAux) ;

						#ifdef _DEBUG
						assert (LIS_ObterQtdElem(pCabecaBaralho) == 40) ;
						printf("Baralho preenchido com o vetor embaralhado.\n") ;
						Delay() ;
						#endif

						//distribui as maos
						mesaCondRet = MES_DistribuirMaos(pCabecaSuperior, qtdJogadores) ;

						#ifdef _DEBUG
						assert (mesaCondRet == MES_CondRetOK) ;
						printf("Maos distribuidas.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
						scanf(" %c", opcaoDebug);
						#endif

						opcao = PrintarTelaMaoDeOnze(qtdJogadores, pCabecaSuperior,
													 pontosPartidaPar, pontosPartidaImpar) ;

						switch (opcao) {

						case 49: //correu
							switch (equipeComOnze) {
							case EQUIPE_PAR:
								pontosPartidaImpar += 1 ;
								break;
							case EQUIPE_IMPAR:
								pontosPartidaPar += 1 ;
								break;
							} //fim switch

							MES_TransferirTodasCartasProLixo(pCabecaSuperior) ;

							#ifdef _DEBUG
							assert (LIS_ObterQtdElem(pCabecaBaralho) == 0) ;
							assert (LIS_ObterQtdElem(pCabecaMao1) == 0) ;
							assert (LIS_ObterQtdElem(pCabecaMao2) == 0) ;
							assert (LIS_ObterQtdElem(pCabecaMao3) == 0) ;
							assert (LIS_ObterQtdElem(pCabecaMao4) == 0) ;
							assert (LIS_ObterQtdElem(pCabecaMao5) == 0) ;
							assert (LIS_ObterQtdElem(pCabecaMao6) == 0) ;
							assert (LIS_ObterQtdElem(pCabecaMesa) == 0) ;
							assert (LIS_ObterQtdElem(pCabecaLixo) > 0) ;
							printf("Todas cartas foram transferidas pro lixo.\n") ;
							Delay();
							#endif

							break;

						case 50: //aceitou
							valorRodada = 3 ;

							#ifdef _DEBUG
							assert (valorRodada == 3) ;
							printf("Valor da rodada foi atualizado.\n") ;
							Delay();
							#endif

							break;

						} //fim switch "opcao"

					} //fim while "opcao != 50"

				} //fim if "mao de onze"

			} //fim else if "mao de onze"
				
		} //fim while "rodada"

		opcao = PrintarTelaFimPartida(pCabecaSuperior, equipeVencedoraDaPartida, qtdPartidas,
									  pontosPartidaPar, pontosPartidaImpar) ;

		MES_DestruirListas (pCabecaSuperior, pCabecaBaralho,
						  	pCabecaMao1, pCabecaMao2,
						  	pCabecaMao3, pCabecaMao4,
						  	pCabecaMao5, pCabecaMao6,
						  	pCabecaLixo, pCabecaMesa) ;

		#ifdef _DEBUG
		printf("Listas destruidas e variaveis alocadas liberadas.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
		scanf(" %c", opcaoDebug);
		#endif

	} //fim while partida

	#ifdef _DEBUG
	free(opcaoDebug);
	#endif

	return 0;
}

/**************** FUNÇÕES DE IMPRESSAO DE LISTAS NA TELA ******************/
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
	MES_IdentificarQuemJogouQual(qtdJogadores, quemJogouAPrimeira, quemJogouASegunda, quemJogouATerceira, 
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
			printf ("                                    MESA:\n") ;
			printf ("                               VIRA - %s de %s\n", valorStr, naipeStr);
			break;

		case 2: //primeira carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("                          JOGADOR %d - %s\n", quemJogouAPrimeira, valorStr);
			}
			else {
				printf ("                          JOGADOR %d - %s de %s\n", quemJogouAPrimeira, valorStr, naipeStr);
			}
			break;
		
		case 3: //segunda carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("                          JOGADOR %d - %s\n", *quemJogouASegunda, valorStr);
			}
			else {
				printf ("                          JOGADOR %d - %s de %s\n", *quemJogouASegunda, valorStr, naipeStr);
			}
			break;

		case 4: //terceira carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("                          JOGADOR %d - %s\n", *quemJogouATerceira, valorStr);
			}
			else {
				printf ("                          JOGADOR %d - %s de %s\n", *quemJogouATerceira, valorStr, naipeStr);
			}
			break;

		case 5: //quarta carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("                          JOGADOR %d - %s\n", *quemJogouAQuarta, valorStr);
			}
			else {
				printf ("                          JOGADOR %d - %s de %s\n", *quemJogouAQuarta, valorStr, naipeStr);
			}
			break;

		case 6: //quinta carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("                          JOGADOR %d - %s\n", *quemJogouAQuinta, valorStr);
			}
			else {
				printf ("                          JOGADOR %d - %s de %s\n", *quemJogouAQuinta, valorStr, naipeStr);
			}
			break;

		case 7: //sexta carta colocada na mesa por um jogador
			if (strcmp(valorStr, "X") == 0 ) {
				printf ("                          JOGADOR %d - %s\n", *quemJogouASexta, valorStr);
			}
			else {
				printf ("                          JOGADOR %d - %s de %s\n", *quemJogouASexta, valorStr, naipeStr);
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
	printf("\n                                    MAO:\n") ;
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
		printf ("                                %d) %s de %s\n", i+1, valorStr, naipeStr);

		//avancando com o elemento
		CondRetLis = LIS_AvancarElementoCorrente(pCabecaMao, 1) ;

	}//fim for

} /***************** Fim função: &Printar mao *************************/


/********************* FUNÇÕES DE IMPRESSAO DE TELAS **********************/
/***************************************************************************
*  Função: &Printar tela inicial
***************************************************************************/
int PrintarTelaInicio () {

	char * opcao = (char*)malloc(sizeof(char));

	#ifdef _DEBUG
		system("cls") ;
	#endif

	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
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

	#ifdef _DEBUG
		system("cls") ;
	#endif
			 
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	printf(" No jogo de truco os jogadores sao distribuidos em duas equipes: PAR e IMPAR.\n") ;

	printf(" Cada partida eh formada por inumeras rodadas e termina quando alguma equipe consegue 12 ou mais pontos.\n") ;
	printf(" Cada rodada eh formada por ate 3 baterias de apostas e pode valer 1, 3, 6 ou 12 pontos.\n") ;
	printf(" Cada bateria de apostas eh formada por 2, 4 ou 6 jogadas.\n\n") ;

	printf(" As opcoes de jogadas sao:\n") ;
	printf(" Apostar carta, dispensar carta ou aumentar valor da rodada (para 3, 6 ou 12 pontos).\n\n") ;

	printf(" No caso de aumento de aposta, as opcoes de jogadas sao:\n") ;
	printf(" Correr, aceitar ou aumentar ainda mais o valor da aposta.\n\n") ;

	printf(" Caso alguem aumente o valor da aposta:\n") ;
	printf(" Cada jogador da equipe adversaria deve 'aceitar' o aumento de valor.\n\n") ;

	printf(" Caso alguem 'corra' do aumento de aposta:\n") ;
	printf(" O aumento do valor da rodada nao ocorre e a equipe adversaria ganha a rodada.\n\n") ;

	printf(" Em cada rodada, uma carta eh retirada do baralho e colocada sobre a mesa (a vira).\n") ;
	printf(" Essa carta determina qual a carta mais forte da rodada (a manilha).\n\n") ;

	printf(" Em cada bateria de apostas, vence o jogador que apostar a carta mais forte:\n\n") ;

	printf("                  4 (mais fraca)         Ouros (mais fraco)\n");
	printf("                  5                      Espadas\n");
	printf("                  6                      Copas\n");
	printf("                  7                      Paus  (mais forte)\n");
	printf("                  Q\n");
	printf("                  J\n");
	printf("                  K                      Quando alguem dispensa uma\n");
	printf("                  A                      carta essa carta tem seu valor\n");
	printf("                  2                      representado na mesa como X\n");
	printf("                  3 (mais forte)\n\n");

	printf(" Os naipes apenas sao considerados para manilhas.\n") ;
	printf(" Ou seja, caso ninguem aposte uma manilha, pode haver empate.\n\n") ;

	printf(" Caso apenas um jogador aposte manilha, ele vence a bateria de apostas.\n") ;
	printf(" Caso mais de um jogador aposte manilha, o desempate eh feito pelos naipes.\n\n") ;

	printf(" Em cada rodada, vence a equipe que ganhar primeiro duas baterias de apostas.\n\n") ;

	printf(" Em caso de empate na primeira, as duas equipes pontuam com essa bateria de apostas.\n") ;
	printf(" Em caso de empate na segunda, vence a equipe que tiver vencido a primeira.\n") ;
	printf(" Em caso de empate na primeira e na segunda, vence a equipe que vencer a terceira.\n") ;
	printf(" Em caso de empate na terceira, vence a equipe que tiver vencido a primeira.\n") ;
	printf(" Em caso de empate nas tres baterias de apostas, ninguem pontua na rodada.\n\n") ;

	printf(" O que deseja fazer?\n\n");
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

	#ifdef _DEBUG
		system("cls") ;
	#endif

	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
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

	#ifdef _DEBUG
		system("cls") ;
	#endif
	
	//tela de confirmacao 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	switch (quemJoga) {
	case 1: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 2: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 3: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 4: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 5: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 6: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	}
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "                   Equipe Par                 Equipe Impar\n") ;
	if (pontosPartidaPar < 10) {
		printf(	   "                   Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	else {
		printf(	   "                   Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	printf(		   "                   Rodada: %d/2                Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;

	if (pontosPartidaPar < 11 && pontosPartidaImpar <11) {
		printf(" Jogador %d joga (nao deixe que ninguem veja suas cartas).\n\n", quemJoga) ;
	}
	else {
		printf(" Jogador %d joga.\n\n", quemJoga) ;
	}
	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", jogada, 1);

	while (*jogada != 49) {
		scanf_s(" %c", jogada, 1);
	} //fim while

	system("cls");

	//tela da jogada
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	switch (quemJoga) {
	case 1: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 2: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 3: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 4: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 5: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 6: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	}
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "                   Equipe Par                 Equipe Impar\n") ;
	if (pontosPartidaPar < 10) {
		printf(	   "                   Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	else {
		printf(	   "                   Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	printf(		   "                   Rodada: %d/2                Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	if (valorRodada < 10) {
		printf(	   "                                                         Valor da Rodada: %d\n", valorRodada) ;
	}
	else {
		printf(	   "                                                        Valor da Rodada: %d\n", valorRodada) ;
	}

	PrintarMesa(pCabecaMesa, quemJogouAPrimeira, qtdJogadores) ;
	if (pontosPartidaPar == 11 && pontosPartidaImpar == 11){
		printf(	   "\n                                (Mao de Ferro)\n") ;
	}
	else {
		PrintarMao(pCabecaMao) ;
	}

	printf(		   " \n O que deseja fazer?\n\n") ;

	switch (MES_ObterQtdCartas(pCabecaMao, COM_PRIMEIRA, COM_ULTIMA)) {

	case 1: //1 carta na mao
		printf(" (1) Apostar carta 1\n") ;
		printf(" (4) Dispensar carta 1\n") ;

		if (quemAumentou != quemJoga) {
			if ( (pontosPartidaPar < 11 && pontosPartidaImpar < 11) ||
				 (pontosPartidaPar < 11 && pontosPartidaImpar == 11) ||
				 (pontosPartidaPar == 11 && pontosPartidaImpar < 11) ) {
				switch (valorRodada) {
				case 1: printf(" (7) Pedir truco\n"); break;
				case 3: printf(" (7) Pedir seis\n"); break;
				case 6: printf(" (7) Pedir nove\n"); break;
				case 9: printf(" (7) Pedir doze\n"); break;
				} //fim switch
			}

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
			if ( (pontosPartidaPar < 11 && pontosPartidaImpar < 11) ||
				 (pontosPartidaPar < 11 && pontosPartidaImpar == 11) ||
				 (pontosPartidaPar == 11 && pontosPartidaImpar < 11) ) {
				switch (valorRodada) {
				case 1: printf(" (7) Pedir truco\n"); break;
				case 3: printf(" (7) Pedir seis\n"); break;
				case 6: printf(" (7) Pedir nove\n"); break;
				case 9: printf(" (7) Pedir doze\n"); break;			
				} //fim switch
			}

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
			if ( (pontosPartidaPar < 11 && pontosPartidaImpar < 11) ||
				 (pontosPartidaPar < 11 && pontosPartidaImpar == 11) ||
				 (pontosPartidaPar == 11 && pontosPartidaImpar < 11) ) {
				switch (valorRodada) {
				case 1: printf(" (7) Pedir truco\n"); break;
				case 3: printf(" (7) Pedir seis\n"); break;
				case 6: printf(" (7) Pedir nove\n"); break;
				case 9: printf(" (7) Pedir doze\n"); break;
				} //fim switch
			}

			#ifdef _DEBUG
			if (valorRodada != 11) {
				if (pontosPartidaPar != 11 || pontosPartidaImpar != 11) {
					printf(" (8) Pedir onze (para testes)\n") ;
				}
			}
			#endif

			printf("\n Opcao: ") ;
			scanf_s(" %c", jogada, 1) ;

			#ifndef _DEBUG
			while (*jogada != 49 && *jogada != 50 && *jogada != 51 && *jogada != 55) {
				scanf_s(" %c", jogada, 1);
			} //fim while
			#endif

			#ifdef _DEBUG
			while (*jogada != 49 && *jogada != 50 && *jogada != 51 && *jogada != 55 && *jogada != 56) {
				scanf_s(" %c", jogada, 1);

			} //fim while
			#endif
		} //fim if

		else {

			#ifdef _DEBUG
			if (valorRodada != 11 && pontosPartidaPar != 11 && pontosPartidaImpar != 11) {
				printf(" (8) Aumentar pontuacao pra 11 (para testes)\n") ;
			}
			#endif

			printf("\n");
			printf(" Opcao: ") ;
			scanf_s(" %c", jogada, 1) ;

			#ifndef _DEBUG
			while (*jogada != 49 && *jogada != 50 && *jogada != 51) {
				scanf_s(" %c", jogada, 1);
			} //fim while
			#endif

			#ifdef _DEBUG
			while (*jogada != 49 && *jogada != 50 && *jogada != 51 && *jogada != 56) {
				scanf_s(" %c", jogada, 1);
			} //fim while
			#endif
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

	#ifdef _DEBUG
		system("cls") ;
	#endif

	//tela de confirmacao
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	switch (quemJoga) {
	case 1: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 2: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 3: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 4: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 5: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 6: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	}
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(" Jogador %d joga (nao deixe que ninguem veja suas cartas).\n\n", quemJoga) ;
	printf(" Digite '1' para avancar.\n");
	printf(" ");
	scanf_s(" %c", opcao, 1);

	system("cls") ;

	//printa cabeçalho da tela
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	switch (quemJoga) {
	case 1: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 2: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 3: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 4: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 5: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	case 6: printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR JOGADOR %d ~~~~~~~~~~~~~~~~~~~~~~~~~~\n", quemJoga); break;
	}
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "                   Equipe Par                 Equipe Impar\n") ;
	printf(		   "                   Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	printf(		   "                   Rodada: %d/2                Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	if (valorRodada < 10) {
		printf(	   "                                                         Valor da Rodada: %d\n", valorRodada) ;
	}
	else {
		printf(	   "                                                        Valor da Rodada: %d\n", valorRodada) ;
	}

	LIS_IrInicioLista(pCabecaSuperior) ;
	LIS_AvancarElementoCorrente(pCabecaSuperior, quemJoga) ;
	pCabecaMao = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	PrintarMesa(pCabecaMesa, quemJogouAPrimeira, qtdJogadores) ;
	PrintarMao(pCabecaMao) ;

	printf(" \n O que deseja fazer?\n\n") ;
	printf(" (1) Correr   | (2) Aceitar") ;

	switch (valorRodada) {
	case 3: printf("   | (3) Pedir seis\n"); break;
	case 6: printf("   | (3) Pedir nove\n"); break;
	case 9: printf("   | (3) Pedir doze\n"); break;
	case 12: printf("\n"); break;
	}

	printf("\n Opcao: ") ;
	scanf_s(" %c", opcao, 1) ;

	while (*opcao < 49 && *opcao > 52) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls") ;
	return *opcao ;

} /*********** FIM FUNÇÃO: Printar tela correr aceitar aumentar ***********/


/***************************************************************************
*  Função: &Printar tela fim das apostas
***************************************************************************/
void PrintarTelaFimBateriaDeApostas(LIS_tppLista pCabecaSuperior,  
									int equipeVencedoraDaAposta, int qtdRodadas,
									int quemJogouAPrimeira, int qtdJogadores, int quemCorreu,
									int pontosRodadaPar, int pontosRodadaImpar,
									int pontosPartidaPar, int pontosPartidaImpar) {

	char * opcao = (char*)malloc(sizeof(char)) ;
	
	LIS_tppLista pCabecaMesa = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	LIS_IrFinalLista(pCabecaSuperior) ;
	pCabecaMesa = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;

	#ifdef _DEBUG
		system("cls") ;
	#endif
	
	//tela fim apostas 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RODADA %d ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", qtdRodadas) ;

	switch (equipeVencedoraDaAposta) {

	case EMPATE3:
		printf(	   "                    Terceira bateria de apostas empatou\n") ;
		printf(	   "                        (nenhuma das equipes pontua)\n") ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                    Equipe Par                  Equipe Impar\n") ;
		printf(	   "                    Partida: %d/12               Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   "                    Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EMPATE2:
		printf(	   "                     Segunda bateria de apostas empatou\n") ;
		printf(	   "                         (nenhuma das equipes pontua)\n") ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                    Equipe Par                  Equipe Impar\n") ;
		printf(	   "                    Partida: %d/12               Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   "                    Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EMPATE1:
		printf(	   "                    Primeira bateria de apostas empatou \n") ;
		printf(	   "                          (as duas equipes pontuam)\n") ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                    Equipe Par                Equipe Impar\n") ;
		printf(	   "                    Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   "                    Rodada: %d(+1)/2           Rodada: %d(+1)/2\n", pontosRodadaPar-1, pontosRodadaImpar-1) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EQUIPE_PAR:
		printf(	   "                      Equipe PAR venceu a(s) aposta(s)\n") ; 
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                    Equipe Par                 Equipe Impar\n") ;
		printf(	   "                    Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   "                    Rodada: %d(+1)/2            Rodada: %d/2\n", pontosRodadaPar-1, pontosRodadaImpar) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EQUIPE_IMPAR:
		printf(	   "                      Equipe IMPAR venceu a(s) aposta(s)\n") ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                    Equipe Par                Equipe Impar\n") ;
		printf(	   "                    Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   "                    Rodada: %d/2               Rodada: %d(+1)/2\n", pontosRodadaPar, pontosRodadaImpar-1) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
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

				printf(	   "                       Equipe PAR venceu a(s) aposta(s)\n") ;
				printf(	   "                              (jogador %d correu)\n", quemCorreu) ;
		
			switch (pontosRodadaPar) {

			case 0: //EQUIPE PAR TEM 0 PONTO
				printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
				printf(	   "                    Equipe Par                Equipe Impar\n") ;
				printf(	   "                    Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
				printf(	   "                    Rodada: %d(+2)/2           Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
				break;

			case 1: //EQUIPE PAR TEM 1 PONTO
				printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
				printf(	   "                    Equipe Par                Equipe Impar\n") ;
				printf(	   "                    Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
				printf(	   "                    Rodada: %d(+1)/2           Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
				break;

			} // fim switch "equipe par venceu"

			break;

		case EQUIPE_IMPAR: //EQUIPE IMPAR VENCEU

				printf(	   "                      Equipe IMPAR venceu a(s) aposta(s)\n") ;
				printf(	   "                              (jogador %d correu)\n", quemCorreu) ;

			switch (pontosRodadaImpar) {

			case 0: //EQUIPE IMPAR TEM 0 PONTO
				printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
				printf(	   "                    Equipe Par                Equipe Impar\n") ;
				printf(	   "                    Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
				printf(	   "                    Rodada: %d/2               Rodada: %d(+2)/2\n", pontosRodadaPar, pontosRodadaImpar) ;
				break;

			case 1: //EQUIPE IMPAR TEM 1 PONTO
				printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
				printf(	   "                    Equipe Par                Equipe Impar\n") ;
				printf(	   "                    Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
				printf(	   "                    Rodada: %d/2               Rodada: %d(+1)/2\n", pontosRodadaPar, pontosRodadaImpar) ;
				break;
			} // fim switch "equipe impar venceu"

			break;

		} // fim switch

		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
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

	#ifdef _DEBUG
		system("cls") ;
	#endif
	
	//tela fim rodada 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RODADA %d ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", qtdRodadas) ;

	switch (equipeVencedoraDaRodada) {

	case EQUIPE_PAR:
		printf(	   "                         Equipe PAR venceu a rodada\n") ; 
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                   Equipe Par                  Equipe Impar\n") ;
		printf(	   "                   Partida: %d(+%d)/12           Partida: %d/12\n", pontosPartidaPar-(valorRodada), valorRodada, pontosPartidaImpar) ;
		printf(	   "                   Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ; 
		break ;

	case EQUIPE_IMPAR:
		printf(	   "                        Equipe IMPAR venceu a rodada\n") ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                   Equipe Par                 Equipe Impar\n") ;
		printf(	   "                   Partida: %d/12            Partida: %d(+%d)/12\n", pontosPartidaPar, pontosPartidaImpar-(valorRodada), valorRodada) ;
		printf(	   "                   Rodada: %d/2                Rodada: %d/2\n", pontosRodadaPar, pontosRodadaImpar) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
		break ;

	case NINGUEM:
		printf(	   "                                Rodada empatou\n") ;
		printf(	   "                         (nenhuma das equipes pontua)\n") ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                   Equipe Par                  Equipe Impar\n") ;
		printf(	   "                   Partida: %d/12               Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   "                   Rodada: %d/2                 Rodada: %d/2\n", pontosRodadaPar-1, pontosRodadaImpar-1) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
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

	#ifdef _DEBUG
		system("cls") ;
	#endif
	
	//tela fim apostas 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PARTIDA %d ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", qtdPartidas) ;

	switch (equipeVencedoraDaPartida) {

	case EQUIPE_PAR:
		printf(	   "                         Equipe PAR venceu a partida\n") ; 
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                  Equipe Par: %d            Equipe Impar: %d\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	case EQUIPE_IMPAR:
		printf(	   "                        Equipe IMPAR venceu a partida\n") ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		printf(	   "                  Equipe Par: %d            Equipe Impar: %d\n", pontosPartidaPar, pontosPartidaImpar) ;
		printf(	   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
		break ;

	} //fim switch

	printf(" \n O que deseja fazer?\n\n") ;
	printf(" (1) Ir pro inicio | (2) Sair\n\n") ;
	printf(" Opcao: ");

	while (*opcao != 49 && *opcao != 50) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls");

	return *opcao ;
	
} //fim função Printar tela fim partida

/***************************************************************************
*  Função: &Printar tela de correr, aceitar ou aumentar
***************************************************************************/
int PrintarTelaMaoDeOnze(int qtdJogadores, LIS_tppLista pCabecaSuperior,
						 int pontosPartidaPar, int pontosPartidaImpar) {

	int equipeComOnze = INICIALIZAR ;

	//aloca memoria pra opcao de jogada escolhida										
	char * opcao = (char*)malloc(sizeof(char)) ;

	//declara e aloca memoria pra cabeca da mao e da mesa
	LIS_tppLista pCabecaMao1 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao2 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	LIS_tppLista pCabecaMao3 = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

	if (pontosPartidaPar == 11 && pontosPartidaImpar < 11) {
		equipeComOnze = EQUIPE_PAR ;
	}
	else if (pontosPartidaPar < 11 && pontosPartidaImpar == 11) {
		equipeComOnze = EQUIPE_IMPAR ;
	}

	#ifdef _DEBUG
	system("cls") ;
	#endif

	//tela de confirmacao
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	switch (equipeComOnze) {
	case EQUIPE_IMPAR: 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "                   Equipe Par                 Equipe Impar\n") ;
	if (pontosPartidaPar < 10) {
		printf(	   "                   Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	else {
		printf(	   "                   Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	printf(		   "                   Rodada: 0/2                Rodada: 0/2\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(		   " Equipe impar decide (nao deixe que a equipe adversaria veja suas cartas).\n\n");
	break;
	case EQUIPE_PAR:   
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "                   Equipe Par                 Equipe Impar\n") ;
	if (pontosPartidaPar < 10) {
		printf(	   "                   Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	else {
		printf(	   "                   Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	printf(		   "                   Rodada: 0/2                Rodada: 0/2\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n") ;
	printf(		   " Equipe par decide (nao deixe que a equipe adversaria veja suas cartas).\n\n");
	break;
	}
	printf(		   " Digite '1' para avancar.\n");
	printf(		   " ");
	scanf_s(	   " %c", opcao, 1);

	system("cls") ;

	//printa cabeçalho da tela
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOGO DE TRUCO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	switch (equipeComOnze) {
	case EQUIPE_IMPAR: 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE IMPAR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	break;
	case EQUIPE_PAR:   
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EQUIPE PAR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	break;
	}
	printf(		   "                   Equipe Par                 Equipe Impar\n") ;
	if (pontosPartidaPar < 10) {
		printf(	   "                   Partida: %d/12              Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	else {
		printf(	   "                   Partida: %d/12             Partida: %d/12\n", pontosPartidaPar, pontosPartidaImpar) ;
	}
	printf(		   "                   Rodada: 0/2                Rodada: 0/2\n") ;
	printf(		   " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
	printf(		   "                                                          Valor da Rodada: 1\n") ;

	LIS_IrInicioLista(pCabecaSuperior) ;

	switch (equipeComOnze){

	case EQUIPE_PAR:

		switch (qtdJogadores) {

		case 2:
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao1) ;
			break;

		case 4:
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao1) ;
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao2) ;
			break;

		case 6:
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao1) ;
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao2) ;
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao3) ;
			break;
		} //fim switch

		break;

	case EQUIPE_IMPAR:
		
		switch (qtdJogadores) {

		case 2:
			LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
			pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao1) ;
			break;

		case 4:
			LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
			pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao1) ;
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao2) ;
			break;

		case 6:
			LIS_AvancarElementoCorrente(pCabecaSuperior, 1) ;
			pCabecaMao1 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao1) ;
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao2 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao2) ;
			LIS_AvancarElementoCorrente(pCabecaSuperior, 2) ;
			pCabecaMao3 = (LIS_tppLista)LIS_ObterValor(pCabecaSuperior) ;
			PrintarMao(pCabecaMao3) ;
			break;
		} //fim switch

		break;

	} //fim switch

	printf(" \n O que deseja(m) fazer?\n\n") ;
	printf(" (1) Correr - Equipe adversaria ganha a rodada e ganha 1 ponto.\n (2) Aceitar - Rodada passa a valer 3 pontos.\n\n") ;

	printf(" Opcao: ") ;
	scanf_s(" %c", opcao, 1) ;

	while (*opcao < 49 && *opcao > 50) {
		scanf_s(" %c", opcao, 1);
	} //fim while

	system("cls") ;
	return *opcao ;

} /*********** FIM FUNÇÃO: Printar tela mão de onze ***********/

/********************* FUNÇÕES DE EXECUCAO DE OPÇÕES **********************/
/***************************************************************************
*  Função: &Executar opcao da tela de inicio
***************************************************************************/
int ExecutarOpcaoInicio (int opcao) {

	int qtdJogadores ;

	#ifdef _DEBUG
	char * opcaoDebug = (char*)malloc(sizeof(char)) ;
	#endif

	qtdJogadores = INICIALIZAR ;

	switch(opcao) {

	case 49: //(1) iniciar partida

		qtdJogadores = 0;
		break;

	case 50: //(2) ver regras

		#ifdef _DEBUG
			printf("Escolheu ver regras.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
			scanf(" %c", opcaoDebug);
			Delay() ;
		#endif

		qtdJogadores = 0;
		break;

	case 51: //(3) sair
		#ifdef _DEBUG
			printf("Escolheu sair.\n") ;
			scanf(" %c", opcaoDebug);
			Delay() ;
		#endif
		exit(0);
		break;

	} //fim switch

	return qtdJogadores;
}

/***************************************************************************
*  Função: &Executar opcao da tela de regras
***************************************************************************/
int ExecutarOpcaoRegras (int opcao) {

	int qtdJogadores = INICIALIZAR ;

	#ifdef _DEBUG
	char * opcaoDebug = (char*)malloc(sizeof(char)) ;
	#endif

	qtdJogadores = INICIALIZAR ;

	switch(opcao) {
	case 49: //(1) voltar

		#ifdef _DEBUG
			printf("Escolheu voltar.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
			scanf(" %c", opcaoDebug);
			Delay() ;
		#endif

		opcao = PrintarTelaInicio();
		qtdJogadores = ExecutarOpcaoInicio(opcao);
		break;
	case 50: //(2) sair

		#ifdef _DEBUG
			printf("Escolheu sair.\n\nDigite qualquer coisa e tecle 'enter'\n") ;
			scanf(" %c", opcaoDebug);
			Delay() ;
		#endif

		exit(0);
		break;
	}

	return qtdJogadores ;
}

/***************************************************************************
*  Função: &Executar opcao da tela da rodada
***************************************************************************/
int ExecutarOpcaoJogada(LIS_tppLista pCabecaSuperior, int quemJoga, int jogada, int valorRodada) {

	switch(jogada) {

	case APOSTAR_CARTA_1: //(1)

		ExecutarOpcaoApostarCarta (pCabecaSuperior, quemJoga, jogada) ;

		#ifdef _DEBUG
			printf("Apostou carta 1.\n") ;
			Delay() ;
		#endif

		break;

	case APOSTAR_CARTA_2: //(2)
		ExecutarOpcaoApostarCarta (pCabecaSuperior, quemJoga, jogada) ;

		#ifdef _DEBUG
			printf("Apostou carta 2.\n") ;
			Delay() ;
		#endif

		break;
	
	case APOSTAR_CARTA_3: //(3)
		ExecutarOpcaoApostarCarta (pCabecaSuperior, quemJoga, jogada) ;

		#ifdef _DEBUG
			printf("Apostou carta 3.\n") ;
			Delay() ;
		#endif

		break;
		
	case DISPENSAR_CARTA_1: //(4)
		ExecutarOpcaoDispensarCarta (pCabecaSuperior, quemJoga, jogada) ;

		#ifdef _DEBUG
			printf("Dispensou carta 1.\n") ;
			Delay() ;
		#endif

		break;

	case DISPENSAR_CARTA_2: //(5)
		ExecutarOpcaoDispensarCarta (pCabecaSuperior, quemJoga, jogada) ;

		#ifdef _DEBUG
			printf("Dispensou carta 2.\n") ;
			Delay() ;
		#endif

		break;

	case DISPENSAR_CARTA_3: //(6)
		ExecutarOpcaoDispensarCarta (pCabecaSuperior, quemJoga, jogada) ;

		#ifdef _DEBUG
			printf("Dispensou carta 3.\n") ;
			Delay() ;
		#endif

		break;

	case AUMENTAR_APOSTA: //(7)

		#ifdef _DEBUG
			printf("Pediu para aumentar o valor da rodada.\n") ;
			Delay() ;
		#endif

		switch(valorRodada) {
		case 1:
			return 3;
		case 3:
			return 6;
		case 6:
			return 9;
		case 9:
			return 12;
		} //fim switch

	#ifdef _DEBUG
	case 56: //(8)
		printf("Pediu para aumentar o valor da rodada pra 11.\n") ;
		Delay() ;
		return 11;
	#endif

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

#ifdef _DEBUG
void Delay () {
	int a, b, c, d ;
	c = INICIALIZAR ;
	for (a = 0; a < 30000; a++) {
		for (b = 0; b < 6000; b++) {
			c++ ;
			d = c * b ;
		}
	}
} //fim função
#endif