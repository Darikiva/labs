package com.mythrpool;

import java.util.Queue;

public class PoolTHread extends Thread{
    private Queue<Runnable> taskQueue = null;
    private boolean stopped = false;

    public PoolTHread(Queue<Runnable> queue) {
        taskQueue = queue;
    }

    @Override
    public void run() {
        while (!stopped) {
            Runnable runnable = taskQueue.poll();
            if (runnable != null) runnable.run();
        }
    }

    public synchronized void doStop() {
        stopped = true;
        this.interrupt();
    }

    public synchronized boolean isStopped() {
        return stopped;
    }
}
