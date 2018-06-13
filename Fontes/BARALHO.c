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
#include "BARALHO.h"
#include "LISTA.h"
#include "CONTA.h"

#undef BARALHO_OWN

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

	CNT_InicializarContadores(NULL, NULL) ;

	#ifdef _DEBUG
		CNT_CONTAR("Antes de entrar no for 'Preenchendo o vetor'") ;
	#endif

	//preenchendo o vetor de cartas de forma ordenada
	for (i = 0; i < TAM; i++, valor++) {
		
		#ifdef _DEBUG
			CNT_CONTAR("Depois de entrar no for 'Preenchendo o vetor'") ;
		#endif
		
		//faz a transformacao de int pra tipo especifico
		BAR_tpValorCarta Valor = (BAR_tpValorCarta) valor;
		BAR_tpNaipeCarta Naipe = (BAR_tpNaipeCarta) naipe;

		BAR_tppCarta pCarta = BAR_CriarCarta(Valor, Naipe);

		vtCartas[i] = pCarta ;
		
		#ifdef _DEBUG
			CNT_CONTAR("Antes de entrar no if 'NULL'") ;
		#endif

		if (vtCartas[i] == NULL) {

			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no if 'null'") ;
			#endif

			return BAR_CondRetNaoPreencheuVetor ;
		}
		
		#ifdef _DEBUG
			CNT_CONTAR("Antes de entrar no if 'i = 9 ou 19 ou 29'") ;
		#endif
		
		if (i == 9 || i == 19 || i == 29) {

			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no if 'i = 9 ou 19 ou 29'") ;
			#endif

			//reinicia o preenchimento do valor de 0 a 9
			valor = -1 ;
			//passa pro proximo naipe
			naipe++;

		} //fim if

		#ifdef _DEBUG
			CNT_CONTAR("Depois de sair do if 'i = 9 ou 19 ou 29'") ;
		#endif

	} //fim for

	#ifdef _DEBUG
		CNT_CONTAR("Depois de sair do for 'preencher o vetor'") ;
	#endif

	return BAR_CondRetOK ;

} /***************** Fim função: &Preencher vetor cartas *******************/

/***************************************************************************
*  Função: BAR &Embaralhar vetor cartas
***************************************************************************/
BAR_tpCondRet BAR_EmbaralharVetorCartas (BAR_tppCarta vtCartas[]) {

	int i ,
		valor = 0,
		naipe = 0 ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Antes de entrar no for 'Preenchendo o vetor'") ;
	#endif

	//preenchendo o vetor de cartas de forma ordenada
	for (i = 0; i < TAM; i++, valor++) {
		
		#ifdef _DEBUG
			CNT_CONTAR("Depois de entrar no for 'Preenchendo o vetor'") ;
		#endif
		
		//faz a transformacao de int pra tipo especifico
		BAR_tpValorCarta Valor = (BAR_tpValorCarta) valor;
		BAR_tpNaipeCarta Naipe = (BAR_tpNaipeCarta) naipe;

		BAR_tppCarta pCarta = BAR_CriarCarta(Valor, Naipe);
		vtCartas[i] = pCarta;
		
		#ifdef _DEBUG
			CNT_CONTAR("Antes de entrar no if 'i = 9 ou 19 ou 29'") ;
		#endif
		
		if (i == 9 || i == 19 || i == 29) {
			
			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no if 'i = 9 ou 19 ou 29'") ;
			#endif

			//reinicia o preenchimento do valor de 0 a 9
			valor = -1 ;
			//passa pro proximo naipe
			naipe++;

		} //fim if
	} //fim for
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de sair do for 'Preenchendo o vetor'") ;
	#endif
	
	//função suporte da rand que faz gerar números diferentes sempre
	srand ((unsigned)time(NULL));

	#ifdef _DEBUG
		CNT_CONTAR("Antes de entrar no for 'Embaralhando o vetor'") ;
	#endif
	
	//embaralhando o vetor (troca os indices aleatoriamente)
	for (i = 0; i < TAM; i++){
				
		#ifdef _DEBUG
			CNT_CONTAR("Depois de entrar no for 'Embaralhando o vetor'") ;
		#endif
		
		//declara um ponteiro pra um tipo carta
		BAR_tppCarta pCartaAux;
		
		//gera um número aleatorio entre 0 e 39
		int random = rand() % TAM ;

		//embaralhando os indices
		pCartaAux = vtCartas[i] ;
		vtCartas[i] = vtCartas[random] ;
		vtCartas[random] = pCartaAux ;
		
		#ifdef _DEBUG
			CNT_CONTAR("Antes de entrar no if 'NULL'") ;
		#endif

		if (vtCartas[i] == NULL) {
			
			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no if 'NULL'") ;
			#endif
			
			return BAR_CondRetNaoEmbaralhouVetor ;
		}
		
		#ifdef _DEBUG
			CNT_CONTAR("Não entrou no if 'NULL'") ;
		#endif
		
	} //fim for

	#ifdef _DEBUG
		CNT_CONTAR("Depois de sair do for 'Embaralhando o vetor'") ;
	#endif
	
	return BAR_CondRetOK ;

} /***************** Fim função: &Embaralhar vetor cartas ******************/

