#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GRAU_MINIMO_INDICE 3
#define FATOR_CONJSEQ 2

typedef struct nodo
{
    int numChaves;                          // Quantidade atual de chaves
    bool ehFolha;                           // Se TRUE indica que o nó é uma folha
    int chaves[2 * FATOR_CONJSEQ - 1];      // Vetor de chaves
    struct nodo *filhos[2 * FATOR_CONJSEQ]; // Vetor de filhos

} nodo;

nodo* buscar(nodo *x, int chave){ // Metodo para buscar chaves em um nodo  

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
        return buscar(x->filhos[i], chave);
    }
    
}

nodo* criarNodo() { // Metodo para criar um nodo basico

    nodo *x = (nodo *)malloc(sizeof(nodo)); 
    x->ehFolha = true;
    x->numChaves = 0;

    return x;
}

nodo* dividirFilhos(nodo *x, int i){
    printf("Entrando no metodo dividirFilhos...\n");

    nodo *z = (nodo *)malloc(sizeof(nodo));
    nodo *y = x->filhos[i]; // Cria um nodo auxiliar para esta operacao
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
    
    x->filhos[i+1] = z; // Indica z como um dos filhos de x

    for (int j = x->numChaves; j >= i; j--) // Realoca as chaves de x para criar espaco para uma chave vinda de y
    {
        x->chaves[j+1] = x->chaves[j]; 
    }
    
    x->chaves[i] = y->chaves[FATOR_CONJSEQ-1]; // Copia a chave do meio de y para x
    x->numChaves++; // Aumenta a contagem de chaves de x

    return x;
}

nodo* inserirNodoNaoCheio(nodo *x, int chave){
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
    } 
    else 
    {
        while (i >= 0 && chave < x->chaves[i]) // Se o nodo nao for uma folha, busca o filho que deve receber a nova chave
        {
            i--;
        }
        
        i = i + 1;

        if (x->filhos[i]->numChaves == (2 * FATOR_CONJSEQ - 1)) // Verifica se o filho ja esta cheio
        {
            printf("Filho Cheio! Necessario dividir...\n");
            x = dividirFilhos(x, i); // Em caso positivo, chama o metodo de divisao das chaves

            if (chave > x->chaves[i])
            {
                i++;
            }
            printf("Divisao bem sucedida...\n");
        }
        
        x->filhos[i] = inserirNodoNaoCheio(x->filhos[i], chave);
    }
    
    return x;
}

nodo* inserir(nodo *raiz, int chave){
    printf("Entrando no metodo inserir...\n");

    nodo *r = raiz; // Instancia o nodo recebido como raiz

    if (r->numChaves == (2 * FATOR_CONJSEQ - 1)) // Se r estiver cheio, aumenta a altura da arvore
    {
        printf("Nodo cheio...\n");
        nodo *s = criarNodo(); // Aloca memoria para o novo nodo
        raiz = s;
        s->ehFolha = false;
        s->numChaves = 0;
        s->filhos[0] = r; // Transforma o antigo nodo raiz em um dos filhos do novo nodo s
        s = dividirFilhos(s,0); // Divide o antigo nodo raiz e move uma chave para o novo nodo s
        s = inserirNodoNaoCheio(s, chave);
        
        return s;
    }
    else // Se r nao estiver cheio, chama o inserirNodoNaoCheio para r
    {
        return inserirNodoNaoCheio(r, chave);
    }
}

nodo* removerDeUmNodoFolha(nodo *x, int i) // Metodo para remover uma chave de um nodo folha
{
    for (int i = i + 1; i < x->numChaves; i++) // Realoca todas as chaves, tornando a chave a ser excluida inacessível
    {
        x->chaves[i-1] = x->chaves[i];
    }
    
    x->numChaves = x->numChaves - 1; // Diminui a contagem de chaves

    return x;
}

int obterAntecessor(nodo *x, int i)
{
    nodo *atual = x->filhos[i];
    while (atual->ehFolha == false)
    {
        atual = atual->filhos[atual->numChaves];
    }

    return atual->chaves[atual->numChaves-1];
    
}

int obterSucessor(nodo *x, int i)
{
    nodo *atual = x->filhos[i+1];
    while (atual->ehFolha == false)
    {
        atual = atual->filhos[0];
    }

    return atual->chaves[0];
    
}

nodo* juntar(nodo *x, int i){ // Metodo que faz a uniao de do filho a esquerda com o filho a direita

    nodo *filhoEsquerda = x->filhos[i];
    nodo *filhoDireita = x->filhos[i+1];

    filhoEsquerda->chaves[FATOR_CONJSEQ-1] = x->chaves[i];

    for (int i = 0; i < filhoDireita->numChaves; i++) //Copia as chaves do filho da direita pro filho da esquerda
    {
        filhoEsquerda->chaves[i+FATOR_CONJSEQ] = filhoDireita->chaves[i];
    }
    
    if (filhoEsquerda->ehFolha == false)
    {
        for (int i = 0; i < filhoDireita->numChaves; i++) // Copia os filhos 
        {
            filhoEsquerda->filhos[i+FATOR_CONJSEQ] = filhoDireita->filhos[i];
        }
        
    }
    
    for (int j = i + 1; j < x->numChaves; j++)
    {
        x->chaves[j-1] = x->chaves[j];
    }
    
    for (int j = i + 2; j < x->numChaves; j++)
    {
        x->filhos[j-1] = x->filhos[j];
    }

    filhoEsquerda->numChaves += filhoDireita->numChaves+1;
    x->numChaves = x->numChaves - 1;

    free(filhoDireita);

    return x;
}

