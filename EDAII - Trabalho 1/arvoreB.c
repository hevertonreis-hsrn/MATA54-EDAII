#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GRAU_MINIMO_INDICE 3
#define FATOR_CONJSEQ 2

typedef struct
{
    long posicao;                           // Posicao deste Nodo no arquivo
    long posNodoRaiz;                       // Posicao do Nodo raiz
    int numChaves;                          // Quantidade atual de chaves
    bool ehFolha;                           // Se TRUE indica que o nó é uma folha
    int chaves[2 * FATOR_CONJSEQ - 1];      // Vetor de chaves
    long filhos[2 * FATOR_CONJSEQ];         // Vetor de filhos
} Nodo;

FILE* abrirArquivo(){

    FILE *arquivo = NULL; // Aloca estrutura de dados para manipulação de arquivos
    arquivo = fopen("arvoreB","r+"); // Abre o arquivo "arvoreB" em modo de leitura ("r", do ingles "read")

    if (arquivo == NULL) // Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro na abertura do arquivo - Programa abortado!\n");
		exit(-1);
    }

    return arquivo;
}

long buscar(long posicaoRaiz, int chave){ // Metodo para buscar chaves em um Nodo  

    FILE *arq = abrirArquivo();
    Nodo x;
    fseek (arq, posicaoRaiz, SEEK_SET);
    fread (&x, sizeof (Nodo), 1, arq);
    fclose(arq);
    free(arq);
    int i = 0;

    while (i <= x.numChaves && chave > x.chaves[i]) // Busca a primeira chave maior ou igual a chave indicada
    {
        i++;
    }

    if (i <= x.numChaves && chave == x.chaves[i]) // Se a chave procurada esta neste Nodo, retorna o Nodo
    {
        return x.posicao;
    }
    else if (x.ehFolha == true) // Retorna NULL se a chave nao foi encontrada nesse Nodo, e esse eh um Nodo folha
    {
        return -1;
    }
    else // Inicia o processo de busca nos filhos deste Nodo
    {
        FILE *arq = abrirArquivo();
        Nodo filho;
        fseek(arq, x.filhos[i], SEEK_SET);
        fread(&filho, sizeof(Nodo), 1, arq);
        fclose(arq);
        free(arq);

        buscar(filho.posicao, chave);

    }
}

