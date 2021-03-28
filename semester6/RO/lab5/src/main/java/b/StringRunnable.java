package b;

import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class StringRunnable implements Runnable {

    private final int stringIndex;
    private final CyclicBarrier cyclicBarrier;

    @Override
    public void run() {
        Random random = new Random(System.currentTimeMillis());
        while (!Thread.currentThread().isInterrupted()) {
            StringBuilder stringBuilder = Application.getStringbuilders()[stringIndex];
            switch (random.nextInt(4)) {
                case 0:
                    replaceChars(stringBuilder, 'A', 'C');
                    break;
                case 1:
                    replaceChars(stringBuilder, 'B', 'D');
                    break;
                default:
                    break;
            }
            try {
                cyclicBarrier.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
                Thread.currentThread().interrupt();
            } catch (BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }

    private void replaceChars(StringBuilder stringBuilder, char ch1, char ch2) {
        for (int i = 0; i < stringBuilder.length(); i++) {
            if (stringBuilder.charAt(i) == ch1) {
                stringBuilder.setCharAt(i, ch2);
            } else if (stringBuilder.charAt(i) == ch2) {
                stringBuilder.setCharAt(i, ch1);
            }
        }
    }

    public StringRunnable(int stringIndex, CyclicBarrier cyclicBarrier) {
        this.stringIndex = stringIndex;
        this.cyclicBarrier = cyclicBarrier;
    }
}