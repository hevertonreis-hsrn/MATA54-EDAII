import java.io.Serializable;
import java.util.ArrayList;

class Verbete implements Serializable{

    public Verbete(){

    }

    public Verbete(String palavra, String classe, String[] traducoes){
        palavraOrigem = palavra;
        classePalavra = classe;
        this.traducoes = traducoes;
    }

    public String palavraOrigem;
    public String classePalavra;
    public String[] traducoes = new String[10];

}

public class Dicionario {

    static Armazenamento dadosArquivo = new Armazenamento();

    public static int InserirDicionario(Verbete verbete){

        int posicao = 0;
        ArrayList<Object> dicionario = dadosArquivo.lerListaArquivo("dicionario.dat");

        if(dicionario == null){
            dicionario = new ArrayList<>();
            dicionario.add(verbete);
            dadosArquivo.gravarListaArquivo(dicionario, "dicionario.dat");
            return dicionario.size() - 1;
        } else if(!dicionario.isEmpty()) {

            int n = dicionario.size();
            for (int i = 0; i < n; i++) {

                if (dicionario.get(i) == null) {
                    dicionario.set(i, verbete);
                    posicao = i;
                    dadosArquivo.gravarListaArquivo(dicionario, "dicionario.dat");
                    System.out.println("Salvo na posição:" + posicao);
                    return posicao;
                }
            }

            dicionario.add(verbete);
            dadosArquivo.gravarListaArquivo(dicionario, "dicionario.dat");
            return dicionario.size() - 1;
        }

        return -1;
    }
}
