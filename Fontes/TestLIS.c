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
#include    "CEspDin.h"
#include    "LerParm.h"

#include    "Lista.h"


static const char RESET_TEST_CMD          [ ] = "=resetteste"         ; //1
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"         ; //2
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"      ; //3
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"      ; //4
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"       ; //5
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"        ; //6
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem"     ; //7
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"        ; //8
static const char IR_INICIO_CMD           [ ] = "=irinicio"           ; //9
static const char IR_FIM_CMD              [ ] = "=irfinal"            ; //10
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"        ; //11
static const char EXCLUIR_PTR_ELEM_CMD    [ ] = "=excluirptrparaelem" ; //12
static const char OBTER_QTD_ELEM_CMD      [ ] = "=obterqtdelem"       ; //13

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

static int IdentificarComando( char * ComandoTeste ) ;
static void DestruirValor( void * pValor ) ;
static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  string  CondRetEsp
*     =inselemapos                  inxLista  string  CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) {
  int inxLista  = -1 ,
      numLidos   = -1 ,
      CondRetEsp = -1  ,
      comando = -1 ;

  void * valor ;

  TST_tpCondRet CondRet ;

  char   StringDado[  DIM_VALOR ] ;
  char * pDado ;

  int ValEsp = -1 ;

  int i ;

  int numElem = -1 ;

  StringDado[ 0 ] = 0 ;

  comando = IdentificarComando(ComandoTeste) ;

  switch (comando) {

  case 1: //RESETTESTE

    for( i = 0 ; i < DIM_VT_LISTA ; i++ ) {
       vtListas[ i ] = NULL ;
    }

    return TST_CondRetOK ;

  case 2: //CRIARLISTA

    numLidos = LER_LerParametros( "i", &inxLista ) ;

    if ( ( numLidos != 1 ) || ( ! ValidarInxLista( inxLista , VAZIO ))) {
       return TST_CondRetParm ;
    }

    vtListas[ inxLista ] = LIS_CriarLista( DestruirValor ) ;

    return TST_CompararPonteiroNulo( 1, vtListas[ inxLista ], "Erro em ponteiro de nova lista."  ) ;

  case 3: //DESRUIRLISTA

    numLidos = LER_LerParametros( "i", &inxLista ) ;

    if ( ( numLidos != 1 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO ))) {
       return TST_CondRetParm ;
    }

    LIS_DestruirLista( vtListas[ inxLista ] ) ;
    vtListas[ inxLista ] = NULL ;

    return TST_CondRetOK ;

  case 4: //ESVAZIARLISTA

    numLidos = LER_LerParametros( "i", &inxLista ) ;

    if ( ( numLidos != 1 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO ))) {
       return TST_CondRetParm ;
    }

    LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

    return TST_CondRetOK ;

  case 5: //INSERIRELEMENTOANTES

    numLidos = LER_LerParametros( "isi", &inxLista, StringDado, &CondRetEsp ) ;

    if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista, NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    }

    pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;

    if ( pDado == NULL ) {
       return TST_CondRetMemoria ;
    }

    strcpy( pDado, StringDado ) ;

    CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , pDado ) ;

    if ( CondRet != LIS_CondRetOK )
    {
       free( pDado ) ;
    }

    return TST_CompararInt( CondRetEsp, CondRet, "Condicao de retorno errada ao inserir antes." ) ;

  case 6: //INSERIRELEMENTOAPOS

    numLidos = LER_LerParametros( "isi", &inxLista, StringDado, &CondRetEsp ) ;

    if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    }

    pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;

    if ( pDado == NULL ) {
       return TST_CondRetMemoria ;
    }

    strcpy( pDado, StringDado ) ;


    CondRet = LIS_InserirElementoApos( vtListas[ inxLista ], pDado ) ;

    if ( CondRet != LIS_CondRetOK ) {
       free( pDado ) ;
    }

    return TST_CompararInt( CondRetEsp, CondRet, "Condicao de retorno errada ao inserir apos." ) ;

  case 7: //OBTERVALORELEM

    numLidos = LER_LerParametros( "isi" , &inxLista , StringDado , &ValEsp ) ;

    if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    }

    pDado = ( char * ) LIS_ObterValor( vtListas[ inxLista ] ) ;

    if ( ValEsp == 0 ) {
       return TST_CompararPonteiroNulo( 0, pDado, "Valor não deveria existir." ) ;
    }

    if ( pDado == NULL ) {
       return TST_CompararPonteiroNulo( 1, pDado, "Dado tipo um deveria existir." ) ;
    }

    return TST_CompararString( StringDado, pDado, "Valor do elemento errado." ) ;

  case 8: //EXCLUIRELEM

    numLidos = LER_LerParametros( "ii", &inxLista, &CondRetEsp ) ;

    if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    } /* if */

    return TST_CompararInt(CondRetEsp, LIS_ExcluirElemento( vtListas[ inxLista ] ), 
                           "Condição de retorno errada ao excluir.") ;

  case 9: //IRINICIO

    numLidos = LER_LerParametros( "i" , &inxLista ) ;

    if ( ( numLidos != 1 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    }

    LIS_IrInicioLista( vtListas[ inxLista ] ) ;

    return TST_CondRetOK ;

  case 10: //IRFINAL

    numLidos = LER_LerParametros( "i" , &inxLista ) ;

    if ( ( numLidos != 1 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    }

    LIS_IrFinalLista( vtListas[ inxLista ] ) ;

    return TST_CondRetOK ;

  case 11: //AVANCARELEM

    numLidos = LER_LerParametros( "iii" , &inxLista , &numElem , &CondRetEsp ) ;

    if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    }

    return TST_CompararInt( CondRetEsp , LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                            "Condicao de retorno errada ao avancar" ) ;

  case 12: //EXCLUIRPTRPARAELEM

    numLidos = LER_LerParametros( "i" , &inxLista) ;

    if ( ( numLidos != 1 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    }

    valor = LIS_ObterValor(vtListas[inxLista]) ;

    if (valor == NULL) {
      return TST_CondRetParm ;
    }

    if (LIS_ExcluirPtrParaElemento (vtListas[inxLista]) != LIS_CondRetOK) {
      return TST_CondRetErro ;
    }

    else {
      if (valor == NULL) {
        return TST_CondRetOK ;
      }
      else {
        return TST_CondRetErro ;
      }
    }

  case 13: //OBTERQTDELEM

    numLidos = LER_LerParametros( "i" , &inxLista) ;

    if ( ( numLidos != 1 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) ) {
       return TST_CondRetParm ;
    }

    if (LIS_ObterQtdElem (vtListas[inxLista]) < 0 ) {
      return TST_CondRetErro ;
    }

    return TST_CondRetOK ;

  default: //COMANDO NAO EXISTE

    return TST_CondRetNaoConhec ;

  } //fim switch 'comando'

} /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*  $FC Função: TLIS -Destruir valor
***********************************************************************/
void DestruirValor( void * pValor ) {
  free( pValor ) ;
} /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*  $FC Função: TLIS -Validar indice de lista
***********************************************************************/
int ValidarInxLista( int inxLista , int Modo ) {

  if ( ( inxLista <  0 ) || ( inxLista >= DIM_VT_LISTA )) {
     return FALSE ;
  }
     
  if ( Modo == VAZIO ) {
     if ( vtListas[ inxLista ] != 0 ) {
        return FALSE ;
     }
  } 

  else {
     if ( vtListas[ inxLista ] == 0 ) {
        return FALSE ;
     }
  }
     
  return TRUE ;

} /* Fim função: TLIS -Validar indice de lista */

