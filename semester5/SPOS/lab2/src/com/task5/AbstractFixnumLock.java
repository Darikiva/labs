package com.task5;


import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;


public abstract class AbstractFixnumLock implements FixnumLock{
    private int numberOfThreads;
    private List<AbstractMap.SimpleEntry<Long, Integer>> registeredThreads;
    private List<Integer> freeID;

    private static final Object syncObj = new Object();

    AbstractFixnumLock(int numberOfThreads) {
        this.numberOfThreads = numberOfThreads;
        this.registeredThreads = new ArrayList<>();
        initializeFreeID();
    }

    private void initializeFreeID() {
        freeID = new ArrayList<>();
        for (int i = 0; i < numberOfThreads; i++) {
            this.freeID.add(i);
        }
    }

    @Override
    public int getId() {
        for (AbstractMap.SimpleEntry<Long, Integer> item : registeredThreads) {
            if (item.getKey() == Thread.currentThread().getId()) {
                return item.getValue();
            }
        }
        return -1;
    }

    @Override
    public int register() {
        synchronized (syncObj) {
            int id = getId();
            if (!freeID.isEmpty()) {
                if (id != -1) {
//                    System.out.println("Thread with id " + id + " already registered.");
                } else {
                    registeredThreads.add(new AbstractMap.SimpleEntry<>(Thread.currentThread().getId(), freeID.get(0)));
                    freeID.remove(freeID.get(0));
//                    System.out.println("Thread with id " + getId() + " is registered.");
                    return getId();
                }
            } else {
//                System.out.println("Threads number limit already reached. Can't register thread with actual id " + Thread.currentThread().getId());
            }
            return -1;
        }
    }

    @Override
    public int unregister() {
        synchronized (syncObj) {
            int id = getId();
            if (id != -1) {
                registeredThreads.remove(new AbstractMap.SimpleEntry<>(Thread.currentThread().getId(), id));
                freeID.add(id);
//                System.out.println("Unregister thread with id " + id + ".");
                return id;
            } else {
//                System.out.println("Thread with actual id " + Thread.currentThread().getId() + " is not registered.");
            }
            return -1;
        }
    }

    private void reset() {
        synchronized (syncObj) {
            registeredThreads.clear();
            initializeFreeID();
        }
    }
}