/***************************************************************************
*  Função: BAR  &Criar baralho
***************************************************************************/
LIS_tppLista BAR_CriarBaralho() {
	
//	int i ; //contador
	

	#ifdef _DEBUG
		CNT_CONTAR("Antes de chamar 'LIS_CriarLista'") ;
	#endif
	
	//cria uma lista retornando um ponteiro pra cabeca da lista
	LIS_tppLista pCabecaBaralho = LIS_CriarLista (BAR_DestruirCarta) ;

	//assertiva de saída
	#ifdef _DEBUG
		assert( pCabecaBaralho != NULL ) ;
	#endif
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'LIS_CriarLista'") ;
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
		CNT_CONTAR("Antes de entrar no for 'Preenche usando o vetor embaralhado'") ;
	#endif
	
	//preenche um por um usando o vetor embaralhado
	for (i = 0; i < TAM; i++){
		
		#ifdef _DEBUG
			CNT_CONTAR("Depois de entrar no for 'Preenche usando o vetor embaralhado'") ;
		#endif
		
		BAR_tppCarta pCarta;
		pCarta = VetorAux[i] ;
	
		#ifdef _DEBUG
			CNT_CONTAR("Antes de chamar 'LIS_InserirElementoApos'") ;
		#endif
		
		//é inserido um elemento na lista Baralho e 
		//seu valor é um ponteiro pra um tipo Carta
		condRetLista = LIS_InserirElementoApos (pCabecaBaralho, pCarta) ;

		#ifdef _DEBUG
			CNT_CONTAR("Depois de chamar 'Lis_InserirElementoApois e antes de entrar no if 'Assertiva de saída'") ;
		#endif
		
		//assertiva de saída
		if (condRetLista != LIS_CondRetOK){
			
			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no if 'Assertiva de saída'") ;
			#endif
			
			printf("\nNão inseriu carta no baralho.");
			return BAR_CondRetNaoInseriuCarta;
		}//fim if

		#ifdef _DEBUG
			CNT_CONTAR("Não entrou no if 'Assertiva de saída'") ;
		#endif
		
	}//fim for


	#ifdef _DEBUG
		CNT_CONTAR("Depois de sair do for 'Preenche usando o vetor embaralhado' e antes de chamar 'LIS_IrInicioLista'") ;
	#endif
	
	//elemento corrente passa a ser o primeiro
	LIS_IrInicioLista(pCabecaBaralho) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'LIS_IrInicioLista' e antes de entrar no segundo if 'Assertiva de saída'") ;
	#endif

	//assertivas de saída
	if (LIS_ObterQtdElem(pCabecaBaralho) < 40) {
		
		#ifdef _DEBUG
			CNT_CONTAR("Depois de entrar no segundo if 'Assertiva de saída'") ;
		#endif
		
		return BAR_CondRetNaoPreencheuBaralho ;
	}
	

	#ifdef _DEBUG
		CNT_CONTAR("Não entrou no segundo if 'Assertiva de saída'") ;
	#endif
	
	else {
		
		#ifdef _DEBUG
			CNT_CONTAR("Entrou no else") ;
		#endif
		
		return BAR_CondRetOK ;
	}
   
} /***************** Fim função: BAR &Preencher baralho ***********************/

