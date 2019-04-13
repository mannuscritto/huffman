#ifndef __LISTA__
#define __LISTA__
#include "arvore.h"

struct no_lista
{
   ARVORE info;
   struct no_lista* prox;
};

typedef struct no_lista* LISTA;

int criar_lista (LISTA*);
int inserir_ordenado (LISTA*, ARVORE);
int remove_primeiro_lista (LISTA*, ARVORE*);
int tamanho_da_lista (LISTA);
#endif