nodo* pegarDoAnterior(nodo *x, int i)
{
    nodo *filhoEsquerda = x->filhos[i-1];
    nodo *filhoDireita = x->filhos[i];

    for (int i = filhoDireita->numChaves-1; i >= 0; i--) //Copia as chaves do filho da direita pro filho da esquerda
    {
        filhoDireita->chaves[i+1] = filhoDireita->chaves[i];
    }
    
    if (filhoDireita->ehFolha == false)
    {
        for (int i = filhoDireita->numChaves; i >= 0; i--) // Copia os filhos 
        {
            filhoDireita->filhos[i+1] = filhoDireita->filhos[i];
        }
        
    }
    
    filhoDireita->chaves[0] = x->chaves[i-1];

    if (filhoDireita->ehFolha == false)
    {
        x->filhos[0] = filhoEsquerda->filhos[filhoEsquerda->numChaves];        
    }

    x->chaves[i-1] = filhoEsquerda->chaves[filhoEsquerda->numChaves-1];

    filhoDireita->numChaves+= 1;
    filhoEsquerda->numChaves-= 1;

    return x;
}

nodo* pegarDoProximo(nodo *x, int i)
{
    nodo *filhoEsquerda = x->filhos[i];
    nodo *filhoDireita = x->filhos[i+1];

    filhoEsquerda->chaves[filhoEsquerda->numChaves] = x->chaves[i];

    if (filhoEsquerda->ehFolha == false)
    {
        filhoEsquerda->filhos[filhoEsquerda->numChaves+1] = filhoDireita->filhos[0];        
    }
    
    x->chaves[i] = filhoDireita->chaves[0];

    for (int i = 1; i < filhoDireita->numChaves; i++)
    {
        filhoDireita->chaves[i-1] = filhoDireita->chaves[i];
    }
    
    if (filhoDireita->ehFolha == false)
    {
        for (int i = 1; i <= filhoDireita->numChaves; i++)
        {
            filhoDireita->filhos[i-1] = filhoDireita->filhos[i];
        }
        
    }
    

    filhoDireita->numChaves-= 1;
    filhoEsquerda->numChaves+= 1;

    return x;
}

nodo* preencher(nodo *x, int i)
{

    if (i != 0 && x->filhos[i-1]->numChaves >= FATOR_CONJSEQ) // 
    {
        x = pegarDoAnterior(x,i);
    }
    else if (i != x->numChaves && x->filhos[i+1]->numChaves >= FATOR_CONJSEQ)
    {
        x = pegarDoProximo(x,i);
    }
    else
    {
        if (i != x->numChaves)
        {
            x = juntar(x,i);
        }
        else
        {
            x = juntar(x,i);
        }
        
    }
    
    return x;
}

nodo* removerDeUmNodoNaoFolha(nodo *x, int i) // Metodo para remover uma chave de um nodo nao folha
{
    int chave = x->chaves[i];

    if(x->filhos[i]->numChaves >= FATOR_CONJSEQ){

        int antecessor = obterAntecessor(x,i);
        x->chaves[i] = antecessor;
        x->filhos[i] = remover(x->filhos[i],antecessor);
    }
    else if (x->filhos[i+1]->numChaves >= FATOR_CONJSEQ)
    {
        int sucessor = obterSucessor(x,i);
        x->chaves[i] = sucessor;
        x->filhos[i+1] = remover(x->filhos[i+i],sucessor);
    }
    else
    {
        x = juntar(x,i);
        x->filhos[i] = remover(x->filhos[i], chave);
    }

    return x;
}

nodo* remover(nodo *x, int chave){ // Metodo para remover chaves em um nodo  

    int i = 0;

    while (i <= x->numChaves && chave > x->chaves[i]) // Busca a primeira chave maior ou igual a chave indicada
    {
        i++;
    }

    if (i <= x->numChaves && chave == x->chaves[i]) // Verifica se a chave procurada esta neste nodo
    {
        if (x->ehFolha == true) // Remove a chave se for um nodo folha
        {
            x = removerDeUmNodoFolha(x,i);
        }
        else{ // Remove a chave se nao for um nodo folha
            x = removerDeUmNodoNaoFolha(x,i);
        }

    }
    else
    {
        if (x->ehFolha == true) // Retorna NULL se a chave nao foi encontrada nesse nodo, e esse eh um nodo folha
        {
            return NULL;
        }

        bool chaveExiste = ( (i == x->numChaves)? true : false );

        if(x->filhos[i]->numChaves < FATOR_CONJSEQ) // Se o filho onde a chave esta tem menos do que t chaves, preenche esse filho
        {
            x->filhos[i] = preencher(x,i);
        }

        if (chaveExiste && i > x->numChaves)
        {
            x->filhos[i-1] = remover(x->filhos[i-1],chave);
        }
        else
        {
            x->filhos[i] = remover(x->filhos[i],chave);
        }
    }

  return x;
}

void imprimirArvore(nodo *arvore, int nivel){ //Metodo para imprimir uma  representacao da arvore

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
            imprimirArvore(arvore->filhos[i], nivel + 1);
        }
        
    }
    
}

int main(){
    
    char comando;
    int chave = 0;

    nodo *arvore = criarNodo();

    printf("Rodando...\n");
    printf("Insira um comando...\n");
    while(comando != 'e'){

        scanf(" %c", &comando);

        if (comando == 'i')
        {
            scanf(" %d", &chave);

            arvore = inserir(arvore, chave);
        }
        
        if (comando == 'b')
        {
            scanf(" %d", &chave);

            arvore = buscar(arvore, chave);

            for (int i = 0; i < 3; i++)
            {
                printf ("Chave: %d\n", arvore->chaves[i]);
            }
                        
        }

        if (comando == 'p')
        {
            imprimirArvore(arvore, 0);
        }
        
        
    }
}