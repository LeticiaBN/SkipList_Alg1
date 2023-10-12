#include <stdlib.h>
#include <stdio.h>
#include "skiplist.h"
#include "item.h"

typedef struct no_ NO;

//para fazer a estrutura de skiplist, usaremos um no proximo para apontar para o proximo no que esta no mesmo nivel do atual e um no abaixo para descer o nivel
struct no_{
    ITEM *item;
    NO *proximo;
    NO *baixo;
    int nivel;
};

//explicar
struct skiplist_{ 
    NO *cabeca;
    int tamanho;
};

//funcao para criar a skiplist
SKIPLIST *skiplist_criar(void) {
    //declarar e alocar com malloc a skiplist
    SKIPLIST *lista;
    if ((lista = (SKIPLIST *) malloc(sizeof(SKIPLIST))) == NULL) {
        printf("Erro na alocacao\n");
        exit(1);
    }

    return lista;
}

bool skiplist_vazia(SKIPLIST *lista) {
    if(lista != NULL && (lista->cabeca->proximo) == NULL) {
        return true;
    }
    return false;
}