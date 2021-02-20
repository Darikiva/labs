package main;

import java.util.concurrent.atomic.AtomicBoolean;

public class Manager {
    static Integer honey_pot = 20;
    static AtomicBoolean semaphore = new AtomicBoolean();
    static final int MAX_CAPACITY = 20;
    static VinnieThread vinnie = new VinnieThread();

    public void goToWork() {
        vinnie.start();
        MyThreadPool pool = new MyThreadPool(10);
    }
}
