package com.CustomCyclicBarrier;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class MyClass {
    private MyCyclicBarrier cyclicBarrier;
    private List<List<Integer>> partialResults
            = Collections.synchronizedList(new ArrayList<>());
    private Random random = new Random();
    private int NUM__PARTIAL__RESULTS;
    private int NUM__WORKERS;

    class ThreadHelper extends Thread {

        private int time;

        public ThreadHelper(int time) {
            this.time = time;
        }

        @Override
        public void run() {
            try {
                Thread.sleep(time);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            try {
                cyclicBarrier.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void runSimulation(int numWorkers, int numberOfPartialResults) {
        Runnable w = new Runnable() {
            @Override
            public void run() {
                System.out.println("ended");
            }
        };
        cyclicBarrier = new MyCyclicBarrier(numWorkers, w);
        for (int i = 0; i < numWorkers; ++i) {
            ThreadHelper hel = new ThreadHelper((55 - i * 10) * 500);
            hel.start();
        }

        for (int i = 0; i < numWorkers; ++i) {
            ThreadHelper hel = new ThreadHelper((i + 1) * 500);
            hel.start();
        }
    }
}
