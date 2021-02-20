package manager;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.CyclicBarrier;

public class Manager {
    static CyclicBarrier barrier;

    public void goToWork() {
        final ArrayList<SmokerThread> smokers = new ArrayList<>(3);
        for (int i = 0; i < 3; ++i) {
            smokers.add(new SmokerThread(i + 1));
        }
        barrier = new CyclicBarrier(3, new Runnable(){
			@Override
			public void run() {
                Random random = new Random();
                int number = Math.abs(random.nextInt()) % 3 + 1;
                System.out.println("Generate " + number);
                for (int i = 0; i < 3; ++i) {
                    smokers.get(i).getPart(number);
                }
			}
        });
        for (int i = 0; i < 3; ++i) {
            smokers.get(i).start();
        }
    }
}
