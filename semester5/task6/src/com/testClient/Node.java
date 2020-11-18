package com.testClient;

public class Node {
    private Node next;
    private int value;

    public Node getNext() {
        return next;
    }

    public int getValue() {
        return value;
    }

    public void setNext(Node next) {
        this.next = next;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public Node(Node next, int value) {
        this.next = next;
        this.value = value;
    }
}
