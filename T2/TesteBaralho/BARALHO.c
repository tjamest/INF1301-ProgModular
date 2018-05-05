
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

	int i;

	//aloca memória pro ponteiro que aponta pra cabeca
	//do baralho (um ponteiro pro tipo lista)
	LIS_tppLista pCabecaBaralho = LIS_CriarLista (BAR_DestruirCarta) ;
		
	//cria um vetor de 40 elementos que são ponteiros pra tpCarta
	BAR_tpCarta VetorAux[40] ;
	
	//declara uma variável que armazena a condição de
	//retorno de funções de manipulação da lista
	LIS_tpCondRet condRetLista;
	
	//declara uma variável que armazena o ponteiro
	//pro tpCarta que é o elemento do vetor
	BAR_tpCarta *pCarta;
	
	//criando o vetor baralho ordenado
	pCarta=BAR_CriarCarta(_4,Ouros);
	VetorAux[0] = *pCarta;
	pCarta=BAR_CriarCarta(_5,Ouros);
	VetorAux[1] = *pCarta;
	pCarta=BAR_CriarCarta(_6,Ouros);
	VetorAux[2] = *pCarta;
	pCarta=BAR_CriarCarta(_7,Ouros);
	VetorAux[3] = *pCarta;
	pCarta=BAR_CriarCarta(_Q,Ouros);
	VetorAux[4] = *pCarta;
	pCarta=BAR_CriarCarta(_J,Ouros);
	VetorAux[5] = *pCarta;
	pCarta=BAR_CriarCarta(_K,Ouros);
	VetorAux[6] = *pCarta;
	pCarta=BAR_CriarCarta(_A,Ouros);
	VetorAux[7] = *pCarta;
	pCarta=BAR_CriarCarta(_2,Ouros);
	VetorAux[8] = *pCarta;
	pCarta=BAR_CriarCarta(_3,Ouros);
	VetorAux[9] = *pCarta;

	pCarta=BAR_CriarCarta(_4,Espadas);
	VetorAux[10] = *pCarta;
	pCarta=BAR_CriarCarta(_5,Espadas);
	VetorAux[11] = *pCarta;
	pCarta=BAR_CriarCarta(_6,Espadas);
	VetorAux[12] = *pCarta;
	pCarta=BAR_CriarCarta(_7,Espadas);
	VetorAux[13] = *pCarta;
	pCarta=BAR_CriarCarta(_Q,Espadas);
	VetorAux[14] = *pCarta;
	pCarta=BAR_CriarCarta(_J,Espadas);
	VetorAux[15] = *pCarta;
	pCarta=BAR_CriarCarta(_K,Espadas);
	VetorAux[16] = *pCarta;
	pCarta=BAR_CriarCarta(_A,Espadas);
	VetorAux[17] = *pCarta;
	pCarta=BAR_CriarCarta(_2,Espadas);
	VetorAux[18] = *pCarta;
	pCarta=BAR_CriarCarta(_3,Espadas);
	VetorAux[19] = *pCarta;

	pCarta=BAR_CriarCarta(_4,Copas);
	VetorAux[20] = *pCarta;
	pCarta=BAR_CriarCarta(_5,Copas);
	VetorAux[21] = *pCarta;
	pCarta=BAR_CriarCarta(_6,Copas);
	VetorAux[22] = *pCarta;
	pCarta=BAR_CriarCarta(_7,Copas);
	VetorAux[23] = *pCarta;
	pCarta=BAR_CriarCarta(_Q,Copas);
	VetorAux[24] = *pCarta;
	pCarta=BAR_CriarCarta(_J,Copas);
	VetorAux[25] = *pCarta;
	pCarta=BAR_CriarCarta(_K,Copas);
	VetorAux[26] = *pCarta;
	pCarta=BAR_CriarCarta(_A,Copas);
	VetorAux[27] = *pCarta;
	pCarta=BAR_CriarCarta(_2,Copas);
	VetorAux[28] = *pCarta;
	pCarta=BAR_CriarCarta(_3,Copas);
	VetorAux[29] = *pCarta;

	pCarta=BAR_CriarCarta(_4,Paus);
	VetorAux[30] = *pCarta;
	pCarta=BAR_CriarCarta(_5,Paus);
	VetorAux[31] = *pCarta;
	pCarta=BAR_CriarCarta(_6,Paus);
	VetorAux[32] = *pCarta;
	pCarta=BAR_CriarCarta(_7,Paus);
	VetorAux[33] = *pCarta;
	pCarta=BAR_CriarCarta(_Q,Paus);
	VetorAux[34] = *pCarta;
	pCarta=BAR_CriarCarta(_J,Paus);
	VetorAux[35] = *pCarta;
	pCarta=BAR_CriarCarta(_K,Paus);
	VetorAux[36] = *pCarta;
	pCarta=BAR_CriarCarta(_A,Paus);
	VetorAux[37] = *pCarta;
	pCarta=BAR_CriarCarta(_2,Paus);
	VetorAux[38] = *pCarta;
	pCarta=BAR_CriarCarta(_3,Paus);
	VetorAux[39] = *pCarta;
	
	//checando se o vetor está preenchido
	printf("Checando se o vetor esta preenchido:\n");
	for (i = 0; i < 40; i++){
		printf("VetorAux[%d]: Valor %d / Naipe %d\n",(i+1), 
			VetorAux[i].valor,VetorAux[i].naipe);
	} //fim for

	//função suporte da rand que faz gerar números diferentes sempre
	srand ((unsigned)time(NULL));

	//embaralhando o vetor (troca os indices aleatoriamente)
	for (i = 0; i < 40; i++){

		BAR_tpCarta pCartaAux;
		
		//gera um número aleatorio entre 0 e 39
		int random = rand() % 40 ;

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
	printf("\nChecando se o vetor esta embaralhado:\n");
	for (i = 0; i < 40; i++){
		printf("VetorAux[%d]: Valor %d / Naipe %d\n",(i+1), 
			VetorAux[i].valor,VetorAux[i].naipe);
	} //fim for
	
	// preenche um por um usando o vetor embaralhado
	for (i = 0; i < 40; i++){
		
		//pCarta recebe um ponteiro pra um tipo Carta do vetor embaralhado
		pCarta = &VetorAux[i] ;

		//checando se pCarta recebe um valor aleatorio
		printf("\npCarta: Valor %d / Naipe %d", pCarta->valor,pCarta->naipe);
		
		//é inserido um elemento na lista Baralho e 
		//seu valor é um ponteiro pra um tipo Carta
		condRetLista = LIS_InserirElementoApos (pCabecaBaralho, pCarta) ;

		//assertiva de saída
		if (condRetLista != LIS_CondRetOK){
			printf("\nNão inseriu elemento");
			return NULL;
		}
		else{
			printf("    (Elemento inserido)");
		}

	} //fim for
	// fim minha solução
	
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
/*BAR_tpCondRet BAR_ObterInfoCarta(BAR_tppCarta carta, 
				 BAR_tpValorCarta *valor,
				 BAR_tpNaipeCarta *naipe) {
	//assertiva de entrada
	if (carta == NULL)
		return BAR_tpCondRetParamIncorretos;
	
	valor = carta->valor;
	naipe = carta->naipe;
	
	//faltou assertiva de saída
	
	return BAR_tpCondRetOK;
} /************ Fim função: BAR &Obter informações da carta ****************/


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/
//não há funções encapsuladas no módulo

/************ FIM DO MÓDULO DE IMPLEMENTAÇÃO: BAR Baralho ******************/
