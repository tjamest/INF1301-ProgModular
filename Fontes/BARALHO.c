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
*  Versão  		Autor  			Data    	Observações
*	  3			 gsc		 11/mai/2018	criada a TransferirCarta
*	  2			 gsc		 10/mai/2018	revisão para entrega na data
*     1     gsc, jvr, tgf    19/abr/2018    início desenvolvimento
***************************************************************************/

#include   <stdio.h>	//printf
#include   <stdlib.h>	//malloc, free
#include   <assert.h>	//assert
#include   <time.h>

#define BARALHO_OWN
#include "baralho.h"
#include "lista.h"
#undef BARALHO_OWN

#ifdef _DEBUG
   #include   "generico.h"
   #include   "cespdin.h"
   #include   "conta.h"
   #include   "..\\tabelas\\IdTiposEspaco.def"
#endif

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

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
//nao ha funcoes encapsuladas no modulo


/***********  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ******************/

/***************************************************************************
*  Função: BAR &Preencher vetor cartas
***************************************************************************/
BAR_tpCondRet BAR_PreencherVetorCartas (BAR_tppCarta vtCartas[]) {

	int i ,
		valor = 0,
		naipe = 0 ;

	BAR_tpValorCarta Valor ;
	BAR_tpNaipeCarta Naipe ;

	BAR_tppCarta pCarta ;

	#ifdef _DEBUG
		CNT_CONTAR("BAR_PreencherVetorCartas") ;
	#endif

	//preenchendo o vetor de cartas de forma ordenada
	for (i = 0; i < TAM; i++, valor++) {
		
		//faz a transformacao de int pra tipo especifico
		Valor = (BAR_tpValorCarta) valor;
		Naipe = (BAR_tpNaipeCarta) naipe;

		pCarta = BAR_CriarCarta(Valor, Naipe);

		vtCartas[i] = pCarta ;

		if (vtCartas[i] == NULL) {

			return BAR_CondRetNaoPreencheuVetor ;
		}
		
		if (i == 9 || i == 19 || i == 29) {

			//reinicia o preenchimento do valor de 0 a 9
			valor = -1 ;
			//passa pro proximo naipe
			naipe++;

		} //fim if

	} //fim for

	return BAR_CondRetOK ;

} /***************** Fim função: &Preencher vetor cartas *******************/

/***************************************************************************
*  Função: BAR &Embaralhar vetor cartas
***************************************************************************/
BAR_tpCondRet BAR_EmbaralharVetorCartas (BAR_tppCarta vtCartas[]) {

	int i ,
		valor = 0,
		naipe = 0 ;

	BAR_tpValorCarta Valor ;
	BAR_tpNaipeCarta Naipe ;
	BAR_tppCarta pCarta ;
	
	#ifdef _DEBUG
		CNT_CONTAR("BAR_EmbaralharVetorCartas") ;
	#endif

	//preenchendo o vetor de cartas de forma ordenada
	for (i = 0; i < TAM; i++, valor++) {
		
		//faz a transformacao de int pra tipo especifico
		Valor = (BAR_tpValorCarta) valor;
		Naipe = (BAR_tpNaipeCarta) naipe;

		pCarta = BAR_CriarCarta(Valor, Naipe);
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

		int random ;
		
		//gera um número aleatorio entre 0 e 39
		random = rand() % TAM ;

		//embaralhando os indices
		pCartaAux = vtCartas[i] ;
		vtCartas[i] = vtCartas[random] ;
		vtCartas[random] = pCartaAux ;

		if (vtCartas[i] == NULL) {
			
			return BAR_CondRetNaoEmbaralhouVetor ;
		}
		
	} //fim for
	
	return BAR_CondRetOK ;

} /***************** Fim função: &Embaralhar vetor cartas ******************/

