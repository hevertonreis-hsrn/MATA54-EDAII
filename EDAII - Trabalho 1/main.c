#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRAU_MINIMO_INDICE 3
#define FATOR_CONJSEQ 2

//Definindo estrutura do registro.
typedef struct
{
    int chave;
    char nome[20];
    int idade;
} Registro;

//Definindo estrutura de cada noh da árvore.
struct nohArvore
{
    int contaChaves;
    int chaves[(2*FATOR_CONJSEQ)-1];
    struct nohArvore* filhos[2*FATOR_CONJSEQ];
} ;

//Definindo noh raiz.
struct nohArvore *raiz;

//Definindo estrutura que cria o noh efetivamente.
struct nohArvore *criarNoh(int chave, struct nohArvore *filho)
{
    struct nohArvore *novoNoh;
    novoNoh = (struct nohArvore *)malloc(sizeof(struct nohArvore));
    novoNoh->chaves[1] = chave;
    novoNoh->contaChaves = 1;
    novoNoh->filhos[0] = raiz;
    novoNoh->filhos[1] = filho;
    return novoNoh;
}

void buscaNoh(int chave, int *posicao, struct nohArvore *nohAtual ){
    if (!nohAtual) return;

    if (chave < nohAtual->chaves[1]) { //Verifica a posicao mais a esquerda
        *posicao = 0;
    } else { //Inicia uma busca através das chaves deste noh.
        for (*posicao = nohAtual->contaChaves; 
        (chave < nohAtual->chaves[*posicao] && *posicao > 1); 
        (*posicao)--);
        if (chave == nohAtual->chaves[*posicao]){
            printf("Chave %d foi encontrada!", chave);
            return;
        }
    }

    buscaNoh(chave, posicao, nohAtual->filhos[*posicao]); //Em caso de falha, chama a funcao novamente

    return;
}

void inserirNoh(int chave, int *posicao, struct nohArvore *noh, struct nohArvore *filho){

    int i = noh->contaChaves;

    while (i > posicao)
    {
        noh->chaves[i+1] = noh->chaves[i];
        noh->filhos[i+1] = noh->filhos[i];
        i--;
    }
    
    noh->chaves[i+1] = chave;
    noh->filhos[i+1] = filho;
    noh->contaChaves++;
}

void dividirNoh(int chave, int *posChave, int posicao, struct nohArvore *noh, struct nohArvore *filho, struct nohArvore **novoNoh){

    int medio, i;

    if (posicao > FATOR_CONJSEQ)
    {
        medio = FATOR_CONJSEQ + 1;
    } else {
        medio = FATOR_CONJSEQ;
    }
    
    *novoNoh = (struct nohArvore *)malloc(sizeof(struct nohArvore));
    i = medio + 1;
    while (i <= GRAU_MINIMO_INDICE)
    {
        (*novoNoh)->chaves[i-medio] = noh->chaves[i];
        (*novoNoh)->filhos[i-medio] = noh->filhos[i];
        i++;
    }
    noh->contaChaves = medio;
    (*novoNoh)->contaChaves = GRAU_MINIMO_INDICE - medio;

    if (posicao <= FATOR_CONJSEQ)
    {
        inserirNoh(chave, posicao, noh, filho);
    } else {
        inserirNoh(chave, posicao - medio, *novoNoh, filho);
    }
    *posChave = noh->chaves[noh->contaChaves];
    (*novoNoh)->filhos[0] = noh->filhos[noh->contaChaves];
    noh->contaChaves--;
}

int definirValor(int chave, int *posChave, struct nohArvore *noh, struct nohArvore **filho){

    int posicao;
    if (!noh)
    {
        *posChave = chave;
        *filho = NULL;
        return 1;
    }
    
    if (chave < noh->chaves[1]) { //Verifica a posicao mais a esquerda
        posicao = 0;
    } else { //Inicia uma busca através das chaves deste noh.
        for (posicao = noh->contaChaves; 
        (chave < noh->chaves[posicao] && posicao > 1); 
        (posicao)--);
        if (chave == noh->chaves[posicao]){
            printf("Insercao nao eh permitida!");
            return 0;
        }
    }
    
    if (definirValor(chave, posChave, noh->filhos[posicao], filho))
    {
        if (noh->contaChaves < GRAU_MINIMO_INDICE)
        {
            inserirNoh(*posChave, posicao, noh, *filho);
        } else {
            dividirNoh(*posChave, posChave, posicao, noh, *filho, filho);
        }
        
    }
    
}

void inserir(int chave){

    int flag, i;
    struct nohArvore *filho;

    flag = definirValor(chave, &i, raiz, &filho);
    if(flag) raiz = criarNoh(i, filho);
}



//Funcoes do programa principal


void insereRegistro(){

}

void consultaRegistro(){

}

void removeRegistro(){
    
}

void imprimeArvore(){

}

void imprimeChavesCrescente(){

}

int main() {

    FILE *arquivo;
    arquivo = fopen("arquivoPrincipal","r+");

    if (arquivo == NULL)
    {
        printf ("Erro na abertura do arquivo \"arquivoPrincipal\" - Programa abortado\n");
		exit(-1);
    }

    Registro reg;
    int posicao;
	
	printf("Informe uma chave: ");
	scanf("%d",&(reg.chave));
	printf("Entre com um nome: ");
	scanf("%s", reg.nome);
	printf("Entre com uma posicao do arquivo: ");
	scanf("%d",&posicao);

    printf("Armazenando registro no arquivo ...\n");
    
    fseek(arquivo, posicao*sizeof(Registro), SEEK_SET);

	if (fwrite (&reg, sizeof(Registro), 1, arquivo) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");

	fclose(arquivo);
}