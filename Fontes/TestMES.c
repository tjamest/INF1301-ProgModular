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
static const char IDENTIFICAR_QUEM_JOGOU_QUAL_CMD [ ] 	= "=identificarquemjogouqual" ; //11
static const char DESTRUIR_LISTAS_CMD [ ] 				= "=destruirlistas" ; 			//12

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NaoNULL 1

#define DIM_VT_LISTA_DE_LISTAS 1
#define DIM_VT_MAOS  6
#define DIM_VT_MESA  1
#define DIM_VT_LIXO  1

#define DEIXA_VIRA 0
#define TIRA_VIRA 1

#define SEM_PRIMEIRA 0
#define COM_PRIMEIRA 1
#define SEM_ULTIMA 0
#define COM_ULTIMA 1

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
*     =criarmesa <qtdCartas>
*		- retorna um ponteiro pra tipo carta que é armazenado no vtMesa.
*		insere cartas na mesa criada.
*
*	  =criarmao <inxMao>
*		- retorna um ponteiro pra cabeça da mao que é armazenado no vtMaos.
*
*	  =criarlixo
*		- retorna um ponteiro pra cabeça do lixo que é armazenado no vtLixo.
*
*     =distribuirmaos
*     =esvaziarmesa

*	  =esvaziarlixo
*		- deve-se esvaziar uma mesa com cartas antes para que tenha cartas no lixo.
*
*	  =obterqtdcartas <tipoPrimeira> <tipoUltima>
*		- os tipos podem ser semprimeira ou comprimeira e semltima ou comultima.
*
*	  =transferircartasprolixo
*
*	  =identificarquemjogouqual <qtdJogadores> <quemJogouAPrimeira>
***************************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )  {
  
	LIS_tppLista pCabecaBaralho ; 
	BAR_tppCarta pCarta ;

  	int inxMao  = -1 ,
  		qtdJogadores = -1 ,
  		qtdCartas = -1 ,
      	numLidos = -1 ,
	  	comando = 0 ,
	  	tipoEsvaziarMesa = -1 ,
	  	tipoPrimeira = -1 ,
	  	tipoUltima = -1 ,
	  	quemJogouAPrimeira = -1 ,
	  	i ;

	int * quemJogouASegunda = (int*)malloc(sizeof(int)) ;
	int * quemJogouATerceira = (int*)malloc(sizeof(int)) ;
	int * quemJogouAQuarta = (int*)malloc(sizeof(int)) ;
	int * quemJogouAQuinta = (int*)malloc(sizeof(int)) ;
	int * quemJogouASexta = (int*)malloc(sizeof(int)) ;

	pCabecaBaralho = (LIS_tppLista)malloc(sizeof(LIS_tppLista)) ;
	pCarta = (BAR_tppCarta)malloc(sizeof(BAR_tppCarta)) ;

	pCabecaBaralho = BAR_CriarBaralho() ;
	BAR_PreencherVetorCartas(VetorAux) ;
	BAR_EmbaralharVetorCartas(VetorAux) ;
	BAR_PreencherBaralho(pCabecaBaralho, VetorAux) ;

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

		//insere o baralho na lista de listas
		LIS_IrInicioLista(vtListaDeListas[0]) ;
		LIS_InserirElementoApos(vtListaDeListas[0], pCabecaBaralho) ;

		//assertiva de saida do conteudo do ponteiro
		return TST_CompararPonteiroNulo( NaoNULL , 
										 vtListaDeListas[0] ,
						 				 "Erro na criacao do ponteiro da lista de listas." ) ;

	case 3: //CRIAR MESA

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &qtdCartas ) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || qtdCartas < 0 && qtdCartas > 7)  {
			return TST_CondRetParm ;
		}//fim if

		//criarmesa retorna ponteiro pra tpLista
		vtMesa[0] = MES_CriarMesa() ;

		//inserir cartas na mesa
		for (i = 0 ; i < qtdCartas ; i++) {
			BAR_TransferirCarta(pCabecaBaralho, vtMesa[0]) ;
		}

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

		//2 jogadores
		if (vtMaos[0] != NULL && vtMaos[1] != NULL) {

			LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[0]) ;		//1
			LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[1]) ;		//2
			qtdJogadores = 2 ;

			//4 jogadores
			if (vtMaos[2] != NULL && vtMaos[3] != NULL) {

				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[2]) ;		//3
				LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[3]) ;		//4
				qtdJogadores = 4 ;

				//6 jogadores
				if (vtMaos[4] != NULL && vtMaos[5] != NULL) {

					LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[4]) ;		//5
					LIS_InserirElementoApos(vtListaDeListas[0], vtMaos[5]) ;		//6
					qtdJogadores = 6 ;

				}

				//se a mao 5 ou 6 for null
				else {
					qtdJogadores = 4 ;
				}

			}//fim if

			//se a mao 3 ou 4 for null
			else {
				qtdJogadores = 2 ;
			}

		}//fim if

		//se a mao 1 ou 2 for null
		else {
			return TST_CondRetParm ;
		}

		if (MES_DistribuirMaos(vtListaDeListas[0], qtdJogadores) != TST_CondRetOK) {

			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 7: //ESVAZIAR MESA

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "i" , &tipoEsvaziarMesa ) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 1) || (tipoEsvaziarMesa != DEIXA_VIRA && tipoEsvaziarMesa != TIRA_VIRA) )  {
			return TST_CondRetParm ;
		}//fim if

		if (MES_EsvaziarMesa (vtMesa[0], vtLixo[0], tipoEsvaziarMesa) != MES_CondRetOK) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

  	case 8: //ESVAZIAR LIXO

		if (MES_EsvaziarLixo (vtLixo[0]) != MES_CondRetOK) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 9: //OBTER QTD DE CARTAS

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "ii" , &tipoPrimeira, &tipoUltima ) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 2) || 
		     (tipoPrimeira != COM_PRIMEIRA && tipoPrimeira != SEM_PRIMEIRA) ||
		     (tipoUltima != COM_ULTIMA && tipoUltima != SEM_ULTIMA) )  {
			return TST_CondRetParm ;
		}//fim if

		qtdCartas = LIS_ObterQtdElem(vtMesa[0]) ;

		if (tipoPrimeira == COM_PRIMEIRA) {

			//com primeira com ultima
			if (tipoUltima == COM_ULTIMA) {
				if ((qtdCartas) != MES_ObterQtdCartas(vtMesa[0], COM_PRIMEIRA, COM_ULTIMA)) {
					return TST_CondRetErro ;
				}
				else {
					return TST_CondRetOK ;
				}
			}

			//com primeira sem ultima
			else {
				if ((qtdCartas-1) != MES_ObterQtdCartas(vtMesa[0], COM_PRIMEIRA, SEM_ULTIMA)) {
					return TST_CondRetErro ;
				}
				else {
					return TST_CondRetOK ;
				}
			}
		}//fim if

		else {

			//sem primeira com ultima
			if (tipoUltima == COM_ULTIMA) {
				if ((qtdCartas-1) != MES_ObterQtdCartas(vtMesa[0], SEM_PRIMEIRA, COM_ULTIMA)) {
					return TST_CondRetErro ;
				}
				else {
					return TST_CondRetOK ;
				}
			}

			//sem primeira sem ultima
			else {
				if ((qtdCartas-2) != MES_ObterQtdCartas(vtMesa[0], SEM_PRIMEIRA, SEM_ULTIMA)) {
					return TST_CondRetErro ;
				}
				else {
					return TST_CondRetOK ;
				}
			}
		}//fim else

	case 10: //TRANSFERIR CARTAS PRO LIXO

		LIS_IrInicioLista (vtListaDeListas[0]) ;
		LIS_InserirElementoApos (vtListaDeListas[0], vtMaos[0]) ;
		LIS_InserirElementoApos (vtListaDeListas[0], vtMaos[1]) ;
		LIS_InserirElementoApos (vtListaDeListas[0], vtMaos[2]) ;
		LIS_InserirElementoApos (vtListaDeListas[0], vtMaos[3]) ;
		LIS_InserirElementoApos (vtListaDeListas[0], vtMaos[4]) ;
		LIS_InserirElementoApos (vtListaDeListas[0], vtMaos[5]) ;
		LIS_InserirElementoApos (vtListaDeListas[0], vtLixo[0]) ;
		LIS_InserirElementoApos (vtListaDeListas[0], vtMesa[0]) ;

		if (MES_TransferirTodasCartasProLixo (vtListaDeListas[0]) != MES_CondRetOK) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 11: //IDENTIFICAR QUEM JOGOU QUAL

		//conta quantos parametros foram declarados
		numLidos = LER_LerParametros( "ii" , &qtdJogadores, &quemJogouAPrimeira ) ;

		//assertiva de entrada dos parametros do comando
		if ( (numLidos != 2) || 
		     (qtdJogadores != 2 && qtdJogadores != 4 && qtdJogadores != 6) ||
		     (quemJogouAPrimeira < 1 || quemJogouAPrimeira > 6) )  {
			return TST_CondRetParm ;
		}//fim if

		if (MES_IdentificarQuemJogouQual(qtdJogadores, 
										 quemJogouAPrimeira, quemJogouASegunda,
										 quemJogouATerceira, quemJogouAQuarta,
										 quemJogouAQuinta, quemJogouASexta) != MES_CondRetOK) {
			return TST_CondRetErro ;
		}

		return TST_CondRetOK ;

	case 12: //DESTRUIR LISTAS

		MES_DestruirListas( vtListaDeListas[0], pCabecaBaralho, vtMaos[0], vtMaos[1],
							vtMaos[2], vtMaos[3], vtMaos[4], vtMaos[5], vtLixo[0], vtMesa[0] ) ;

		vtListaDeListas[0] = NULL ;
		pCabecaBaralho = NULL ;
		vtMaos[0] = NULL ;
		vtMaos[1] = NULL ;
		vtMaos[2] = NULL ;
		vtMaos[3] = NULL ;
		vtMaos[4] = NULL ;
		vtMaos[5] = NULL ;
		vtLixo[0] = NULL ;
		vtMesa[0] = NULL ;

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

	else if ( strcmp( ComandoTeste , IDENTIFICAR_QUEM_JOGOU_QUAL_CMD ) == 0 ) {
		return 11 ;
  	}

  	else if ( strcmp( ComandoTeste , DESTRUIR_LISTAS_CMD ) == 0 ) {
		return 12 ;
  	}

  	else {
  		return 0 ;
  	}
} /************** Fim função: &Identificar Comando ************************/


/********* FIM DO MÓDULO DE IMPLEMENTAÇÃO: TMES Teste Mesa ****************/

