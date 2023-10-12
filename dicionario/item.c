#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"

struct item_{ 
   char palavra[40];
   char definicao[140];
};

ITEM *item_criar (char palavra[40], char definicao[140]){
   ITEM *item;
   
   item = (ITEM *) malloc(sizeof(ITEM));
   
   if (item != NULL){
      strcpy(item->palavra, palavra);
      strcpy(item->definicao, definicao);
      return(item);
   }
   return(NULL);
}

bool item_apagar(ITEM **item){
   if (*item != NULL){
      free (*item);
      *item = NULL;
      return(true);
   }
   return(false);
}

char *item_get_definicao(ITEM *item){
   if (item != NULL)
     return(item->definicao);
   exit(1);
}

char *item_get_palavra(ITEM *item){
   if (item != NULL)
     return(item->palavra);
   exit(1);
}


bool item_set_definicao(ITEM *item, char definicao[140]){
   if (item != NULL){
      strcpy(item->definicao, definicao);
      return (true);
   }
   return (false);
}

void item_imprimir(ITEM *item){
   if (item != NULL)
      printf("%s %s\n", item->palavra, item->definicao);
}
