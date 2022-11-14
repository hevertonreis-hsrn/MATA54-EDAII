import java.io.*;
import java.Util.Scanner;

public class Nodo {

    public Nodo(){
        Palavra = "";
        Filhos = new List<Nodo>();
    }

    public Nodo(String palavra){
        Palavra = palavra;
        Filhos = new List<Nodo>(); 
    }

    public String Palavra;
    public List<Nodo> Filhos;
}

public class Arvore {

    private Nodo raiz;

    public Arvore(){
        raiz = new Nodo("");
    }

    public void Inserir(String palavra){
        InserirRecursivo(palavra, raiz);
    }

    private void InserirRecursivo(String palavra, Nodo nodoAtual){

        int combinacoes = CombinaCharConsecutivo(palavra, nodoAtual);

        int tamanhoTermo = nodoAtual.Palavra.length();
        int tamanhoPalavra = palavra.length();

        if( (combinacoes == 0) ||
        (nodoAtual == raiz) ||
        ( (combinacoes > 0) && (combinacoes < tamanhoPalavra) && (combinacoes >= tamanhoTermo) )
        ){

            bool inserido = false;
            var novaPalavra = palavra.substring(combinacoes, tamanhoPalavra - combinacoes); 

            for(Nodo filho : nodoAtual.Filhos){

                if(filho.Palavra.startsWith(novaPalavra[0].toString())){
                    inserido = true;
                    InserirRecursivo(novaPalavra, filho);
                }
            }

            if(!inserido){
                nodoAtual.Filhos.add(new Nodo(palavra));
            }
        } else if(combinacoes < tamanhoPalavra){

            String raizComum = palavra.substring(0, combinacoes);
            
        }
    }

    private int CombinaCharConsecutivo(String palavra, Nodo nodoAtual){

        int combinacoes = 0;
        int tamanhoMin = 0;

        int tamanhoTermo = nodoAtual.Palavra.length();
        int tamanhoPalavra = palavra.length();

        if( tamanhoTermo >= tamanhoPalavra ){
            tamanhoMin = tamanhoPalavra;
        } else if( tamanhoTermo < tamanhoPalavra ){
            tamanhoMin = tamanhoTermo;
        }

        if(tamanhoMin > 0){

            for(int i = 0; i < tamanhoMin; i++){

                if(palavra[i] == nodoAtual.Palavra[i]){
                    combinacoes++;
                } else {
                    break;
                }
            }
        }

        return combinacoes;
    }

    public static void main(String[] args) {
        
    }
}