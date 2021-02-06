package main_b;

import javax.swing.JSlider;

public class MyThread extends Thread {
    JSlider slider;
    volatile boolean prioritized;
    int sign;
    boolean running;

    MyThread(JSlider slider, int sign) {
        this.slider = slider;
        this.sign = sign;
        this.running = true;
    }

    public JSlider getSlider() {
        return slider;
    }

    public void setSlider(JSlider slider) {
        this.slider = slider;
    }

    public void setRunning(boolean running) {
        this.running = running;
    }

    @Override
    public void run() {
        // TODO Auto-generated method stub
        // super.run();
        while (running) {
            // if (prioritized) {
                synchronized (slider) {
                    if (sign == 1 && slider.getValue() < 90) {
                        slider.setValue(slider.getValue() + 2);
                    } else if (sign == -1 && slider.getValue() > 10) {
                        slider.setValue(slider.getValue() - 2);
                    }
                    try {
                        Thread.sleep(500);
                    } catch (InterruptedException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                }
            // }
            // System.out.println("wow ");
        }

    }

}
