/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data         Observações
*     6        gsc      26/jun/2018   inclusão de controles de teste com o módulo Conta 
*	    5		   gsc, tgf   11/mai/2018   criadas as funções ObterQtdElem e ExcluirPtrParaElem 
*     4        avs      01/fev/2006   criar linguagem script simbólica
*     3        avs      08/dez/2004   uniformização dos exemplos
*     2        avs      07/jul/2003   unificação de todos os módulos em um só projeto
*     1        avs      16/abr/2003   início desenvolvimento
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"

#ifdef _DEBUG
   #include   "Generico.h"
   #include   "CEspDin.h"
   #include   "Conta.h"
   #include   "..\\tabelas\\IdTiposEspaco.def"
#endif

#undef LISTA_OWN

/***********************************************************************
*  $TC Tipo de dados: LIS Elemento da lista
***********************************************************************/
typedef struct tagElemLista {
	void * pValor ;	//Ponteiro para o valor contido no elemento
  struct tagElemLista * pAnt ; //Ponteiro para o elemento predecessor
  struct tagElemLista * pProx ; //Ponteiro para o elemento sucessor
} tpElemLista ;

/***********************************************************************
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
***********************************************************************/
typedef struct LIS_tagLista {

	//Ponteiro para a origem da lista
    tpElemLista * pOrigemLista ;

	//Ponteiro para o final da lista
    tpElemLista * pFimLista ; 

	//Ponteiro para o elemento corrente da lista
	tpElemLista * pElemCorr ;

	//Número de elementos da lista
	int numElem ;

	///Ponteiro para a função de destruição do valor contido em um elemento
	void ( * ExcluirValor ) ( void * pValor ) ;

} LIS_tpLista ;

/************ PROTÓTIPOS DAS FUNÇÕES ENCAPSULADAS NO MÓDULO ***************/
static void LiberarElemento( LIS_tppLista   pLista, tpElemLista * pElem ) ;
static tpElemLista * CriarElemento( LIS_tppLista pLista, void * pValor ) ;
static void LimparCabeca( LIS_tppLista pLista ) ;

/***********  CÓDIGO DAS FUNÇÕES EXPORTADAS PELO MÓDULO  ******************/

/***************************************************************************
*  Função: LIS  &Criar lista
***************************************************************************/
LIS_tppLista LIS_CriarLista( void   ( * ExcluirValor ) ( void * pDado ) )
{
      LIS_tpLista * pLista = NULL ;

      #ifdef _DEBUG
        CNT_CONTAR("LIS_CriarLista - Entrou e declarou variaveis") ;
      #endif

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } //fim if

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pLista, LIS_TipoEspacoLista ) ;
      #endif

      return pLista ;

} /***************** Fim função: LIS &Criar lista **********************/

/***************************************************************************
*  Função: LIS  &Destruir lista
***************************************************************************/
void LIS_DestruirLista( LIS_tppLista pLista )
{
      #ifdef _DEBUG
        assert( pLista != NULL ) ;
        CNT_CONTAR("LIS_DestruirLista - Entrou e assertou pLista != NULL") ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

} /***************** Fim função: LIS &Destruir lista *******************/

/***************************************************************************
*  Função: LIS  &Esvaziar lista
***************************************************************************/
void LIS_EsvaziarLista( LIS_tppLista pLista )
{
      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
        assert( pLista != NULL ) ;
        CNT_CONTAR("LIS_EsvaziarLista - Entrou, declarou variaveis e assertou pLista != NULL") ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } //fim while

      LimparCabeca( pLista ) ;

} /***************** Fim função: LIS &Esvaziar lista *******************/

/***************************************************************************
*  Função: LIS  &Inserir elemento antes
***************************************************************************/
LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista, void * pValor )
{
      tpElemLista * pElem ;

      #ifdef _DEBUG
        assert( pLista != NULL ) ;
        CNT_CONTAR("LIS_InserirElementoAntes - Entrou, declarou variaveis e assertou pLista != NULL") ;
      #endif

      // Criar elemento a inserir antes

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } //fim if

      // Encadear o elemento antes do elemento corrente

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } //fim if

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } //fim if

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

} /********* Fim função: LIS &Inserir elemento antes *******************/

/***************************************************************************
*  Função: LIS  &Inserir elemento após
***************************************************************************/
LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista, void * pValor )   
{
      tpElemLista * pElem ;

      #ifdef _DEBUG
        assert( pLista != NULL ) ;
        CNT_CONTAR("LIS_InserirElementoApos - Entrou, declarou variaveis e assertou pLista != NULL") ;
      #endif

      // Criar elemento a inserir após

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } //fim if

      // Encadear o elemento após o elemento

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } //fim if

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } //fim if
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

} /********* Fim função: LIS &Inserir elemento após ********************/