/***************************************************************************
*  Função: BAR  &Criar baralho
***************************************************************************/
LIS_tppLista BAR_CriarBaralho() {
	
	LIS_tppLista pCabecaBaralho ;	

	#ifdef _DEBUG
		CNT_CONTAR("BAR_CriarBaralho") ;
	#endif
	
	//cria uma lista retornando um ponteiro pra cabeca da lista
	pCabecaBaralho = LIS_CriarLista (BAR_DestruirCarta) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaBaralho != NULL ) ;
	#endif

	return pCabecaBaralho ;
   
} /***************** Fim função: BAR &Criar baralho ***********************/

/***************************************************************************
*  Função: BAR  &Preencher baralho
***************************************************************************/
BAR_tpCondRet BAR_PreencherBaralho(LIS_tppLista pCabecaBaralho, BAR_tppCarta VetorAux[TAM]) {
	
	int i ; //contador

	//declara uma variável que armazena a condição de
	//retorno de funções de manipulação da lista
	LIS_tpCondRet condRetLista;

	#ifdef _DEBUG
		CNT_CONTAR("BAR_PreencherBaralho") ;
	#endif
	
	//preenche um por um usando o vetor embaralhado
	for (i = 0; i < TAM; i++){
		
		BAR_tppCarta pCarta;
		
		pCarta = VetorAux[i] ;
		
		//é inserido um elemento na lista Baralho e 
		//seu valor é um ponteiro pra um tipo Carta
		condRetLista = LIS_InserirElementoApos (pCabecaBaralho, pCarta) ;
		
		//assertiva de saída
		if (condRetLista != LIS_CondRetOK){
			
			printf("\nNão inseriu carta no baralho.");
			return BAR_CondRetNaoInseriuCarta;
		}//fim if
		
	}//fim for
	
	//elemento corrente passa a ser o primeiro
	LIS_IrInicioLista(pCabecaBaralho) ;

	//assertivas de saída
	if (LIS_ObterQtdElem(pCabecaBaralho) < 40) {
		
		return BAR_CondRetNaoPreencheuBaralho ;
	}

	else {
		
		return BAR_CondRetOK ;
	}
   
} /***************** Fim função: BAR &Preencher baralho ***********************/

/****************************************************************************
*  $FC Função: BAR  &Criar Carta
****************************************************************************/
BAR_tppCarta BAR_CriarCarta (BAR_tpValorCarta valor, BAR_tpNaipeCarta naipe) {

	BAR_tppCarta pCarta ;

	#ifdef _DEBUG
		CNT_CONTAR("BAR_CriarCarta") ;
	#endif
	
	//declara um ponteiro pra um tipo carta e aloca memoria
	pCarta = (BAR_tppCarta) malloc(sizeof(BAR_tpCarta)) ;
	
	//atribui valor e naipe a um tipo carta
	pCarta->valor = valor ;
	pCarta->naipe = naipe ;
	
	#ifdef _DEBUG
		CED_DefinirTipoEspaco(pCarta, BAR_TipoEspacoCarta) ;
	#endif
	
	//retorna um ponteiro pra um tipo carta
	return pCarta ;
	
} /******************** Fim função: BAR &Criar Carta ***********************/

/***************************************************************************
*  Função: BAR  &Destruir carta
***************************************************************************/
void BAR_DestruirCarta(void * pCarta) {

	BAR_tppCarta pCartaAux = (BAR_tppCarta) pCarta;
	
	#ifdef _DEBUG
		CNT_CONTAR("BAR_DestruirCarta") ;
	#endif
	
	if (pCarta == NULL) {
		return;
	}
	
	free(pCartaAux);

} /************ Fim função: BAR &Destruir carta ****************************/

/***************************************************************************
*  Função: BAR  &Destruir baralho
***************************************************************************/
void BAR_DestruirBaralho(void * pLista) {

	#ifdef _DEBUG
		CNT_CONTAR("BAR_DestruirBaralho") ;
	#endif

	#ifdef _DEBUG
		assert( pLista != NULL ) ;
	#endif
	
	LIS_EsvaziarLista( pLista ) ;

    free( pLista ) ;
	
} /************ Fim função: BAR &Destruir baralho ****************************/

