package com.testClient;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        try (Socket socket = new Socket("localhost", 3345);
             BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
             ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
             DataInputStream ois = new DataInputStream(socket.getInputStream()); )
        {
            while (!socket.isOutputShutdown()) {
                if (br.ready()) {
                    String clientCommand = br.readLine();
                    String[] for_person = clientCommand.split(" +\t*");
                    if (for_person.length != 3) {
                        System.out.println("Not correct info");
                    } else {
                        Person person = new Person(for_person[0], for_person[1], Integer.valueOf(for_person[2]));
                        oos.writeObject(person);
                        oos.flush();
                    }
                }

            }
            System.out.println("Close");
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}