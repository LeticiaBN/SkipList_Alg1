#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
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

int aleatorio(void) {
    srand(time(NULL));
    int a = rand() % 2 + 1;

    int nivel = 0;

    while (a != 2) {
        a = rand() % 2 + 1;
        
        nivel++;

        if(nivel == 20) {
            break;
        }
    }

    return nivel;
}

NO *no_criar(ITEM *item, int level, NO *proximo, NO *baixo){
    NO *no;
    if ((no = (NO *) malloc(sizeof(NO))) == NULL) {
        printf("Erro na alocacao\n");
        exit(1);
    }

    no->item = item;
    no->proximo = proximo;
    no->baixo = baixo;
    no->level = level;
    
    return no;
}

//funcao para criar a skiplist
SKIPLIST *skiplist_criar(void) {
    //declarar e alocar com malloc a skiplist
    SKIPLIST *lista;
    if ((lista = (SKIPLIST *) malloc(sizeof(SKIPLIST))) == NULL) {
        printf("Erro na alocacao\n");
        exit(1);
    }
    
    NO *upleft = no_criar(NULL, 0, NULL, NULL);
    if (upleft == NULL) {
        printf("Erro na alocacao\n");
        exit(1);
    }

    lista->upleft = upleft;
    lista->maxlevel = 20;
    lista->level = 0;

    return lista;
}

//funcao para realizar a busca de uma palavra e a impressao de sua definicao
int skiplist_busca(SKIPLIST *lista, char palavra[40]) {
    printf("TESTE A\n\n");
    if(lista != NULL && skiplist_vazia(lista) == 0) {
        printf("TESTE B\n\n");
        NO *sentinela = lista->upleft;
        //sentinela eh o no auxiliar que ira ajudar na busca

        //loop para buscar a palavra nos leveis acima do 0
        //busca vertical
        while(sentinela->level != 0) {
            
            //busca horizontal (verifica se a palavra a ser inserida é menor que a proxima da lista)
            while((sentinela->proximo != NULL) && strcmp(item_get_palavra(sentinela->proximo->item), palavra) < 0) {
    
                sentinela = sentinela->proximo;
            } //quando ele encontra um valor maior que a palavra a ser inserida, ele desce para o proximo level
            sentinela = sentinela->baixo;
        }
        printf("TESTE C\n\n");
        //busca no level 0
        while((sentinela->proximo != NULL) && strcmp(item_get_palavra(sentinela->proximo->item), palavra) < 0) {
            sentinela = sentinela->proximo;
        }   
        printf("TESTE D\n\n");
        //se a palavra a ser buscada nao for igual a palavra atual, ele ira retornar 1 (true), e se a palavra a ser buscada for igual a palavra atual, ele ira retornar 0 (false)
        if((sentinela->proximo != NULL) && strcmp(item_get_palavra(sentinela->item), palavra) != 0) {
            return 0;
        }
        printf("TESTE E\n\n");
        return 1;
    }
    return -1;
} 

