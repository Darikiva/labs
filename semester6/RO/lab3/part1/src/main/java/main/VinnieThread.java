package main;

public class VinnieThread extends Thread{
    private volatile boolean is_sleeping;

    public void wakeUp() {
        is_sleeping = false;
    }

    private void fallAsleep() {
        is_sleeping = true;
    }

    @Override
    public void run() {
        while (true) {
            if (!is_sleeping) {
                System.out.println("Vinnie eat honey");
                Manager.honey_pot = 0;
                fallAsleep();
            }
        }
    }
}
