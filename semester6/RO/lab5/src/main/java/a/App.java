package a;
import java.util.Arrays;
import java.util.Random;

public class App {

    public static void main(String[] args) {
        int size = 150;
        int partsNumber = 3;
        Rookie.fillFinishedArray(3);
        // 1 - turned right, -1 - turned left
        int[] rookies = new int[size];

        MyCyclicBarrier cyclicBarrier = new MyCyclicBarrier(partsNumber);
        Random random = new Random(System.currentTimeMillis());

        for (int i = 0; i < size; i++) {
            if (random.nextBoolean()) {
                rookies[i] = 1;
            } else {
                rookies[i] = -1;
            }
        }

        Thread[] threads = new Thread[partsNumber];

        for (int i = 0; i < partsNumber; i++) {
            threads[i] = new Thread(new Rookie(rookies, i, 50 * i, 50 * (i + 1), cyclicBarrier));
        }

        for (int i = 0; i < partsNumber; i++) {
            threads[i].start();
        }

        for (int i = 0; i < partsNumber; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
                Thread.currentThread().interrupt();
            }
        }

        System.out.println(Arrays.toString(rookies));
    }
}