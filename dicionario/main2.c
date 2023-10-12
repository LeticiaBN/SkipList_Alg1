#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "item.h"

int main () {
    ITEM *teste;
    char test[40];
    char testt[140];
    
    scanf("%s", test);
    scanf(" %139[^\n]", testt);

    teste = item_criar(test, testt);

    item_imprimir(teste);

    return 0;
}