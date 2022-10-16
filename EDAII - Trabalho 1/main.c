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