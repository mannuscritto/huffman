#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int criar_arvore (ARVORE *t) {
	*t = NULL;
	if (*t == NULL)
		return 1;
	else
		return 0;
}

int inserir_esquerda (ARVORE *t, ARVORE filho) {
	if (t->esq != NULL) {
		return 0;	
	}
	t->esq = filho;
	return 1;
}

int inserir_direita  (ARVORE *t, ARVORE filho) {
	if (t->dir != NULL) {
		return 0;	
	}	
	t->dir = filho;
	return 1;
}

ARVORE* aloca_noh_arvore(char *simb, unsigned freq) {
	AB t;
	t = (AB) malloc(sizeof (struct no_arvore));
	if (t == NULL) {
		printf("Sem memoria para alocar novo no de arvore\n");
		exit(1);
	}
	strcpy(t->simbolos, simb);
	t->frequencia = freq;
	t->esq = NULL;
	t->dir = NULL;
	return t;
}
