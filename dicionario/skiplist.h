#ifndef SKIPLIST_H
	#define SKIPLIST_H
	
	#include "item.h"

	typedef struct skiplist_ SKIPLIST;

	SKIPLIST *skiplist_criar(void);
	int lista_inserir(SKIPLIST *lista, ITEM *item);
	int skiplist_busca(SKIPLIST *lista, char *palavra);
	void skiplist_imprimir(SKIPLIST *lista, char letra);
	int skiplist_vazia(SKIPLIST *lista);
	//remocao
	//alterar

#endif