/***************************************************************************
*  Função: LIS  &Excluir elemento
***************************************************************************/
LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
{
      tpElemLista * pElem ;

      #ifdef _DEBUG
        assert( pLista  != NULL ) ;
        CNT_CONTAR("LIS_ExcluirElemento - Entrou, declarou variaveis e assertou pLista != NULL") ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } //fim if

      pElem = pLista->pElemCorr ;

      // Desencadeia à esquerda

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } //fim if

      // Desencadeia à direita

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } //fim if

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

} /************* Fim função: LIS &Excluir elemento *********************/

/***************************************************************************
*  Função: LIS  &Excluir ponteiro para elemento
***************************************************************************/
LIS_tpCondRet LIS_ExcluirPtrParaElemento( LIS_tppLista pLista )
{
  tpElemLista *pElem ;

  #ifdef _DEBUG
    assert( pLista  != NULL ) ;
    CNT_CONTAR("LIS_ExcluirPtrParaElemento - Entrou, declarou variaveis e assertou pLista != NULL") ;
  #endif

  if ( pLista->pElemCorr == NULL )
  {
     return LIS_CondRetListaVazia ;
  } //fim if

  pElem = pLista->pElemCorr ;

  // Desencadeia à esquerda

     if ( pElem->pAnt != NULL )
     {
        pElem->pAnt->pProx   = pElem->pProx ;
        pLista->pElemCorr    = pElem->pAnt ;
     } else {
        pLista->pElemCorr    = pElem->pProx ;
        pLista->pOrigemLista = pLista->pElemCorr ;
     } //fim if

  // Desencadeia à direita

     if ( pElem->pProx != NULL )
     {
        pElem->pProx->pAnt = pElem->pAnt ;
     } else
     {
        pLista->pFimLista = pElem->pAnt ;
     } //fim if

  free(pElem) ;

pLista->numElem-- ;

return LIS_CondRetOK ;

} /**** Fim função: LIS &Excluir ponteiro para elemento ****************/

/***************************************************************************
*  Função: LIS  &Obter quantidade de elementos
***************************************************************************/
int LIS_ObterQtdElem( LIS_tppLista pLista ) {

	int qtd;

  #ifdef _DEBUG
    assert( pLista  != NULL ) ;
    CNT_CONTAR("LIS_ObterQtdElem - Entrou, declarou variaveis e assertou pLista != NULL") ;
  #endif

  qtd = pLista->numElem;
  return qtd;

} /******** Fim função: LIS &Obter quantidade de elementos ****************/

/***************************************************************************
*  Função: LIS  &Obter referência para o valor contido no elemento
***************************************************************************/
void * LIS_ObterValor( LIS_tppLista pLista ) {

	#ifdef _DEBUG
    assert( pLista != NULL ) ;
    CNT_CONTAR("LIS_ObterValor - Entrou e assertou pLista != NULL") ;
  #endif

    if ( pLista->pElemCorr == NULL )
    {
		return NULL ;
    } //fim if

    return pLista->pElemCorr->pValor ;

} /* Fim função: LIS &Obter referencia para valor contido no elemento */

/***************************************************************************
*  Função: LIS  &Ir para o elemento inicial
***************************************************************************/
void LIS_IrInicioLista( LIS_tppLista pLista ) {

	#ifdef _DEBUG
    assert( pLista != NULL ) ;
    CNT_CONTAR("LIS_IrInicioLista - Entrou e assertou pLista != NULL") ;
  #endif

  pLista->pElemCorr = pLista->pOrigemLista ;

} /*************** Fim função: LIS &Ir inicio lista ********************/

/***************************************************************************
*  Função: LIS  &Ir para o elemento final
***************************************************************************/
void LIS_IrFinalLista( LIS_tppLista pLista ) {

	#ifdef _DEBUG
		assert( pLista != NULL ) ;
    CNT_CONTAR("LIS_IrFinalLista - Entrou e assertou pLista != NULL") ;
  #endif

  pLista->pElemCorr = pLista->pFimLista ;

} /*************** Fim função: LIS &Ir final lista *********************/

/***************************************************************************
*  Função: LIS  &Avançar elemento
***************************************************************************/
LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista, int numElem) {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
         CNT_CONTAR("LIS_AvancarElementoCorrente - Entrou, declarou variaveis e assertou pLista != NULL") ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

} /*************** Fim função: LIS &Avancar elemento *******************/

