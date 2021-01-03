package com.task5;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicIntegerArray;
import java.util.concurrent.locks.Condition;

public class ImprovedBakeryLock extends AbstractFixnumLock implements java.util.concurrent.locks.Lock {
    AtomicIntegerArray ticket;
    AtomicIntegerArray overs;
    AtomicIntegerArray entering;
    int threads;
    AtomicInteger counter;
    AtomicInteger count_overs;
    boolean flag;

    private final Object syncObject = new Object();

    ImprovedBakeryLock(int numberOfThreads) {
        super(numberOfThreads);
        counter = new AtomicInteger(1);
        count_overs = new AtomicInteger(0);
        threads = numberOfThreads;
        ticket = new AtomicIntegerArray(numberOfThreads);
        overs = new AtomicIntegerArray(numberOfThreads);
        entering = new AtomicIntegerArray(numberOfThreads);

    }

    @Override
    public void lock() {
        register();
        int pid = getId();
        entering.set(pid, 1);
        synchronized (syncObject)
        {
            if (counter.get() == threads + 1) {
                overs.set(pid, count_overs.incrementAndGet());
                counter.set(1);
            } else {
                overs.set(pid, count_overs.get());
            }
//            ticket.set(pid, counter.getAndIncrement());
        }
        ticket.set(pid, counter.getAndIncrement());
        entering.set(pid, 0);
        for (int i = 0; i < ticket.length(); ++i) {
            if (i != pid) {
                while (entering.get(i) == 1){
                    Thread.yield();
                }
                while (ticket.get(i) != 0 && (( overs.get(pid) > overs.get(i))
                        || (overs.get(pid) == overs.get(i) && ticket.get(pid) > ticket.get(i)))) {
                    Thread.yield();
                }
            }
        }
    }

    @Override
    public void lockInterruptibly() throws InterruptedException {

    }

    @Override
    public boolean tryLock() {
        return false;
    }

    @Override
    public boolean tryLock(long time, TimeUnit unit) throws InterruptedException {
        return false;
    }

    @Override
    public void unlock() {
        int pid = getId();
        ticket.set(pid, 0);
    }

    @Override
    public Condition newCondition() {
        return null;
    }
}
