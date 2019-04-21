#ifndef __HUFFMAN__
#define __HUFFMAN__
#include "arvore.h"
#include "lista.h"

// TAB_FREQ tabela[256];
// ARVORE arvore_huffman;
// LISTA lista;
// tabela[0].simbolo = 'j';
// tabela[0].frequencia = 120;
// constroi_lista (tabela, &lista);
// constroi_arvore (lista, &arvore_huffman;

int constroi_lista (unsigned*, LISTA*);
int constroi_arvore (LISTA, ARVORE*);
int codifica (ARVORE, char*, char*, char *);
int decodifica (ARVORE, char*, char*);
int imprime_codigos (ARVORE);

#endif