/****************************************************************************
*  $FC Função: BAR  &Criar Carta
****************************************************************************/
BAR_tppCarta BAR_CriarCarta (BAR_tpValorCarta valor, BAR_tpNaipeCarta naipe) {

	#ifdef _DEBUG
		CNT_CONTAR("Antes de alocar o espaço para carta") ;
	#endif
	
	//declara um ponteiro pra um tipo carta e aloca memoria
	BAR_tppCarta pCarta = (BAR_tppCarta) malloc(sizeof(BAR_tpCarta)) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Antes de atribuir o valor e o naipe") ;
	#endif
	
	//atribui valor e naipe a um tipo carta
	pCarta->valor = valor ;
	pCarta->naipe = naipe ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de atribuir o valor e o naipe") ;
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
		CNT_CONTAR("Antes de entrar no if 'NULL'") ;
	#endif
	
	if (pCarta == NULL) {

		#ifdef _DEBUG
			CNT_CONTAR("Depois de entrar no if 'NULL'") ;
		#endif
		
		return;
	}

	#ifdef _DEBUG
		CNT_CONTAR("Não entrou no if 'NULL'") ;
	#endif
	
	free(pCartaAux);

} /************ Fim função: BAR &Destruir carta ****************************/

/***************************************************************************
*  Função: BAR  &Destruir baralho
***************************************************************************/
void BAR_DestruirBaralho(void * pLista) {

	LIS_tpCondRet condRetLista ;

	#ifdef _DEBUG
		assert( pLista != NULL ) ;
	#endif

	#ifdef _DEBUG
		CNT_CONTAR("Antes de chamar 'LIS_ExcluirElemento'") ;
	#endif
	
	condRetLista = LIS_ExcluirElemento(pLista) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'LIS_ExcluirElemento'") ;
	#endif
	
} /************ Fim função: BAR &Destruir baralho ****************************/

/***************************************************************************
*  Função: BAR  &Obter carta corrente
***************************************************************************/
BAR_tppCarta BAR_ObterCartaCorr(LIS_tppLista pCabecaLista) {

	#ifdef _DEBUG
		CNT_CONTAR("Antes de chamar 'LIS_ObterValor'") ;
	#endif
	
	//obtem o valor corrente de uma lista e retorna
	BAR_tppCarta pCarta = (BAR_tppCarta)LIS_ObterValor (pCabecaLista) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'LIS_ObterValor'") ;
	#endif
	
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
		assert( pCarta != NULL ) ;
	#endif

	return pCarta->naipe;
} /***************** Fim função: BAR &Obter naipe **************************/

/***************************************************************************
*  Função: BAR  &Obter valor
****************************************************************************/
BAR_tpValorCarta BAR_ObterValor(BAR_tppCarta pCarta) {
	
	#ifdef _DEBUG
		assert( pCarta != NULL ) ;
	#endif

	return pCarta->valor;
} /***************** Fim função: BAR &Obter valor **************************/

/***************************************************************************
*  Função: BAR  &Transferir carta
****************************************************************************/
BAR_tpCondRet BAR_TransferirCarta(LIS_tppLista pOrigem, LIS_tppLista pDestino) {

	LIS_tpCondRet CondRetLista ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Antes de chamar 'BAR_ObterCartaCorr'") ;
	#endif
	
	BAR_tppCarta pCarta = BAR_ObterCartaCorr(pOrigem) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'BAR_ObterCartaCorr' e antes de entrar no if 'NULL'") ;
	#endif
	
	//assertiva de saida
	if (pCarta == NULL) { 
		
	#ifdef _DEBUG
		CNT_CONTAR("Depois de entrar no if 'NULL'") ;
	#endif
		
		return BAR_CondRetNaoObteveCarta ;
	}

	#ifdef _DEBUG
		CNT_CONTAR("Antes de chamar 'LIS_InserirElementoApos'") ;
	#endif
	
	CondRetLista = LIS_InserirElementoApos(pDestino, pCarta) ;

	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'LIS_InserirElementoApos' e antes de entrar no if 'Assertiva de saída'") ;
	#endif
	
	//assertiva de saida
	if (CondRetLista == LIS_CondRetFaltouMemoria) {
		
	#ifdef _DEBUG
		CNT_CONTAR("Depois de entrar no if 'Assertiva de saída'") ;
	#endif
		
		return BAR_CondRetNaoInseriuCarta ;
	}

	#ifdef _DEBUG
		CNT_CONTAR("Antes de chamar 'LIS_ExcluirPtrParaElemento'") ;
	#endif
	
	CondRetLista = LIS_ExcluirPtrParaElemento(pOrigem) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'LIS_ExcluirPtrParaElemento' e antes de entrar no segundo if 'Assertiva de saída") ;
	#endif

	//assertiva de saida
	if (CondRetLista == LIS_CondRetListaVazia) {
		
	#ifdef _DEBUG
		CNT_CONTAR("Depois de entrar no segundo if 'Assertiva de saída'") ;
	#endif
		
		return BAR_CondRetNaoExcluiuPtrParaElem ;
	}
	
	#ifdef _DEBUG
		CNT_CONTAR("Não entrou no segundo if 'Assertiva de saída'") ;
	#endif

	return BAR_CondRetOK ;

} /***************** Fim função: BAR &Transferir carta *********************/

