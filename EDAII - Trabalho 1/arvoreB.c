#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GRAU_MINIMO_INDICE 3
#define FATOR_CONJSEQ 2

typedef struct nodo
{
    long posicao;                           // Posicao deste nodo no arquivo
    int numChaves;                          // Quantidade atual de chaves
    bool ehFolha;                           // Se TRUE indica que o nó é uma folha
    int chaves[2 * FATOR_CONJSEQ - 1];      // Vetor de chaves
    long filhos[2 * FATOR_CONJSEQ];         // Vetor de filhos
} nodo;

nodo* buscar(FILE *arq, nodo *x, int chave){ // Metodo para buscar chaves em um nodo  

    int i = 0;

    while (i <= x->numChaves && chave > x->chaves[i]) // Busca a primeira chave maior ou igual a chave indicada
    {
        i++;
    }

    if (i <= x->numChaves && chave == x->chaves[i]) // Se a chave procurada esta neste nodo, retorna o nodo
    {
        return x;
    }
    else if (x->ehFolha == true) // Retorna NULL se a chave nao foi encontrada nesse nodo, e esse eh um nodo folha
    {
        return NULL;
    }
    else // Inicia o processo de busca nos filhos deste nodo
    {
        nodo *filho;
        fseek(arq, x->filhos[i], SEEK_SET);
        fread(&filho, sizeof(nodo), 1, arq);
        return buscar(arq, filho, chave);
    }
    
}

