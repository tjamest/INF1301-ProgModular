/***************************************************************************
*  $MCI Módulo de implementação: TBAR Teste baralho
*
*  Arquivo gerado:              TestBAR.c
*  Letras identificadoras:      TBAR
*
*  Projeto: INF 1301 - Jogo de Truco
*  Autores: gsc, tgf, jvr
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  2       gsc   20/jun/2018 inserção de contadores
*     1       gsc   26/abr/2018 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include    "Baralho.h"


static const char RESET_TESTE_CMD [ ] 				= "=resetteste" ; 				//1
static const char CRIAR_BARALHO_CMD [ ] 			= "=criarbaralho" ; 			//2
static const char CRIAR_CARTA_CMD [ ] 				= "=criarcarta" ;				//3
static const char DESTRUIR_CARTA_CMD [ ] 			= "=destruircarta" ; 			//4
static const char OBTER_NAIPE_CMD [ ] 				= "=obternaipe"	; 				//5
static const char OBTER_VALOR_CMD [ ] 				= "=obtervalor" ; 				//6
static const char PREENCHER_VETOR_CARTAS_CMD [ ] 	= "=preenchervetorcartas" ; 	//7
static const char EMBARALHAR_VETOR_CARTAS_CMD [ ] 	= "=embaralharvetorcartas" ;	//8
static const char PREENCHER_BARALHO_CMD	[ ] 		= "=preencherbaralho" ; 		//9
static const char DESTRUIR_BARALHO_CMD	[ ] 		= "=destruirbaralho" ; 			//10

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NaoNULL 1

#define DIM_VT_BARALHO   10
#define DIM_VT_CARTA  40

LIS_tppLista vtBaralhos[ DIM_VT_BARALHO ] ;
BAR_tppCarta vtCartas[ DIM_VT_CARTA ] ;

/************* PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO **************/
	static int IdentificarComando( char * ComandoTeste ) ;
   	static int ValidarInxBaralho( int inxBaralho, int Modo ) ;
   	static int ValidarInxCarta( int inxCarta, int Modo ) ;

/**************  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ***************/

