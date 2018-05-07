#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "LISTA.h"
#include "BARALHO.h"
	
int main (void) {

	LIS_tppLista pCabecaBaralho = BAR_CriarBaralho () ;

	BAR_tppCarta pCarta = (BAR_tppCarta)LIS_ObterValor(pCabecaBaralho);

	BAR_tpNaipeCarta naipe = BAR_ObterNaipe (pCarta) ;
	BAR_tpValorCarta valor = BAR_ObterValor (pCarta) ;

	printf("\nNaipe: %d / Valor: %d\n", naipe, valor);

	return 0;
}
