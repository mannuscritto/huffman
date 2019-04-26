#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "huffman.h"

/* Funcao constroi_lista
 * @Parametro unsigned *n: vetor de inteiro sem sinal 
 * que armazena frequencia absoluta de cada caractere
 * pelo seu codigo ASCII
 * @Parametro LISTA *l: ponteiro que aponta para lista
 * que foi apenas inicializada no programa principal
 * @Retorno int: retorna 0 em caso de falha e 1 em
 * caso de sucesso
 */
int constroi_lista (unsigned *n, LISTA *l) {
	int i;
	//laco que percorre cada posicao da tabela de frequencia
	for (i = 0; i < 256; i++) {
		//verifica se a posicao correspondente ao caracter eh maior que zero
		//o que implica que aquela caracter apareceu alguma vez no arquivo
		if (n[i] > 0) {
			ARVORE temp_arvore;
			char c[2];
			c[0] = i;//o caracter eh armazenado pelo seu codigo ASCII
			c[1] = '\0';
			//aloca um noh de arvore com o caracter e frequencia correspondente
			temp_arvore = aloca_noh_arvore(c, n[i]);
			temp_arvore->esq = NULL;
			temp_arvore->dir = NULL;
			//insere num noh de lista o noh de arvore alocado
			if (!inserir_ordenado(l, temp_arvore)) {
				printf("Falha ao inserir ordenado");
				return 0;
			}
		}
	}
	return 1;
}

/* Funcao constroi_arvore
 * @Parametro LISTA l: recebe uma lista que contem nohs de arvore
 * que armazenam um caracter e sua frequencia correspondente
 * @Parametro ARVORE *t: recebe um ponteiro de arvore que foi
 * apenas inicializada no programa principal
 * @Retorno int: retorna 0 em caso de falha e 1 em caso de sucesso
 */
int constroi_arvore (LISTA l, ARVORE *t) {
    ARVORE s1, s2, novo;
    //Laco que percorre em quanto a lista tiver mais de um noh
	while (tamanho_da_lista(l) > 1) {
		//aloca na memoria um novo noh de arvore com o 
		//tamanho da struct noh_arvore
		novo = (ARVORE)malloc(sizeof(struct no_arvore));
		//remove os dois nohs de lista com os nohs de arvore
		//que armazenam os caracteres com menores frequencias
        if (!remove_primeiro_lista(&l, &s1)) return 0;
        if (!remove_primeiro_lista(&l, &s2)) return 0;
        //o novo noh de ARVORE aponta para os dois nohs removidos
        novo->esq = s2;
        novo->dir = s1;
        char str_temp[512];
        strcpy(str_temp, s1->simbolos);
		strcat(str_temp, s2->simbolos);
		//recebe como simbolos a concatenacao dos dois nohs removidos
        strcpy(novo->simbolos, str_temp);
        //recebe como frequencia a soma dos dois nohs removidos
        novo->frequencia = s1->frequencia + s2->frequencia;
        //o novo noh eh inserido na lista
        if (!inserir_ordenado(&l, novo)) return 0;
    }
    //no final, o ponteiro de arvore aponta para o ultimo noh de
	//lista restante que contem em si o ponteiro para a ARVORE que
	//armazena todos os caracteres e suas frequencias
    if (!remove_primeiro_lista(&l, t)) return 0;
    ARVORE temp = *t;
    return 1;
}

/* Funcao codifica
 * @Parametro ARVORE t: recebe a arvore com todos os caracteres
 * @Parametro char *a: recebe o vetor de char (string) que guarda
 * a palavra a ser codificada que foi dada pelo usuario
 * @Parametro char *b: recebe o vetor de char (string) em que sera
 * armazenado o padrao de bits correspondente a palavra codificada
 * @Retorno int: retorna 0 em caso de falha e 1 em caso de sucesso
 */
int codifica(ARVORE t, char *a, char *b) {
	int i;
	//declaracao de matriz de char (vetor de string) que armazena
	//o padrao de bits para cada caractere da palavra
	//[veja strlen(a) na primeira dimensao]
	char s[16], codificado[strlen(a)][16];
	strcpy(b, "");
	strcpy(s, "");
	//laco que inicializa todas as posicoes da matriz como uma string vazia
	for (i = 0; i < strlen(a); i++) {
		strcpy(codificado[i], "");
	}
	//chama funcao auxiliar
	if (!__codifica(t, a, codificado, s)) return 0;
	int qtd_char = 0;
	//laco que percorre cada caracter da palavra a ser codificada
	//dada pelo usuario
	for (i = 0; i < strlen(a); i++) {
		//se naquela posicao de caracter houver algum padrao de bits
		if (strcmp(codificado[i], "") != 0) {
			//concatena para o @Parametro b
			strcat(b, codificado[i]);
			qtd_char++;
		}
	}
	//se o numero de caracteres efetivamente codificados for
	//menor que o numero de caracteres presente na palavra
	//dada pelo usuario, algum caracter nao existe no 
	//@Parametro t e, portanto, @Retorno eh 0
	if (qtd_char < strlen(a)) return 0;
	return 1;
}

