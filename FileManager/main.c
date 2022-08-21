#include<stdio.h>
#include<stdlib.h>

#define TAMARQUIVO 10
#define TAMNOME 20

typedef struct {
	int cpf;
	char nome[TAMNOME];
} Dados;

int main() {

    FILE *file = NULL; //Aloca estrutura de dados para manipulação de arquivos
    file = fopen("file.txt","r+"); //Abre o arquivo "file.txt" em modo de leitura ("r", do ingles "read")

    if (file == NULL) //Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro na abertura do arquivo \"dados\" - Programa abortado\n");
		exit(-1);
    }

    Dados registro;
    int posicao;
	
	printf("Informe um valor para o CPF (apenas numeros): ");
	scanf("%d",&(registro.cpf));
	printf("Informe um valor para o Nome (maximo de 20 caracteres): ");
	scanf("%s", registro.nome);
	printf("Informe a posicao do arquivo onde deseja inserir os dados: ");
	scanf("%d",&posicao);

    printf("Armazenando registro no arquivo ...\n");
	fseek(file, posicao*sizeof(Dados), SEEK_SET);	
	if (fwrite(&registro, sizeof(Dados), 1, file) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");

	fclose(file);
}