/***************************************************************************
*  Função: LIS  &Procurar elemento contendo valor
***************************************************************************/
LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista, void * pValor ) {

    tpElemLista * pElem ;

    #ifdef _DEBUG
       assert( pLista  != NULL ) ;
       CNT_CONTAR("LIS_ProcurarValor - Entrou, declarou variaveis e assertou pLista != NULL") ;
    #endif

    if ( pLista->pElemCorr == NULL )
    {
       return LIS_CondRetListaVazia ;
    } //fim if

    for ( pElem  = pLista->pElemCorr ;
          pElem != NULL ;
          pElem  = pElem->pProx )
    {
       if ( pElem->pValor == pValor )
       {
          pLista->pElemCorr = pElem ;
          return LIS_CondRetOK ;
       } //fim if
    } //fim if

    return LIS_CondRetNaoAchou ;

} /***** Fim função: LIS &Procurar elemento contendo valor **************/


/***********  CÓDIGO DAS FUNÇÕES ENCAPSULADAS NO MÓDULO  *******************/

/***************************************************************************
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
***************************************************************************/
void LiberarElemento( LIS_tppLista pLista, tpElemLista  * pElem   ) {

  #ifdef _DEBUG
     assert( pLista  != NULL ) ;
  #endif

  if ( ( pLista->ExcluirValor != NULL )
      && ( pElem->pValor != NULL        ))
  {
     pLista->ExcluirValor( pElem->pValor ) ;
  } /* if */

  free( pElem ) ;

  pLista->numElem-- ;

} /*********** Fim função: LIS -Liberar elemento da lista *****************/

/***************************************************************************
*  $FC Função: LIS  -Criar o elemento
***************************************************************************/
tpElemLista * CriarElemento( LIS_tppLista pLista, void * pValor  ) {

	tpElemLista * pElem ;

  #ifdef _DEBUG
     assert( pLista  != NULL ) ;
  #endif

  pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
  if ( pElem == NULL )
  {
     return NULL ;
  } /* if */

  pElem->pValor = pValor ;
  pElem->pAnt   = NULL  ;
  pElem->pProx  = NULL  ;

  pLista->numElem ++ ;

  #ifdef _DEBUG
 	  CED_DefinirTipoEspaco( pElem, LIS_TipoEspacoElemLista ) ;
  #endif

  return pElem ;

} /*************** Fim função: LIS -Criar o elemento **********************/

/***************************************************************************
*  $FC Função: LIS  -Limpar a cabeça da lista
***************************************************************************/
void LimparCabeca( LIS_tppLista pLista ) {

  #ifdef _DEBUG
    assert( pLista  != NULL ) ;
  #endif

	pLista->pOrigemLista = NULL ;
  pLista->pFimLista = NULL ;
  pLista->pElemCorr = NULL ;
  pLista->numElem   = 0 ;

} /********* Fim função: LIS -Limpar cabeca da lista **********************/

/***************************************************************************
*  $FC Função: LIS  -Verificar lista
***************************************************************************/
/*#ifdef _DEBUG
LIS_tpCondRet LIS_VerificarLista( void * pListaParm ) {

  LIS_tpLista * pLista = NULL ;

  if ( LIS_VerificarCabeca( pListaParm ) != LIS_CondRetOK ) {
     return LIS_CondRetErroEstrutura ;
  }

  CED_MarcarEspacoAtivo( pListaParm ) ;

  pLista = ( LIS_tpLista * ) ( pListaParm ) ;

  return VerificarElem( pLista->pElemCorr ) ;

} /**************** Fim função: LIS -Verificar lista ***********************/
//#endif

/***************************************************************************
*  $FC Função: LIS  -Verificar cabeca
***************************************************************************/
/*#ifdef _DEBUG
LIS_tpCondRet LIS_VerificarCabeca( void * pCabecaParm ) {

  tpLista * pLista = NULL ;

  	// Verifica o tipo do espaço
	if ( pCabecaParm == NULL ) {
		TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
		return LIS_CondRetErroEstrutura ;
	}

	if ( ! CED_VerificarEspaco( pCabecaParm , NULL )) {
		TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
		return LIS_CondRetErroEstrutura ;
	}

	if (TST_CompararInt(ARV_TipoEspacoCabeca, CED_ObterTipoEspaco(pCabecaParm),
		"Tipo do espaço de dados não é cabeça de árvore.") != TST_CondRetOK) {
		return LIS_CondRetErroEstrutura ;
	}

	pArvore = ( tpArvore * )( pCabecaParm ) ;

  	// Verifica raiz da árvore
	if ( pArvore->pNoRaiz != NULL ) {
		if (TST_CompararPonteiro(pCabecaParm, pArvore->pNoRaiz->pCabeca,
	     	"Nó raiz não aponta para cabeça.") != TST_CondRetOK) {
	   		return LIS_CondRetErroEstrutura ;
		}
	} 
	else {
		if ( TST_CompararPonteiro( NULL , pArvore->pNoCorr ,
		     "Árvore vazia tem nó corrente não NULL." ) != TST_CondRetOK ) {
	   		return LIS_CondRetErroEstrutura ;
		}
	}

  	// Verifica corrente
     if ( pArvore->pNoCorr != NULL ) {
        if ( TST_CompararPonteiro( pCabecaParm , pArvore->pNoCorr->pCabeca ,
             "Nó corrente não aponta para cabeça." ) != TST_CondRetOK ) {
           return LIS_CondRetErroEstrutura ;
        }
     } else {
        if ( TST_CompararPonteiro( NULL , pArvore->pNoRaiz ,
             "Árvore não vazia tem nó corrente NULL." ) != TST_CondRetOK ) {
           return LIS_CondRetErroEstrutura ;
        }
     }

  return LIS_CondRetOK ;

} /* Fim função: LIS  &Verificar um nó cabeça */
//#endif

