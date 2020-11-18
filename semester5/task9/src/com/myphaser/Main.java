package com.myphaser;

public class Main {

    public static void main(String[] args) {
        MyPhaser ph = new MyPhaser(4);
        ph.arrive();
        ph.register();
        new Thread() {public void run(){
            try {
                ph.arriveAndAwait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }}.start();
        ph.arrive();
        ph.arrive();
        ph.arriveAndDeregister();
    }
}
