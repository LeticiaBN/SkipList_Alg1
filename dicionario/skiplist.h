#ifndef SKIPLIST_H
	#define SKIPLIST_H
	
	#include "item.h"

	#define TAM_MAX 20
	typedef struct skiplist_ SKIPLIST;
	typedef struct no_ NO;

	SKIPLIST *skiplist_criar(void);
	NO *skiplist_inserir(SKIPLIST *lista, ITEM *item, NO *atual);
	ITEM *skiplist_busca(SKIPLIST *lista, ITEM *item, NO *atual);
	NO *skiplist_busca_letra(SKIPLIST *lista, char c);
	int skiplist_imprimir_busca(SKIPLIST *lista, char *palavra);
	int skiplist_imprimir(SKIPLIST *lista, char c);
	int skiplist_alterar_definicao(SKIPLIST *lista, char *palavra, char *definicao);
	NO *skiplist_upleft(SKIPLIST *lista);
	int skiplist_remover(SKIPLIST* skiplist, ITEM* item, NO* atual);
	void skiplist_apagar(SKIPLIST **lista);

	//colocar if lista != NULL nas funcoes

#endif
