#pragma once
#if ! defined( MESA_ )
#define MESA_
/***************************************************************************
*  $MCD Módulo de definição: MES  MESA
*
*  Arquivo gerado:              MESA.h
*  Letras identificadoras:      MES
*
*  Projeto: INF 1301 Jogo de Truco
*  Gestor:
*  Autores: gsc, jvr, tgf
*
*  $HA Histórico de evolução:
*     Versão      Autor         Data            Observações
*     1            gsc        19/abr/2018     início desenvolvimento
*
*  $ED Descrição do módulo
*     
***************************************************************************/

#include "lista.h"
#include "baralho.h"

#if defined( MESA_OWN )
   #define MESA_EXT
#else
   #define MESA_EXT extern
#endif

/***************************************************************************
*  $TC Tipo de dados: MES Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de MES.
***************************************************************************/
typedef enum {
   MES_CondRetOK,
   MES_CondRetNaoDistribuiuMaos,
   MES_CondRetNaoEsvaziouMesa,
   MES_CondRetNaoEsvaziouLixo,		
   MES_CondRetNaoTransferiuTodasCartasProLixo,
   MES_CondRetNaoIdentificouQuemJogouQual
} MES_tpCondRet;

/***************************************************************************
*  $FC Função: MES  &Criar Lista de Listas
*
*  $ED Descrição da função
*     Cria uma lista que terá elementos tipo ponteiro pra lista.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca da lista
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta lista. 
***************************************************************************/
LIS_tppLista MES_CriarListaDeListas() ;

/***************************************************************************
*  $FC Função: MES  &Criar Mesa
*
*  $ED Descrição da função
*     Cria uma lista mesa vazia.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca da mesa
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta mesa. 
***************************************************************************/
LIS_tppLista MES_CriarMesa() ;

/***************************************************************************
*  $FC Função: MES  &Criar Mao
*
*  $ED Descrição da função
*     Cria uma lista mão vazia.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca da mao
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta mao. 
***************************************************************************/
LIS_tppLista MES_CriarMao() ;

/***************************************************************************
*  $FC Função: MES  &Criar lixo
*
*  $ED Descrição da função
*     Cria a lista lixo vazia.
*
*  $FV Valor retornado
*     Se executar corretamente retorna o ponteiro para a cabeca do lixo
*     (ponteiro para o tipo lista). Este ponteiro será utilizado pelas
*     funções que manipulem esta mao. 
***************************************************************************/
LIS_tppLista MES_CriarLixo() ;

