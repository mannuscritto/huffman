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
	
char *readFile(char *);	
	
int main(int argc, char *argv[])
{
	ARVORE codigo;
	unsigned tabela[256] = {0};
	LISTA lista_inicial;
	char palavra[30], codificado[1024];
	float taxaC;
	
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
	char *arquivo = readFile("dicionario.txt");
	
	int i;
	for (i = 0; i < strlen(arquivo); i++) {
		tabela[arquivo[i]]++;
	}
	
	if(!constroi_lista (tabela, &lista_inicial)) return 0;
	if(!constroi_arvore(lista_inicial, &codigo)) return 0;
	
	char temp_cod[2048];
	if (codifica(codigo, arquivo, temp_cod)) {
		taxaC = (float)((float)(strlen(temp_cod)) / (float)(strlen(arquivo) * (float)(8)));
		//taxaC = (float)((float)1110/(float)1704);
		printf("A taxa de compressao eh de %5.2f%%\n", (1-taxaC)*100);
	} else {
		printf("Erro ao codificar\n");
	}
	
	// ler a palavra para palavra[30]
	printf("Escreva uma palavra: ");
	scanf("%[^\n]s", palavra);

	if (codifica (codigo, palavra, codificado)) {
		printf("%s -> %s\n", palavra, codificado);
	} else {
		printf("%s contem simbolos que nao existem na tabela\n", palavra);
	}
		
	if (!imprime_codigos(codigo)) return 0;
		
	// ler um padrao de bits para codificado
	printf("Digite um padrao de bits codificado: ");
	scanf("%s", codificado);
	strcpy(palavra, "");
	if (decodifica(codigo, codificado, palavra))
		printf("%s -> %s\n", codificado, palavra);
	else
		printf("Esse padrao nao pode ser decodificado com essa arvore\n");
	system("PAUSE");
	return 0;
}

char *readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL; //could not open file

    code = malloc(1000);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // don't forget to terminate with the null character
    code[n] = '\0';        

    return code;
}