/***************************************************************************
*  $FC Função: LIS  -Verificar elemento
***************************************************************************/
/*
#ifdef _DEBUG
LIS_tpCondRet LIS_VerificarElem( void * pElemParm ) {

  tpElemLista * pElem = NULL ;
  LIS_tpLista * pLista = NULL ;

  	//Verificar se é nó estrutural
	if ( pElemParm == NULL ) {
		TST_NotificarFalha( "Tentou verificar elemento inexistente." ) ;
		return LIS_CondRetErroEstrutura ;
	}

	if ( ! CED_VerificarEspaco( pElemParm , NULL )) {
		TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
		return LIS_CondRetErroEstrutura ;
	}

	if ( TST_CompararInt( LIS_TipoEspacoElemLista, CED_ObterTipoEspaco( pElemParm ) ,
	  	 				  "Tipo do espaço de dados não é elemento de lista." ) != TST_CondRetOK ) {
		return LIS_CondRetErroEstrutura ;
	}

	pElem  = ( tpElemLista * )( pElemParm ) ;
	//pLista = pNo->pCabeca ;

  	//Verificar cabeça
	if ( pArvore->pNoRaiz != NULL  ) {
		if ( TST_CompararPonteiro( pArvore , pArvore->pNoRaiz->pCabeca ,
		     "Nó não pertence à árvore." ) != TST_CondRetOK ) {
		   return LIS_CondRetErroEstrutura ;
		}
	} 
	else {
		return TST_NotificarFalha( "Nó pertence a árvore vazia." ) ;
	}

  	//Verificar pai
	if ( pNo->pNoPai != NULL ) {
		if ( ( pNo->pNoPai->pNoEsq != pNo ) && ( pNo->pNoPai->pNoDir != pNo )) {
	   		return LIS_CondRetErroEstrutura ;
		}
	}
	else {
		if ( TST_CompararPonteiro( pNo , pArvore->pNoRaiz ,
		     "Nó raiz não é apontado por cabeça da árvore." ) != TST_CondRetOK ) {
			return LIS_CondRetErroEstrutura ;
		}
	}

  	// Verificar filho à esquerda
	if ( pNo->pNoEsq != NULL ) {
		if ( TST_CompararPonteiro( pNo , pNo->pNoEsq->pNoPai ,
		     "Pai de filho à esquerda não é este nó." ) != TST_CondRetOK ) {
	   		return LIS_CondRetErroEstrutura ;
		}
		if ( TST_CompararPonteiro( pArvore , pNo->pNoEsq->pCabeca ,
		     "Filho à esquerda não pertence à mesma árvore." ) != TST_CondRetOK ) {
	   		return LIS_CondRetErroEstrutura ;
		}
	}

  	// Verificar filho à direita
    if ( pNo->pNoDir != NULL )
    {
        if ( TST_CompararPonteiro( pNo , pNo->pNoDir->pNoPai ,
             "Pai de filho à direita não é este nó." ) != TST_CondRetOK ) {
           return LIS_CondRetErroEstrutura ;
        }
        if ( TST_CompararPonteiro( pArvore , pNo->pNoDir->pCabeca ,
             "Filho à direita não pertence à mesma árvore." ) != TST_CondRetOK ) {
           return LIS_CondRetErroEstrutura ;
        }
    }


  return LIS_CondRetOK ;

} // Fim função: LIS  &Verificar um elemento de estrutura
#endif
*/

/************* FIM DO MÓDULO DE IMPLEMENTAÇÃO: LIS Lista ******************/