/***************************************************************************
*  Função: BAR  &Verificar se eh manilha
****************************************************************************/
BAR_tpCondRet BAR_VerificarSeEhManilha(BAR_tppCarta pAposta, BAR_tppCarta pVira) {

	//declara valor especifico pra vira e pra carta apostada
	BAR_tpValorCarta valorEspVira, valorEspAposta, valorEspManilha;

	#ifdef _DEBUG
		CNT_CONTAR("Antes de chamar 'BAR_ObterValor' para aposta") ;
	#endif
	
	//obtem o valor tpValorCarta da carta que acabou de ser apostada e da vira
	valorEspAposta = BAR_ObterValor(pAposta) ;
	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'BAR_ObterValor para aposta e antes de chamar para vira'") ;
	#endif
	valorEspVira = BAR_ObterValor(pVira) ;
	
	#ifdef _DEBUG
		CNT_CONTAR("Depois de chamar 'Bar_ObterValor'para vira e antes de entrar no for 'vira = 9'") ;
	#endif

	if ((int)valorEspVira == 9) {
		
		#ifdef _DEBUG
			CNT_CONTAR("Depois de entrar no if 'vira = 9'") ;
		#endif

		(int)valorEspManilha = 0 ;
		
		#ifdef _DEBUG
			CNT_CONTAR("Antes de entrar no if 'Aposta = Manilha'") ;
		#endif

		if (valorEspAposta == valorEspManilha) {
			
			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no if 'Aposta = Manilha'") ;
			#endif
			
			return BAR_CondRetEhManilha ;
		} //fim if
		
		#ifdef _DEBUG
			CNT_CONTAR("Antes de entrar no else do 'Aposta = manilha'") ;
		#endif
		
		else {
			
			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no else do 'Aposta = manilha'") ;
			#endif
			
			return BAR_CondRetNaoEhManilha ;
		} //fim else

	} //fim if

	#ifdef _DEBUG
		CNT_CONTAR("Antes de entrar no else do 'Vira = 9'") ;
	#endif
	
	else {
		
		#ifdef _DEBUG
			CNT_CONTAR("Depois de entrar no else do 'Vira = 9'") ;
		#endif

		(int)valorEspManilha = ((int)valorEspVira) + 1 ;

		#ifdef _DEBUG
			CNT_CONTAR("Antes de entrar no segundo if 'Aposta = Manilha'") ;
		#endif
		
		if (valorEspAposta == valorEspManilha) {
			
			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no segundo if 'Aposta = Manilha'") ;
			#endif
			
			return BAR_CondRetEhManilha ;
		} //fim if
		
		#ifdef _DEBUG
			CNT_CONTAR("Antes de entrar no else do segundo if 'Aposta = Manilha'") ;
		#endif
		
		else {
			
			#ifdef _DEBUG
				CNT_CONTAR("Depois de entrar no else do segundo if 'Aposta = Manilha'") ;
			#endif
			
			return BAR_CondRetNaoEhManilha ;
		} //fim else

	} //fim else
}

/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//nao ha funcoes encapsuladas no modulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
