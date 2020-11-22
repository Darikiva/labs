package com.nonblockqueue;

import java.util.concurrent.atomic.AtomicReference;

public class NonBlockingQueue {
    private Node dummy = new Node(0, null);
    private AtomicReference<Node> head = new AtomicReference<>(dummy);
    private AtomicReference<Node> tail = new AtomicReference<>(dummy);

    public AtomicReference<Node> getTail() {
        return tail;
    }

    static public class Node {
        public int val;
        public AtomicReference<Node> next;

        Node(int val, Node next) {
            this.val = val;
            this.next = new AtomicReference<>(next);
        }
        public String toString() {
            return Integer.toString(val);
        }
    }
//    public NonBlockingQueue() {
//        head = tail = new AtomicReference<>(new Node(null, 0));
//    }

    public void enqueue(int value) {
        Node new_node = new Node(value, null);
        while (true) {
            Node currentTail = tail.get();
//            System.out.println(currentTail);
            Node tailNext = currentTail.next.get();
//            System.out.println(tailNext);
            if (currentTail == tail.get()) {
                if (tailNext != null) {
                    tail.compareAndSet(currentTail, tailNext);
                } else {
                    if (currentTail.next.compareAndSet(null, new_node)){
                        tail.compareAndSet(currentTail, new_node);
                        return;
                    }
                }
            }
        }
    }

    public boolean dequeue() {
        while (true) {
            Node first = head.get();
            Node last = tail.get();
            Node next = first.next.get();
            if (first == head.get()) {
                if (first == last) {
                    if (next == null) return false;
                    tail.compareAndSet(last, next);
                } else {
                    int val = next.val;
                    if (head.compareAndSet(first, next))
                        return true;
                }
            }
        }
    }

    public String toString() {
        StringBuilder answer = new StringBuilder();
        Node tmp = head.get();
        int counter = 0;
        while (tmp != null) {
            ++counter;
            answer.append(tmp.val);
            if(tmp.next != null) {
                if (counter < 11) {
                    answer.append(' ');
                } else {
                    counter = 0;
                    answer.append('\n');
                }
            }
            tmp = tmp.next.get();
        }
        return answer.toString();
    }
}
