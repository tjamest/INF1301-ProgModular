/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
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


static const char RESET_BARALHO_CMD     [ ] = "=resetteste"       ;
static const char CRIAR_BARALHO_CMD     [ ] = "=criarbaralho"     ;
static const char DESTRUIR_BARALHO_CMD  [ ] = "=destruirbaralho"  ;
//static const char CRIAR_CARTA_CMD       [ ] = "=criarcarta"       ;
//static const char DESTRUIR_CARTA_CMD    [ ] = "=destruircarta"    ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_BARALHO   10
#define DIM_VT_CARTA  40
#define DIM_VALOR     100

LIS_tppLista vtBaralhos[ DIM_VT_BARALHO ] ;
//BAR_tppCarta vtCartas[ DIM_VT_CARTA ] ;

/************* PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO **************/
   static int ValidarInxBaralho( int inxBaralho, int Modo ) ;

/**************  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ***************/

/***************************************************************************
*  $FC Função: TBAR &Testar baralho
*
*  $ED Descrição da função
*     Podem ser criados até 10 baralhos guardados em um vetor, 
*     identificados pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de baralho e provoca vazamento de memória.
*     =criarbaralho                 <inxBaralho>
*     =destruirbaralho              <inxBaralho>
*     =criarcarta                   <int>  <int> 
*     =destruircarta                <inxCarta>   
***************************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )  {
  
  //VARIÁVEIS USADAS POR TODOS COMANDOS
  int inxBaralho  = -1 ,
      numLidos   = -1 ,
      CondRetEsp = -1  ;
  char   StringDado[  DIM_VALOR ] ;
  int ValEsp = -1 ;
  int i ;
  int numElem = -1 ;
  StringDado[ 0 ] = 0 ;

  //RESET TEST
  //se o comando for "resettest":
  if ( strcmp( ComandoTeste , RESET_BARALHO_CMD ) == 0 )  {
    //preenche o vetor baralho com Null
    for( i = 0 ; i < DIM_VT_BARALHO ; i++ ) {
               vtBaralhos[ i ] = NULL ;
    }
    return TST_CondRetOK ;
  } //fim ativa: Efetuar reset de teste de baralho

  //CRIAR BARALHO
  //se o comando for "criarbaralho"
  else if ( strcmp( ComandoTeste , CRIAR_BARALHO_CMD ) == 0 ) {

    //conta quantos parametros foram declarados
    numLidos = LER_LerParametros( "i" , &inxBaralho ) ;

    //se for diferente de 1 retorna erro de declaração de parametro
    if ( (numLidos != 1) || (! ValidarInxBaralho( inxBaralho , VAZIO )) )  {
      return TST_CondRetParm ;
    }//fim if

    //criarbaralho retorna ponteiro pra tpLista
    vtBaralhos[ inxBaralho ] = BAR_CriarBaralho( ) ;

    //retorna TST_CondRetErro se os dois ponteiros forem diferentes
    //retorna TST_CondRetOK se os dois ponteiros forem iguais
    //0 = ponteiro Null   //1 = ponteiro não-Null
    return TST_CompararPonteiroNulo( 1 , vtBaralhos[ inxBaralho ] ,
                              "Erro em ponteiro de nova lista."  ) ;

  } //fim ativa: Testar CriarBaralho

  //DESTRUIR BARALHO
  //se o comando for "destruirbaralho"
  else if ( strcmp( ComandoTeste , DESTRUIR_BARALHO_CMD ) == 0 ) {

    //conta quantos parametros foram declarados
    numLidos = LER_LerParametros( "i" , &inxBaralho ) ;

    //se for diferente de 1 retorna erro de declaração de parametro
    if ( (numLidos != 1) || (! ValidarInxBaralho( inxBaralho , NAO_VAZIO )) )  {
      return TST_CondRetParm ;
    }//fim if

	//anula o ponteiro pro baralho
    vtBaralhos[ inxBaralho ] = NULL ;

    return TST_CondRetOK ;

  } //fim ativa: Testar DestruirBaralho

/*  //CRIAR CARTA
  //se o comando for "criarcarta"
	else if ( strcmp( ComandoTeste , CRIAR_CARTA_CMD ) == 0 ){

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "iii" , &inxBaralho, &valorCarta,
                                         &naipeCarta ) ;

		//se for diferente de 4 retorna erro de declaração de parametro
        	if ( (numLidos != 4) || ValidarInxBaralho ( inxBaralho ) == 0 ){
			return TST_CondRetParm ;
		}

		//transformando o parâmetro int recebido em tipo específico
		switch (valorCarta) {
		case 0: ValorCarta = _4;	break;
		case 1: ValorCarta = _5;	break;
		case 2: ValorCarta = _6;	break;
		case 3:	ValorCarta = _7;	break;
		case 4:	ValorCarta = _Q;	break;
		case 5:	ValorCarta = _J;	break;
		case 6:	ValorCarta = _K;	break;
		case 7:	ValorCarta = _A;	break;
		case 8:	ValorCarta = _2;	break;
		case 9:	ValorCarta = _3;	break;
		default: 
			printf("Erro de parametro invalido") ;
			return TST_CondRetParm ;
		}//fim switch valorCarta

		switch (naipeCarta) {
		case 0: NaipeCarta = Ouros;		break;
		case 1:	NaipeCarta = Espadas;	break;
		case 2:	NaipeCarta = Copas;		break;
		case 3:	NaipeCarta = Paus;		break;
		default:
			printf("Erro de parametro invalido") ;
			return TST_CondRetParm ;
		}//fim switch naipeCarta

		//armazena em pCarta um ponteiro pra um tipo carta criado
		pCarta = BAR_CriarCarta( ValorCarta, NaipeCarta ) ;

		//adiciona uma carta no baralho
		CondRetLista = LIS_InserirElementoApos(vtBaralhos[inxBaralho], pCarta);
		
		//assertiva de saída
		if (CondRetLista != LIS_CondRetOK) {
			return TST_CondRetErro;
		}

		return TST_CondRetOK ;

	} //fim ativa: Testar CriarCarta*/

return TST_CondRetNaoConhec ;

} /***************** Fim função: TBAR &Testar baralho *********************/


/***************  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  **************/

/***************************************************************************
*  $FC Função: TBAR - Validar indice de baralho
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

} /************** Fim função: TBAR &Validar indice baralho ****************/


/********* FIM DO MÓDULO DE IMPLEMENTAÇÃO: TBAR Teste Baralho *************/

