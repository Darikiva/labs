package com.testClient;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class MyPhaser {
    private int phase;
    private int parties;
    private int arrived, unarrived;
    Map<Integer, Runnable> onAdvance;

    public MyPhaser(int parties) {
        this.parties = parties;
        this.unarrived = parties;
        this.arrived = 0;
        onAdvance = new HashMap<>();
    }

    public void setOnAdvance(Runnable action, int phase) {
        onAdvance.put(phase, action);
    }

    public int getPhase() {
        return phase;
    }

    public int getParties() {
        return parties;
    }

    public int getArrived() {
        return arrived;
    }

    public int getUnarrived() {
        return unarrived;
    }

    private boolean tryOpen() {
        if (unarrived == 0) {
            if (onAdvance.get(phase) != null) onAdvance.get(phase).run();
            arrived = 0;
            unarrived = parties;
            notifyAll();
            ++phase;
            return true;
        } else {
            return false;
        }
    }

    public synchronized void register() {
        ++parties;
        ++unarrived;
    }

    public synchronized void arrive() {
        ++arrived;
        --unarrived;
        tryOpen();
    }

    public synchronized void arriveAndDeregister() {
        --parties;
        --unarrived;
        tryOpen();
    }

    public synchronized void arriveAndAwait() throws InterruptedException {
        ++arrived;
        --unarrived;
        if (!tryOpen()) {
            this.wait();
        }
    }


}
