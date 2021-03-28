package a;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.concurrent.atomic.AtomicBoolean;


public class Rookie implements Runnable {

    private static final ArrayList<Boolean> partFinished = new ArrayList<>();

    private static final AtomicBoolean finished = new AtomicBoolean(false);
    
    private final int[] rookies;
    private final int partIndex;
    private final int leftIndex;
    private final int rightIndex;
    private final MyCyclicBarrier cyclicBarrier;
    
    public Rookie(int[] rookies, int partIndex, int leftIndex, int rightIndex, MyCyclicBarrier cyclicBarrier) {
        this.rookies = rookies;
        this.partIndex = partIndex;
        this.leftIndex = leftIndex;
        this.rightIndex = rightIndex;
        this.cyclicBarrier = cyclicBarrier;
    }

    @Override
    public void run() {
        while (!finished.get()) {
            boolean thisPartFinished = partFinished.get(partIndex);
            if (!thisPartFinished) {
                System.out.println(Arrays.toString(rookies));
                boolean formatted = true;
                for (int i = leftIndex; i < rightIndex - 1; i++) {
                    if (rookies[i] != rookies[i + 1]) {
                        rookies[i] *= -1;
                        formatted = false;
                    }
                }
                if (formatted) {
                    finish();
                }
            }
            try {
                cyclicBarrier.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
                Thread.currentThread().interrupt();
            }
        }
    }

    private void finish() {
        System.out.println("Part " + partIndex + " finished");
        partFinished.set(partIndex, true);

        for (boolean currentPartFinished : partFinished) {
            if (!currentPartFinished) {
                return;
            }
        }
        finished.set(true);
    }

    public static void fillFinishedArray(int partsNumber) {
        for (int i = 0; i < partsNumber; i++) {
            partFinished.add(false);
        }
    }


}