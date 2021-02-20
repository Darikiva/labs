package manager;

import java.util.concurrent.BrokenBarrierException;

public class SmokerThread extends Thread {
    private int m_number;
    private boolean able_to_smoke;

    SmokerThread(int number) {
        m_number = number;
        able_to_smoke = false;
    }

    public void getPart(int number) {
        if (m_number + number == 4) {
            able_to_smoke = true;
        } else {
            able_to_smoke = false;
        }
    }

    @Override
    public void run() {
        while (true) {
            if (able_to_smoke) {
                try {
                    System.out.println("Smoker " + m_number);
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
            try {
                Manager.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }
}
