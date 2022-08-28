#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MTAMARQUIVO 10

typedef struct {
	int chave;
} Dados;

typedef struct {
	bool ocupado;
	Dados dados;
} Registro;

int lerArquivo (FILE *file){

	Registro registro;
    int posicao;

	for (int i=0; i < MTAMARQUIVO; i++) {

		fread (&registro, sizeof (Dados), 1, file);

		printf ("Registro: %d\n", i);

		if (registro.ocupado == true) {

			printf ("Ocupado: sim\n");
			printf ("Chave: %d\n", registro.dados.chave);

		} else

			printf ("Ocupado: nao\n");

		printf("\n");
	}
}

int gravarArquivo(FILE *file){

	Registro registro;
	registro.ocupado = false;
    int posicao;
	
	printf("Informe um valor para a chave (apenas numeros): ");
	scanf("%d",&(registro.dados.chave));
	printf("Informe a posicao no arquivo onde deseja inserir os dados: ");
	scanf("%d",&posicao);

    printf("Armazenando registro no arquivo ...\n");
	registro.ocupado = true;

	fseek(file, posicao*sizeof(Registro), SEEK_SET);

	if (fwrite (&registro, sizeof(Registro), 1, file) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");
}

int main() {

    FILE *file = NULL; //Aloca estrutura de dados para manipulação de arquivos
    file = fopen("file.txt","r+"); //Abre o arquivo "file.txt" em modo de leitura ("r", do ingles "read")

    if (file == NULL) //Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro na abertura do arquivo \"dados\" - Programa abortado\n");
		exit(-1);
    }

	//gravarArquivo(file);
	lerArquivo(file);
/*
    Registro registro;
	registro.ocupado = false;
    int posicao;
	
	printf("Informe um valor para a chave (apenas numeros): ");
	scanf("%d",&(registro.dados.chave));
	printf("Informe a posicao no arquivo onde deseja inserir os dados: ");
	scanf("%d",&posicao);

    printf("Armazenando registro no arquivo ...\n");
	fseek(file, posicao*sizeof(Dados), SEEK_SET);
		
	if (fwrite(&registro, sizeof(Dados), 1, file) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");
*/
	fclose(file);
}