package main_b;

import java.util.concurrent.atomic.AtomicInteger;

import javax.swing.Box;
import javax.swing.JFrame;
import javax.swing.JSlider;

public class Appb {
    static AtomicInteger semaphore = new AtomicInteger(0);
    static MyThread thread_left;
    static MyThread thread_right;
    public static void main(String[] args) {
        final JSlider slider = new JSlider();
        slider.setMinimum(0);
        slider.setMaximum(100);
        slider.setMajorTickSpacing(20);
        slider.setMinorTickSpacing(5);
        slider.setPaintTicks(true);
        slider.setPaintLabels(true);

        StartButton start_left = new StartButton("Start 1", Side.LEFT, semaphore, slider);
        StartButton start_right = new StartButton("Start 2", Side.RIGHT, semaphore, slider);
        
        EndButton end_left = new EndButton("End 1", Side.LEFT, semaphore);
        EndButton end_right = new EndButton("End 2", Side.RIGHT, semaphore);

        Box box = Box.createVerticalBox();
        box.add(slider);
        box.add(start_left);
        box.add(start_right);
        box.add(end_left);
        box.add(end_right);

        JFrame myWindow = new JFrame("Пробное окно");
        myWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        myWindow.setSize(400, 300);
        myWindow.setVisible(true);
        myWindow.setContentPane(box);
    }
}