/***************************************************************************
*  $FC Função: MES  &Distribuir maos
*
*  $ED Descrição da função
*     Distribui as maos para os jogadores
*
*  $EP Parâmetros
*     Ponteiro pra cabeca da lista de listas e a qtdJogadores.
***************************************************************************/
MES_tpCondRet MES_DistribuirMaos(LIS_tppLista pCabecaSuperior, int qtdJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Distribuir maos para testar empates
*
*  $ED Descrição da função
*     Distribui as maos de forma que se possa empatar propositalmente.
*     Deve-se comentar com // a função BAR_EmbaralharVetorCartas se for usá-la.
*
*  $EP Parâmetros
*     Ponteiro pra cabeca da lista de listas e a qtdJogadores.
***************************************************************************/
//void MES_DistribuirMaosParaTestarEmpates(LIS_tppLista pCabecaSuperior, int qtdJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Esvaziar mesa
*
*  $ED Descrição da função
*     Tira as cartas da lista mesa e põe na lista lixo.
*
*  $EP Parâmetros
*     Ponteiros para cabeca da mesa, cabeca do lixo e tipo, que pode ser:
*	   TIRA_VIRA ou DEIXA_VIRA caso seja apenas o fim de uma aposta ou fim
*	   de uma rodada.
*
*  $FV Valor retornado
*     MES_CondRetOK se nada deu errado.
*     MES_CondRetNaoEsvaziouMesa se algo deu errado.
***************************************************************************/
MES_tpCondRet MES_EsvaziarMesa (LIS_tppLista pCabecaMesa, LIS_tppLista pCabecaLixo, int tipo) ;

/***************************************************************************
*  $FC Função: MES  &Esvaziar lixo
*
*  $ED Descrição da função
*     Tira as cartas da lista mesa e põe na lista lixo.
*
*  $EP Parâmetros
*     Ponteiro para cabeca do lixo.
*
*  $FV Valor retornado
*     MES_CondRetOK se nada deu errado.
*     MES_CondRetNaoEsvaziouLixo se algo deu errado.
***************************************************************************/
MES_tpCondRet MES_EsvaziarLixo (LIS_tppLista pCabecaLixo) ;

/***************************************************************************
*  $FC Função: MES  &Obter quantidade de cartas
*
*  $ED Descrição da função
*     Obtem a quantidade de cartas na mesa (ou de qualquer lista).
*
*  $EP Parâmetros
*     Ponteiros para cabeca da mesa, e tipos, que podem ser:
*	   COM_PRIMEIRA ou SEM_PRIMEIRA e COM_ULTIMA ou SEM_ULTIMA.
***************************************************************************/
int MES_ObterQtdCartas (LIS_tppLista pCabecaMesa, int tipoVira, int tipoUltimaApostada) ;

/***************************************************************************
*  $FC Função: MES  &Transferir todas cartas pro lixo
*
*  $EP Parâmetros
*     Recebe uma lista de listas de cartas e transfere todos elementos
*	   de todas listas pra penultima lista (lixo).
*
*  $FV Valor retornado
*     MES_CondRetOK se nada deu errado.
*     MES_CondRetNaoTransferiuTodasCartasProLixo se algo deu errado.
***************************************************************************/
MES_tpCondRet MES_TransferirTodasCartasProLixo(LIS_tppLista pCabecaSuperior) ;

/***************************************************************************
*  $FC Função: MES  &Determinar resultado
*
*  $ED Descrição da função
*     Determina o resultado de uma jogada de aposta, que pode ser venceu/perdeu/empatou.
*
*  $EP Parâmetros
*     Recebe uma lista de listas de cartas, quem esta fazendo a jogada,
*     quem fez a primeira jogada da bateria de apostas e a quantidade de jogadores.
*
*  $FV Valor retornado
*     0: se o jogador perdeu de todos adversarios fazendo sua jogada.
*     quemJoga: se o jogador venceu todos adversarios fazendo sua jogada.
*     primeiroComQuemEmpatou: se o jogador empatou com algum adversario.
***************************************************************************/
int MES_DeterminarResultado(LIS_tppLista pCabecaSuperior, int quemJoga, int quemJogouAPrimeira, int qtdJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Definir quem começa
*
*  $ED Descrição da função
*     Define quem começa a partida.
*
*  $EP Parâmetros
*     Recebe a quantidade de jogadores que vao jogar.
*
*  $FV Valor retornado
*     Um numero aleatorio entre 1 e a qtdJogadores.
***************************************************************************/
int MES_DefinirQuemComeca(int qtdJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Identificar quem jogou qual
*
*  $ED Descrição da função
*     Identificar qual jogador jogou qual carta que ta na mesa.
*
*  $EP Parâmetros
*     Recebe a quantidade de jogadores, quem jogou a primeira carta e
*     ponteiros para armazenar quem jogou qual.
*
*  $FV Valor retornado
*     MES_CondRetOK se nada deu errado.
*     MES_CondRetNaoIdentificouQuemJogouQual se algo deu errado.
***************************************************************************/
MES_tpCondRet MES_IdentificarQuemJogouQual(int qtdJogadores, 
                                           int quemJogouAPrimeira, int *quemJogouASegunda,
                                           int *quemJogouATerceira, int *quemJogouAQuarta, 
                                           int *quemJogouAQuinta, int *quemJogouASexta) ;

/***************************************************************************
*  $FC Função: MES  &Proximo jogador
*
*  $ED Descrição da função
*     Determinar o proximo jogador em sequência dentre todos que estao jogando.
*
*  $EP Parâmetros
*     Recebe.quemJoga e a qtdJogadores.
***************************************************************************/
int MES_ProximoJogador(int quemJoga, int qtdJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Proximo jogador da mesma equipe
*
*  $ED Descrição da função
*     Determinar o proximo jogador em sequência da mesma equipe.
*
*  $EP Parâmetros
*     Recebe quemJoga e a qtdJogadores.
***************************************************************************/
int MES_ProximoJogadorDaMesmaEquipe(int quemJoga, int qtdJogadores) ;

/***************************************************************************
*  $FC Função: MES  &Destruir listas
*
*  $ED Descrição da função
*     Destruir e desalocar o espaco ocupado por todas listas.
*
*  $EP Parâmetros
*     Recebe quemJoga e a qtdJogadores.
***************************************************************************/
void MES_DestruirListas (LIS_tppLista pCabecaSuperior, LIS_tppLista pCabecaBaralho,
                         LIS_tppLista pCabecaMao1, LIS_tppLista pCabecaMao2,
                         LIS_tppLista pCabecaMao3, LIS_tppLista pCabecaMao4,
                         LIS_tppLista pCabecaMao5, LIS_tppLista pCabecaMao6,
                         LIS_tppLista pCabecaLixo, LIS_tppLista pCabecaMesa) ;

#undef MESA_EXT

/**************** FIM DO MÓDULO DE DEFINIÇÃO: MES Mesa ********************/

#else
#endif
