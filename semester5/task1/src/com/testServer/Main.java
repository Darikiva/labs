package com.testServer;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import com.testClient.Person;


public class Main {
    static public void main(String[] args) throws InterruptedException {
        try (ServerSocket server = new ServerSocket(3345)) {

            Socket client = server.accept();

            ObjectOutputStream out = new ObjectOutputStream(client.getOutputStream());
            ObjectInputStream in = new ObjectInputStream(client.getInputStream());

            while (!client.isClosed()) {
                try {
                    Person entry = (Person) in.readObject();
                } catch (ClassNotFoundException e) {
                    System.out.println(e);
                }
                System.out.println("good");



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