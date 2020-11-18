package com.testClient;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Future;

public class MyThreadPool {
    private Queue<Runnable> taskQueue = null;
    private List<PoolTHread> threads = new ArrayList<>();
    private boolean stopped = false;
    int maxSize;

    public MyThreadPool(int numThreads, int maxThreads) {
        taskQueue = new ConcurrentLinkedQueue<Runnable>();

        for (int i = 0; i < numThreads; ++i) {
            threads.add(new PoolTHread(taskQueue));
        }
        for(PoolTHread thread: threads) {
            thread.start();
        }
    }

    public synchronized void execute(Runnable task){
        if (!stopped) {
            this.taskQueue.add(task);
        }
    }

    public synchronized void stop() {
        stopped = true;
        for (PoolTHread thr: threads) {
            thr.doStop();
        }
    }
}
