import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class Armazenamento {

    public void gravarListaArquivo(ArrayList<Object> lista, String nomeArquivo){

        File arquivo = new File(nomeArquivo);

        try {

            arquivo.delete();
            arquivo.createNewFile();
            
            FileOutputStream fluxoArquivo = new FileOutputStream(arquivo);
            ObjectOutputStream fluxoObjeto = new ObjectOutputStream(fluxoArquivo);

            fluxoObjeto.writeObject(lista);
            fluxoObjeto.close();

        } catch (IOException erro) {
            System.out.println("Erro: " + erro.getMessage());
        }

    }

    public ArrayList<Object> lerListaArquivo(String nomeArquivo){

        Object dados = null;

        try {

            File arquivo = new File(nomeArquivo);

            if (arquivo.exists()) {
                FileInputStream fluxoArquivo = new FileInputStream(arquivo);
                ObjectInputStream fluxoObjeto = new ObjectInputStream(fluxoArquivo);
                dados = fluxoObjeto.readObject();
                fluxoObjeto.close();
            }
            
        } catch (IOException erro1) {
            return null;
        } catch(ClassNotFoundException erro2) {
            return null;
        }

        return (ArrayList<Object>) dados;
    }

    public static void gravarObjetoArquivo(Object dicionario, String nomeArquivo){

        File arquivo = new File(nomeArquivo);

        try {

            arquivo.delete();
            arquivo.createNewFile();

            FileOutputStream fluxoArquivo = new FileOutputStream(arquivo);
            ObjectOutputStream fluxoObjeto = new ObjectOutputStream(fluxoArquivo);

            fluxoObjeto.writeObject(dicionario);
            fluxoObjeto.close();

        } catch (IOException erro) {
            System.out.println("Erro: " + erro.getMessage());
        }

    }

    public static Object lerObjetoArquivo(String nomeArquivo){

        Object dados = null;

        try {

            File arquivo = new File(nomeArquivo);

            if (arquivo.exists()) {
                FileInputStream fluxoArquivo = new FileInputStream(arquivo);
                ObjectInputStream fluxoObjeto = new ObjectInputStream(fluxoArquivo);
                dados = fluxoObjeto.readObject();
                fluxoObjeto.close();
            }

        } catch (IOException erro1) {
            return null;
        } catch(ClassNotFoundException erro2) {
            return null;
        }

        return (Nodo) dados;
    }
    
}