#include <stdlib.h>
#include <stdio.h>
#include "item.h"

typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *proximo;
    NO *baixo;
};
//malloc pra setar o vetor

struct skiplist_{ 
    NO *inicio;
    NO *fim;
    int tamanho;
};

SKIPLIST *skiplist_criar(void) {
    SKIPLIST *lista;
    lista = (SKIPLIST *) malloc(sizeof(SKIPLIST));

    return lista;
}