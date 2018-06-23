/***************************************************************************
*  $MCI Módulo de implementação: TMES Teste mesa
*
*  Arquivo gerado:              TestMES.c
*  Letras identificadoras:      TMES
*
*  Projeto: INF 1301 - Jogo de Truco
*  Autores: gsc, tgf, jvr
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gsc   22/jun/2018 início desenvolvimento
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
#include    "Mesa.h"


static const char RESET_TESTE_CMD [ ] 					= "=resetteste" ; 				//1
static const char CRIAR_LISTA_DE_LISTAS_CMD [ ] 		= "=criarlistadelistas" ; 		//2
static const char CRIAR_MESA_CMD [ ] 					= "=criarmesa" ;				//3
static const char CRIAR_MAO_CMD [ ] 					= "=criarmao" ; 				//4
static const char CRIAR_LIXO_CMD [ ] 					= "=criarlixo"	; 				//5
static const char DISTRIBUIR_MAOS_CMD [ ] 				= "=distribuirmaos" ; 			//6
static const char ESVAZIAR_MESA_CMD [ ] 				= "=esvaziarmesa" ; 			//7
static const char ESVAZIAR_LIXO_CMD [ ] 				= "=esvaziarlixo" ;				//8
static const char OBTER_QTD_CARTAS_CMD [ ] 				= "=obterqtdcartas" ; 			//9
static const char TRANSFERIR_CARTAS_PRO_LIXO_CMD [ ] 	= "=transferircartasprolixo" ;	//10
static const char DETERMINAR_RESULTADO_CMD [ ] 			= "=determinarresultado" ; 		//11
static const char DEFINIR_QUEM_COMECA_CMD [ ] 			= "=definirquemcomeca" ; 		//12
static const char IDENTIFICAR_QUEM_JOGOU_QUAL_CMD [ ] 	= "=identificarquemjogouqual" ; //13

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NaoNULL 1

#define DIM_VT_LISTA_DE_LISTAS 1
#define DIM_VT_MAOS  6
#define DIM_VT_MESA  1
#define DIM_VT_LIXO  1

LIS_tppLista vtListaDeListas [ DIM_VT_LISTA_DE_LISTAS ] ;
LIS_tppLista vtMaos [ DIM_VT_MAOS ] ;
LIS_tppLista vtMesa [ DIM_VT_MESA ] ;
LIS_tppLista vtLixo [ DIM_VT_LIXO ] ;
BAR_tppCarta VetorAux [ 40 ] ;

/************* PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO **************/
	static int IdentificarComando( char * ComandoTeste ) ;
   	static int ValidarInxMao( int inxBaralho, int Modo ) ;

/**************  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ***************/

