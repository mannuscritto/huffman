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
	ARVORE temp = *t;
	if (temp->esq != NULL) {
		return 0;	
	}
	temp->esq = filho;
	return 1;
}

int inserir_direita  (ARVORE *t, ARVORE filho) {
	ARVORE temp = *t;
	if (temp->dir != NULL) {
		return 0;	
	}	
	temp->dir = filho;
	return 1;
}

ARVORE aloca_noh_arvore(char *simb, unsigned freq) {
	ARVORE t;
	t = (ARVORE) malloc(sizeof (struct no_arvore));
	ARVORE temp = t;
	if (temp == NULL) {
		printf("Sem memoria para alocar novo no de arvore\n");
		exit(1);
	}
	strcpy(temp->simbolos, simb);
	temp->frequencia = freq;
	temp->esq = NULL;
	temp->dir = NULL;
	return temp;
}
