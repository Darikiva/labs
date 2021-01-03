package com.task5;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) throws InterruptedException {
        ImprovedBakeryLock lock = new ImprovedBakeryLock(5);
        MyInt var = new MyInt();
        ArrayList<Thread> thrs = new ArrayList<>(5);
        for (int i = 0; i < 5; ++i) {
            thrs.add(new Thread(() -> {
//                    lock.lock();
                for (int j = 0; j < 5000000; ++j)
                {
                    lock.lock();
                    var.increment();
                    lock.unlock();
                }
//                System.out.println(finalI);
//                    lock.unlock();
//                    lock.lock();
//                    lock.unlock();
            }));
            thrs.get(i).start();
        }
        for(int i = 0; i < thrs.size(); ++i) {
            thrs.get(i).join();
        }
        System.out.println("Var = " + var);
    }
}
