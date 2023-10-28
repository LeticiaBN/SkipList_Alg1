#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "skiplist.h"
#include "item.h"

/*
A estrutura da skiplist é composta de um nó upleft, que é o nó que se encontra no level mais alto e mais à esquerda da lista,
e de um int maxlevel, indicando o level máximo da lista
*/
struct skiplist_{ 
    NO *upleft;
    int maxlevel;
};

/*
A estrutura dos nós possui:
item, que contem palavra[51] e descricao[141]
o level, que indica o level do nó atual
proximo e baixo, que aponta para os nós proximo e abaixo do atual
*/
struct no_{
    ITEM *item;
    int level;
    NO *proximo;
    NO *baixo;
};

/*
Função para gerar um número aleatório entre 0 e 1
*/
int aleatorio(void) {
    return (rand()%2);
}

/*
Função para criar e alocar um nó, com seu item, level e nós próximo e baixo
*/
NO *no_criar(ITEM *item, int level, NO *proximo, NO *baixo) {
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


//Função para criar e alocar a skiplist, o upleft e todas os leveis dele
SKIPLIST *skiplist_criar(void) {
    //Declarando e alocando a skiplist com malloc
    SKIPLIST *lista;
    if ((lista = (SKIPLIST *) malloc(sizeof(SKIPLIST))) == NULL) {
        printf("Erro na alocacao\n");
        exit(1);
    }
    
    //declarar e alocar o nó upleft (que é o nó cabeça da skiplist)
    //o tamanho dele será o nivel maximo da skiplist
    NO *upleft = no_criar(NULL, TAM_MAX-1, NULL, NULL);
    if (upleft == NULL) {
        printf("Erro na alocacao\n");
        exit(1);
    }
    int level = TAM_MAX-1;
    
    //Como a lista esta vazia quando é criada, o proximo do upleft será NULL, pois ele não tem um próximo
    //O level do upleft será o level mais alto da lista
    upleft->proximo = NULL; 
    upleft->level = level;
    
    //nó auxiliar para ajudar na criação e alocação dos nós abaixo do upleft
    NO *aux = upleft;
    lista->upleft = upleft;

    //Função para criar, alocar e colocar na skiplist os nós abaixo do upleft (que serão iguais o upleft, servindo apenas como um nó cabeça e não tendo um ITEM)
    for(int i = 0; i < TAM_MAX-1; i++) {
        level--;

        NO *novo_upleft = (NO *) malloc(sizeof(NO));
        novo_upleft->proximo = NULL;
        novo_upleft->level = level;

        aux->baixo = novo_upleft;
        aux = novo_upleft;
    }
    
    //Tamanho máximo da lista
    lista->maxlevel = TAM_MAX;

    return lista;
}

//Função para inserir um item na skiplist
NO *skiplist_inserir(SKIPLIST *lista, ITEM *item, NO *atual) {
    if(lista != NULL) {
        NO *ultimo = NULL;
        //loop para encontrar a posição em que o item vai ser inserido
        while(1) {
            //se não existe um proximo nó nesse nível, sai do loop
            if(atual->proximo == NULL) {
                break;
            }

            //se existe um próximo nó no nivel, mas a palavra a ser inserida é menor que a palavra sendo checada, sai do loop
            if((atual->proximo != NULL) && (strcmp(item_get_palavra(item), item_get_palavra(atual->proximo->item)) < 0)) {
                break;
            }

            //caso o nó atual não se encaixe em nenhuma das situações acima, passa para o próximo nó
            atual = atual->proximo;
        }

        //se existe um nível abaixo, por recursividade, passa a inserir com o nó atual um nivel abaixo
        //quando a função localizar o local correto de se inserir, o atribui à variável ultimo
        if (atual->baixo != NULL) {
            ultimo = skiplist_inserir(lista, item, atual->baixo);
        }

        //se o ultimo existir ou o nivel atual for o menor possivel, ele irá inserir o item, ajustando os ponteiros dos nós ao redor da inserção
        if(ultimo != NULL || atual->level == 0) {
            //criação do nó
            NO *novo;
            if((novo = (NO *)malloc(sizeof(NO))) == NULL) {
                printf("Erro na alocacao\n");
                exit(1);
            }

            //inserção do item na posição e ajuste dos nós ao redor
            novo->item = item;
            novo->baixo = ultimo;
            novo->level = atual->level;
            novo->proximo = atual->proximo;
            atual->proximo = novo;

            //se o aleatorio for igual 1 e o level do nó for menor q o level máximo da skiplist, ele retorna o nó desse item
            //se o aleatório for igual a 0, ele adiciona mais um level do item
            if(aleatorio() && (atual->level < (TAM_MAX-1))) {
                //retorna o nó desse item, já inserido
                return novo;
            } 
        }
    }
    //se a lista não existir, retorna NULL
    return NULL;
}

//função para realizar a busca de uma palavra e a impressão de sua definição
ITEM *skiplist_busca(SKIPLIST *lista, ITEM *item, NO *atual) {
    if(lista != NULL) {
        //se a palavra condiz com a palavra buscada, retorna o item que contém essa palavra
        if((atual->proximo != NULL) && (atual->proximo->item != NULL) && (strcmp(item_get_palavra(item), item_get_palavra(atual->proximo->item)) == 0)){
            return atual->proximo->item;
        }

        //se a palavra não é encontrada diretamente, entra no loop
        while(1){
            //se não existe uma proxima posição nesse nivel da skiplist, sai do loop
            if(atual->proximo == NULL){
                break;
            }
            //se ele encontra a palavra, retorna o item que contém essa palavra
            if((atual->proximo != NULL) && (atual->proximo->item != NULL) && (strcmp(item_get_palavra(item), item_get_palavra(atual->proximo->item)) == 0)){
                return atual->proximo->item;
            }
            //se a palavra é menor que a palavra do próximo checada na skiplist, sai do loop
            if((atual->proximo != NULL) && (atual->proximo->item != NULL) && (strcmp(item_get_palavra(item), item_get_palavra(atual->proximo->item)) < 0)){
                break;
            }

            //caso as condições não se encaixem em nenhuma das acima, avança para o próximo nó
            atual = atual->proximo;
        }

        //se o item não foi encontrado mas ainda existe um nivel abaixo, com recursividade, faz a busca novamente mas iniciando de um nivel abaixo do nó atual
        if(atual->baixo != NULL){
            return skiplist_busca(lista, item, atual->baixo);
        } else { //se não existir nível abaixo, retorna NULL
            return NULL;
        }
    }
    //se a lista não existir, retorna NULL
    return NULL;
}

//função para realizar a busca de uma palavra e retornar sua posição na skiplist
NO *skiplist_busca_letra(SKIPLIST *lista, char c) {
    if (lista != NULL && lista->upleft != NULL) {
        NO *encontrado = lista->upleft;

        //se o encontrado não for NULL, entra no loop para encontrar a primeira palavra iniciada pela letra c
        while (encontrado != NULL) {

            //se existir um encontrado proximo, entra no if para fazer a busca
            if (encontrado->proximo != NULL) {
                
                //criar um char proximo que recebe a primeira letra da palavra do próximo nó
                char proximo_c = item_get_palavra(encontrado->proximo->item)[0];

                //se esse char proximo for menor que a letra buscada, passa para o próximo nó
                if (proximo_c < c) {
                    encontrado = encontrado->proximo;
                
                } else if (proximo_c == c) { //se esse char proximo for igual à letra buscada, entra na condição
                
                    //se existir um nivel abaixo, o nó desce de nível
                    if (encontrado->baixo != NULL) {
                        encontrado = encontrado->baixo;
                    
                    } else { // se não existir, o nó procurado foi encontrado
                        return encontrado->proximo;
                    }

                } else { //se esse char proximo for maior que a letra buscada, o nó desce de nível
                    encontrado = encontrado->baixo;
                }
            } else { //se não existir um encontrado proximo, o nó desce um nível
                encontrado = encontrado->baixo;
            }
        }
    }
    return NULL;
}

//função para imprimir a palavra e a definição de uma palavra buscada
int skiplist_imprimir_busca(SKIPLIST *lista, char *palavra) {
    //se a skiplist existir, entra na função
    if(lista != NULL) {
        ITEM *encontrado;
        NO *sentinela;
        sentinela = lista->upleft;

        //cria o item buscar para entrar como parametro da busca corretamente
        ITEM *buscar;
        buscar = item_criar(palavra, "");
        encontrado = skiplist_busca(lista, buscar, sentinela);
        //apaga o item pois ele não será mais utilizado
        item_apagar(&buscar);

        //se o item não foi encontrado, imprime OPERACAO INVALIDA
        if(encontrado == NULL || strcmp(item_get_palavra(encontrado), palavra) != 0) {
            return 0;
        }

        //se o item foi encontrado, imprime a palavra e a definição
        item_imprimir(encontrado);
        return 1;

    //se a skiplist não existe, imprime OPERACAO INVALIDA
    } else { 
        return 0;
    }
}

//função para imprimir as palavras iniciadas por uma letra
int skiplist_imprimir(SKIPLIST *lista, char c){  
    //se a lista existir
    if(lista != NULL) {
        NO* primeiro;

        //se nao existir palavras iniciadas pela letra
        if((primeiro = skiplist_busca_letra(lista, c)) == NULL){
            return 0;
        }
        //se existir, imprime todas as palavras iniciadas pela letra
        while (primeiro != NULL && item_get_palavra(primeiro->item)[0] == c) {
            item_imprimir(primeiro->item);
            primeiro = primeiro->proximo;
        }

        return 1;
    }
}

//função para alterar a definição de uma palavra da skiplist
int skiplist_alterar_definicao(SKIPLIST *lista, char *palavra, char *definicao) {
    //se a skiplist existe, entra na função
    if(lista != NULL) {
        ITEM *encontrado;
        NO *sentinela = lista->upleft;
        
        //cria um item somente para buscar a palavra na função busca
        ITEM *buscar;
        buscar = item_criar(palavra, "");
        
        //busca a palavra procurada
        encontrado = skiplist_busca(lista, buscar, sentinela);
        //apaga o item buscar pois não será mais utilizado
        item_apagar(&buscar);

        //se a palavra não foi encontrada, imprime OPERACAO INVALIDA
        if(encontrado == NULL || strcmp(item_get_palavra(encontrado), palavra) != 0) {
            return 0;
        }
        //se encontrar, altera a definição antiga pela nova
        item_set_definicao((encontrado), definicao);
        return 1;

    } else { //se a skiplist não existe, imprime OPERACAO INVALIDA
        return 0;
    }
}

//função para retornar o upleft da skiplist
NO *skiplist_upleft(SKIPLIST *lista) {
    //se a skiplist existir, retorna o seu upleft
    if(lista != NULL) {
        return (lista->upleft);
    }
    //se a skiplist não existir, retorna NULL
    return NULL;
}

//função para remover uma palavra do dicionario
int skiplist_remover(SKIPLIST* skiplist, ITEM* item, NO* atual) {
    //criar uma flag para confirmar se a remoção ocorreu corretamente ou não
    int flag = 0;
    while(1) {
        //se o upleft->proximo é NULL, não existem elementos nesse nivel da skiplist, então sai do loop
        if (atual->proximo == NULL) {
            break;
        }

        //se o item é igual, entra num loop
        if (atual->proximo->item != NULL && strcmp(item_get_palavra(item), item_get_palavra(atual->proximo->item)) == 0) {
            while(1) {
                //procura a palavra no nivel atual
                while (strcmp(item_get_palavra(item), item_get_palavra(atual->proximo->item)) > 0) {
                    atual = atual->proximo;
                }

                //remove o nó
                NO *tmp = atual->proximo; //nó a ser removido
                ITEM *item_a_remover = tmp->item; //item a ser removido
                atual->proximo = tmp->proximo;
                tmp->proximo = NULL;

                //desaloca o nó
                free(tmp);

                //só apaga o item se ele estiver no último nivel
                //atualiza a flag para mostrar que a remoção funcionou corretamente
                if (atual->level == 0) {
                    item_apagar(&item_a_remover);
                    flag++;
                    return flag;
                }
                //se não estiver no nivel mais baixo, desce mais uma vez
                atual = atual->baixo;     
            }
            return flag;
        }
        
        //se a palavra não for a palavra procurada, sai do loop
        if (atual->proximo->item != NULL && strcmp(item_get_palavra(item), item_get_palavra(atual->proximo->item)) < 0) {
            break;
        }
        //avança para o próximo nó
        atual = atual->proximo;
    }

    //se existir um nó abaixo do atual, com recursividade, retorna a função com a posição abaixo do nó correto
    if (atual->baixo != NULL) {
        skiplist_remover(skiplist, item, atual->baixo);
    }
}

//função para desalocar os nós e a skiplist
void skiplist_apagar(SKIPLIST **lista) {
    //se a skiplist existir, entra na função
    if (lista != NULL) {
        NO *sentinela = (*lista)->upleft;

        //enquanto existir nós alocados, entra no loop
        while (sentinela != NULL) {
            NO *atual = sentinela;
            NO *proximo = sentinela->proximo;

            //se existir um próximo, começa a apagar o nó
            while (proximo != NULL) {
                NO *tmp = proximo;
                proximo = proximo->proximo;

                //só apaga o item caso o nó esteja no nivel mais baixo
                if (tmp->level == 0 && tmp->item != NULL) {
                    item_apagar(&(tmp->item));
                }
                //desaloca o nó
                free(tmp);
            }
            
            //se não existir, desce um nivel e desaloca o nó atual
            sentinela = sentinela->baixo;
            //desaloca o nó
            free(atual);
        }
        
        //por fim, desaloca a skiplist
        free(*lista);
        *lista = NULL;
    }
}