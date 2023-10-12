#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "skiplist.h"
#include "item.h"

typedef struct no_ NO;

//para fazer a estrutura de skiplist, usaremos um nó proximo para apontar para o proximo nó que esta no mesmo level do atual e um nó abaixo para descer o level
struct no_{
    ITEM *item;
    int level;
    NO *proximo;
    NO *baixo;
};

//a estrutura da skiplist será composta de um nó upleft, que é o nó do ultimo level mais a esquerda da lista
//também terá um int maxlevel, que é o level maximo da lista e um int level, que irá mostrar o atual level da lista
struct skiplist_{ 
    NO *upleft;
    int maxlevel;
    int level;
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

//funcao para realizar a busca de uma palavra e a impressao de sua definicao
void skiplist_busca(SKIPLIST *lista, char *palavra) {
    NO *sentinela = lista->upleft;
    //sentinela eh o no auxiliar que ira ajudar na busca

    //loop para buscar a palavra nos leveis acima do 0
    //busca vertical
    while(sentinela->level != 0) {
        //busca horizontal (verifica se a palavra a ser inserida é menor que a proxima da lista)
        while(strcmp(item_get_palavra(sentinela->proximo->item), palavra) < 0) {
            sentinela = sentinela->proximo;
        } //quando ele encontra um valor maior que a palavra a ser inserida, ele desce para o proximo level
        sentinela = sentinela->baixo;
    }

    //busca no level 0
    while(strcmp(item_get_palavra(sentinela->proximo->item), palavra) < 0) {
        sentinela = sentinela->proximo;
    }

    //se a palavra a ser buscada nao for igual a palavra atual, ele ira imprimir "operacao invalida", pois a palavra nao existe no dicionario
    if(strcmp(item_get_palavra(sentinela->item), palavra) != 0) {
        printf("OPERACAO INVALIDA\n");
    } else {
        //se existir, ele ira imprimir a palavra e sua definicao
        item_imprimir(sentinela->item);
    }
} 

void skiplist_imprimir(SKIPLIST *lista, char letra) {
   
} 

bool skiplist_vazia(SKIPLIST *lista) {
    if(lista != NULL && (lista->upleft->proximo) == NULL) {
        return true;
    }
    return false;
}

