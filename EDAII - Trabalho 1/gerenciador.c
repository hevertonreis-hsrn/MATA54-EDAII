#include <stdio.h>

FILE* abrirArquivo(char nomeArquivo[]){

    FILE *arquivo = NULL; // Aloca estrutura de dados para manipulação de arquivos
    arquivo = fopen(nomeArquivo,"r+"); // Abre o arquivo "arvoreB" em modo de leitura ("r", do ingles "read")

    if (arquivo == NULL) // Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro na abertura do arquivo - Programa abortado!\n");
		exit(-1);
    }

    return arquivo;
}