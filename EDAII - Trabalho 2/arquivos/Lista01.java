package arquivos;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class Lista01 {
    
    public static void main(String[] args) {

        Scanner ler = new Scanner(System.in);
    
        // [ A ] declarando e instanciando uma agenda de contatos
        ArrayList<String> agenda = new ArrayList<>();

        String comando = "";

        while(!comando.equals("e")){

            comando = ler.nextLine();

            if(comando.equals("i")){

                //System.out.printf("Informe o índice:\n");
                //int index = ler.nextInt();
                System.out.printf("Informe um nome:\n");
                String texto = ler.nextLine();

                int pos = agenda.size();

                agenda.add(texto);

                System.out.println("Salvo na posição:" + pos);

                pos = agenda.size();

                System.out.println("Tamanho da Lista:" + pos);
            }

            if(comando.equals("if")){

                System.out.printf("Informe um nome:\n");
                String texto = ler.nextLine();

                if(!agenda.isEmpty()){
                    
                     /*for (String contato: agenda) {

                       if(contato == null){
                            agenda.set(agenda.indexOf(contato),texto);
                            pos = agenda.indexOf(contato);
                            System.out.println("Salvo na posição:" + pos);
                            break;
                        }
                    }*/

                    int n = agenda.size();
                    for (int i = 0; i<n; i++) {

                        if(agenda.get(i) == null){
                            agenda.set(i,texto);
                            int pos = i;
                            System.out.println("Salvo na posição:" + pos);
                            break;
                        }
                        
                    }

                    if(!agenda.contains(texto)){
                        agenda.add(texto);
                    }
                    
                } else {
                    agenda.add(texto);
                }           

                //agenda.add(texto);

                //System.out.println("Salvo na posição:" + pos);

                int pos = agenda.size();

                System.out.println("Tamanho da Lista:" + pos);
            }

            if(comando.equals("ln")){

                // [ C ] mostrando os "n" contatos da agenda (usando o índice)
                // número de elementos da agenda: método size()
                System.out.printf("Percorrendo o ArrayList (usando o índice)\n");
                int n = agenda.size();
                for (int i = 0; i<n; i++) {
                    System.out.printf("Posição %d- %s\n", i, agenda.get(i));
                }

            }

            if(comando.equals("r")){

                System.out.printf("\nInforme a posição a ser excluída:\n");
                int i = ler.nextInt();
            
                try {
                    // [ D ] remove o i-ésimo contato da agenda
                    agenda.set(i,null);
                    //agenda.remove(i);
                } catch (IndexOutOfBoundsException e) {
                    // exceção lançada para indicar que um índice (i)
                    // está fora do intervalo válido (de 0 até agenda.size()-1)
                    System.out.printf("\nErro: posição inválida (%s).",
                    e.getMessage());
                }
            }

            if(comando.equals("lf")){

                // [ E ] mostrando os "n" contatos da agenda (usando for-each)
                System.out.printf("\nPercorrendo o ArrayList (usando for-each)\n");
                int i = 0;
                for (String contato: agenda) {
                    System.out.printf("Posição %d- %s\n", i, contato);
                    i++;
                }
            }

            if(comando.equals("li")){

                // [ F ] mostrando os "n" contatos da agenda (com iterator)
                System.out.printf("\nPercorrendo o ArrayList (usando iterator)\n");
                int i = 0;
                Iterator<String> iterator = agenda.iterator();
                while (iterator.hasNext()) {
                    System.out.printf("Posição %d- %s\n", i, iterator.next());
                    i++;
                }
            }

        }
        
        ler.close();
        
    }
}
