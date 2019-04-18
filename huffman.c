#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "huffman.h"

int constroi_lista (unsigned *n, LISTA *l) {
	
}

int constroi_arvore (LISTA l, ARVORE *t) {
    ARVORE s1, s2;
    ARVORE temp = *t;
	while (tamanho_da_lista(l) > 1) {
        if (!remove_primeiro_lista(&l, &s1)) return 0;
        if (!remove_primeiro_lista(&l, &s2)) return 0;
        temp->esq = s1;
        temp->dir = s2;
        temp->frequencia = s1->frequencia + s2->frequencia;
        if (!inserir_ordenado(&l, temp)) return 0;
    }
    //if (!remove_primeiro_lista(l, *t)) return 0;
    
}

int codifica (ARVORE t, char *a, char *b) {
    ARVORE temp = t;
    int i;
	for (i = 0; i < 30; i++) {
		while (t->esq != NULL) {
			if (strcmp(&a[i], t->simbolos) != 0) {
				if (strcmp(&a[i], t->esq->simbolos) != 0) {
					temp = temp->esq;
					b[strlen(b)] = '0';
				} else {
					temp = temp->dir;
					b[strlen(b)] = '1';
				}
			}	
		}
	}
}

int decodifica (ARVORE t, char *a, char *b) {
	
}

int imprime_codigos (ARVORE t) {
	
}
