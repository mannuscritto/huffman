#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "arvore.h"
#include "lista.h"
/*
1. Contar a frequencia absoluta dos simbolos em um arquivo informado
2. Montar a tabela de frequencias ordenada
3. Construir a arvore de Huffman para esse arquivo (tabela de freq)
4. Qual a taxa de compressao para o arquivo informado
5. Digitar uma palavra e imprimir o codigo para cada simbolo
6. Digitar um padrao de bits, e apresentar a palavra correspondente
*/	
	
int main(int argc, char *argv[])
{
	ARVORE codigo;
	unsigned tabela[256] = {0};
	LISTA lista_inicial;
	char palavra[30], codificado[1024];
	
	// inicializar as estruturas
	if (!criar_arvore(&codigo)) {
		printf("Erro ao criar a arvore");
		exit(1);
	}
	codigo = (ARVORE)malloc(sizeof(struct no_arvore));
	if (!criar_lista(&lista_inicial)) {
		printf("Erro ao inicializar a lista");
		exit(1);
	}
	// Ler o arquivo linha, por linha
	//   Para cada caracter da linha, incrementar a frequencia dele na tabela
	char arquivo[256];
	
	printf("Escreva uma string: ");
	scanf("%s", arquivo);
	int i;
	for (i = 0; i < strlen(arquivo); i++) {
		tabela[arquivo[i]]++;
	}
	
	if(!constroi_lista (tabela, &lista_inicial)) return 0;
	if(!constroi_arvore(lista_inicial, &codigo)) return 0;
	
	// ler a palavra para palavra[30]
	printf("Escreva uma string: ");
	scanf("%s", palavra);

	if (codifica (codigo, palavra, codificado)) {
		printf("%s -> %s\n", palavra, codificado);
	} else {
		printf("%s contem simbolos que nao existem na tabela\n", palavra);
	}
		
	if (!imprime_codigos(codigo)) return 0;
		
	// ler um padrao de bits para codificado
	char padrao[128];
	printf("Digite um padrao de bits codificado: ");
	scanf("%s", padrao);
	strcpy(palavra, "");
	if (decodifica(codigo, padrao, palavra))
		printf("%s -> %s\n", padrao, palavra);
	else
		printf("Esse padrao nao pode ser decodificado com essa arvore\n");
	system("PAUSE");	
	return 0;
}