/***************************************************************************
*  $FC Função: Identificar Comando
***************************************************************************/
int IdentificarComando( char * ComandoTeste ) {

  //RESET TEST (se o comando for "resettest")
  if ( strcmp( ComandoTeste , RESET_TEST_CMD ) == 0 )  {
    return 1 ;
  }

  //CRIAR LISTA (se o comando for "criarlista")
  else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 ) {
    return 2 ;
  }

  //DESTRUIR LISTA (se o comando for "destruirlista")
  else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 ) {
    return 3 ;
  }

  //ESVAZIAR LISTA (se o comando for "esvaziarlista")
  else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 ) {
    return 4 ;
  }

  //INSERIR ELEMENTO ANTES (se o comando for "inselemantes")
  else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 ) {
    return 5 ;
  }

  //INSERIR ELEMENTO APOS (se o comando for "inselemapos")
  else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 ) {
    return 6 ;
  }

  //OBTER VALOR ELEMENTO (se o comando for "obtervalorelem")
  else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 ) {
    return 7 ;
  }

  //EXCLUIR ELEMENTO (se o comando for "excluirelem")
  else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 ) {
    return 8 ;
  }

  //IR INICIO (se o comando for "irinicio")
  else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 ) {
    return 9 ;
  }

  //IR FINAL (se o comando for "irfinal")
  else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 ) {
    return 10 ;
  }

  //AVANCAR ELEMENTO (se o comando for "avancarelem")
  else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 ) {
    return 11 ;
  }

  //EXCLUIR PTR PARA ELEMENTO (se o comando for "excluirptrparaelem")
  else if ( strcmp( ComandoTeste , EXCLUIR_PTR_ELEM_CMD ) == 0 ) {
    return 12 ;
  }

  //OBTER QTD DE ELEMENTOS (se o comando for "obterqtdelem")
  else if ( strcmp( ComandoTeste , OBTER_QTD_ELEM_CMD ) == 0 ) {
    return 13 ;
  }

  //COMANDO NAO EXISTE
  else {
    return 0 ;
  }
} /************** Fim função: -Identificar comando ************************/

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

