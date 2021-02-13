package main;

import javax.swing.JSlider;

public class MyThread extends Thread {
    JSlider m_slider;
    Side m_side;
    boolean m_running;

    MyThread(JSlider slider, Side side) {
        this.m_slider = slider;
        this.m_side = side;
        this.m_running = true;
    }

    public JSlider getSlider() {
        return m_slider;
    }

    public void setSlider(JSlider slider) {
        this.m_slider = slider;
    }

    public void setRunning(boolean running) {
        this.m_running = running;
    }

    @Override
    public void run() {
        while (true) {
            while (m_running) {
                synchronized (m_slider) {
                    if (m_side == Side.RIGHT && m_slider.getValue() < 90) {
                        m_slider.setValue(m_slider.getValue() + 2);
                    } else if (m_side == Side.LEFT && m_slider.getValue() > 10) {
                        m_slider.setValue(m_slider.getValue() - 2);
                    }
                    try {
                        Thread.sleep(500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                // System.out.println(m_slider.getValue());
            }
        }
    }

}
