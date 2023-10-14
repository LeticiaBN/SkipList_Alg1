/*
Trabalho 1 - SkipList

Nomes - n°USP
Letícia Barbosa Neves - 14588659
Pedro Louro Fernandes - 13672446
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "item.h"
#include "skiplist.h"

int main () {
    srand(time(NULL));

    SKIPLIST *lista;

    lista = skiplist_criar();

    ITEM *a;
    ITEM *b;
    ITEM *c;
    ITEM *d;
    ITEM *e;

    a = item_criar("abaacx", "fruta doce");
    b = item_criar("aa", "vrum vrum");
    c = item_criar("aavalo", "animal pocotó");
    d = item_criar("aba", "animal pocotó");
    e = item_criar("aiamante", "faz armadura pika");

    lista_inserir(lista, a);
    skiplist_imprimir(lista, 'c');
    printf("A\n\n");
    lista_inserir(lista, b);
    skiplist_imprimir(lista, 'c');
    printf("B\n\n");
    lista_inserir(lista, c);
    skiplist_imprimir(lista, 'c');
    printf("C\n\n");
    lista_inserir(lista, d);
    skiplist_imprimir(lista, 'c');
    printf("D\n\n");
    lista_inserir(lista, e);
    skiplist_imprimir(lista, 'c');
    printf("E\n\n");
    skiplist_imprimir(lista, 'a');
    printf("F\n\n");
    return 0;
}

/*
implementar o print da busca
//se a palavra a ser buscada nao for igual a palavra atual, ele ira imprimir "operacao invalida", pois a palavra nao existe no dicionario
        if(strcmp(item_get_palavra(sentinela->item), palavra) != 0) {
            printf("OPERACAO INVALIDA\n");
        } else {
            //se existir, ele ira imprimir a palavra e sua definicao
            item_imprimir(sentinela->item);
        }
*/

/*
str1 = palavra
str2 = definicao

O dicionario deve ter as funçoes:
insercao (str1, str2) - insere nova palavra e definicao
alteracao (str1, str2) - altera a definicao de uma palavra
remocao (str1) - remove uma palavra
busca (str1) - imprime a definicao da palavra buscada
impressao (ch1) - imprime todas as palavras iniciadas pelo ch1 e suas definicoes (em ordem alfabetica)

remover, alterar ou buscar nao exista, devera ser impresso "OPERACAO INVALIDA"
ch1, deve imprimir "NAO HA PALAVRAS INICIADAS POR %c, ch1"

palavra -> 50 ch
definicao -> 140 ch

usar a estrutura de dados SKIP LIST
*/