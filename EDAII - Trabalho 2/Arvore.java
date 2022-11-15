import java.util.*;;

class Nodo {

    //public Nodo(){
    //    Palavra = "";
    //    List<Nodo> Filhos = new ArrayList<>();
    //}

    public Nodo(String palavra){
        Palavra = palavra;
        List<Nodo> Filhos = new ArrayList<Nodo>();
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

            boolean inserido = false;
            String novaPalavra = palavra.substring(combinacoes, tamanhoPalavra - combinacoes); 

            if(nodoAtual.Filhos != null) {
                for (Nodo filho : nodoAtual.Filhos) {

                    char caractere = novaPalavra.charAt(0);
                    String comecaCom = Character.toString(caractere);

                    if (filho.Palavra.startsWith(comecaCom)) {
                        inserido = true;
                        InserirRecursivo(novaPalavra, filho);
                    }
                }
            }
            if(!inserido){
                if (nodoAtual.Filhos != null) {
                    nodoAtual.Filhos.add(new Nodo(novaPalavra));
                }
            }

        } else if(combinacoes < tamanhoPalavra){

            String raizComum = palavra.substring(0, combinacoes);
            String ramoPalavraAnterior = nodoAtual.Palavra.substring(combinacoes, tamanhoTermo - combinacoes);
            String ramoNovaPalavra = palavra.substring(combinacoes, tamanhoPalavra - combinacoes);

            nodoAtual.Palavra = raizComum;

            Nodo novoNodoPalavraAnterior = new Nodo(ramoPalavraAnterior);
            novoNodoPalavraAnterior.Filhos.addAll(nodoAtual.Filhos);

            nodoAtual.Filhos.clear();
            nodoAtual.Filhos.add(novoNodoPalavraAnterior);

            Nodo novoNodoNovaPalavra = new Nodo(ramoNovaPalavra);
        } else if (combinacoes > tamanhoTermo ) {

            String novaPalavraNodo = nodoAtual.Palavra.substring(tamanhoTermo, tamanhoPalavra);
            Nodo novoNodo = new Nodo(novaPalavraNodo);
            nodoAtual.Filhos.add(novoNodo);
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

                char[] novaPalavra = palavra.toCharArray();
                char[] palavraDoNodo = nodoAtual.Palavra.toCharArray();

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

        int tamanhoTermo = nodoAtual.Palavra.length();
        int tamanhoPalavra = palavra.length();

        if ( (combinacoes == 0) ||
                (nodoAtual == raiz) ||
                ( (combinacoes > 0) && (combinacoes < tamanhoPalavra) && (combinacoes >= tamanhoTermo) )
        ){

            String novaPalavra = palavra.substring(combinacoes, tamanhoPalavra - combinacoes);
            for (Nodo filho : nodoAtual.Filhos) {

                char caractere = novaPalavra.charAt(0);
                String comecaCom = Character.toString(caractere);

                if (filho.Palavra.startsWith(comecaCom)){
                    return BuscarRecursivo(novaPalavra, filho);
                }
            }
            return false;
        } else if (combinacoes == tamanhoTermo) {
            return true;
        } else return false;
    }

    public void Remover(String palavra){

        RemoverRecursivo(palavra, raiz);

    }

    private void RemoverRecursivo(String palavra, Nodo nodoAtual) {

        int combinacoes = CombinaCharConsecutivo(palavra, nodoAtual);

        int tamanhoTermo = nodoAtual.Palavra.length();
        int tamanhoPalavra = palavra.length();

        if ( (combinacoes == 0) ||
                (nodoAtual == raiz) ||
                ( (combinacoes > 0) && (combinacoes < tamanhoPalavra) && (combinacoes >= tamanhoTermo) )
        ){
            String novaPalavra = palavra.substring(combinacoes, tamanhoPalavra - combinacoes);
            for (Nodo filho : nodoAtual.Filhos) {

                char caractere = novaPalavra.charAt(0);
                String comecaCom = Character.toString(caractere);

                if (filho.Palavra.startsWith(comecaCom)){
                    if (novaPalavra == filho.Palavra){
                        if ((long) filho.Filhos.size() == 0){
                            nodoAtual.Filhos.remove(filho);

                        }
                    }
                    RemoverRecursivo(novaPalavra, filho);
                }
            }
        }
    }

    public static void main(String[] args) {

        Arvore arvore = new Arvore();

        arvore.Inserir("romane");
        arvore.Inserir("romanus");
        arvore.Inserir("romulus");
        arvore.Inserir("rubens");
        arvore.Inserir("ruber");
        arvore.Inserir("rubicon");
        arvore.Inserir("rubicundus");

        System.out.println(
                arvore.Buscar("romulus") ?
                "Existe na arvore" :
                "Nao existe na arvore");

        arvore.Remover("romanus");

        System.out.println(
                arvore.Buscar("romulus") ?
                        "Existe na arvore" :
                        "Nao existe na arvore");
    }
}