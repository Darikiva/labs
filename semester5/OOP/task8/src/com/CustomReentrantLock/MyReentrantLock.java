package com.CustomReentrantLock;

public class MyReentrantLock {
    boolean isLocked;
    long threadId;
    private int lockCount;

    private final Object sync_obj = new Object();

    public MyReentrantLock() {
        isLocked = false;
        threadId = 0;
        lockCount = 0;
    }

    synchronized public void lock() throws InterruptedException {
        while (isLocked && Thread.currentThread().getId() != threadId) {
            wait();
        }
//        System.out.println("Thread " + Thread.currentThread().getId() + " locked this locker");
        isLocked = true;
        threadId = Thread.currentThread().getId();
        ++lockCount;
    }

    synchronized public void unlock() {
        if (!isLocked || this.threadId != Thread.currentThread().getId()) {
            return;
        }
        -- lockCount;
        if (lockCount == 0) {
//            System.out.println("Thread " + Thread.currentThread().getId() + " UNlocked this locker");
            isLocked = false;
            notify();
        }
    }
}
