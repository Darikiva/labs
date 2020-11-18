package com.noIdea;

import com.nonblockqueue.*;

public class Main {

    public static void main(String[] args) {
        NonBlockingQueue helo = new NonBlockingQueue();
        for (int i = 0; i < 10; ++i) {
            int finalI = i;
            Thread thr = new Thread(() -> {
                for (int j = finalI * 10; j < (finalI  + 1) * 10; ++j)
                helo.enqueue(j);
            });
            thr.start();
            helo.enqueue(i);
        }

        for (int i = 0; i < 10; ++i) {
            Thread thread = new Thread(() -> {
                for (int j = 0; j < 5; ++j)
                    helo.dequeue();
            });
            thread.start();
        }
        System.out.println(helo);
    }
}
