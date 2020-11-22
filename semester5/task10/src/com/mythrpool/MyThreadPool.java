package com.mythrpool;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;

public class MyThreadPool {
    private Queue<Runnable> taskQueue = null;
    private List<PoolTHread> threads = new ArrayList<>();
    private boolean stopped = false;
    int maxSize;

    public int getSize() {
        return taskQueue.size();
    }

    public MyThreadPool(int numThreads) {
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