/***************************************************************************
*  $FC Função: TBAR &Efetuar comando
*
*  $ED Descrição da função
*     Podem ser criados até 10 baralhos guardados em um vetor, 
*     identificados pelos índices 0 a 9
*     Podem ser criadas até 40 cartas guardadas em um vetor, 
*     identificadas pelos índices 0 a 39
*
*     Comandos disponíveis:
*
*     =resetteste
*       - anula os vetores de baralhos e cartas e provoca vazamento de memória.
*
*     =criarbaralho 	<inxBaralho>
*		- retorna um ponteiro pra cabeça do baralho que é armazenado no vtBaralhos.
*
*     =criarcarta 		<int>  <int> 
*		- retorna um ponteiro pra tipo carta que é armazenado no vtCartas.
*
*     =destruircarta 	<inxCarta>   
*     =obternaipe 		<inxCarta>
*	  =preenchervetorcartas
*	  =embaralharvetorcartas
*	  =preencherbaralho <inxBaralho>
*	  =destruirbaralho 	<inxBaralho>
***************************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )  {
  
  	int inxBaralho  = -1 ,
	  	inxCarta = -1 ,
      	numLidos = -1 ,
	  	comando = 0 ,
	  	i ;

	BAR_tpValorCarta ValorCarta ;
  	BAR_tpNaipeCarta NaipeCarta ;

  	int valorCarta, naipeCarta ;

  	comando = IdentificarComando(ComandoTeste) ;

  	switch (comando) {

  	case 1: //resetteste

  		//preenche o vetor baralhos com Null
		for( i = 0 ; i < DIM_VT_BARALHO ; i++ ) {
			vtBaralhos[ i ] = NULL ;
		}

		//preenche o vetor cartas com Null
		for( i = 0 ; i < DIM_VT_CARTA ; i++ ) {
			vtCartas[ i ] = NULL ;
		}

		return TST_CondRetOK ;

	case 2: //criarbaralho

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &inxBaralho ) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (! ValidarInxBaralho( inxBaralho , VAZIO )) )  {
			return TST_CondRetParm ;
		}//fim if

		//criarbaralho retorna ponteiro pra tpLista
		vtBaralhos[inxBaralho] = BAR_CriarBaralho(vtCartas) ;

		//assertiva de saida do conteudo do ponteiro
		return TST_CompararPonteiroNulo( NaoNULL , 
										 vtBaralhos[inxBaralho] ,
						 				 "Erro na criacao do ponteiro do baralho." ) ;

	case 3: //criarcarta

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "iii" , &inxCarta, &valorCarta, &naipeCarta ) ;

		//assertiva de entrada dos parametros do comando
        if ( (numLidos != 3) || (! ValidarInxCarta( inxCarta , VAZIO )) ){
			return TST_CondRetParm ;
		}

		//transformando o parâmetro int recebido em tipo especifico
		if (  (valorCarta >= 0 && valorCarta <= 9) 
		   && (naipeCarta >= 0 && naipeCarta <= 3) ) {

			ValorCarta = (BAR_tpValorCarta) valorCarta;
			NaipeCarta = (BAR_tpNaipeCarta) naipeCarta;

		}//fim if

		//assertiva de entrada do valor e naipe recebidos
		else {
			printf("Erro de parametro invalido") ;
			return TST_CondRetParm ;
		} //fim if

		//armazena no vetor de cartas um ponteiro pra um tipo carta criado
		vtCartas[ inxCarta ] = BAR_CriarCarta( ValorCarta, NaipeCarta ) ;

		//assertiva de saida do conteudo do vetor carta
		return TST_CompararPonteiroNulo( NaoNULL , 
										 vtCartas[ inxCarta ] ,
										 "Erro na criacao do ponteiro da carta."  ) ;

	case 4: //destruircarta

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &inxCarta ) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (! ValidarInxCarta( inxCarta , NAO_VAZIO )) )  {
			return TST_CondRetParm ;
		}//fim if

		//destruicao do conteudo do vetor
		BAR_DestruirCarta( vtCartas[ inxCarta ] ) ;
		
		if (vtBaralhos[inxBaralho] != NULL) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 5: //obternaipe

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros("i" , &inxCarta) ;
	
		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (! ValidarInxCarta(inxCarta , NAO_VAZIO)) ) {
			return TST_CondRetParm ;
		}//fim if

		NaipeCarta = BAR_ObterNaipe (vtCartas[inxCarta]) ;

		//assertiva de saida do conteudo de naipe
		if ( NaipeCarta < 0 || NaipeCarta > 3 ) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 6: //obtervalor

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &inxCarta) ;
	
		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (! ValidarInxCarta(inxCarta , NAO_VAZIO)) ) {
			return TST_CondRetParm ;
		}//fim if

		ValorCarta = BAR_ObterValor (vtCartas[inxCarta]) ;

		//assertiva de saida do conteudo de valor
		if ( ValorCarta < 0 || ValorCarta > 9 ) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 7: //preenchervetorcartas

		if ( BAR_PreencherVetorCartas (vtCartas) != BAR_CondRetOK  ) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

  	case 8: //embaralharvetorcartas

		if ( BAR_EmbaralharVetorCartas (vtCartas) != BAR_CondRetOK  ) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 9: //preecherbaralho

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &inxBaralho) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (! ValidarInxBaralho(inxBaralho , NAO_VAZIO)) ) {
			return TST_CondRetParm ;
		}//fim if

		if ( BAR_PreencherBaralho (vtBaralhos[inxBaralho], vtCartas) != BAR_CondRetOK  ) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 10: //destruirbaralho

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &inxBaralho) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (! ValidarInxBaralho(inxBaralho , NAO_VAZIO)) ) {
			return TST_CondRetParm ;
		}//fim if

		BAR_DestruirBaralho (vtBaralhos[inxBaralho]) ;

		if (vtBaralhos[inxBaralho] != NULL) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	default: //comando nao existe

		return TST_CondRetNaoConhec ;

  	} //fim switch "comando"

} /***************** Fim função: TBAR &Testar baralho *********************/


