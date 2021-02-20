package main;

public class PoolThread extends Thread {
    private boolean stopped = false;

    @Override
    public void run() {
        while (!stopped) {
            if (Manager.semaphore.compareAndSet(false, true)) {
                if (Manager.honey_pot == Manager.MAX_CAPACITY) {
                    Manager.semaphore.set(false);
                    continue;
                }
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                ++Manager.honey_pot;
                System.out.println("Put 1 dose of honey; capacity = " + Manager.honey_pot);
                if (Manager.honey_pot == Manager.MAX_CAPACITY) {
                    Manager.vinnie.wakeUp();
                }
                Manager.semaphore.set(false);
            }
        }
    }

    public synchronized void doStop() {
        stopped = true;
        // this.interrupt();
    }

    public synchronized boolean isStopped() {
        return stopped;
    }
}