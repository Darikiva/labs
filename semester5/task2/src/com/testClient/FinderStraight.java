package com.testClient;

import java.util.Vector;

public class FinderStraight extends Thread{
    private Vector<Double> alpha, beta, x;
    private Double x_p;

    FinderStraight(Vector<Double> alpha, Vector<Double> beta, Double x_p) {
        this.alpha = alpha;
        this.beta = beta;
        x = new Vector<>(alpha.size());
        x.setSize(alpha.size() - 1);
        x.set(x.size() - 1, x_p);
    }

    public Vector<Double> getX() {
        return x;
    }

    public void run() {
        for(int i = x.size() - 2; i >= 0; --i) {
            x.set(i, alpha.get(i + 1) * x.get(i + 1) + beta.get(i + 1));
        }
    }
}
