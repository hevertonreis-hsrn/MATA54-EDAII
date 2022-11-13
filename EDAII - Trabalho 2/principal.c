#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct nodo
{
    char termo[30];
    int filhos[2];
} Nodo;

Nodo* criarNodo(){
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    return n;
}

void inserir(char *palavra, Nodo *raiz){

    inserirRecursivo(palavra, raiz);
}

int combinaCharConsecutivo(char *palavra, Nodo *nodoAtual){

    int contaCombinacao = 0;
    int tamanhoMin = 0;

    int tamanhoTermo = (int)strlen(nodoAtual->termo);
    int tamanhoPalavra = (int)strlen(palavra);

    // Verifica qual palavra é menor
    if ( tamanhoTermo >= tamanhoPalavra)
    {
        tamanhoMin = tamanhoPalavra;
    } else if (tamanhoTermo < tamanhoPalavra)
    {
        tamanhoMin = tamanhoTermo;
    }
    
    if (tamanhoMin > 0)
    {
        //Percorre os dois fluxos
        for (int i = 0; i < tamanhoMin; i++)
        {
            // Se dois caracteres na mesma posicao sao iguais, incrementa o contador, caso contrario, interrompe o laco
            if (palavra[i] == nodoAtual->termo[i])
            {
                contaCombinacao++;
            } else {
                break;
            }
            
        }
         
    }
    
    return contaCombinacao;
}

void inserirRecursivo(char *partePalavra, Nodo *nodoAtual){

    int combinacoes = combinaCharConsecutivo(partePalavra, nodoAtual);

    if ( (combinacoes == 0) || () )
    {
        /* code */
    }
    
}


int main(int argc, char const *argv[])
{
    Nodo *raiz = criarNodo();
    return 0;
}
