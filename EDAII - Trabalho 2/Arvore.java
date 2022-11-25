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
    public int posicaoDicionario;
}

public class Arvore {

    private static Nodo raiz;

    public Arvore(){
        raiz = new Nodo("");
    }

    public void Inserir(String palavra, Verbete verbete){
        InserirRecursivo(palavra, raiz, verbete);
    }

    private void InserirRecursivo(String palavra, Nodo nodoAtual, Verbete verbete){

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
                    InserirRecursivo(novaPalavra, filho, verbete);
                }
            }

            if(!inserido){
                Nodo nodoNovaPalavra = new Nodo(novaPalavra);
                nodoAtual.filhos.add(nodoNovaPalavra);
                int posNovoNodo = nodoAtual.filhos.indexOf(nodoNovaPalavra);
                nodoAtual.filhos.get(posNovoNodo).posicaoDicionario = Dicionario.InserirDicionario(verbete);
            }

        } else if(combinacoes < tamanhoPalavra){

            String raizComum = palavra.substring(0, combinacoes);
            String ramoPalavraAnterior = nodoAtual.palavra.substring(combinacoes, tamanhoTermo);
            String ramoNovaPalavra = palavra.substring(combinacoes, tamanhoPalavra);

            nodoAtual.palavra = raizComum;

            Nodo novoNodoPalavraAnterior = new Nodo(ramoPalavraAnterior);
            novoNodoPalavraAnterior.filhos.addAll(nodoAtual.filhos);
            novoNodoPalavraAnterior.posicaoDicionario = nodoAtual.posicaoDicionario;

            nodoAtual.filhos.clear();
            nodoAtual.filhos.add(novoNodoPalavraAnterior);

            Nodo novoNodoNovaPalavra = new Nodo(ramoNovaPalavra);
            nodoAtual.filhos.add(novoNodoNovaPalavra);
            int posNovoNodo = nodoAtual.filhos.indexOf(novoNodoNovaPalavra);
            nodoAtual.filhos.get(posNovoNodo).posicaoDicionario = Dicionario.InserirDicionario(verbete);
            
        } else if (combinacoes > tamanhoTermo ) {

            String novaPalavraNodo = nodoAtual.palavra.substring(tamanhoTermo, tamanhoPalavra);
            Nodo novoNodo = new Nodo(novaPalavraNodo);
            nodoAtual.filhos.add(novoNodo);            
            int posNovoNodo = nodoAtual.filhos.indexOf(novoNodo);
            nodoAtual.filhos.get(posNovoNodo).posicaoDicionario = Dicionario.InserirDicionario(verbete);
        }
    }

    private static int CombinaCharConsecutivo(String palavra, Nodo nodoAtual){

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

    public static void Remover(String palavra){

        RemoverRecursivo(palavra, raiz);

    }

    private static void RemoverRecursivo(String palavra, Nodo nodoAtual) {

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

                            Armazenamento dadosArquivo = new Armazenamento();
                            ArrayList<Object> dicionario = dadosArquivo.lerListaArquivo("dicionario.dat");
                            dicionario.set(filho.posicaoDicionario,null);
                            dadosArquivo.gravarListaArquivo(dicionario, "dicionario.dat");
                            
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

            Verbete verbete = new Verbete();

            comando = entrada.nextLine();

            if(comando.equals("i")){

                String palavra = entrada.nextLine();
                String classe = entrada.nextLine();
                int qtdTraducoes = entrada.nextInt();

                verbete.palavraOrigem = palavra;
                verbete.classePalavra = classe;

                entrada.nextLine();
                for (int i = 0; i<qtdTraducoes; i++) {
                    verbete.traducoes[i] = entrada.nextLine();
                }

                arvore.Inserir(palavra, verbete);

            }

            if(comando.equals("c")){

                String palavra = entrada.nextLine();

                boolean resultado = arvore.Buscar(palavra);

                System.out.println(
                resultado ?
                "Existe na arvore" :
                "Nao existe na arvore");
            }

            if(comando.equals("r")){

                String palavra = entrada.nextLine();
                Remover(palavra);
            }
        }

        entrada.close();
    }
}