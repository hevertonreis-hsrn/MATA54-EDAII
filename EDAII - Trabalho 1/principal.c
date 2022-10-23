#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvoreB.c"
#include "registro.h"

#define MTAMNOME 20
#define ARQARVORE "arvoreB"

int noSeq = 0;

void imprimirArvoreCompleta(long posicaoRaiz, int nivel){ //Metodo para imprimir uma  representacao da arvore

    FILE *arqPT = abrirArquivo(ARQARVORE);
    Nodo x;
    fseek (arqPT, posicaoRaiz, SEEK_SET);
    fread (&x, sizeof (Nodo), 1, arqPT);
    fclose(arqPT);
    free(arqPT);

    noSeq++;
    printf("No: %d: ", noSeq);
    for (int i = 0; i < x.numChaves; i++)
    {
        printf("apontador: %ld chave: %d ", (x.posicao+i)*sizeof(Registro), x.chaves[i]);
    }
    printf("\n");

    for (int i = 0; i <= x.numChaves; i++)
    {
        if (x.ehFolha == false)
        {
            FILE *arqPF = abrirArquivo(ARQARVORE);
            Nodo filho;
            fseek(arqPF, x.filhos[i], SEEK_SET);
            fread(&filho, sizeof(Nodo), 1, arqPF);
            fclose(arqPF);
            free(arqPF);

            imprimirArvoreCompleta(filho.posicao, nivel + 1);
        }
        
    }
}

int main() {

    arvoreB();
    
	char comando;

    while(comando != 'e'){

        scanf(" %c", &comando);

        if (comando == 'i')
        {   
            int chave = 0;

            Registro reg;
            scanf("%d", &chave);
            reg.chave = chave;
            scanf(" %s", reg.nome);
            scanf("%d", &reg.idade);

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
                long posNodo = inserir(h.posNodoRaiz, chave);

                FILE *aL = abrirArquivo(ARQARVORE);
                Nodo local;
                fseek(aL, posNodo, SEEK_SET);
                fread(&local, sizeof(Nodo), 1, aL);
                fclose(aL);
                free(aL);

                int localChave = 0;

                for (int i = 0; i < (2 * FATOR_CONJSEQ - 1); i++)
                {
                    if (local.chaves[i] == chave)
                    {
                        localChave = i;
                    }
                    
                }

                FILE *regS = abrirArquivo(ARQREG);
                fseek(regS, (posNodo+localChave)*(sizeof(Registro)),SEEK_SET);
                fwrite (&reg, sizeof(Registro), 1, regS);
                fclose(regS);
                free(regS);
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
                        localChave = i;
                    }                    
                }

                FILE *regC = abrirArquivo(ARQREG);
                Registro rC;
                fseek(regC, (buscaExistente+localChave)*(sizeof(Registro)),SEEK_SET);
                fread(&rC, sizeof(Registro), 1, regC);
                fclose(regC);
                free(regC);

                printf("chave: %d\n", rC.chave);
                printf("nome: %s\n", rC.nome);
                printf("idade: %d\n", rC.idade);

            }
        }
        if (comando == 'p')
        {

            FILE *arqP = abrirArquivo(ARQARVORE);
            Header h;
            fseek (arqP, 0, SEEK_SET);
            fread (&h, sizeof (Header), 1, arqP);
            fclose(arqP);
            free(arqP);

            imprimirArvoreCompleta(h.posNodoRaiz, 0);
            noSeq = 0;
        }
        
    }
}