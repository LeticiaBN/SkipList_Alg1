#ifndef ITEM_H
	#define ITEM_H

	typedef struct item_ ITEM;

	ITEM *item_criar (char *palavra, char *definicao);
	void item_apagar(ITEM **item);
	void item_imprimir(ITEM *item);
	char *item_get_definicao(ITEM *item);
	char *item_get_palavra(ITEM *item);
	void item_set_definicao(ITEM *item, char *definicao);

#endif
