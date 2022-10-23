#ifndef REGISTRO_H
#define REGISTRO_H

#define GRAU_MINIMO_INDICE 3
#define FATOR_CONJSEQ 2

typedef struct registro
{
    int chave;
    char nome[20];
    int idade;
} Registro;

typedef struct folha
{
    Registro registros[2*FATOR_CONJSEQ-1];
} Folha;


#endif // REGISTRO_H