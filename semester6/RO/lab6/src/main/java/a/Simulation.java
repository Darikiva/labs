package a;

import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicBoolean;

public class Simulation implements Runnable {
    private Integer[][] field;
    private int row_number;
    private int column_number;
    Buffer buffer;
    CyclicBarrier barrier;

    Integer[][] getField() {
        return field;
    }

    Simulation(Buffer buffer, CyclicBarrier barrier, int row_number, int column_number) {
        this.buffer = buffer;
        this.barrier = barrier;
        this.row_number = row_number;
        this.column_number = column_number;
        field = new Integer[row_number][column_number];
        for (int i = 0; i < row_number; ++i) {
            Random random = new Random();
            for (int j = 0; j < column_number; ++j) {
                field[i][j] = Math.abs(random.nextInt() % (Manager.CIVILIZATION_NUMBER + 1));
            }
        }
    }

    public void update() {

        for (int i = 0; i < field.length; ++i) {
            for (int j = 0; j < field[0].length; ++j) {
                System.out.print(field[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
        System.out.println();
    }

    @Override
    public void run() {
        while (true) {
            // update();
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            buffer.putInSecondary(field);
        }
    }
}
