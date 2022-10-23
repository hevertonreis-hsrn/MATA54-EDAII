#ifndef ARVORE_H
#define ARVORE_H

#define GRAU_MINIMO_INDICE 3
#define FATOR_CONJSEQ 2

typedef struct nodo
{
    long posicao;                           // Posicao deste Nodo no arquivo
    int numChaves;                          // Quantidade atual de chaves
    bool ehFolha;                           // Se TRUE indica que o nó é uma folha
    int chaves[2 * FATOR_CONJSEQ - 1];      // Vetor de chaves
    long filhos[2 * FATOR_CONJSEQ];         // Vetor de filhos
    char offset[44];                        // Garante que a arevore reserva esapaço para os registros 
} Nodo;

typedef struct header
{
    long posNodoRaiz;                       // Posicao do Nodo raiz
} Header;

long buscar(long posicaoRaiz, int chave);
long criarNodo();
void dividirFilhos(long posicaoRaiz, int i);
long inserirNodoNaoCheio(long posicaoRaiz, int chave);
long inserir(long posicaoRaiz, int chave);
void imprimirArvore(long posicaoRaiz, int nivel);
void lerNodoNaPosicao(long posicaoNodo);

#endif // ARVORE_H