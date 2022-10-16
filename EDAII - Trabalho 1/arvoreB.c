#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GRAU_MINIMO_INDICE 3
#define FATOR_CONJSEQ 2

typedef struct nodo
{
    int numChaves;                          // quantidade atual de chaves
    bool ehFolha;                           // se TRUE indica que o nó é uma folha
    int chaves[2 * FATOR_CONJSEQ - 1];      // vetor de chaves
    struct nodo *filhos[2 * FATOR_CONJSEQ]; // vetor de filhos

} nodo;

//struct nodo *raiz;

nodo* criarArvore() {

    //FILE *arquivo;
    //arquivo = fopen("arvoreB","wb");

    //if (arquivo == NULL){
    //    printf("Erro ao abrir o arquivo!");
    //    exit(-1);
    //}

    nodo *x = (nodo *)malloc(sizeof(nodo)); // alocacao do nodo
    x->ehFolha = true;
    x->numChaves = 0;

    //fwrite (&x, sizeof(nodo), 1, arquivo);
    //fclose(arquivo);

    return x;
}

nodo* dividirFilhos(nodo *x, int i, nodo *y){

    int j;

    nodo *z = (nodo *)malloc(sizeof(nodo));
    z->ehFolha = y->ehFolha;
    z->numChaves = FATOR_CONJSEQ - 1;

    for (j = 0; j < FATOR_CONJSEQ - 1; j++) // transfere as chaves do nodo y pro novo nodo z
    {
        z->chaves[j] = y->chaves[j+FATOR_CONJSEQ];
    }
    
    if (!y->ehFolha)  // se y nao for uma folha, transefere seus filhos para z
    {
        for (int j = 0; j < FATOR_CONJSEQ; j++)
        {
            z->filhos[j] = y->filhos[j+FATOR_CONJSEQ];
        }
    }
    
    y->numChaves = FATOR_CONJSEQ - 1;

    for (j = x->numChaves + 1; j >= i + 1; j--) // realoca os filhos de x
    {
        x->filhos[j+1] = x->filhos[j];
    }
    
    x->filhos[i+1] = z; //indica z como um dos filhos de x

    for (j = x->numChaves; j >= i; j--) // realoca as chaves de x
    {
        x->chaves[j+1] = x->chaves[j]; 
    }
    
    x->chaves[i] = y->chaves[FATOR_CONJSEQ];
    x->numChaves++;

    return x;
}

nodo* inserirNodo(nodo *raiz, int chave){

    nodo *r = raiz;

    if (r->numChaves == (2 * FATOR_CONJSEQ - 1))
    {
        nodo *s = criarArvore();
        s->ehFolha = false;
        s->numChaves = 0;
        s->filhos[0] = r;
        s = dividirFilhos(s,0,r);
        s = inserirNodoNaoCheio(s, chave);
        return s;
    }
    else
    {
        return inserirNodoNaoCheio(r, chave);
    }
}

nodo* inserirNodoNaoCheio(nodo *x, int chave){

    int i = x->numChaves;

    if (x->ehFolha)
    {
        while (i >= 0 && chave < x->chaves[i]) // desloca as chaves existentes para alocar a nova chave a esquerda
        {
            x->chaves[i+1] = x->chaves[i];
            i--;
        }
        
        x->chaves[i+1] = chave;
        x->numChaves++;
    } 
    else 
    {
        while (i >= 0 && chave < x->chaves[i])
        {
            i--;
        }
        
        i++;

        if (x->filhos[i]->numChaves == (2 * FATOR_CONJSEQ - 1))
        {
            x = dividirFilhos(x, i, x->chaves[i]);

            if (chave > x->chaves[i])
            {
                i++;
            }
            
        }
        
        x->filhos[i] = inserirNodoNaoCheio(x->filhos[i], chave);
    }
    
    return x;
}

nodo* buscar(nodo *x, int chave){

    int i =0;

    while (i <= x->numChaves && chave > x->chaves[i])
    {
        i++;
    }

    if (i <= x->numChaves && chave == x->chaves[i])
    {
        return (x, i);
    }
    
    if (x->ehFolha)
    {
        return NULL;
    }
    else 
    {
        return buscar(x->filhos[i], chave);
    }
    
}

int main(){
    //criarArvore();
    printf("Rodando...\n");
    /*
    nodo arvore;
    FILE *arqArvore;
    arqArvore = fopen("arvoreB","rb");

    if (arqArvore == NULL) //Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro na abertura do arquivo");
		exit(-1);
    }  

	for (int i=0; i < GRAU_MINIMO_INDICE; i++) {

		fread (&arvore, sizeof (nodo), 1, arqArvore);

		printf ("Registro: %d\n", i);

		if (arvore.ehFolha == true) {

			printf ("Numero de Chaves: %d\n", arvore.numChaves);

		} else

			printf ("Nao eh uma folha\n");

		printf("\n"); 
    }

    fclose(arqArvore);*/
}