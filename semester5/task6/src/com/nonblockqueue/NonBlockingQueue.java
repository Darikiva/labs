package com.nonblockqueue;

public class NonBlockingQueue {
    private Node head = null;
    private Node tail = null;

    public NonBlockingQueue() {
        head = tail = new Node(null, 0);
    }

    private synchronized boolean compareAndSwap(Node value, Node expectedValue, Node newValue) {
        if (value == expectedValue) {
            if (value != null) {
                value.setNext(newValue);
            }
            return true;
        }
        return false;
    }

    public void enqueue(int value) {
        Node new_node = new Node(null, value);
        Node tail = null;

        while (true) {
            tail = this.tail;
            Node next = tail.getNext();
            if (tail == this.tail) {
                if (next == null){
                    synchronized (this) {
                        if (tail.getNext() == next) {
                            tail.setNext(new_node);
                            break;
                        }
                    }
                } else {
                    synchronized (this) {
                        if (this.tail == tail) {
                            this.tail = next;
                        }
                    }
                }
            }
        }
        synchronized (this) {
            if (this.tail == tail) {
                this.tail = new_node;
            }
        }
    }

    public boolean dequeue() {
        while (true) {
            Node head = this.head;
            Node tail = this.tail;
            Node next = head.getNext();
            if (head == this.head) {
                if (head == tail) {
                    if (next == null) {
                        return false;
                    }
                    synchronized (this) {
                        if (this.tail == tail) {
                            this.tail = next;
                        }
                    }
                } else {
                    int pvalue = next.getValue();
                    synchronized (this) {
                        if (this.head == head) {
                            this.head = next;
                            break;
                        }
                    }
                }
            }
        }
        return true;
    }

    public String toString() {
        StringBuilder answer = new StringBuilder();
        Node tmp = head;
        int counter = 0;
        while (tmp != null) {
            ++counter;
            answer.append(tmp.getValue());
            if(tmp.getNext() != null) {
                if (counter < 11) {
                    answer.append(' ');
                } else {
                    counter = 0;
                    answer.append('\n');
                }
            }
            tmp = tmp.getNext();
        }
        return answer.toString();
    }
}
