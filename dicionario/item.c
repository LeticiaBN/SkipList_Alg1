#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "item.h"

//o dicionario contará com um item contendo a palavra e sua definicao
struct item_{ 
   char palavra[51];
   char definicao[141];
};

//função para criar um item com uma palavra e definicao definidas
ITEM *item_criar (char *palavra, char *definicao){
   //cria e aloca o item
   ITEM *item;
   item = (ITEM *) malloc(sizeof(ITEM));
   
   //se a alocação for bem sucedida, irá definir sua palavra e definição e retornar o item
   if (item != NULL) {
      strcpy(item->palavra, palavra);
      strcpy(item->definicao, definicao);
      return(item);
   }
   //retorna NULL caso a alocação tenha dado errado
   return NULL;
}

//função para desalocar o item
void item_apagar(ITEM **item){
   if (*item != NULL) {
      free (*item);
      *item = NULL;
   }
}

//função para retornar a definicao de um item
char *item_get_definicao(ITEM *item){
   if (item != NULL) {
      return(item->definicao);
   }
   return NULL;
}

//função para retornar a palavra de um item
char *item_get_palavra(ITEM *item){
   if (item != NULL) {
      return(item->palavra);
   }
   return NULL;
}

//função para alterar a definicao de um item
void item_set_definicao(ITEM *item, char *definicao){
   if (item != NULL) {
      strcpy(item->definicao, definicao);
   }
}

//função para imprimir um item
void item_imprimir(ITEM *item){
   if (item != NULL) {
      printf("%s %s", item->palavra, item->definicao);
   }
}
