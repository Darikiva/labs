package com.CustomReentrantLock;

public class MyClass {

    static void simulation() {
        System.out.println("wow");
        MyReentrantLock reentrantLock = new MyReentrantLock();
        int a = 0;
        for (int i = 0; i < 5; ++i) {
            int finalI = i;
            Thread new_th = new Thread() {
                @Override
                public void run() {
                    try {
                        reentrantLock.lock();
                        Thread.sleep(finalI * (500));
                        reentrantLock.unlock();

                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            };
            new_th.start();
        }
    }
}