nodo* criarNodo(FILE *arq) { // Metodo para criar um nodo basico

    nodo *x = (nodo *)malloc(sizeof(nodo)); 
    x->ehFolha = true;
    x->numChaves = 0;

    fseek(arq, 0, SEEK_END);
	long offset = ftell(arq);
    x->posicao = offset;

    if (fwrite (&x, sizeof(nodo), 1, arq) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");

    return x;
}

nodo* dividirFilhos(FILE *arq, nodo *x, int i){

    printf("Entrando no metodo dividirFilhos...\n");

    nodo *z = criarNodo(arq);             // Cria um novo nodo z

    nodo *y;                              // Realiza a leitura do i-ezimo filho de x como um nodo y
    fseek (arq, x->filhos[i], SEEK_SET);
    fread (&y, sizeof (nodo), 1, arq);

    z->ehFolha = y->ehFolha;
    z->numChaves = FATOR_CONJSEQ - 1;

    for (int j = 0; j < FATOR_CONJSEQ - 1; j++) // Copia as ultimas t-1 chaves de y para z
    {
        z->chaves[j] = y->chaves[j+FATOR_CONJSEQ];
    }
    
    if (y->ehFolha == false)  // Copia os ultimos t filhos de y para z
    {
        for (int j = 0; j < FATOR_CONJSEQ; j++)
        {
            z->filhos[j] = y->filhos[j+FATOR_CONJSEQ];
        }
    }
    
    y->numChaves = FATOR_CONJSEQ - 1; //Reduz o numero de chaves em y

    for (int j = x->numChaves + 1; j >= i + 1; j--) // Realoca os filhos de x para criar espaco para o novo nodo filho
    {
        x->filhos[j+1] = x->filhos[j];
    }
    
    x->filhos[i+1] = z->posicao; // Indica z como um dos filhos de x

    for (int j = x->numChaves; j >= i; j--) // Realoca as chaves de x para criar espaco para uma chave vinda de y
    {
        x->chaves[j+1] = x->chaves[j]; 
    }
    
    x->chaves[i] = y->chaves[FATOR_CONJSEQ-1]; // Copia a chave do meio de y para x
    x->numChaves++; // Aumenta a contagem de chaves de x

    fseek (arq, y->posicao, SEEK_SET); // Realiza o salvamento das alteracoes do nodo y no arquivo
    if (fwrite (&y, sizeof(nodo), 1, arq) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");

    fseek (arq, x->posicao, SEEK_SET); // Realiza o salvamento das alteracoes do nodo x no arquivo
    if (fwrite (&x, sizeof(nodo), 1, arq) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");

    fseek (arq, z->posicao, SEEK_SET); // Realiza o salvamento das alteracoes do nodo z no arquivo
    if (fwrite (&z, sizeof(nodo), 1, arq) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");

    return x;
}

nodo* inserirNodoNaoCheio(FILE *arq, nodo *x, int chave){

    printf("Entrando no metodo inserirNodoNaoCheio...\n");

    int i = x->numChaves-1; // Inicia o indice pelo elemento mais a direita

    if (x->ehFolha == true)
    {
        while (i >= 0 && chave < x->chaves[i]) // Se for um nodo folha, desloca as chaves existentes para abrir espaço para a nova chave
        {
            x->chaves[i+1] = x->chaves[i];
            i--;
        }
        
        x->chaves[i+1] = chave; // Insere a chave na posicao aberta
        x->numChaves++; // Incrementa a quantidade de chaves em x

        fseek (arq, x->posicao, SEEK_SET); // Realiza o salvamento das alteracoes do nodo no arquivo
        if (fwrite (&x, sizeof(nodo), 1, arq) == 1)
		    printf("Registro armazenado com sucesso\n");
	    else
		    printf("Erro no armazenamento do registro\n");

    } 
    else 
    {
        while (i >= 0 && chave < x->chaves[i]) // Se o nodo nao for uma folha, busca o filho que deve receber a nova chave
        {
            i--;
        }
        
        i = i + 1;

        nodo *filho;                              // Realiza a leitura do i-ezimo filho de x
        fseek (arq, x->filhos[i], SEEK_SET);
        fread (&filho, sizeof (nodo), 1, arq);

        if (filho->numChaves == (2 * FATOR_CONJSEQ - 1)) // Verifica se o filho ja esta cheio
        {
            printf("Filho Cheio! Necessario dividir...\n");
            x = dividirFilhos(arq, x, i); // Em caso positivo, chama o metodo de divisao das chaves

            if (chave > x->chaves[i])
            {
                i++;
            }
            printf("Divisao bem sucedida...\n");
        }
        
        filho = inserirNodoNaoCheio(arq, filho, chave);
    }
    
    return x;
}

nodo* inserir(FILE *arq, nodo *raiz, int chave){
    printf("Entrando no metodo inserir...\n");

    nodo *r = raiz; // Instancia o nodo recebido como raiz

    if (r->numChaves == (2 * FATOR_CONJSEQ - 1)) // Se r estiver cheio, aumenta a altura da arvore
    {
        printf("Nodo cheio...\n");
        nodo *s = criarNodo(arq); // Aloca memoria para o novo nodo
        raiz = s;
        s->ehFolha = false;
        s->numChaves = 0;
        s->filhos[0] = r->posicao; // Transforma o antigo nodo raiz em um dos filhos do novo nodo s
        s = dividirFilhos(arq,s,0); // Divide o antigo nodo raiz e move uma chave para o novo nodo s
        s = inserirNodoNaoCheio(arq, s, chave);
        
        return s;
    }
    else // Se r nao estiver cheio, chama o inserirNodoNaoCheio para r
    {
        return inserirNodoNaoCheio(arq, r, chave);
    }
}

void imprimirArvore(FILE *arq, nodo *arvore, int nivel){ //Metodo para imprimir uma  representacao da arvore

    for (int i = 0; i < nivel; i++)
    {
        printf("    ");
    }
    
    printf("|");
    for (int i = 0; i < arvore->numChaves; i++)
    {
        printf("%d|", arvore->chaves[i]);
    }
    printf("\n");

    for (int i = 0; i <= arvore->numChaves; i++)
    {
        if (arvore->ehFolha == false)
        {
            nodo *filho;
            fseek(arq, arvore->filhos[i], SEEK_SET);
            fread(&filho, sizeof(nodo), 1, arq);
            imprimirArvore(arq, filho, nivel + 1);
        }
        
    }
    
}

int main(){

    FILE *arquivo = NULL; // Aloca estrutura de dados para manipulação de arquivos
    arquivo = fopen("arvoreB","r+"); // Abre o arquivo "arvoreB" em modo de leitura ("r", do ingles "read")

    if (arquivo == NULL) // Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro na abertura do arquivo - Programa abortado!\n");
		exit(-1);
    }

    nodo *arvore;

    fseek (arquivo, 0, SEEK_END); // Inicia leitura pelo fim do arquivo do arquivo
    long tamanho = ftell(arquivo);

    if (tamanho == 0)
    {
        printf("Nenhum dado encontrado! Arvore vazia\n\n");
        arvore = criarNodo(arquivo);    
    }
    else
    {
        fseek (arquivo, 0, SEEK_SET);
        fread (&arvore, sizeof (nodo), 1, arquivo); // Realiza a leitura do arquivo e aloca dados na estrutura da arvore
    }
        
    char comando;
    int chave = 0;

    printf("Rodando...\n");
    printf("Insira um comando...\n");
    while(comando != 'e'){

        scanf(" %c", &comando);

        if (comando == 'i')
        {
            scanf(" %d", &chave);

            arvore = inserir(arquivo, arvore, chave);
        }
        
        if (comando == 'b')
        {
            scanf(" %d", &chave);

            arvore = buscar(arquivo, arvore, chave);

            for (int i = 0; i < 3; i++)
            {
                printf ("Chave: %d\n", arvore->chaves[i]);
            }
                        
        }

        if (comando == 'p')
        {
            imprimirArvore(arquivo, arvore, 0);
        }
        
        
    }

    fclose(arquivo);
}