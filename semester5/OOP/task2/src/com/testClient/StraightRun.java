package com.testClient;

import java.util.ArrayList;
import java.util.Vector;

public class StraightRun extends Thread {
    private Vector<Vector<Double>> matrix;
    private Vector<Double> f;
    private int left, right;
    private Vector<Double> alpha = new Vector<>();
    private Vector<Double> beta = new Vector<>();

    StraightRun() {
    }

    StraightRun(Vector<Vector<Double>> matrix, Vector<Double> f) {
        this.matrix = matrix;
        this.f = f;
    }

    public Vector<Vector<Double>> getList() {
        return matrix;
    }

    public Vector<Double> getAlpha () {
        return alpha;
    }

    public Vector<Double> getBeta () {
        return beta;
    }

    public void setList(Vector<Vector<Double>> matrix) {
        this.matrix = matrix;
    }

    public void setRange(int left, int right) {
        this.left = left;
        this.right = right;
    }

    public void run() {
        alpha.setSize(right - left + 2);
        beta.setSize(right - left + 2);

        alpha.set(1, -matrix.get(0).get(2) / matrix.get(0).get(1));
        beta.set(1, f.get(0) / matrix.get(0).get(1));

        for (int i = left + 1; i <= right; ++i) {
            Double ai = matrix.get(i).get(0);
            Double bi = matrix.get(i).get(2);
            Double ci = matrix.get(i).get(1);
            Double fi = f.get(i);

            Double new_beta = (fi - ai * beta.get(i)) / (ai * alpha.get(i) + ci);
            beta.set(i + 1, new_beta);

            Double new_alpha = -bi / (ai * alpha.get(i) + ci);
            alpha.set(i + 1, new_alpha);
        }

    }
}
