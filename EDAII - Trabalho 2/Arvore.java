import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Nodo {

    public Nodo(String palavra){
        this.palavra = palavra;
        filhos = new ArrayList<>();
    }

    public String palavra;
    public List<Nodo> filhos;
}

public class Arvore {

    private final Nodo raiz;

    public Arvore(){
        raiz = new Nodo("");
    }

    public void Inserir(String palavra){
        InserirRecursivo(palavra, raiz);
    }

    private void InserirRecursivo(String palavra, Nodo nodoAtual){

        int combinacoes = CombinaCharConsecutivo(palavra, nodoAtual);

        int tamanhoTermo = nodoAtual.palavra.length();
        int tamanhoPalavra = palavra.length();

        if( (combinacoes == 0) ||
        (nodoAtual == raiz) ||
        ( (combinacoes > 0) && (combinacoes < tamanhoPalavra) && (combinacoes >= tamanhoTermo) )
        ){

            boolean inserido = false;
            String novaPalavra = palavra.substring(combinacoes, tamanhoPalavra); 


            for (Nodo filho : nodoAtual.filhos) {

                char caractere = novaPalavra.charAt(0);
                String comecaCom = Character.toString(caractere);

                if (filho.palavra.startsWith(comecaCom)) {
                    inserido = true;
                    InserirRecursivo(novaPalavra, filho);
                }
            }

            if(!inserido){
                nodoAtual.filhos.add(new Nodo(novaPalavra));
            }

        } else if(combinacoes < tamanhoPalavra){

            String raizComum = palavra.substring(0, combinacoes);
            String ramoPalavraAnterior = nodoAtual.palavra.substring(combinacoes, tamanhoTermo);
            String ramoNovaPalavra = palavra.substring(combinacoes, tamanhoPalavra);

            nodoAtual.palavra = raizComum;

            Nodo novoNodoPalavraAnterior = new Nodo(ramoPalavraAnterior);
            novoNodoPalavraAnterior.filhos.addAll(nodoAtual.filhos);

            nodoAtual.filhos.clear();
            nodoAtual.filhos.add(novoNodoPalavraAnterior);

            Nodo novoNodoNovaPalavra = new Nodo(ramoNovaPalavra);
            nodoAtual.filhos.add(novoNodoNovaPalavra);

        } else if (combinacoes > tamanhoTermo ) {

            String novaPalavraNodo = nodoAtual.palavra.substring(tamanhoTermo, tamanhoPalavra);
            Nodo novoNodo = new Nodo(novaPalavraNodo);
            nodoAtual.filhos.add(novoNodo);
        }
    }

    private int CombinaCharConsecutivo(String palavra, Nodo nodoAtual){

        int combinacoes = 0;
        int tamanhoMin;

        int tamanhoTermo = nodoAtual.palavra.length();
        int tamanhoPalavra = palavra.length();

        tamanhoMin = Math.min(tamanhoTermo, tamanhoPalavra);

        if(tamanhoMin > 0){

            for(int i = 0; i < tamanhoMin; i++){

                char[] novaPalavra = palavra.toCharArray();
                char[] palavraDoNodo = nodoAtual.palavra.toCharArray();

                if(novaPalavra[i] == palavraDoNodo[i]){
                    combinacoes++;
                } else {
                    break;
                }
            }
        }

        return combinacoes;
    }

    public boolean Buscar(String palavra){
        
        return BuscarRecursivo(palavra, raiz);
    }

    private boolean BuscarRecursivo(String palavra, Nodo nodoAtual) {

        int combinacoes = CombinaCharConsecutivo(palavra, nodoAtual);

        int tamanhoTermo = nodoAtual.palavra.length();
        int tamanhoPalavra = palavra.length();

        if ( (combinacoes == 0) ||
                (nodoAtual == raiz) ||
                ( (combinacoes > 0) && (combinacoes < tamanhoPalavra) && (combinacoes >= tamanhoTermo) )
        ){

            String novaPalavra = palavra.substring(combinacoes, tamanhoPalavra);

            for (Nodo filho : nodoAtual.filhos) {

                char caractere = novaPalavra.charAt(0);
                String comecaCom = Character.toString(caractere);

                if (filho.palavra.startsWith(comecaCom)){
                    return BuscarRecursivo(novaPalavra, filho);
                }
            }

            return false;
        } else return combinacoes == tamanhoTermo;
    }

    public void Remover(String palavra){

        RemoverRecursivo(palavra, raiz);

    }

    private void RemoverRecursivo(String palavra, Nodo nodoAtual) {

        int combinacoes = CombinaCharConsecutivo(palavra, nodoAtual);

        int tamanhoTermo = nodoAtual.palavra.length();
        int tamanhoPalavra = palavra.length();

        if ( (combinacoes == 0) ||
                (nodoAtual == raiz) ||
                ( (combinacoes > 0) && (combinacoes < tamanhoPalavra) && (combinacoes >= tamanhoTermo) )
        ){
            String novaPalavra = palavra.substring(combinacoes, tamanhoPalavra);

            for (Nodo filho : nodoAtual.filhos) {

                char caractere = novaPalavra.charAt(0);
                String comecaCom = Character.toString(caractere);

                if (filho.palavra.startsWith(comecaCom)){
                    if (novaPalavra.equals(filho.palavra)){
                        if ((long) filho.filhos.size() == 0){

                            nodoAtual.filhos.remove(filho);
                            return;
                        }
                    }
                    RemoverRecursivo(novaPalavra, filho);
                }
            }
        }
    }

    public static void main(String[] args) {

        Arvore arvore = new Arvore();

        Scanner entrada = new Scanner(System.in);
        String comando = "";

        //arvore.Inserir("romane");
        //arvore.Inserir("romanus");
        //arvore.Inserir("romulus");
        //arvore.Inserir("rubens");
        //arvore.Inserir("ruber");
        //arvore.Inserir("rubicon");
        //arvore.Inserir("rubicundus");

        while(!comando.equals("e")){

            comando = entrada.nextLine();

            if(comando.equals("i")){

                String palavra = "";
                palavra = entrada.nextLine();

                arvore.Inserir(palavra);

            }

            if(comando.equals("c")){

                String palavra = "";
                palavra = entrada.nextLine();

                boolean resultado = arvore.Buscar(palavra);

                System.out.println(
                resultado ?
                "Existe na arvore" :
                "Nao existe na arvore");
            }
        }

        entrada.close();
    }
}