int lista_inserir(SKIPLIST *lista, ITEM *item) {
    if(lista != NULL) {
        //se a lista não existir, a função ira retornar 0 (falso)
        //se a palavra ja existe no dicionario, nao ha necessidade de inserir ela novamente
        printf("TESTE 1\n\n");
        if(skiplist_busca(lista, item_get_palavra(item)) == 1) {
            return 0;
        }
        printf("TESTE 2\n\n");

        //o nó sentinela servira como auxilio para sabermos onde o novo nó deverá ser inserido em cada nivel
        NO *sentinela = lista->upleft;
        //updates é um vetor de nós, ele irá guardar o sentinela de cada nível para realizar a insercao posteriormente
        NO *updates[20];
        printf("TESTE 3\n\n");

        int no_level = aleatorio();
        printf("TESTE 4\n\n");
        //esse loop ira buscar e guardar o sentinela de cada nivel no vetor updates enquanto o nivel nao for 0
        while(sentinela->level != 0) {
            while((sentinela->proximo != NULL) && strcmp(item_get_palavra(sentinela->proximo->item), item_get_palavra(item)) < 0) {
                sentinela = sentinela->proximo;
            }
            updates[sentinela->level] = sentinela;
            sentinela = sentinela->baixo;
        }
        printf("TESTE 5\n\n");

        //esse loop ira buscar e guardar o sentinela do nivel 0
        while((sentinela->proximo != NULL) && (strcmp(item_get_palavra(sentinela->proximo->item), item_get_palavra(item)) < 0)) {
            sentinela = sentinela->proximo;
        }
        updates[sentinela->level] = sentinela;
        printf("TESTE 6\n\n");
        //
        int nivel_atual = 0;

        //esse loop ira inserir o novo nó de cada nível em seu lugar
        while(nivel_atual <= lista->level) {
            NO *novo = no_criar(item, nivel_atual, NULL, NULL);
            printf("TESTE 7\n\n");
            //se o nivel for 0, ele irá atualizar somente o no proximo, sendo que o no abaixo sera nulo
            if(nivel_atual == 0) {
                novo->proximo = (updates[nivel_atual])->proximo;
                novo->baixo = NULL;
            } else { //se o nivel for acima de 0, ele ira atualizar tanto os ponteiros proximo e baixo
                novo->proximo = (updates[nivel_atual])->proximo;
                novo->baixo = (updates[nivel_atual-1])->proximo;
            }
            printf("TESTE 8\n\n");
            (updates[nivel_atual])->proximo = novo;
            nivel_atual++;
        }
        printf("TESTE 9\n\n");
        //caso o level da lista va aumentar, sera necessario criar um novo nó upleft
        for(int i = (lista->level+1); i <= no_level; i++) {
            NO *novissimo = no_criar(item, i, NULL, (updates[i-1]->proximo));
            NO *novo_upleft = no_criar(NULL, i, novissimo, lista->upleft);

            lista->upleft = novo_upleft;
            updates[i] = novo_upleft;
        }
        printf("TESTE 10\n\n");
        lista->level = no_level;

        return 1;
    }
    return 0;
}

void skiplist_imprimir(SKIPLIST *lista, char letra) {
    if(lista != NULL && skiplist_vazia(lista) == 0) {
        printf("teste 1\n\n");
        NO *sentinela = lista->upleft;
        //sentinela eh o no auxiliar que ira ajudar na busca

        //loop para buscar a palavra nos leveis acima do 0
        //busca vertical
        while(sentinela->level != 0) {
            printf("teste 2\n\n");
            //busca horizontal (verifica se a palavra a ser inserida é menor que a proxima da lista)
            while((sentinela->proximo != NULL) && (item_get_palavra(sentinela->proximo->item))[0] < letra) {
                printf("teste 3\n\n");
                sentinela = sentinela->proximo;
            } //quando ele encontra um valor maior que a palavra a ser inserida, ele desce para o proximo level
            sentinela = sentinela->baixo;
        }

        printf("teste 4\n\n");

        //busca no level 0
        while((sentinela->proximo != NULL) && (item_get_palavra(sentinela->proximo->item))[0] < letra) {
            printf("teste 5\n\n");
            sentinela = sentinela->proximo;
        }

        if((sentinela->proximo != NULL) && (item_get_palavra(sentinela->proximo->item))[0] != letra) {
            printf("NAO HA PALAVRAS INICIADAS POR %c", letra);
        }
        printf("teste 6\n\n");
        while((sentinela->proximo != NULL) && (item_get_palavra(sentinela->proximo->item))[0] == letra) {
            printf("teste 7\n\n");
            item_imprimir(sentinela->proximo->item);
            sentinela = sentinela->proximo;
        }
    }
} 

int skiplist_vazia(SKIPLIST *lista) {
    if(lista != NULL && ((lista->upleft->proximo) == NULL)) {
        return 1;
    }
    return 0;
}