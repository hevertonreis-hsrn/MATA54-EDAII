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

	FILE *f = file;

	int i;
	Registro r;
	fseek (file, 0, SEEK_SET);
	
	for (i=0; i < MTAMARQUIVO; i++) {

		long offset = ftell(file);

		fread (&r, sizeof (Registro), 1, f);

		printf ("Registro: %d\n", i);
		if (r.ocupado == true) {
			printf ("Ocupado: sim\n");
			printf ("Chave: %d\n", r.dados.chave);
			printf ("Offset: %d\n", offset);
		} else
			printf ("Ocupado: nao\n");
		printf("\n");
	}
}

int lerArquivoNaPosicao (FILE *file, long p){

	FILE *f = file;

	int i;
	long posicao = p;
	Registro r;
	fseek (file, posicao, SEEK_SET);

	long offset = ftell(file);

	fread (&r, sizeof (Registro), 1, f);

	if (r.ocupado == true) {
		printf ("Ocupado: sim\n");
		printf ("Chave: %d\n", r.dados.chave);
		printf ("Offset: %d\n", offset);
	} else
		printf ("Ocupado: nao\n");
		printf("\n");
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
    file = fopen("file","r+"); //Abre o arquivo "file.txt" em modo de leitura ("r", do ingles "read")

    if (file == NULL) //Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro na abertura do arquivo \"dados\" - Programa abortado\n");
		exit(-1);
    }

	char comando;
	gravarArquivo(file);
	
	printf("Rodando...\n");
    printf("Insira um comando...\n");
    while(comando != 'e'){

        scanf(" %c", &comando);

        if (comando == 'g')
        {
            gravarArquivo(file);
		}

		if (comando == 'l')
        {
            lerArquivo(file);
		}

		if (comando == 'p')
		{
			printf("Indique a posicao do arquivo...\n");
			long p;
			scanf("%d", &p);
			lerArquivoNaPosicao(file,p);
		}
		
	}
	
	fclose(file);
}