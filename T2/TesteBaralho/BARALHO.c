
/***************************************************************************
*  $MCI Módulo de implementação: BAR  Baralho
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Projeto: INF 1301 Jogo de Truco
*  Autores: gsc, jvr, tgf
*
*  $HA Histórico de evolução:
*  Versão  	Autor    	Data    	Observações
*     1     gsc, jvr, tgf    19/abr/2018    início desenvolvimento
***************************************************************************/

#include   <stdio.h>
#include   <stdlib.h> 
#include   <string.h>
#include   <malloc.h>
#include   <time.h>

#define BARALHO_OWN
#include "BARALHO.h"
#include "LISTA.h"

#undef BARALHO_OWN

#define TAM 40


/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//não há funções encapsuladas no módulo

/***************************************************************************
*  $TC Tipo de dados: BAR tpCarta
*
*  $ED Descrição do tipo
*     Estrutura de uma carta, que tem um valor e um naipe.
***************************************************************************/
typedef struct BAR_tagCarta {
	BAR_tpValorCarta valor ;
	BAR_tpNaipeCarta naipe ;
} BAR_tpCarta;

/***********  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ******************/

/***************************************************************************
*  Função: BAR  &Criar baralho
***************************************************************************/
LIS_tppLista BAR_CriarBaralho() {

	int i; //contador
	int valor = 0, naipe = 0;

	//aloca memória pro ponteiro que aponta pra cabeca
	//do baralho (um ponteiro pro tipo lista)
	LIS_tppLista pCabecaBaralho = LIS_CriarLista (BAR_DestruirCarta) ;
		
	//cria um vetor de TAM elementos que são ponteiros pra tpCarta
	BAR_tpCarta VetorAux[TAM] ;
	
	//declara uma variável que armazena a condição de
	//retorno de funções de manipulação da lista
	LIS_tpCondRet condRetLista;
	
	//declara uma variável que armazena o ponteiro
	//pro tpCarta que é o elemento do vetor
	BAR_tpCarta *pCarta;

	//preenchendo o baralho de forma ordenada
	for (i = 0; i < TAM; i++, valor++) {
		
		BAR_tpValorCarta Valor = (BAR_tpValorCarta) valor;
		BAR_tpNaipeCarta Naipe = (BAR_tpNaipeCarta) naipe;

		pCarta = BAR_CriarCarta(Valor, Naipe);
		VetorAux[i] = *pCarta;

		if (i == 9 || i == 19 || i == 29) {
			//reinicia o preenchimento do valor de 0 a 9
			valor = -1 ;
			//passa pro proximo naipe
			naipe++;
		}
	} //fim for
	
	//checando se o vetor está preenchido
/*	printf("Checando se o vetor esta preenchido:\n");
	for (i = 0; i < TAM; i++){
		printf("VetorAux[%d]: Valor %d / Naipe %d\n",(i+1), 
			VetorAux[i].valor,VetorAux[i].naipe);
	} //fim for*/

	//função suporte da rand que faz gerar números diferentes sempre
	srand ((unsigned)time(NULL));

	//embaralhando o vetor (troca os indices aleatoriamente)
	for (i = 0; i < TAM; i++){

		BAR_tpCarta pCartaAux;
		
		//gera um número aleatorio entre 0 e 39
		int random = rand() % TAM ;

		//um ponteiro pra um tipo Carta recebe um ponteiro pra um tipo Carta
		pCartaAux = VetorAux[i] ;
		
		//o ponteiro pra um tipo Carta usado anteriormente recebe agora
		//um ponteiro pra um tipo Carta escolhido aleatoriamente
		VetorAux[i] = VetorAux[random] ;
		
		//o ponteiro pra um tipo Carta aleatório
		//recebe o ponteiro pra um tipo Carta inicial
		VetorAux[random] = pCartaAux ;
		
	} //fim for

	//checando se o vetor está embaralhado
/*	printf("\nChecando se o vetor esta embaralhado:\n");
	for (i = 0; i < TAM; i++){
		printf("VetorAux[%d]: Valor %d / Naipe %d\n",(i+1), 
			VetorAux[i].valor,VetorAux[i].naipe);
	} //fim for*/
	
	// preenche um por um usando o vetor embaralhado
	for (i = 0; i < TAM; i++){
		
		//pCarta recebe um ponteiro pra um tipo Carta do vetor embaralhado
		pCarta = &VetorAux[i] ;

/*		//checando se pCarta recebe um valor aleatorio
		printf("\npCarta: Valor %d / Naipe %d", pCarta->valor,pCarta->naipe);*/
		
		//é inserido um elemento na lista Baralho e 
		//seu valor é um ponteiro pra um tipo Carta
		condRetLista = LIS_InserirElementoApos (pCabecaBaralho, pCarta) ;

		//assertiva de saída
		if (condRetLista != LIS_CondRetOK){
			printf("\nNão inseriu elemento");
			return NULL;
		}

	} //fim for
	
  return pCabecaBaralho ;
   
} /***************** Fim função: BAR &Criar baralho ***********************/


/****************************************************************************
*  $FC Função: BAR  &Criar Carta
****************************************************************************/
BAR_tppCarta BAR_CriarCarta (BAR_tpValorCarta valor, BAR_tpNaipeCarta naipe) {

	//declara um ponteiro pra um tipo carta com valor null
	BAR_tpCarta * pCarta = NULL;
	
	//aloca memoria pra esse ponteiro do tamanho do tipo carta
	pCarta = (BAR_tpCarta*) malloc(sizeof(BAR_tpCarta)) ;
	
	//assertiva
	if (pCarta == NULL) {
		return NULL ;
	}
	
	//atribui valor e naipe a um tipo carta
	pCarta->valor = valor ;
	pCarta->naipe = naipe ;
	
	//retorna um ponteiro pra um tipo carta
	return pCarta ;
	
} /******************** Fim função: BAR &Criar Carta ***********************/


/***************************************************************************
*  Função: BAR  &Destruir baralho
***************************************************************************/
void BAR_DestruirBaralho(void * pCabecaBaralho) {
//tem que ser void e *void pra LIS_CriarLista aceitar
	
	//destruição do ponteiro pro tipo lista
	free(pCabecaBaralho) ;	
	
} /************* Fim função: BAR &Destruir baralho ************************/


/***************************************************************************
*  Função: BAR  &Destruir carta
***************************************************************************/
void BAR_DestruirCarta(void * pCarta) {
//tem que ser void e *void pra LIS_CriarLista aceitar
	
	//destruição do ponteiro pro tipo carta
	free(pCarta) ;
	
} /************ Fim função: BAR &Destruir carta ****************************/


/***************************************************************************
*  Função: BAR  &Obter informações da carta
***************************************************************************/
BAR_tpCondRet BAR_ObterInfoCarta(BAR_tppCarta pCarta, 
				 BAR_tpValorCarta *pValor, 
				 BAR_tpNaipeCarta *pNaipe) {

	//assertiva de entrada
	if (pCarta == NULL)
		return BAR_CondRetParamIncorretos;
	
	*pValor = pCarta->valor;
	*pNaipe = pCarta->naipe;
	
	//assertiva de saída
	if (pValor == NULL || pNaipe == NULL) {
		return BAR_CondRetNaoObteveInfo;
	}
	
	return BAR_CondRetOK;
} /************ Fim função: BAR &Obter informações da carta ****************/


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//não há funções encapsuladas no módulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
