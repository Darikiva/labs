package com.CustomReentrantLock;

public class MyReentrantLock {
    boolean isLocked;
    long threadId;
    private int lockCount;

    public MyReentrantLock() {
        isLocked = false;
        threadId = 0;
        lockCount = 0;
    }

    synchronized public void lock() throws InterruptedException {
        if (threadId == Thread.currentThread().getId()) return;
        while (isLocked) {
            wait();
        }
        System.out.println("Thread " + Thread.currentThread().getId() + " locked this locker");
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
            System.out.println("Thread " + Thread.currentThread().getId() + " UNlocked this locker");
            isLocked = false;
            notify();
        }
    }
}
