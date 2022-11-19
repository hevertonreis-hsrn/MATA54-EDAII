import java.util.List;

class Verbete {

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

    public static int InserirDicionario(Verbete verbete, List<Verbete> dicionario){

        int posicao = 0;

        if(!dicionario.isEmpty()){

            int n = dicionario.size();
            for (int i = 0; i<n; i++) {

                if(dicionario.get(i) == null){
                    dicionario.set(i,verbete);
                    posicao = i;
                    System.out.println("Salvo na posição:" + posicao);
                    return posicao;
                }
            }

            if(!dicionario.contains(verbete)){
                dicionario.add(verbete);
                return dicionario.size() - 1;
            }

        } else {
            dicionario.add(verbete);
            return dicionario.size() - 1;
        }

        return -1;
    }
}