/***************************************************************************
*  $FC Função: TBAR &Efetuar comando
*
*  $ED Descrição da função
*     Podem ser criadas até 6 mãos guardadas em um vetor, 
*     identificados pelos índices 0 a 5.
*     Pode ser criada 1 lista de listas.
*	  Pode ser criado 1 lixo.
*	  Pode ser criada 1 mesa.
*
*     Comandos disponíveis:
*
*     =resetteste
*       - anula os vetores e provoca vazamento de memória.
*
*     =criarlistadelistas
*		- retorna um ponteiro pra cabeça da lista que é armazenado no vtListaDeListas.
*
*     =criarmesa
*		- retorna um ponteiro pra tipo carta que é armazenado no vtMesa.
*
*	  =criarmao <inxMao>
*		- retorna um ponteiro pra cabeça da mao que é armazenado no vtMaos.
*
*	  =criarlixo
*		- retorna um ponteiro pra cabeça do lixo que é armazenado no vtLixo.
*
*     =distribuirmaos <inxQtdJogadores>
*     =esvaziarmesa
*	  =esvaziarlixo
*	  =obterqtdcartas
*	  =transferircartasprolixo
*	  =determinarresultado
*	  =definirquemcomeca
*	  =identificarquemjogouqual
***************************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )  {
  
	LIS_tppLista pCabecaBaralho ; 

  	int inxMao  = -1 ,
  		inxQtdJogadores = -1 ,
      	numLidos = -1 ,
	  	comando = 0 ,
	  	i ;

	pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;

  	comando = IdentificarComando(ComandoTeste) ;

  	switch (comando) {

  	case 1: //RESET TESTE

  		//preenche o vetor lista de listas com Null
		for( i = 0 ; i < DIM_VT_LISTA_DE_LISTAS ; i++ ) {
			vtListaDeListas[ i ] = NULL ;
		}

		//preenche o vetor mesa com Null
		for( i = 0 ; i < DIM_VT_MESA ; i++ ) {
			vtMesa[ i ] = NULL ;
		}

		//preenche o vetor maos com Null
		for( i = 0 ; i < DIM_VT_MAOS ; i++ ) {
			vtMaos[ i ] = NULL ;
		}

		//preenche o vetor lixo com Null
		for( i = 0 ; i < DIM_VT_LIXO ; i++ ) {
			vtLixo[ i ] = NULL ;
		}

		return TST_CondRetOK ;

	case 2: //CRIAR LISTA DE LISTAS

		//criarlistadelistas retorna ponteiro pra tpLista
		vtListaDeListas[0] = MES_CriarListaDeListas() ;

		//assertiva de saida do conteudo do ponteiro
		return TST_CompararPonteiroNulo( NaoNULL , 
										 vtListaDeListas[0] ,
						 				 "Erro na criacao do ponteiro da lista de listas." ) ;

	case 3: //CRIAR MESA

		//criarmesa retorna ponteiro pra tpLista
		vtMesa[0] = MES_CriarMesa() ;

		//assertiva de saida do conteudo do ponteiro
		return TST_CompararPonteiroNulo( NaoNULL , 
										 vtMesa[0] ,
						 				 "Erro na criacao do ponteiro da mesa." ) ;

	case 4: //CRIAR MAO

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &inxMao ) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (! ValidarInxMao( inxMao , VAZIO )) )  {
			return TST_CondRetParm ;
		}//fim if

		//criarbaralho retorna ponteiro pra tpLista
		vtMaos[inxMao] = MES_CriarMao() ;

		//assertiva de saida do conteudo do ponteiro
		return TST_CompararPonteiroNulo( NaoNULL , 
										 vtMaos[inxMao] ,
						 				 "Erro na criacao do ponteiro da mao." ) ;

	case 5: //CRIAR LIXO

		//criarlixo retorna ponteiro pra tpLista
		vtLixo[0] = MES_CriarLixo() ;

		//assertiva de saida do conteudo do ponteiro
		return TST_CompararPonteiroNulo( NaoNULL , 
										 vtLixo[0] ,
						 				 "Erro na criacao do ponteiro do lixo." ) ;

	case 6: //DISTRIBUIR MAOS

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &inxQtdJogadores ) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (inxQtdJogadores != 2 && inxQtdJogadores != 4 && inxQtdJogadores != 6) )  {
			return TST_CondRetParm ;
		}//fim if

		pCabecaBaralho = BAR_CriarBaralho() ;
		BAR_PreencherVetorCartas(VetorAux) ;
		BAR_EmbaralharVetorCartas(VetorAux) ;
		BAR_PreencherBaralho(pCabecaBaralho, VetorAux) ;

		LIS_IrInicioLista(vtListaDeListas[0]) ;
		LIS_InserirElementoApos(vtListaDeListas[0], pCabecaBaralho) ;	//inicio

		if (inxQtdJogadores == 2) {

			if (vtMaos[0] == NULL || vtMaos[1] == NULL) {
				return TST_CondRetParm ;
			}

			LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[0]) ;		//1
			LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[1]) ;		//2

		}

		else {

			if (inxQtdJogadores == 4) {

				if (vtMaos[0] == NULL || vtMaos[1] == NULL ||
					vtMaos[2] == NULL || vtMaos[3] == NULL) {
					return TST_CondRetParm ;
				}

				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[0]) ;		//1
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[1]) ;		//2
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[2]) ;		//3
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[3]) ;		//4
			}

			else {

				if (vtMaos[0] == NULL || vtMaos[1] == NULL ||
					vtMaos[2] == NULL || vtMaos[3] == NULL ||
					vtMaos[4] == NULL || vtMaos[5] == NULL) {
					return TST_CondRetParm ;
				}

				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[0]) ;		//1
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[1]) ;		//2
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[2]) ;		//3
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[3]) ;		//4
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[4]) ;		//5
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[5]) ;		//6

			}

		}

		if (MES_DistribuirMaos(vtListaDeListas[0], inxQtdJogadores) != TST_CondRetOK) {

			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 7: //ESVAZIAR MESA

		return TST_CondRetOK ;

  	case 8: //ESVAZIAR LIXO

		return TST_CondRetOK ;

	case 9: //OBTER QTD DE CARTAS

		return TST_CondRetOK ;

	case 10: //TRANSFERIR CARTAS PRO LIXO

		return TST_CondRetOK ;

	case 11: //DETERMINAR RESULTADO

		return TST_CondRetOK ;

	case 12: //DEFINIR QUEM COMECA

		return TST_CondRetOK ;

	case 13: //IDENTIFICAR QUEM JOGOU QUAL

		return TST_CondRetOK ;

	default: //COMANDO NAO EXISTE

		return TST_CondRetNaoConhec ;

  	} //fim switch "comando"

} /***************** Fim função: TBAR &Testar mesa *********************/


