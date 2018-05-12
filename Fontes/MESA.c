/***************************************************************************
*  $MCI Módulo de implementação: MES  Mesa
*
*  Arquivo gerado:              MESA.c
*  Letras identificadoras:      MES
*
*  Projeto: INF 1301 Jogo de Truco
*  Autores: gsc, jvr, tgf
*
*  $HA Histórico de evolução:
*  Versão  		Autor  			Data    	Observações
*     1     gsc, jvr, tgf    11/mai/2018    início desenvolvimento
***************************************************************************/

#include   <stdio.h>	//printf
#include   <stdlib.h>	//malloc, free
#include   <assert.h>	//assert

#define MESA_OWN
#include "MESA.h"
#include "BARALHO.h"
#include "LISTA.h"

#undef MESA_OWN


/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//ainda nao ha funcoes encapsuladas no modulo


/***********  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ******************/

/***************************************************************************
*  Função: MES  &Criar mesa
***************************************************************************/
LIS_tppLista MES_CriarMesa(BAR_tppCarta vtCartas[], int numJogadores) {

	int inx; //indice do vetor
	
	//cria uma lista retornando um ponteiro pra cabeca da lista
	LIS_tppLista pCabecaMesa = LIS_CriarLista (BAR_DestruirCarta) ;

	//declara uma variável que armazena a condição de
	//retorno de funções de manipulação da lista
	LIS_tpCondRet condRetLista;

	//declara um ponteiro pra um tipo carta
	BAR_tppCarta pCarta;
	
	switch (numJogadores) {
		case 2: inx = 33; break;
		case 4: inx = 27; break;
		case 6: inx = 21; break;
		default: return NULL;
	}

	//armazena a vira no primeiro elemento da mesa
	pCarta = vtCartas[inx] ;
	
	//é inserido um elemento na lista Baralho e 
	//seu valor é um ponteiro pra um tipo Carta
	condRetLista = LIS_InserirElementoApos (pCabecaMesa, pCarta) ;

	//assertiva de saída
	if (condRetLista != LIS_CondRetOK){
		printf("\nNão inseriu carta no baralho.");
		return NULL;
	}//fim if

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaMesa) ;

	return pCabecaMesa ;
   
} /******************* Fim função: BAR &Criar mesa *************************/

/***************************************************************************
*  Função: MES  &Criar mao
***************************************************************************//*
LIS_tppLista MES_CriarMao(BAR_tppCarta vtCartas[], int numMao) {

	int inx; //indice do vetor
	
	//cria uma lista retornando um ponteiro pra cabeca da lista
	LIS_tppLista pCabecaMao = LIS_CriarLista (BAR_DestruirCarta) ;

	//declara uma variável que armazena a condição de
	//retorno de funções de manipulação da lista
	LIS_tpCondRet condRetLista;

	//declara um ponteiro pra um tipo carta
	BAR_tppCarta pCarta;
	

	//PAREI AQUI FUDEU Q TEM Q PASSAR NUMERO DE JOGADORES E NUMERO DA MAO
	switch (numMao) {
		case 1: inx = 33; break;
		case 2: inx = 27; break;
		case 3: inx = 21; break;
		case 4: inx = 21; break;
		case 5: inx = 21; break;
		case 6: inx = 21; break;
		default: return NULL;
	}

	//armazena a vira no primeiro elemento da mesa
	pCarta = vtCartas[inx] ;
	
	//é inserido um elemento na lista Baralho e 
	//seu valor é um ponteiro pra um tipo Carta
	condRetLista = LIS_InserirElementoApos (pCabecaMesa, pCarta) ;

	//assertiva de saída
	if (condRetLista != LIS_CondRetOK){
		printf("\nNão inseriu carta no baralho.");
		return NULL;
	}//fim if

	//elemento corrente passa a ser o primeiro
	IrInicioLista(pCabecaMesa) ;

	return pCabecaMesa ;
   
} /******************* Fim função: BAR &Criar mesa *************************/


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//ainda nao ha funcoes encapsuladas no modulo


/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
