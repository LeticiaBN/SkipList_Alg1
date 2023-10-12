#ifndef ITEM_H
	#define ITEM_H
	
	#include <stdbool.h>

	typedef struct item_ ITEM;

	ITEM *item_criar (char palavra[40], char definicao[140]);
	bool item_apagar(ITEM **item);
	void item_imprimir(ITEM *item);
	char *item_get_definicao(ITEM *item);
	char *item_get_palavra(ITEM *item);
	bool item_set_definicao(ITEM *item, char definicao[140]);

#endif