/***************  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  **************/

/***************************************************************************
*  $FC Função: Validar indice de baralho
***************************************************************************/
int ValidarInxMao( int inxMao, int Modo ){

	if ( ( inxMao <  0 ) || ( inxMao >= DIM_VT_MAOS )){
		return FALSE ;
	} // if
         
    if ( Modo == VAZIO ){
		if ( vtMaos [ inxMao ] != 0 ){
			return FALSE ;
        } //fim if
	} 
	else{
		if ( vtMaos [ inxMao ] == 0 ) {
			return FALSE ;
        } //fim if
    } //fim if
         
    return TRUE ;

} /************** Fim função: &Validar indice baralho *********************/

/***************************************************************************
*  $FC Função: Identificar Comando
***************************************************************************/
int IdentificarComando( char * ComandoTeste ) {

  	if ( strcmp( ComandoTeste , RESET_TESTE_CMD ) == 0 )  {
  		return 1 ;
  	}

  	else if ( strcmp( ComandoTeste , CRIAR_LISTA_DE_LISTAS_CMD ) == 0 ) {
  		return 2 ;
  	}

	else if ( strcmp( ComandoTeste , CRIAR_MESA_CMD ) == 0 ) {
		return 3 ;
	}

	else if ( strcmp( ComandoTeste , CRIAR_MAO_CMD ) == 0 ) {
		return 4 ;
	}

	else if ( strcmp( ComandoTeste , CRIAR_LIXO_CMD ) == 0 ) {
		return 5 ;
  	}

	else if ( strcmp( ComandoTeste , DISTRIBUIR_MAOS_CMD ) == 0 ) {
		return 6 ;
  	}

	else if ( strcmp( ComandoTeste , ESVAZIAR_MESA_CMD ) == 0 ) {
		return 7 ;
  	}

	else if ( strcmp( ComandoTeste , ESVAZIAR_LIXO_CMD ) == 0 ) {
		return 8 ;
  	}

	else if ( strcmp( ComandoTeste , OBTER_QTD_CARTAS_CMD ) == 0 ) {
		return 9 ;
  	}

	else if ( strcmp( ComandoTeste , TRANSFERIR_CARTAS_PRO_LIXO_CMD ) == 0 ) {
		return 10 ;
  	}

	else if ( strcmp( ComandoTeste , DETERMINAR_RESULTADO_CMD ) == 0 ) {
		return 11 ;
  	}

	else if ( strcmp( ComandoTeste , DEFINIR_QUEM_COMECA_CMD ) == 0 ) {
		return 12 ;
  	}

	else if ( strcmp( ComandoTeste , IDENTIFICAR_QUEM_JOGOU_QUAL_CMD ) == 0 ) {
		return 13 ;
  	}

  	else {
  		return 0 ;
  	}
} /************** Fim função: &Identificar Comando ************************/


/********* FIM DO MÓDULO DE IMPLEMENTAÇÃO: TMES Teste Mesa *************/

