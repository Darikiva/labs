package com.CustomCyclicBarrier;

public class MyCyclicBarrier {
    int initParties;
    int partiesAwait;
    Runnable cbEvent;

    public MyCyclicBarrier(int parties, Runnable cbEvent) {
        initParties = parties;
        partiesAwait = parties;
        this.cbEvent = cbEvent;
    }

    public MyCyclicBarrier(int parties) {
        initParties = parties;
        partiesAwait = parties;
        this.cbEvent = null;
    }

    public synchronized void await() throws InterruptedException {
        --partiesAwait;
        System.out.println("Thread " + Thread.currentThread().getId() + " waiting for : " + partiesAwait + " parties");
        if (partiesAwait > 0) {
            this.wait();
        } else {
            partiesAwait = initParties;

            notifyAll();

            if (cbEvent != null) cbEvent.run();
        }
    }
}