/***************  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  **************/

/***************************************************************************
*  $FC Função: Validar indice de baralho
***************************************************************************/
int ValidarInxBaralho( int inxBaralho, int Modo ){

	if ( ( inxBaralho <  0 ) || ( inxBaralho >= DIM_VT_BARALHO )){
		return FALSE ;
	} // if
         
    if ( Modo == VAZIO ){
		if ( vtBaralhos[ inxBaralho ] != 0 ){
			return FALSE ;
        } //fim if
	} 
	else{
		if ( vtBaralhos[ inxBaralho ] == 0 ) {
			return FALSE ;
        } //fim if
    } //fim if
         
    return TRUE ;

} /************** Fim função: &Validar indice baralho *********************/


/***************************************************************************
*  $FC Função: Validar indice de carta
***************************************************************************/
int ValidarInxCarta( int inxCarta, int Modo ){

	if ( ( inxCarta <  0 ) || ( inxCarta >= DIM_VT_CARTA )){
		return FALSE ;
	} // if
         
    if ( Modo == VAZIO ){
		if ( vtCartas[ inxCarta ] != 0 ){
			return FALSE ;
        } //fim if
	} 
	else{
		if ( vtCartas[ inxCarta ] == 0 ) {
			return FALSE ;
        } //fim if
    } //fim if
         
    return TRUE ;

} /************** Fim função: &Validar indice carta ***********************/

/***************************************************************************
*  $FC Função: Identificar Comando
***************************************************************************/
int IdentificarComando( char * ComandoTeste ) {

	//RESET TEST (se o comando for "resettest")
  	if ( strcmp( ComandoTeste , RESET_TESTE_CMD ) == 0 )  {
  		return 1 ;
  	}

 	//CRIAR BARALHO (se o comando for "criarbaralho")
  	else if ( strcmp( ComandoTeste , CRIAR_BARALHO_CMD ) == 0 ) {
  		return 2 ;
  	}

  	//CRIAR CARTA (se o comando for "criarcarta")
	else if ( strcmp( ComandoTeste , CRIAR_CARTA_CMD ) == 0 ) {
		return 3 ;
	}

  	//DESTRUIR CARTA (se o comando for "destruircarta")
	else if ( strcmp( ComandoTeste , DESTRUIR_CARTA_CMD ) == 0 ) {
		return 4 ;
	}

  	//OBTER NAIPE (se o comando for "obternaipe")
	else if ( strcmp( ComandoTeste , OBTER_NAIPE_CMD ) == 0 ) {
		return 5 ;
  	}

  	//OBTER VALOR (se o comando for "obtervalor")
	else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 ) {
		return 6 ;
  	}

  	//PREENCHER VETOR CARTAS (se o comando for "preenchervetorcartas")
	else if ( strcmp( ComandoTeste , PREENCHER_VETOR_CARTAS_CMD ) == 0 ) {
		return 7 ;
  	}

  	//EMBARALHAR VETOR CARTAS (se o comando for "embaralharvetorcartas")
	else if ( strcmp( ComandoTeste , EMBARALHAR_VETOR_CARTAS_CMD ) == 0 ) {
		return 8 ;
  	}

  	//PREENCHER BARALHO (se o comando for "preencherbaralho")
	else if ( strcmp( ComandoTeste , PREENCHER_BARALHO_CMD ) == 0 ) {
		return 9 ;
  	}

  	//DESTRUIR BARALHO (se o comando for "destruirbaralho")
	else if ( strcmp( ComandoTeste , DESTRUIR_BARALHO_CMD ) == 0 ) {
		return 10 ;
  	}

  	//COMANDO NAO EXISTE
  	else {
  		return 0 ;
  	}
} /************** Fim função: &Identificar Comando ************************/


/********* FIM DO MÓDULO DE IMPLEMENTAÇÃO: TBAR Teste Baralho *************/

