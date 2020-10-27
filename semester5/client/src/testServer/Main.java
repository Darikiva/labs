package testServer;

import com.testClient.Person;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {
    static public void main(String[] args) throws InterruptedException {
        try (ServerSocket server = new ServerSocket(3345)) {

            Socket client = server.accept();

            ObjectOutputStream out = new ObjectOutputStream(client.getOutputStream());
            ObjectInputStream in = new ObjectInputStream(client.getInputStream());

            Person entry = null;
            while (!client.isClosed()) {
                try {
                    entry = (Person) in.readObject();

                } catch (ClassNotFoundException e) {
                    System.out.println(e);
                }
                assert entry != null;
                System.out.println(entry.getName_());
                System.out.println(entry.getSurname_());
                System.out.println(entry.getAge_());
                for(int i = 0; i < entry.getAge_(); ++i) {
                    System.out.print(entry.getArr()[i]);
                    System.out.print(" ");
                }



                out.flush();
            }

            in.close();
            out.close();
            client.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}