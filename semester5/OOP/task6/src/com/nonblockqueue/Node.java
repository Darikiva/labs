package com.nonblockqueue;

import java.util.concurrent.atomic.AtomicReference;

public class Node {
    private AtomicReference<Node> next;
    private int value;

    public AtomicReference<Node> getNext() {
        return next;
    }

    public int getValue() {
        return value;
    }

    public Node(AtomicReference<Node> next, int value) {
        this.next = next;
        this.value = value;
    }
}
