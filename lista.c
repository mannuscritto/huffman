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
	LISTA temp = *l;
	if (temp == NULL) {
		*l = novo;
	} else {
		LISTA p, q;
		p = *l;
		q = NULL;
		while ((p != NULL) && (t->frequencia >= p->info->frequencia)) {
			q = p;
			p = p->prox;
		}
		if (q == NULL) {
			return 0;
		}
		q->prox = novo;
		novo->prox = p;
	}
	return 1;
}

int remove_primeiro_lista (LISTA *l, ARVORE *t) {
	LISTA temp = *l;
	if (temp == NULL) {
		printf("A lista esta vazia\n");
		*t = NULL;
		return 0;
	} else {
		*l = temp->prox;
		*t = temp->info;
		free(temp);
		return 1;
	}
}

int tamanho_da_lista (LISTA l) {
    LISTA temp = l;
    int cont = 0;
	while (temp != NULL) {
        temp = temp->prox;
        cont++;    
    }
    return cont;
}

void mostrar_lista(LISTA l) {
	LISTA temp = l;
	if (temp == NULL) {
		printf("Nao eh possivel mostrar lista vazia!\n");
		return;
	}
	printf("Comeco de lista\n");
	for (temp = l; temp != NULL; temp = temp->prox) {
		printf("\nSimbolo: %s | Frequencia: %d\n", temp->info->simbolos, temp->info->frequencia);
	}
	printf("Fim de lista\n");
}
