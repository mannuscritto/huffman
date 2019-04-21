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
        char str_temp[512];
        strcpy(str_temp, s1->simbolos);
		strcat(str_temp, s2->simbolos);
        strcpy(novo->simbolos, str_temp);
        novo->frequencia = s1->frequencia + s2->frequencia;
        if (!inserir_ordenado(&l, novo)) return 0;
    }
    if (!remove_primeiro_lista(&l, t)) return 0;
    ARVORE temp = *t;
    return 1;
}

int codifica (ARVORE t, char *a, char b[][16], char *str) {
	int i;
	if (t == NULL) return 0;
	if (!t->esq && !t->dir) {
		for (i = 0; i < 30; i++) {
			if (t->simbolos[0] == a[i]) {
				strcat(b[i], str);
			}
		}
		return 1;
	}
	int length = strlen(str);
    char leftcode[10],rightcode[10];
    strcpy(leftcode,str);
    strcpy(rightcode,str);
    leftcode[length] = '0';
    leftcode[length+1] = '\0';
    rightcode[length] = '1';
    rightcode[length+1] = '\0';
	if (!codifica(t->esq, a, b, leftcode)) return 0;
	if (!codifica(t->dir, a, b, rightcode)) return 0;
	return 1;
}

int decodifica (ARVORE t, char *a, char *b) {
	
}

int imprime_codigos (ARVORE t) {
	
}
