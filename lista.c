#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"

int criar_lista (LISTA *l) {
	*l = NULL;
	if (*l == NULL)
		return 1;
	else
		return 0;
}

int inserir_ordenado (LISTA *l, ARVORE t) {
	LISTA novo;
	novo = (LISTA)malloc(sizeof(struct no_lista));
	novo->info = t;
	novo->prox = NULL;
	LISTA temp = *s;
	if (temp == NULL) {
		*l = novo;
	} else {
		LISTA p, q;
		p = *l;
		q = NULL;
		while ((p->info->frequencia > t->frequencia) && (p->prox != NULL)) {
			q = p;
			p = p->prox;
		}
		if (q == NULL) {
			return 0;
		}
		p->prox = novo;
		novo->prox = q;
	}
	return 1;
}

int remove_primeiro_lista (LISTA *l, ARVORE *t) {
	LISTA temp = *s;
	if (temp == NULL) {
		printf("A lista esta vazia\n");
		*t = NULL;
		return 0;
	} else {
		*s = temp->prox;
		*t = temp->item;
		free(temp);
		return 1;
	}
}

int tamanho_da_lista (LISTA l) {
	
}
