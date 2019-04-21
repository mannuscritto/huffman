#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "huffman.h"

int constroi_lista (unsigned *n, LISTA *l) {
	int i;
	for (i = 0; i < 256; i++) {
		if (n[i] > 0) {
			ARVORE temp_arvore;
			char c[2];
			c[0] = i;
			c[1] = '\0';
			temp_arvore = aloca_noh_arvore(c, n[i]);
			temp_arvore->esq = NULL;
			temp_arvore->dir = NULL;
			if (!inserir_ordenado(l, temp_arvore)) {
				printf("Falha ao inserir ordenado");
				return 0;
			}
		}
	}
	return 1;
}

int constroi_arvore (LISTA l, ARVORE *t) {
    ARVORE s1, s2, novo;
	while (tamanho_da_lista(l) > 1) {
		novo = (ARVORE)malloc(sizeof(struct no_arvore));
        if (!remove_primeiro_lista(&l, &s1)) return 0;
        if (!remove_primeiro_lista(&l, &s2)) return 0;
        novo->esq = s2;
        novo->dir = s1;
        strcpy(novo->simbolos, "#");
        novo->frequencia = s1->frequencia + s2->frequencia;
        if (!inserir_ordenado(&l, novo)) return 0;
    }
    if (!remove_primeiro_lista(&l, t)) return 0;
    ARVORE temp = *t;
    return 1;
}

int codifica (ARVORE t, char *a, char *b, char *str) {
	if (t == NULL) return 0;
	if (!t->esq && !t->dir)
		strcat(b, str);
	if (t->esq)
		if (!codifica(t->esq, a, b, strcat(str, "0"))) return 0;
	if (t->dir)
		if (!codifica(t->dir, a, b, strcat(str, "1"))) return 0;
	return 1;
}

int decodifica (ARVORE t, char *a, char *b) {
	
}

int imprime_codigos (ARVORE t) {
	
}
