#include <stdio.h>
#include <stdlib.h>
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
  unsigned tabela[256];
  LISTA lista_inicial;
  char palavra[30], codificado[1024];
  
  // inicializar as estruturas
  
  // Ler o arquivo linha, por linha
  //   Para cada caracter da linha, incrementar a frequencia dele na tabela
  
  constroi_lista (tabela, &lista_inicial);
  constroi_arvore (lista_inicial, &codigo);
  
  // ler a palavra para palavra[30]
  if (codifica (codigo, palavra, codificado))
     printf("%s ->%s\n", palavra, codificado);
  else
     printf("%s contem simbolos que nao existem na tabela\n", palavra);
     
  // ler um padrao de bits para codificado
  if (decodifica(codigo, codificado, palavra))
     printf("%s ->%s\n", codificado, palavra);
  else
     printf("Esse padrao nao pode ser decodificado com essa arvore\n");
  
  system("PAUSE");	
  return 0;
}
