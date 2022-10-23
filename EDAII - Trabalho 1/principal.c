#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvoreB.c"
#include "registro.h"

#define MTAMNOME 20
#define ARQARVORE "arvoreB"

int main() {

    arvoreB();

	char comando;
    
    printf("Rodando...\n");
    printf("Insira um comando...\n");
    while(comando != 'e'){

        scanf(" %c", &comando);

        if (comando == 'i')
        {   
            int chave = 0;

            Registro regEntrada;
            scanf("%d", &chave);
            regEntrada.chave = chave;
            //scanf("%s", regEntrada.nome);
            //scanf("%d", regEntrada.idade);

            FILE *arq = abrirArquivo(ARQARVORE);
            Header h;
            fseek (arq, 0, SEEK_SET);
            fread (&h, sizeof (Header), 1, arq);
            fclose(arq);
            free(arq);

            long buscaExistente = buscar(h.posNodoRaiz,chave);

            if (buscaExistente != -1)
            {
                printf("chave ja existente: %d\n", chave);
            }
            else
            {
                long resultado = inserir(h.posNodoRaiz, chave);
                printf("O valor de resultado eh: %ld\n", resultado);

                FILE *aL = abrirArquivo(ARQARVORE);
                Nodo local;
                fseek(aL, resultado, SEEK_SET);
                fread(&local, sizeof(Nodo), 1, aL);
                fclose(aL);
                free(aL);

                int localChave = 0;

                for (int i = 0; i < (2 * FATOR_CONJSEQ - 1); i++)
                {
                    if (local.chaves[i] == chave)
                    {
                        printf("Posicao do registro dentro da folha: %d\n", i);
                        localChave = i;
                    }
                    
                }

                FILE *regS = abrirArquivo(ARQREG);
                Folha fA;
                fseek(regS, resultado, SEEK_SET);
                fread(&fA, sizeof(Folha), 1, regS);

                printf("Chave antes do registro: %d\n", regEntrada.chave);

                fA.registros[localChave] = regEntrada;

                printf("Chave depois do registro: %d\n", fA.registros[localChave].chave);

                fseek(regS, resultado, SEEK_SET);
                if (fwrite (&fA, sizeof(Folha), 1, regS) == 1)
		            printf("insercao com sucesso: %d\n", chave);
	            else
		            printf("erro no armazenamento do registro\n");
                }
            
        }

        if (comando == 'c')
        {
            int chave = 0;
            scanf("%d", &chave);

            FILE *arqC = abrirArquivo(ARQARVORE);
            Header h;
            fseek (arqC, 0, SEEK_SET);
            fread (&h, sizeof (Header), 1, arqC);
            fclose(arqC);
            free(arqC);

            long buscaExistente = buscar(h.posNodoRaiz,chave);

            if (buscaExistente == -1)
            {
                printf("chave nao encontrada: %d\n", chave);
            }
            else
            {

                FILE *aC = abrirArquivo(ARQARVORE);
                Nodo local;
                fseek(aC, buscaExistente, SEEK_SET);
                fread(&local, sizeof(Nodo), 1, aC);
                fclose(aC);
                free(aC);

                int localChave = 0;

                for (int i = 0; i < (2 * FATOR_CONJSEQ - 1); i++)
                {
                    if (local.chaves[i] == chave)
                    {
                        printf("Posicao do registro dentro da folha: %d\n", i);
                        localChave = i;
                    }                    
                }

                FILE *regC = abrirArquivo(ARQREG);
                Folha fC;
                fseek(regC, buscaExistente, SEEK_SET);
                fread(&fC, sizeof(Folha), 1, regC);
                fclose(regC);
                free(regC);

                printf("chave: %d\n", fC.registros[localChave].chave);
            }
        }
        
    }
    
    /*fseek(arquivo, posicao*sizeof(Registro), SEEK_SET);

	if (fwrite (&reg, sizeof(Registro), 1, arquivo) == 1)
		printf("Registro armazenado com sucesso\n");
	else
		printf("Erro no armazenamento do registro\n");

	fclose(arquivo);*/
}