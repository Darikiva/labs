package com.testClient;

import java.util.Vector;

public class FinderReverse extends Thread{
    private Vector<Double> ksi, theta, x;

    FinderReverse(Vector<Double> ksi, Vector<Double> theta, Double x_p) {
        this.ksi = ksi;
        this.theta = theta;
        x = new Vector<>(ksi.size() - 1);
        x.setSize(ksi.size() - 1);
        x.set(0, x_p);
    }

    public Vector<Double> getX() {
        return x;
    }

    public void run() {
        for(int i = 1; i < x.size(); ++i) {
            x.set(i, ksi.get(i + 1) * x.get(i - 1) + theta.get(i + 1));
        }
        x.remove(0);
    }
}
