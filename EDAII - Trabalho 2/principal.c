#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct nodo
{
    char termo[30];
    Nodo *filhos[2];
} Nodo;

// Criar novo nodo
Nodo* criarNodo(){
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    return n;
}

// Alocando nodo raiz
Nodo *raiz;

// Inserir palavra na arvore
void inserir(char *palavra[], Nodo *raiz){

    inserirRecursivo(palavra, raiz);
}

int combinaCharConsecutivo(char *palavra[], Nodo *nodoAtual){

    int contaCombinacao = 0;
    int tamanhoMin = 0;

    int tamanhoTermo = (int)strlen(nodoAtual->termo);
    int tamanhoPalavra = (int)strlen(palavra);

    // Verifica qual palavra é menor e armazena seu tamanho
    if ( tamanhoTermo >= tamanhoPalavra)
    {
        tamanhoMin = tamanhoPalavra;
    } else if (tamanhoTermo < tamanhoPalavra)
    {
        tamanhoMin = tamanhoTermo;
    }
    
    // Procura os caracteres na mesma posicao, e, verifica se sao iguais, incrementa o contador, caso contrario, interrompe o laco
    if (tamanhoMin > 0)
    {
        
        for (int i = 0; i < tamanhoMin; i++)
        { 
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

void inserirRecursivo(char *palavra[], Nodo *nodoAtual){

    int combinacoes = combinaCharConsecutivo(palavra, nodoAtual);

    int tamanhoTermo = (int)strlen(nodoAtual->termo);
    int tamanhoPalavra = (int)strlen(palavra);

    if ( (combinacoes == 0) || 
    (nodoAtual == raiz) || 
    ((combinacoes > 0) && (combinacoes < tamanhoPalavra) && (combinacoes >= tamanhoTermo))
    )
    {
        bool inserido = false;
        char *novaPalavra = malloc(strlen(palavra));

        strncpy(novaPalavra, palavra + combinacoes, tamanhoPalavra - combinacoes);

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < ; j++)
            {
                /* code */
            }
            
        }
        
    }
    
}


int main(int argc, char const *argv[])
{
    raiz = criarNodo();

    char palavra = "batata";

    inserir(palavra,raiz);
    return 0;
}
