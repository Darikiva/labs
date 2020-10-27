package com.testClient;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Vector;

import com.testClient.StraightRun;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int num = in.nextInt();
        Vector<Vector<Double>> matrix = new Vector<>(num);
        matrix.setSize(num);
        matrix.set(0, new Vector<Double>(3));
        matrix.get(0).setSize(3);
        matrix.get(0).set(0, 0.0);
        matrix.get(0).set(1, in.nextDouble());
        matrix.get(0).set(2, in.nextDouble());
        for (int i = 1; i < num - 1; ++i) {
            Vector<Double> new_row = new Vector<>(3);
            new_row.setSize(3);
            for (int j = 0; j < 3; ++j) {
                new_row.set(j, in.nextDouble());
            }
            matrix.set(i, new_row);
        }
        matrix.set(num - 1, new Vector<Double>(3));
        matrix.get(num - 1).setSize(3);
        matrix.get(num - 1).set(2, 0.0);
        matrix.get(num - 1).set(0, in.nextDouble());
        matrix.get(num - 1).set(1, in.nextDouble());

        Vector<Double> f = new Vector<>(num);
        f.setSize(num);
        for(int i = 0; i < num; ++i) {
            f.set(i, in.nextDouble());
        }
        StraightRun strun = new StraightRun(matrix, f);
        ReverseRun rvrun = new ReverseRun(matrix, f);

        int p = num / 2;
        strun.setRange(0, p);
        rvrun.setRange(p, num - 1);
        strun.run();
        rvrun.run();

        try {
            strun.join();
            rvrun.join();
        }
        catch (InterruptedException e) {
            System.out.println("Something's gone wrong");
        }

        /*for(int i = 0; i < strun.getList().size(); ++i) {
            System.out.print(strun.getList().get(i) + " ");
        }
        System.out.println();

        for (Double i : strun.getAlpha()) {
            System.out.print(i + " ");
        }*/
/*

        System.out.println();
        for (Double i: rvrun.getKsi()) {
            System.out.print(i + " ");
        }
*/

        System.out.println();
        Vector<Double> alpha = strun.getAlpha();
        Vector<Double> beta = strun.getBeta();
        Vector<Double> ksi = rvrun.getKsi();
        Vector<Double> theta = rvrun.getTheta();
        Double x_p = (alpha.get(p + 1) * theta.get(0) + beta.get(p + 1)) / (1 - alpha.get(p + 1) * ksi.get(0));
//        System.out.println(x_p);
        FinderStraight finderStraight = new FinderStraight(alpha, beta, x_p);
        FinderReverse finderReverse = new FinderReverse(ksi, theta, x_p);

        finderStraight.run();
        finderReverse.run();

        try {
            finderReverse.join();
            finderStraight.join();
        } catch (InterruptedException e) {

        }

        System.out.println();
        for (Double i: finderStraight.getX()) System.out.print(i + " ");
        for (Double i: finderReverse.getX()) System.out.print(i + " ");
//        Scanner in = new Scanner(System.in);
//        ArrayList<Integer> ar = new ArrayList<>(3);
//        ar.ensureCapacity(3);
//        System.out.print(ar.size());
    }
}
