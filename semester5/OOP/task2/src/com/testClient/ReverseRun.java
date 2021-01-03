package com.testClient;

import java.util.ArrayList;
import java.util.Vector;

public class ReverseRun extends Thread {
    private Vector<Vector<Double>> matrix;
    private Vector<Double> f;
    private int left, right;
    private Vector<Double> ksi = new Vector<>();
    private Vector<Double> theta = new Vector<>();


    ReverseRun() {
    }

    ReverseRun(Vector<Vector<Double>> matrix, Vector<Double> f) {
        this.matrix = matrix;
        this.f = f;
    }

    public Vector<Vector<Double>> getMatrix() {
        return matrix;
    }

    public Vector<Double> getKsi() {
        return ksi;
    }

    public Vector<Double> getTheta() {
        return theta;
    }

    public void setMatrix(Vector<Vector<Double>> list_) {
        this.matrix = list_;
    }

    public void setRange(int left, int right) {
        this.left = left;
        this.right = right;
    }

    public void run() {
        ksi.setSize(right - left + 2);
        theta.setSize(right - left + 2);

        ksi.set(ksi.size() - 1, -matrix.get(matrix.size() - 1).get(0) / matrix.get(matrix.size() - 1).get(1));
        theta.set(theta.size() - 1, f.get(f.size() - 1) / matrix.get(matrix.size() - 1).get(1));

        for (int i = ksi.size() - 2; i >= 0; --i) {
            int index = left + i - 1;
            Double ai = matrix.get(index).get(0);
            Double bi = matrix.get(index).get(2);
            Double ci = matrix.get(index).get(1);
            Double fi = f.get(index);

            Double new_theta = (fi - bi * theta.get(i + 1)) / (ci + bi * ksi.get(i + 1));
            theta.set(i, new_theta);

            Double new_ksi = -ai / (ci + bi * ksi.get(i + 1));
            ksi.set(i, new_ksi);
        }
    }

}
