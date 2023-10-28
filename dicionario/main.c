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

void insercao(SKIPLIST *lista);
void alteracao(SKIPLIST *lista);
void remocao(SKIPLIST *lista);
void busca(SKIPLIST *lista);
void impressao(SKIPLIST *lista);

int main () {
    srand(time(NULL));

    SKIPLIST *lista;

    lista = skiplist_criar();
    
    char operacao[11];
    
    while (scanf(" %s", operacao) != EOF) {
        if(strcmp(operacao, "insercao") == 0) {
            insercao(lista);
        }
        else if (strcmp(operacao, "alteracao") == 0) {
            alteracao(lista);
        }
        else if (strcmp(operacao, "remocao") == 0) {
            remocao(lista);
        }
        else if (strcmp(operacao, "busca") == 0) {
            busca(lista);
        }
        else if (strcmp(operacao, "impressao") == 0) {
            impressao(lista);
        }
    }

    skiplist_apagar(&lista);

    return 0;
}

void insercao(SKIPLIST *lista) {
    char palavra[51];
    char definicao[141];

    scanf(" %s", palavra);
    getchar();
    fgets(definicao, 141, stdin);

    ITEM *inserir;
    inserir = item_criar(palavra, definicao);

    ITEM *encontrado = skiplist_busca(lista, inserir, skiplist_upleft(lista));
    
    if(encontrado != NULL && (strcmp(item_get_palavra(encontrado), item_get_palavra(inserir))) == 0) {
        printf("OPERACAO INVALIDA\n");
        item_apagar(&inserir);
    } else {
        skiplist_inserir(lista, inserir, skiplist_upleft(lista));
    }
}

void alteracao(SKIPLIST *lista) {
    char palavra[51];
    char definicao[141];

    scanf(" %s", palavra);
    getchar();
    fgets(definicao, 141, stdin);
    
    if (skiplist_alterar_definicao(lista, palavra, definicao) == 0) {
        printf("OPERACAO INVALIDA\n");
    }
}

void remocao(SKIPLIST *lista) {
    char palavra[51];

    scanf(" %s", palavra);

    ITEM *removido;
    removido = item_criar(palavra, "");
    if(skiplist_remover(lista, removido, skiplist_upleft(lista)) == 0) {
        printf("OPERACAO INVALIDA\n");
    }
    item_apagar(&removido);
}

void busca(SKIPLIST *lista) {
    char palavra[51];
    scanf(" %s", palavra);
    if(skiplist_imprimir_busca(lista, palavra) == 0) {
        printf("OPERACAO INVALIDA\n");
    }
}

void impressao(SKIPLIST *lista) {
    char ch;
    scanf(" %c", &ch);
    if(skiplist_imprimir(lista, ch) == 0) {
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", ch);
    }
}
