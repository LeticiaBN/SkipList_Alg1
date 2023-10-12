#ifndef SKIPLIST_H
	#define SKIPLIST_H
	
	#include <stdbool.h>
	#include <stdlib.h>
	#include <stdio.h>

	typedef struct skiplist_ SKIPLIST;

	SKIPLIST *skiplist_criar(void);

	bool skiplist_vazia(SKIPLIST *lista);

#endif