/***************************************************************************
*  Função: BAR  &Obter carta corrente
***************************************************************************/
BAR_tppCarta BAR_ObterCartaCorr(LIS_tppLista pCabecaLista) {

	BAR_tppCarta pCarta ;
	
	//obtem o valor corrente de uma lista e retorna
	pCarta = (BAR_tppCarta)LIS_ObterValor (pCabecaLista) ;
	
	//assertiva de saída
	#ifdef _DEBUG
		assert( pCarta != NULL ) ;
    #endif

	return pCarta;
} /***************** Fim função: BAR &Obter carta **************************/

/***************************************************************************
*  Função: BAR  &Obter naipe
****************************************************************************/
BAR_tpNaipeCarta BAR_ObterNaipe(BAR_tppCarta pCarta) {

	#ifdef _DEBUG
		CNT_CONTAR("BAR_ObterNaipe") ;
		assert( pCarta != NULL ) ;
	#endif

	return pCarta->naipe;
} /***************** Fim função: BAR &Obter naipe **************************/

/***************************************************************************
*  Função: BAR  &Obter valor
****************************************************************************/
BAR_tpValorCarta BAR_ObterValor(BAR_tppCarta pCarta) {

	#ifdef _DEBUG
		CNT_CONTAR("BAR_ObterValor") ;
		assert( pCarta != NULL ) ;
	#endif

	return pCarta->valor;
} /***************** Fim função: BAR &Obter valor **************************/

/***************************************************************************
*  Função: BAR  &Transferir carta
****************************************************************************/
BAR_tpCondRet BAR_TransferirCarta(LIS_tppLista pOrigem, LIS_tppLista pDestino) {

	LIS_tpCondRet CondRetLista ;

	BAR_tppCarta pCarta ;
	
	pCarta = BAR_ObterCartaCorr(pOrigem) ;
	
	//assertiva de saida
	if (pCarta == NULL) { 
		
		return BAR_CondRetNaoObteveCarta ;
	}

	CondRetLista = LIS_InserirElementoApos(pDestino, pCarta) ;
	
	//assertiva de saida
	if (CondRetLista == LIS_CondRetFaltouMemoria) {
		
		return BAR_CondRetNaoInseriuCarta ;
	}
	
	CondRetLista = LIS_ExcluirPtrParaElemento(pOrigem) ;

	//assertiva de saida
	if (CondRetLista == LIS_CondRetListaVazia) {

		return BAR_CondRetNaoExcluiuPtrParaElem ;
	}

	return BAR_CondRetOK ;

} /***************** Fim função: BAR &Transferir carta *********************/

/***************************************************************************
*  Função: BAR  &Verificar se eh manilha
****************************************************************************/
BAR_tpCondRet BAR_VerificarSeEhManilha(BAR_tppCarta pAposta, BAR_tppCarta pVira) {

	//declara valor especifico pra vira e pra carta apostada
	BAR_tpValorCarta valorEspVira, valorEspAposta, valorEspManilha;
	
	//obtem o valor tpValorCarta da carta que acabou de ser apostada e da vira
	valorEspAposta = BAR_ObterValor(pAposta) ;
	valorEspVira = BAR_ObterValor(pVira) ;

	if ((int)valorEspVira == 9) {
		
		valorEspManilha = _4 ;

		if (valorEspAposta == valorEspManilha) {
			
			return BAR_CondRetEhManilha ;
		} //fim if
		
		else {
			
			return BAR_CondRetNaoEhManilha ;
		} //fim else

	} //fim if
	
	else {
		
		valorEspManilha = ((int)valorEspVira) + 1 ;

		if (valorEspAposta == valorEspManilha) {
			return BAR_CondRetEhManilha ;
		} //fim if
		
		else {
			return BAR_CondRetNaoEhManilha ;
		} //fim else

	} //fim else
}

/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