long criarNodo() { // Metodo para criar um Nodo basico

    long posicao = 0;
    FILE *arq = abrirArquivo();

    Nodo x;
    x.ehFolha = true;
    x.numChaves = 0;

    fseek(arq, 0, SEEK_END);
	long offset = ftell(arq);
    x.posicao = offset;
    posicao = x.posicao;

    if (fwrite (&x, sizeof(Nodo), 1, arq) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");

    fclose(arq);
    free(arq);

    return posicao;
}

void dividirFilhos(long posicaoRaiz, int i){

    printf("Entrando no metodo dividirFilhos...\n");

    FILE *arqX = abrirArquivo();
    Nodo x;
    fseek (arqX, posicaoRaiz, SEEK_SET);
    fread (&x, sizeof (Nodo), 1, arqX);
    fclose(arqX);
    free(arqX);

    long posNodoZ = criarNodo(); // Cria um novo Nodo z
    FILE *arqZ = abrirArquivo();
    Nodo z;
    fseek (arqZ, posNodoZ, SEEK_SET);
    fread (&z, sizeof (Nodo), 1, arqZ);
    fclose(arqZ);
    free(arqZ);
    z.posNodoRaiz = x.posNodoRaiz;                        

    FILE *arqY = abrirArquivo();
    Nodo y;                              // Realiza a leitura do i-ezimo filho de x como um Nodo y
    fseek (arqY, x.filhos[i], SEEK_SET);
    fread (&y, sizeof (Nodo), 1, arqY);
    fclose(arqY);
    free(arqY);
    y.posNodoRaiz = x.posNodoRaiz;

    z.ehFolha = y.ehFolha;
    z.numChaves = FATOR_CONJSEQ - 1;

    for (int j = 0; j < FATOR_CONJSEQ - 1; j++) // Copia as ultimas t-1 chaves de y para z
    {
        z.chaves[j] = y.chaves[j+FATOR_CONJSEQ];
    }
    
    if (y.ehFolha == false)  // Copia os ultimos t filhos de y para z
    {
        for (int j = 0; j < FATOR_CONJSEQ; j++)
        {
            z.filhos[j] = y.filhos[j+FATOR_CONJSEQ];
        }
    }
    
    y.numChaves = FATOR_CONJSEQ - 1; //Reduz o numero de chaves em y

    for (int j = x.numChaves; j >= i + 1; j--) // Realoca os filhos de x para criar espaco para o novo Nodo filho
    {
        x.filhos[j+1] = x.filhos[j];
    }

    x.filhos[i+1] = z.posicao; // Indica z como um dos filhos de x

    for (int j = x.numChaves - 1; j >= i; j--) // Realoca as chaves de x para criar espaco para uma chave vinda de y
    {
        x.chaves[j+1] = x.chaves[j]; 
    }
    
    x.chaves[i] = y.chaves[FATOR_CONJSEQ-1]; // Copia a chave do meio de y para x
    x.numChaves = x.numChaves + 1; // Aumenta a contagem de chaves de x

    FILE *arqX2 = abrirArquivo();
    fseek (arqX2, x.posicao, SEEK_SET); // Realiza o salvamento das alteracoes do Nodo x no arquivo
    if (fwrite (&x, sizeof(Nodo), 1, arqX2) == 1)
		printf("Registro x armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro x\n");
    fclose(arqX2);
    free(arqX2);

    FILE *arqY2 = abrirArquivo();
    fseek (arqY2, y.posicao, SEEK_SET); // Realiza o salvamento das alteracoes do Nodo y no arquivo
    if (fwrite (&y, sizeof(Nodo), 1, arqY2) == 1)
		printf("Registro y armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro y\n");
    fclose(arqY2);
    free(arqY2);

    FILE *arqZ2 = abrirArquivo();
    fseek (arqZ2, z.posicao, SEEK_SET); // Realiza o salvamento das alteracoes do Nodo z no arquivo
    if (fwrite (&z, sizeof(Nodo), 1, arqZ2) == 1)
		printf("Registro z armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro z\n");
    fclose(arqZ2);
    free(arqZ2);

}

void inserirNodoNaoCheio(long posicaoRaiz, int chave){

    printf("Entrando no metodo inserirNodoNaoCheio...\n");

    FILE *arqX = abrirArquivo();
    Nodo x;
    fseek (arqX, posicaoRaiz, SEEK_SET);
    fread (&x, sizeof (Nodo), 1, arqX);
    fclose(arqX);
    free(arqX);

    int i = x.numChaves - 1; // Inicia o indice pelo elemento mais a direita

    if (x.ehFolha == true)
    {
        while (i >= 0 && x.chaves[i] > chave) // Se for um Nodo folha, desloca as chaves existentes para abrir espaço para a nova chave
        {
            x.chaves[i+1] = x.chaves[i];
            i = i - 1;
        }
        
        x.chaves[i+1] = chave; // Insere a chave na posicao aberta
        x.numChaves = x.numChaves + 1; // Incrementa a quantidade de chaves em x

        FILE *arqX2 = abrirArquivo();
        fseek (arqX2, x.posicao, SEEK_SET); // Realiza o salvamento das alteracoes do Nodo no arquivo
        if (fwrite (&x, sizeof(Nodo), 1, arqX2) == 1)
		    printf("Registro armazenado com sucesso\n");
	    else
		    printf("Erro no armazenamento do registro\n");
        fclose(arqX2);
        free(arqX2);
    } 
    else 
    {
        while (i >= 0 && x.chaves[i] > chave)    // Se o Nodo nao for uma folha, busca o filho que deve receber a nova chave
        {
            i = i - 1;
        }

        FILE *arqF = abrirArquivo();
        Nodo filho;                              // Realiza a leitura do i-ezimo filho de x
        fseek (arqF, x.filhos[i+1], SEEK_SET);
        fread (&filho, sizeof (Nodo), 1, arqF);
        fclose(arqF);
        free(arqF);

        if (filho.numChaves == (2 * FATOR_CONJSEQ - 1)) // Verifica se o filho ja esta cheio
        {
            printf("Filho Cheio! Necessario dividir...\n");
            dividirFilhos(x.posicao, i+1); // Em caso positivo, chama o metodo de divisao das chaves

            FILE *arqF2 = abrirArquivo();
            fseek (arqF2, x.posicao, SEEK_SET);
            fread (&x, sizeof (Nodo), 1, arqF2);
            fclose(arqF2);
            free(arqF2);

            if (x.chaves[i+1] < chave)
            {
                i++;
            }

            printf("Divisao bem sucedida...\n");
        }
        
        inserirNodoNaoCheio(filho.posicao, chave);
    }

}

void inserir(long posicaoRaiz, int chave){

    printf("Entrando no metodo inserir...\n");

    FILE *arqR = abrirArquivo();
    Nodo r;                           // Aloca memoria para o novo Nodo
    fseek (arqR, posicaoRaiz, SEEK_SET);
    fread (&r, sizeof (Nodo), 1, arqR);
    fclose(arqR);
    free(arqR);

    if (r.numChaves == (2 * FATOR_CONJSEQ - 1)) // Se r estiver cheio, aumenta a altura da arvore
    {
        printf("Nodo cheio...\n");

        long posNovoNodo = criarNodo();     // Cria um novo Nodo e retorna a posicao do mesmo
        printf ("Posicao do novo Nodo: %ld\n", posNovoNodo);

        FILE *arqS = abrirArquivo();
        Nodo s;                           // Aloca memoria para o novo Nodo
        fseek (arqS, posNovoNodo, SEEK_SET);
        fread (&s, sizeof (Nodo), 1, arqS);
                   
        s.posNodoRaiz = s.posicao; // Inicia as configuracoes do novo Nodo raiz
        s.ehFolha = false;
        s.numChaves = 0;
        s.filhos[0] = r.posicao; // Transforma o antigo Nodo raiz em um dos filhos do novo Nodo s

        fseek (arqS, s.posicao, SEEK_SET);
        if (fwrite (&s, sizeof(Nodo), 1, arqS) == 1)
		    printf("Registro armazenado com sucesso\n");
	    else
		    printf("Erro no armazenamento do registro\n");
        fclose(arqS);
        free(arqS);

        dividirFilhos(s.posNodoRaiz,0); // Divide o antigo Nodo raiz e move uma chave para o novo Nodo s

        FILE *arqS2 = abrirArquivo();                           // Aloca memoria para o novo Nodo
        fseek (arqS, posNovoNodo, SEEK_SET);
        fread (&s, sizeof (Nodo), 1, arqS);
        fclose(arqS);
        free(arqS);

        int i = 0;
        if(s.chaves[0] < chave){
            i = i + 1;
        }

        inserirNodoNaoCheio(s.filhos[i], chave); // Insere a nova chave em algum lugar da árvore

        printf("Fim da execucao para o Nodo cheio...\n");
    }
    else // Se r nao estiver cheio, chama o inserirNodoNaoCheio para r
    {
        inserirNodoNaoCheio(r.posicao, chave);
    }
    
}

void imprimirArvore(long posicaoRaiz, int nivel){ //Metodo para imprimir uma  representacao da arvore

    printf ("Posicao do no Fluxo: %d\n", posicaoRaiz);

    FILE *arqPT = abrirArquivo();
    Nodo x;
    fseek (arqPT, posicaoRaiz, SEEK_SET);
    fread (&x, sizeof (Nodo), 1, arqPT);
    fclose(arqPT);
    free(arqPT);

    printf ("Posicao do Nodo: %d\n", x.posicao);
    printf ("Posicao do Nodo Raiz: %d\n", x.posNodoRaiz);

    for (int i = 0; i < nivel; i++)
    {
        printf("    ");
    }
    
    printf("|");
    for (int i = 0; i < x.numChaves; i++)
    {
        printf("%d|", x.chaves[i]);
    }
    printf("\n");

    for (int i = 0; i <= x.numChaves; i++)
    {
        if (x.ehFolha == false)
        {
            FILE *arqPF = abrirArquivo();
            Nodo filho;
            fseek(arqPF, x.filhos[i], SEEK_SET);
            fread(&filho, sizeof(Nodo), 1, arqPF);
            fclose(arqPF);
            free(arqPF);
            printf ("Posicao do Filho: %d\n", x.filhos[i]);
            printf ("Posicao do Filho: %d\n", filho.posicao);
            imprimirArvore(filho.posicao, nivel + 1);
        }
        
    }
    
}

void lerNodoNaPosicao(long posicaoNodo){

    FILE *arq = abrirArquivo(); // Abre o arquivo para verificar se já existem dados salvos
    Nodo x;
    fseek (arq, posicaoNodo, SEEK_SET);
    fread(&x, sizeof(Nodo), 1, arq); 
    fclose(arq);
    free(arq);

    printf ("Posicao do Nodo: %d\n", x.posicao);
    printf ("Posicao do Nodo Raiz: %d\n", x.posNodoRaiz);

    for (int i = 0; i < 3; i++)
    {
        printf ("Chave: %d\n", x.chaves[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        printf ("Posicao do Filho: %d\n", x.filhos[i]);
    }
}

int main(){

    FILE *a = abrirArquivo(); // Abre o arquivo para verificar se já existem dados salvos
    fseek (a, 0, SEEK_END); 
    long tamanho = ftell(a);
    fclose(a);
    free(a);

    if (tamanho == 0)
    {
        printf("Nenhum dado encontrado! Arvore vazia\n\n");

        long pos = criarNodo(); // Cria um novo nodo no arquivo
        
        FILE *arq = abrirArquivo(); // Abre o arquivo para leitura
        Nodo a;
        fseek (arq, pos, SEEK_SET);
        fread (&a, sizeof (Nodo), 1, arq);

        a.posNodoRaiz = a.posicao; // Informa ao nodo a posicao do nodo raiz

        fseek (arq, a.posicao, SEEK_SET); // Armazena as alteracoes
        if (fwrite (&a, sizeof(Nodo), 1, arq) == 1)
		    printf("Registro armazenado com sucesso\n");
	    else
		    printf("Erro no armazenamento do registro\n");

        fclose(arq); //Encerra o fluxo de arquivos
        free(arq);
    
    }
        
    char comando;
    int chave = 0;
    int posicao = 0;
    
    printf("Rodando...\n");
    printf("Insira um comando...\n");
    while(comando != 'e'){

        scanf(" %c", &comando);

        if (comando == 'i')
        {

            FILE *arqI = abrirArquivo(); // Abre o arquivo para leitura
            Nodo aI;
            fseek (arqI, 0, SEEK_SET);
            fread (&aI, sizeof (Nodo), 1, arqI);         
            fclose(arqI);
            free(arqI);

            posicao = aI.posNodoRaiz;
            printf ("Posicao do Nodo Raiz: %d\n", posicao);

            scanf(" %d", &chave);

            inserir(posicao, chave);
        }
        
        if (comando == 'b')
        {

            FILE *arqB = abrirArquivo(); // Abre o arquivo para leitura
            Nodo aB;
            fseek (arqB, 0, SEEK_SET);
            fread (&aB, sizeof (Nodo), 1, arqB);         
            fclose(arqB);
            free(arqB);

            posicao = aB.posNodoRaiz;

            scanf(" %d", &chave);

            long posNodo = buscar(posicao, chave);

            if (posNodo == -1)
            {
                printf ("Chave nao encontrada!\n");
            }
            else
            {
                printf ("Esta chave esta no Nodo de posicao: %ld\n", posNodo);

                FILE *arq = abrirArquivo(); // Abre o arquivo para leitura
                Nodo x;
                fseek (arq, posNodo, SEEK_SET);
                fread (&x, sizeof (Nodo), 1, arq);
                fclose(arq);
                free(arq);

                for (int i = 0; i < 3; i++)
                {
                    if(x.chaves[i] == chave){
                        printf ("Posicao: %ld\n", posNodo);
                        printf ("Chave: %d\n", x.chaves[i]);
                    }
                    
                }
            }
               
        }

        if (comando == 'p')
        {
            
            FILE *arqP = abrirArquivo(); // Abre o arquivo para leitura
            Nodo aP;
            fseek (arqP, 0, SEEK_SET);
            fread (&aP, sizeof (Nodo), 1, arqP);         
            fclose(arqP);
            free(arqP);

            posicao = aP.posNodoRaiz;
            printf ("Posicao do Nodo Raiz: %d\n", posicao);

            imprimirArvore(posicao, 0);
        }

        if (comando == 'l')
        {
            int posi;
            scanf(" %d", &posi);
            lerNodoNaPosicao(posi);
        }
        
    }

}