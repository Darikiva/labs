package com.task5;

import java.util.concurrent.locks.Lock;

public interface FixnumLock extends Lock {
    int getId();
    int register();
    int unregister();
    void lock();
    void unlock();
}
