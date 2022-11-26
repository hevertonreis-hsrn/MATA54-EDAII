import java.util.ArrayList;
import java.util.Scanner;

public class Principal {

    public static void main(String[] args) {

        Arvore arvore = new Arvore();

        Scanner entrada = new Scanner(System.in);
        String comando = "";

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

                Nodo verificaNodo = new Nodo("");
                verificaNodo = Arvore.Buscar(palavra);

                if (verificaNodo == null) {
                    arvore.Inserir(palavra, verbete);
                    System.out.println("palavra inserida no dicionario: " + palavra);
                } else {
                    System.out.println("palavra ja existente: " + palavra);
                }

            }

            if(comando.equals("l")){

                String ordem = entrada.nextLine();

                Armazenamento dadosArquivo = new Armazenamento();
                ArrayList<Object> dadosDicionario = dadosArquivo.lerListaArquivo("dicionario.dat");
                ArrayList<Verbete> dicionario = new ArrayList<>();

                for (Object dado : dadosDicionario) {

                    Verbete palavra = (Verbete)dado;

                    if (palavra != null) {
                        dicionario.add((Verbete)dado);
                    }

                }

                int tamanhoLista = dicionario.size();

                for (int i = 0; i < tamanhoLista; i++) {
                    for (int j = i + 1; j < tamanhoLista; j++) {

                        if (dicionario.get(i).palavraOrigem.compareTo(dicionario.get(j).palavraOrigem) > 0) {

                            String temp = dicionario.get(i).palavraOrigem;
                            dicionario.get(i).palavraOrigem = dicionario.get(j).palavraOrigem;
                            dicionario.get(j).palavraOrigem = temp;
                        }
                    }
                }

                if (ordem.equals("c")) {
                    for (int i = 0; i < tamanhoLista; i++) {
                        System.out.println(dicionario.get(i).palavraOrigem);
                    }
                }

                if (ordem.equals("d")) {
                    for (int i = tamanhoLista-1; i >= 0; i--) {
                        System.out.println(dicionario.get(i).palavraOrigem);
                    }
                }

            }

            if(comando.equals("t")){

                String palavra = entrada.nextLine();
                Nodo resultado = arvore.Buscar(palavra);

                if (resultado == null) {
                    System.out.println("palavra inexistente no dicionario: " + palavra);
                } else {

                    int posicao = resultado.posicaoDicionario;

                    Armazenamento dadosArquivo = new Armazenamento();
                    ArrayList<Object> dicionario = dadosArquivo.lerListaArquivo("dicionario.dat");
                    Verbete termo = (Verbete) dicionario.get(posicao);

                    System.out.println("traducoes da palavra: " + palavra);
                    for(int i = 0; i < termo.traducoes.length; i ++){

                        String traducao = termo.traducoes[i];
                        if(traducao != null)
                            System.out.println(traducao);
                    }
                }
            }

            if(comando.equals("a")){

                String classe = entrada.nextLine();
                String ordem = entrada.nextLine();

                Armazenamento dadosArquivo = new Armazenamento();
                ArrayList<Object> dadosDicionario = dadosArquivo.lerListaArquivo("dicionario.dat");
                ArrayList<Verbete> dicionario = new ArrayList<>();

                for (Object dado : dadosDicionario) {

                    Verbete palavra = (Verbete)dado;

                    if (palavra != null) {
                        if( palavra.classePalavra.equals(classe) ){
                            dicionario.add(palavra);
                        }
                    }

                }

                int tamanhoLista = dicionario.size();

                for (int i = 0; i < tamanhoLista; i++) {
                    for (int j = i + 1; j < tamanhoLista; j++) {

                        if (dicionario.get(i).palavraOrigem.compareTo(dicionario.get(j).palavraOrigem) > 0) {

                            String temp = dicionario.get(i).palavraOrigem;
                            dicionario.get(i).palavraOrigem = dicionario.get(j).palavraOrigem;
                            dicionario.get(j).palavraOrigem = temp;
                        }
                    }
                }

                if (ordem.equals("c")) {
                    for (int i = 0; i < tamanhoLista; i++) {
                        System.out.println(dicionario.get(i).palavraOrigem);
                    }
                }

                if (ordem.equals("d")) {
                    for (int i = tamanhoLista-1; i >= 0; i--) {
                        System.out.println(dicionario.get(i).palavraOrigem);
                    }
                }

            }

            if(comando.equals("c")){

                String palavra = entrada.nextLine();
                Nodo resultado = arvore.Buscar(palavra);

                if (resultado == null) {
                    System.out.println("palavra inexistente no dicionario: " + palavra);
                } else {

                    int posicao = resultado.posicaoDicionario;

                    Armazenamento dadosArquivo = new Armazenamento();
                    ArrayList<Object> dicionario = dadosArquivo.lerListaArquivo("dicionario.dat");
                    Verbete termo = (Verbete) dicionario.get(posicao);

                    String classe = "";

                    if (termo.classePalavra.equals("s")) {
                        classe = "substantivo";
                    } else if (termo.classePalavra.equals("a")) {
                        classe = "adjetivo";
                    } else if (termo.classePalavra.equals("v")) {
                        classe = "verbo";
                    }

                    System.out.println("classe da palavra: " + palavra + " : " + classe);

                }
            }

            if(comando.equals("r")){

                String palavra = entrada.nextLine();
                Arvore.Remover(palavra);
            }

        }

        entrada.close();
    }
}
