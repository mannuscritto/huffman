#ifndef __ARVORE__
#define __ARVORE__
struct no_arvore
{
   char simbolos[256];
   unsigned frequencia;
   struct no_arvore* esq;
   struct no_arvore* dir;
};

typedef struct no_arvore* ARVORE;

int criar_arvore (ARVORE*);
int inserir_esquerda (ARVORE*, ARVORE);
int inserir_direita  (ARVORE*, ARVORE);
ARVORE aloca_noh_arvore(char*, unsigned); // simbolo, frequencia
// percurso
void inordem (ARVORE);
#endif