/* Funcao __codifica [auxiliar para Funcao codifica]
 * @Parametro ARVORE t: recebe a arvore com todos os caracteres
 * @Parametro char *a: recebe o vetor de char (string) que guarda
 * a palavra a ser codificada que foi dada pelo usuario
 * @Parametro char b[]: recebe matriz de char (vetor de string)
 * em que serao armazenados o padrao de bits para cada caracter
 * da palavra [@Parametro a] dada pelo usuario
 * @Parametro char *str: vetor de char (string) auxiliar que
 * armazena parte do padrao de bits ate que seja completo
 * @Retorno int: retorna 0 em caso de falha e 1 em caso de sucesso
 */
int __codifica (ARVORE t, char *a, char b[][16], char *str) {
	int i;
	//verifica se @Parametro t eh nulo, se for @Retorno eh 0
	if (t == NULL) return 0;
	//verifica se @Parametro t eh folha, se for @Retorno eh 1
	if (!t->esq && !t->dir) {
		//laco que percorre todos os caracteres de @Parametro a
		for (i = 0; i < strlen(a); i++) {
			//verifica, para cada caracter, se eh igual ao simbolo
			//armazenado pelo @Parametro t
			if (t->simbolos[0] == a[i]) {
				//copia para o @Parametro b, na mesma posicao em
				//que o caracter aparece no @Parametro a, o
				//@Parametro str
				strcpy(b[i], str);
			}
		}
		return 1;
	}
	//definicao de variaveis auxilares que tem por objetivo
	//armazenar um bit por vez ate que corresponda ao padrao
	//de bits completo que codifique o caracter
	int length = strlen(str);
    char leftcode[10],rightcode[10];
    strcpy(leftcode,str);
    strcpy(rightcode,str);
    leftcode[length] = '0';
    leftcode[length+1] = '\0';
    rightcode[length] = '1';
    rightcode[length+1] = '\0';
    //chama por recursao a Funcao __codifica [auxiliar para Funcao codifica]
	if (!__codifica(t->esq, a, b, leftcode)) return 0;
	if (!__codifica(t->dir, a, b, rightcode)) return 0;
	return 1;
}

/* Funcao decodifica
 * @Parametro ARVORE t: recebe a arvore com todos os caracteres
 * @Parametro char *a: recebe o vetor de char (string) que guarda
 * o padrao de bits inserido pelo usuario
 * @Parametro char *b: recebe o vetor de char (string) em que sera
 * armazenada a palavra decodificada correspondente ao padrao de bits
 * @Retorno int: retorna 0 em caso de falha e 1 em caso de sucesso
 */
int decodifica (ARVORE t, char *a, char *b) {
	ARVORE temp = t;
	int i = 0;
	//laco que percorre todos os caracteres do @Parametro a
	while (i <= strlen(a)) {
		//verifica se @Parametro t eh folha
		if (!(temp->esq || temp->dir)) {
			//se for, anexa-se em @Parametro b os simbolos
			//armazenados na ARVORE temp
			strcat(b, temp->simbolos);
			//variavel temporaria temp volta a ser @Parametro t
			temp = t;
		} else {
			//se nao for, verifica se ja verificou todos os caracteres
			//se sim, indica que o padrao de bits nao termina com um
			//codigo valido de caracter, e isso invalida todo o padrao
			//@Retorno eh 0
			if (i == strlen(a)) return 0;
		}
		//se o bit analisado no @Parametro a for 0
		if (a[i] == '0') {
			//A proxima iteracao do laco sera com o filho da esquerda
			temp = temp->esq;
		} else if (a[i] == '1') {
			//A proxima iteracao do laco sera com o filho da direita
			temp = temp->dir;
		}
		i++;
	}
	return 1;
}

int imprime_codigos(ARVORE t) {
	char s[16];
	strcpy(s, "");
	printf("Tabela de codigos\n");
	if (!__imprime_codigos(t, s)) return 0;
	return 1;
}

int __imprime_codigos (ARVORE t, char *str) {
	if (t == NULL) return 0;
	if (!t->esq && !t->dir) {
		printf("%s = %s\n", t->simbolos, str);
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
	if (!__imprime_codigos(t->esq, leftcode)) return 0;
	if (!__imprime_codigos(t->dir, rightcode)) return 0;
	return 1;
}
