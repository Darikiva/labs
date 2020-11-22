package com.mythrpool;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.Queue;

public class Main {

    public static void main(String[] args) throws InterruptedException {
        MyThreadPool pool = new MyThreadPool(5);
        for (int i = 0; i < 20; ++i) {
            int finalI = i;
            pool.execute(new Runnable() {
                @Override
                public void run() {
                    try {
                        Thread.sleep((finalI % 4)*500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println(finalI);
                }
            });
        }
        while (pool.getSize() != 0);
        pool.stop();
    }
}
